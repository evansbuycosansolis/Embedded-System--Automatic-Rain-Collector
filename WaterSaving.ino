







//1)=========================================================================
#include <Stepper.h>
// for rain sensor lowest and highest sensor readings:
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum
//ultrasonic
const int trigPin = 2;
const int echoPin = 4;
//stepper
const int stepsPerRevolution = 180;  // change this to fit the number of steps per revolution
// for your motor initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
int relay = 1;
int x;
//1)=========================================================================








//2)=========================================================================
void setup() {
  //---------------------------------------------
  // Setting Stepper Speed at 60:
     myStepper.setSpeed(60);
  //---------------------------------------------
  
  //---------------------------------------------
  // Initialize Serial at 9600 baud rate:
     Serial.begin(9600); 
  //---------------------------------------------

  //---------------------------------------------
  // initialize the digital pin as an output:
     pinMode(relay, OUTPUT);
  //---------------------------------------------     
}
//2)=========================================================================








//3)=========================================================================
void loop() {

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //++++++++++++++++++++++ This code is for ultrasonic sensor +++++++++++++++++++++++
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  // Variables for getting ping duration and  distance result in inches:
  float duration, inches;
  int x=25;
  int y;
  //---------------------------------------------

  //---------------------------------------------
  // The ultrasonic sensor is triggered by a HIGH pulse of 10 or more microseconds. Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //---------------------------------------------
  
  //---------------------------------------------
  // Read the signal from the sensor: a HIGH pulse whose duration is the time (in microseconds) from the sending of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  //---------------------------------------------

  //---------------------------------------------
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  //---------------------------------------------

  //---------------------------------------------
  // compute water level in the tank.
       y=x-inches;
  //---------------------------------------------


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+++++++++++++++++++++ This Code is for Rain Sensor ++++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  //---------------------------------------------     
  int sensorReading = analogRead(A0);
  // map the sensor range (four options):ex: 'long int map(long int, long int, long int, long int, long int)':
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
  //---------------------------------------------

  //---------------------------------------------
  // Range Cases value:
  Serial.println("Reading Rain Sensor Data...");
  delay(2000);
  Serial.println("...");
  delay(1000);
  Serial.println("......");
  delay(1000);
  Serial.println(".........");
  delay(1000);
  Serial.println("............");
  delay(1000);
  Serial.println("...............");
  delay (3000);
  
  switch (range) {
  case 0:
    delay(1000);
    Serial.println("============================");
    delay(500);
    Serial.println("Heavy Rain Detected!");
    delay(2000);
    
  //---------------------------------------------
  // If ultrasonic sensor detects water tank water level from 2inch to 20inch, stepper motor will turn 180 degrees.  
    
        if (y<2)
            {
              Serial.print(y);
              Serial.println(" inch of Water Level...");
              delay(500);
              Serial.println("Warning! Water Tank Level: Low");
              delay(1000);
              Serial.println("Delaying 3 minutes (For removal of sediments)...");
              delay(10000);
              Serial.println("Initiating Stepper Motor: Openning Water Tank");
              delay(1000);
              Serial.println("... Allowing Water to Enter..."); 
              delay(500);
              steppercounterclockwise();
              Serial.println("Water Entering the Tank...");
              delay (900000);
              stepperclockwise();
            }

            else if (y>20)
            {
              Serial.print(y);
              Serial.println(" inch of Water Level...");
              delay(500);
              Serial.println("Warning! Water Tank Level: High");
              delay(500);
              Serial.println("Initiating Stepper Motor: Closing Water Tank");
              delay(1000);
              Serial.println("... Preventing Water to Enter..."); 
              delay(500);
              stepperclockwise();
              Serial.println("Water Tank Closed...");
              delay (900000);
              
            }

                else
                {
                  Serial.print(y);  
                  Serial.print(" inch of water in the tank");  
                  Serial.println();  
                  delay(100);
                 }
  //---------------------------------------------
  
    break;
    
  case 1:
    delay(1000);
    Serial.println("============================");
    delay(500);
    Serial.println("Moderate Rain Detected!");
    delay(2000);
    
  //---------------------------------------------
  // If ultrasonic sensor detects water tank space from 2inch to 20inch, stepper motor will turn 180 degrees.  
    
        if (y>20)
            {
              Serial.print(y);
              Serial.println(" inch of Water Level...");
              delay(500);
              Serial.println("Warning! Water Tank Level: Low");
              delay(1000);
              Serial.println("Delaying 3 minutes (For removal of sediments)...");
              delay(180000);
              Serial.println("Initiating Stepper Motor: Openning Water Tank");
              delay(1000);
              Serial.println("... Allowing Water to Enter..."); 
              delay(500);
              steppercounterclockwise();
              Serial.println("Water Entering the Tank...");
              delay (900000);
              stepperclockwise();
            }

            else if (y>20)
            {
              Serial.print(y);
              Serial.println(" inch of Water Level...");
              delay(500);
              Serial.println("Warning! Water Tank Level: High");
              delay(500);
              Serial.println("Initiating Stepper Motor: Closing Water Tank");
              delay(1000);
              Serial.println("... Preventing Water to Enter..."); 
              delay(500);
              stepperclockwise();
              Serial.println("Water Tank Closed...");
              delay (900000);
              
            }

                else
                {
                  Serial.print(y);  
                  Serial.print(" inch of water in the tank");  
                  Serial.println();  
                  delay(100);
                 }
  //---------------------------------------------
  
    break;
    
  case 2:
    Serial.println("Not Raining");
    }
  //---------------------------------------------

  //---------------------------------------------
  // wait 15minutes until next read
          delay (10000);
          
  //--------------------------------------------- 
}

//3)=========================================================================







//5)========================================================================
//---------------------------------------------
//stepper motor Clockwise
void stepperclockwise() {
  // step one revolution  in one direction:
  delay(500);
  Serial.println("Stepper Motor rotating Clockwise...");
  myStepper.step(stepsPerRevolution);
  delay (500);
}
//---------------------------------------------
//5)========================================================================








//6)========================================================================
//---------------------------------------------
//stepper motor CounterClockwise
void steppercounterclockwise() {
  // step one revolution in the other direction:
  delay(500);
  Serial.println("Stepper Motor rotating Counterclockwise...");
  myStepper.step(-stepsPerRevolution);
  delay (500);
}
//---------------------------------------------
//6)========================================================================




























//7)========================================================================
//---------------------------------------------
//Code For Relay
void forrelay()
{
  digitalWrite(relay, HIGH);   // turn the relay on (HIGH is the voltage level)
  //delay(20000);               // wait for a second
  digitalWrite(relay, LOW);    // turn the relay off by making the voltage LOW
  //delay(20000);               // wait for a second 
 }
 //---------------------------------------------
//7)========================================================================






//8)========================================================================
//---------------------------------------------
//For ultrasonic sensor
  long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}
//---------------------------------------------
//8)========================================================================




