
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;

int solenoidPin = 6; 
int tempPin = A0; 
int SMPin1 = A1;  
int SMPin2 = A3;
int sensor1 = 12;
int sensor2 = 10;
int tempPower = 3; 

float sumSensor1;
char data = '0';

void setup() {
  // put your setup code here, to run once:
  
    pinMode(solenoidPin, OUTPUT);
    pinMode(sensor1, OUTPUT);
    pinMode(sensor2, OUTPUT);
    pinMode(tempPower, OUTPUT);
    pinMode(SMPin1, OUTPUT);
    pinMode(SMPin2, OUTPUT);
    pinMode(tempPin, INPUT);
   
    digitalWrite(solenoidPin, LOW);
   
    Serial.begin(9600);

    Wire.begin();
    RTC.begin();
    
 
  if (! RTC.isrunning()) {
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
    delay(500);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println(data);
    delay(3000);
    float temperatureF = avgTemperature(tempPower, tempPin);

    DateTime now = RTC.now();
    
    float average1 = sensorAverage(sensor1, SMPin1);
    float average2 = sensorAverage(sensor2, SMPin2);
    
    float avgSensor = (average1 + average2) / 2;   
    float avgmoisture = map(avgSensor, 0, 400, 1, 1000);
    
    if (now.hour() > 1 && now.hour() < 13) {
      
       if (temperatureF < 120) {
      
          if (avgmoisture <= 300 && avgmoisture >= 0){ // less than 20% moil moisture
              
              data = '1'; 
              Serial.println(data);
              digitalWrite(solenoidPin, HIGH);
              delay(7000);
              digitalWrite(solenoidPin, LOW);
            
              
          } else if (avgmoisture <= 500 && avgmoisture > 300) { //above 20% soil moisture
             
              data = '2';
              Serial.println(data);
              digitalWrite(solenoidPin, HIGH);
              delay(5000);
              digitalWrite(solenoidPin, LOW);
      
              
            
          } else if (avgmoisture <= 800 && avgmoisture > 500) { //above 35% soil moisture

              data ='3';
              Serial.println(data);
              delay(6000);
              
          } else if (avgmoisture <= 1000 && avgmoisture > 800){ //above 60% moisture 

             data = '4';
             Serial.println(data);
             delay(6000);
             
          }
             
          } else {
               data = '5'; 
               Serial.println(data);
            }
   
    } 
                 
            delay(3000); //check soil moisture and temperature every minute
            sumSensor1 = 0;
            data = '0';
}
   




float avgTemperature (int power, int pin) {
     
      int sumTemp = 0; 
      int tempValue;
      float temperatureF;
      float avgTemp; 
      float voltage;
      int temperatureC = 0;
      int tempF = 0;
      
      for (int x = 0; x < 5; x++) {
       
        digitalWrite(power, HIGH);
        tempValue = analogRead(pin);
        delay(200);
        tempValue = analogRead(pin);
        delay(200);
        sumTemp += tempValue;
        digitalWrite(power, LOW);
        
     }
     
     avgTemp = sumTemp / 5;
     voltage = map(avgTemp, 0, 1023, 0, 5000 );
     temperatureC = (voltage - 500)/10;
     tempF = (temperatureC * 1.8) + 32;
     return tempF;
}

float sensorAverage(int power, int pin) {
   
    float avgSensor1;
    int moistureData1;

    for (int i = 0; i < 5; i++) {

        digitalWrite(power, HIGH);
        int moistureData1 = analogRead(pin);
        delay(500);
        moistureData1 = analogRead(pin);
        delay(1000);
        sumSensor1 += moistureData1;
        digitalWrite(power, LOW);
    
    }
  
    avgSensor1 = sumSensor1 / 5;
    return avgSensor1;
 
    
}


