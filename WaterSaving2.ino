//============================================================================================
//Rain Sensor
int nRainDigitalIn = 5;
boolean IsRaining = false;

//proximeter
const int trigPin = 4;
const int echoPin = 2;

//============================================================================================


//============================================================================================

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(5,INPUT);
}
//============================================================================================


//============================================================================================

void loop() {  
//rain sensor
 IsRaining = !(digitalRead(nRainDigitalIn));

//proximeter
  int x=25;
  int waterlevel;
  long duration, inches;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  waterlevel=x-inches;

  Serial.print("Tank Water Level: ");
  Serial.print(waterlevel);
  Serial.print("in, ");
  Serial.println();
  delay(100);
 

            if (IsRaining)
              {
                delay (120000);
              }

  
            else if (waterlevel<=22 && IsRaining)
              {
                Serial.println("Weather Condition: Raining ");
                digitalWrite(13,HIGH);
                Serial.println("Valve: Open");            
              }
            
             
            else if (waterlevel<=22 && !IsRaining)
              {
                Serial.println("Weather Condition:  Not Raining ");
                digitalWrite(13,LOW);
                Serial.println("Valve: Close");      
              }


            else if (waterlevel>=23 && IsRaining)
              {
                Serial.println("Weather Condition:  Raining ");
                digitalWrite(13,LOW);
                Serial.println("Valve: Close");      
              }


             else if (waterlevel>=23 && !IsRaining)
              {
                Serial.println("Weather Condition:  Not Raining ");
                digitalWrite(13,LOW);
                Serial.println("Valve: Close");      
              }

  
delay(120000);
}
//============================================================================================


//============================================================================================
long microsecondsToInches(long microseconds)
{
return microseconds / 74 / 2;
}
//============================================================================================
