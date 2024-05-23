#include "CytronMotorDriver.h"
#include "DHT.h"
// Configure the motor driver.
CytronMD motor1(PWM_PWM, 3, 9);   // PWM 1A = Pin 3, PWM 1B = Pin 9.
CytronMD motor2(PWM_PWM, 10, 11); // PWM 2A = Pin 10, PWM 2B = Pin 11.


#define TREDBUTTON 2
#define TYELLOWBUTTON 5
#define TGREENBUTTON 6
#define PIEZO  8
#define RLED 13
#define YLED 12
#define GLED 7
#define IR_LEFT   A0
#define IR_RIGHT  A1
#define fanpin 8
#define tempsensor 4
#define DHTTYPE DHT22
DHT dht(tempsensor, DHTTYPE);


#define NOTE_G4  392
#define NOTE_C5  523
#define NOTE_G5  784
#define NOTE_C6  1047

int startMelody[] = {NOTE_G5, NOTE_C6};
int startNoteDurations[] = {12, 8};
int stopMelody[] = {NOTE_C6, NOTE_G5};
int stopNoteDurations[] = {12, 8};

char inChar;
String inString;

void robotStop();
void robotForward();
void robotReverse();
void robotTurnLeft();
void robotTurnRight();

void setup()
{
  Serial.begin(9600);
  pinMode (RLED, OUTPUT);
  pinMode (YLED, OUTPUT);
  pinMode (GLED, OUTPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  pinMode(fanpin, OUTPUT);
  pinMode(tempsensor, INPUT);
  pinMode(TREDBUTTON, INPUT);
  pinMode(TYELLOWBUTTON, INPUT);
  pinMode(TGREENBUTTON, INPUT);
  dht.begin();
} 


void loop()
{ 
  if (digitalRead(TREDBUTTON) == HIGH){
      Serial.println("TASK 1");
      int leftIR = analogRead(IR_LEFT);
      int rightIR = analogRead(IR_RIGHT);
      Serial.print("Left IR: ");
      Serial.print(leftIR);
      Serial.print("\tRight IR: ");
      Serial.println(rightIR);
      if (1==1) {
       
       while (true) {
        int leftIR = analogRead(IR_LEFT);
        int rightIR = analogRead(IR_RIGHT);
        Serial.print("Left IR: ");
        Serial.print(leftIR);
        Serial.print("\tRight IR: ");
        Serial.println(rightIR);
         if (analogRead(IR_LEFT) < 700 &&
             analogRead(IR_RIGHT) < 700) {
           robotForward();
           //Serial.println("Forward");
         }
         else if (analogRead(IR_LEFT) > 700 &&
                  analogRead(IR_RIGHT) < 700) {
           robotTurnLeft();
           //Serial.println("Left");
         }
         else if (analogRead(IR_LEFT) < 700 &&
                  analogRead(IR_RIGHT) > 700) {
           robotTurnRight();
           //Serial.println("Right");
         }
         else if (analogRead(IR_LEFT) > 700 &&
                  analogRead(IR_RIGHT) > 700) {
            robotTurnRight();
            delay(600);
            while(1){
              if (analogRead(IR_LEFT) < 700 && analogRead(IR_RIGHT) < 700){
                robotTurnRight();
              }
              else{
                break;
             }
           }
         }
       }
     }// line tracing
  }else if (digitalRead(TYELLOWBUTTON)== HIGH){
    Serial.println("TASK 2"); 
   
    int leftIR = analogRead(IR_LEFT);
      int rightIR = analogRead(IR_RIGHT);
      Serial.print("Left IR: ");
      Serial.print(leftIR);
      Serial.print("\tRight IR: ");
      Serial.println(rightIR);
      int lastminutething = 0;
      if (1==1) {
       
       while (true) {
         if (analogRead(IR_LEFT) < 700 &&
             analogRead(IR_RIGHT) < 700) {
           robotForward();
           //Serial.println("Forward");
         }
         else if (analogRead(IR_LEFT) > 700 &&
                  analogRead(IR_RIGHT) < 700) {
           robotTurnLeft();
           //Serial.println("Left");
         }
         else if (analogRead(IR_LEFT) < 700 &&
                  analogRead(IR_RIGHT) > 700) {
           robotTurnRight();
           //Serial.println("Right");
         }
         else if (analogRead(IR_LEFT) > 700 &&
                  analogRead(IR_RIGHT) > 700) {
              if(1 == 1){
             
                robotStop();  
   
                Serial.println("SERIAL AVAILIBILITY:");
                Serial.println(Serial.available());
                Serial.println("_-----------_");
                if (Serial.available()>0) {
                  while (true){
                    String command = Serial.readStringUntil('\n');
                    Serial.println(command);
                    String lcommand = Serial.readStringUntil('\n');
                    Serial.println("Command:");
                    Serial.println(command);
                    if (command == "Debris") {
                      // RED (debris)
                      Serial.println("DETECTED: DEBRIS");
                    } else if (command == "Dinosaur") {
                      Serial.println("DETECTED: DINOSAUR");
                    } else if (command = "Human") {
                      // GREEN (human)
                      Serial.println("DETECTED: HUMAN");
                    }else {
                      // GREEN (human)
                      Serial.println("DETECTED: Nothing");
                    }
                  }
                }
               
          }
       }
       }}// line tracing
  } else if (digitalRead(TGREENBUTTON)==HIGH){
    // task 3
    Serial.println("TASK 3");

    int leftIR = analogRead(IR_LEFT);
      int rightIR = analogRead(IR_RIGHT);
      Serial.print("Left IR: ");
      Serial.print(leftIR);
      Serial.print("\tRight IR: ");
      Serial.println(rightIR);
      if (1==1) {
       
       while (true) {
         if (analogRead(IR_LEFT) < 700 &&
             analogRead(IR_RIGHT) < 700) {
           robotForward();
           //Serial.println("Forward");
         }
         else if (analogRead(IR_LEFT) > 700 &&
                  analogRead(IR_RIGHT) < 700) {
           robotTurnLeft();
           //Serial.println("Left");
         }
         else if (analogRead(IR_LEFT) < 700 &&
                  analogRead(IR_RIGHT) > 700) {
           robotTurnRight();
           //Serial.println("Right");
         }
         else if (analogRead(IR_LEFT) > 700 &&
                  analogRead(IR_RIGHT) > 700) {
            robotStop();
            Serial.println("SERIAL AVAILIBILITY:");
            Serial.println(Serial.available());
            Serial.println("_-----------_");
            if (Serial.available()>0) {
              while (true){
              String command = Serial.readStringUntil('\n');
              Serial.println(command);
              String lcommand = Serial.readStringUntil('\n');
              Serial.println("Command:");
              Serial.println(command);
              if (command == "Temperature") {
                // Read temperature sensor
                float temperature = dht.readTemperature();
                Serial.println("Temperature:");
                digitalWrite(8, LOW);
                Serial.println(temperature);
               
              } else if (command = "Fire") {
                Serial.print("Fan on");
                digitalWrite(8, HIGH);
                delay(1000);
                digitalWrite(8, LOW);
              }
            }}
         }
       }
     }// line tracing
  }//end of tgreenbtn
}// loop end



void playMelody(int *melody, int *noteDurations, int notesLength){
 pinMode(PIEZO, OUTPUT);
 for (int thisNote = 0; thisNote < notesLength; thisNote++) {
   int noteDuration = 1000 / noteDurations[thisNote];
   tone(PIEZO, melody[thisNote], noteDuration);
   int pauseBetweenNotes = noteDuration * 1.30;
   delay(pauseBetweenNotes);
   noTone(PIEZO);
 }
}


void robotStop()
{
 motor1.setSpeed(0);     // Motor 1 stops.
 motor2.setSpeed(0);     // Motor 2 stops.
}


void robotForward()
{
 motor1.setSpeed(150);   // Motor 1 runs forward.
 motor2.setSpeed(-150);   // Motor 2 runs forward.
}

void robotReverse()
{
 motor1.setSpeed(-150);   // Motor 1 runs backward.
 motor2.setSpeed(150);   // Motor 2 runs backward.
}


void robotTurnLeft()
{
 motor1.setSpeed(-150);    // Motor 1 runs forward.
 motor2.setSpeed(-150);   // Motor 2 runs backward.
}


void robotTurnRight()
{
 motor1.setSpeed(150);   // Motor 1 runs backward.
 motor2.setSpeed(150);    // Motor 2 runs forkward.
}
