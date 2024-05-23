from tflite_runtime.interpreter import Interpreter 
import numpy as np
from picamera2 import Picamera2
import cv2
import libcamera
from PIL import Image, ImageDraw, ImageFont
import serial

#red is debris, green is human and yellow is dino

if __name__ == "__main__":
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.reset_input_buffer()


def load_labels(path): # Read the labels from the text file as a Python list.
    with open(path, 'r') as f:
        return [line.strip() for i, line in enumerate(f.readlines())]

def set_input_tensor(interpreter, image):
    tensor_index = interpreter.get_input_details()[0]['index']
    input_tensor = interpreter.tensor(tensor_index)()[0]
    input_tensor[:, :] = image

def classify_image(interpreter, image, top_k=1):
    set_input_tensor(interpreter, image)

    interpreter.invoke()
    output_details = interpreter.get_output_details()[0]
    output = np.squeeze(interpreter.get_tensor(output_details['index']))

    scale, zero_point = output_details['quantization']
    output = scale * (output - zero_point)

    ordered = np.argpartition(-output, 1)
    return [(i, output[i]) for i in ordered[:top_k]][0]

data_folder = "/home/pi/Desktop/Pi/TM/"

model_path = data_folder + "model.tflite"
label_path = data_folder + "labels.txt"

interpreter = Interpreter(model_path)

interpreter.allocate_tensors()
_, height, width, _ = interpreter.get_input_details()[0]['shape']

picam2 = Picamera2()
config = picam2.create_preview_configuration({"format":'XRGB8888',"size":(224,224)})
config["transform"] = libcamera.Transform(hflip=1, vflip=1)
picam2.configure(config)
picam2.start(show_preview=True)

while True:
    image = picam2.capture_array("main")[:,:,:3]
    label_id, prob = classify_image(interpreter, image)
    labels = load_labels(label_path)
    classification_label = labels[label_id]
    result_text = "{} ({})".format(classification_label, np.round(prob*100, 2))
    overlay = np.zeros((500,500,4),dtype=np.uint8)
    overlay[:80,:250] = (0,0,255,54) #blue background
    text_color = (255, 0, 0, 255) #red text
    cv2.putText(overlay, result_text, (0,50), cv2.FONT_HERSHEY_SIMPLEX,
                  1, text_color, 3)
    picam2.set_overlay(overlay)
    
    print("Result: ", label_id, ", Accuracy: ", np.round(prob*100, 2))
    if label_id == 0:
        # Human
        ser.write(b"Human\n")
        print("Human")
    elif label_id == 1:
        # Dinosaur
        ser.write(b"Dinosaur\n")
        print("Dinosaur")
    elif label_id == 2:
        # Background
        ser.write(b"Background\n")
        print("Background")
    elif label_id == 3:
        # Human + debris
        ser.write(b"Human\n")
        print("Human and debris")
    elif label_id == 4:
        # Debris
        ser.write(b"Debris\n")
        print("Debris")
    elif label_id == 5:
        # Temperature
        ser.write(b"Temperature\n")
        print("Temperature")
    elif label_id == 6:
        # Fire
        ser.write(b"Fire\n")
        print("Fire")
