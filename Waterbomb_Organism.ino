/*
   Waterbomb Organism is an interactive installation by Krishnokoli Roy Chakraborty
   Created for course - Creation & Computation - Experiment 2, Indoor/Outdoor
   Digital Futures || OCAD University

   WATERBOMB ORGANISM
   *Based Multi Servo Sweep through timer by Kate Hartman and Nicholas Pucket
   *This work uses light dependent resistors to initialte movement
   *Servo and LEDs only blink if the sensor reads the value <500
   
*/

//servo

#include <Servo.h>

//servo pins
int servoPin1 = 15;
int servoPin2 = 16;

//Move Rate and angles
int moveRate = 10;        //the time between updates in milliseconds
int minAngle = 0;     //sets the low point of the movement range
int maxAngle = 100;   //sets the high point of the movement range
int moveIncrement = 1;    // how much to move the motor each cycle
int servoAngle1;

long lastTimeYouMoved1;

// create the Servo object
Servo servo1;
Servo servo2;

//LED
//define the LEDs pins in an Array
int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

//define the current states
boolean ledStates[] = {false, false, false, false, false, false, false, false, false, false, false};

//define the stored time value
long lastTimeYouBlinked[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//define the total number of LEDs
int ledTotal = sizeof(ledPins) / sizeof(int);

void setup() {

  //servo
  //attach the servo to the corresponding control pin
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servoAngle1 = minAngle;

  //LED
  //forloop for all the led pins
  for (int i = 0; i < ledTotal; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {

  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1);        // delay in between reads for stability

  if (sensorValue < 500)
  {
    //servo 1
    if (millis() - lastTimeYouMoved1 >= moveRate) //this very simple statement is the timer,
    { //it subtracts the value of the moment in time the last blink happened, and sees if that number is larger than your set blinking value
      servo1.write(servoAngle1);

      servoAngle1 += moveIncrement;

      if (servoAngle1 <= minAngle || servoAngle1 >= maxAngle)
      {
        moveIncrement = -moveIncrement;
      }

      lastTimeYouMoved1 = millis();            //save the value in time that this switch occured, so we can use it again.

    }

    //servo 2
    if (millis() - lastTimeYouMoved1 >= moveRate) //this very simple statement is the timer,
    { //it subtracts the value of the moment in time the last blink happened, and sees if that number is larger than your set blinking value
      servo2.write(servoAngle1);

      servoAngle1 += moveIncrement;

      if (servoAngle1 <= minAngle || servoAngle1 >= maxAngle)
      {
        moveIncrement = -moveIncrement;
      }

      lastTimeYouMoved1 = millis();            //save the value in time that this switch occured, so we can use it again.

    }
    //LED
    //define blink per unit of time of the LED
    //it is based on sensor
    int blinkRates[] = {map(analogRead(A0), 0, 1023, 100, 1000), map(analogRead(A0), 0, 1023, 100, 1000), map(analogRead(A0), 0, 1023, 100, 1000), map(analogRead(A0), 0, 1023, 100, 1000), map(analogRead(A0), 0, 1023, 100, 1000), map(analogRead(A0), 0, 1023, 100, 1000), map(analogRead(A0), 0, 1023, 100, 1000), map(analogRead(A0), 0, 1023, 100, 1000), map(analogRead(A0), 0, 1023, 100, 1000), map(analogRead(A0), 0, 1023, 100, 1000), map(analogRead(A0), 0, 1023, 100, 1000),};

    //another loop to check the values for each of the pins
    //the loop/array let us write the function only once and letting the compiler run through the list of values

    for (int i = 0; i < ledTotal; i++)
    {
      if (millis() - lastTimeYouBlinked[i] >= blinkRates[i])
      {
        ledStates[i] = !ledStates[i];
        lastTimeYouBlinked[i] = millis();
      }

      digitalWrite(ledPins[i], ledStates[i]);
    }
  }
}
