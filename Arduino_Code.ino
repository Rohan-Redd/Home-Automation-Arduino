#include <TimeLib.h>

/*
DHT11
This example reads a DHT11 sensor hooked up on pin D7. Reads both
temperature and humidity and sends it to the Serial port
created in Feb 2019 by D. Cuartielles
based on work by F. Vanzati (2011) and M. Loglio (2013)
This example code is in the public domain.
*/

// include the EduIntro library
#include <EduIntro.h>

DHT11 dht11(D2);  // creating the object sensor on pin 'D2'

int C;   // temperature C readings are integers
float F; // temperature F readings are returned in float format
int H;   // humidity readings are integers
int count=0;

void setup()
{
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
  pinMode(5,OUTPUT);//FAN
  pinMode(12,OUTPUT);//LIGHT
  pinMode(7,OUTPUT);//AC
  pinMode(13,OUTPUT);//FIRE ALARM
  pinMode(9,INPUT);//IR SENSOR 1
  pinMode(10, INPUT); //IR SENSOR 2
  
   setTime(3, 10, 30, 24, 5, 2021);
}

void loop()
{
  dht11.update();

  C = dht11.readCelsius();       // Reading the temperature in Celsius degrees and store in the C variable
  F = dht11.readFahrenheit();   // Reading the temperature in Fahrenheit degrees and store in the F variable
  H = dht11.readHumidity();     // Reading the humidity index

  // Print the collected data in a row on the Serial Monitor
  int statusSensor1 = digitalRead (9);
  int statusSensor2 = digitalRead (10);
  /*
  if(C>45){
      digitalWrite(13,HIGH);
  }
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);*/   
  digitalClockDisplay();
  delay(1000);

  if(statusSensor1 == 0)
  {
    delay(1000);
    if(statusSensor2 == 0)
    {
      count = count+1; // PERSON WALKS INTO THE ROOM
      Serial.println("count+\t");
      Serial.println(count);
    }
  }

  if(statusSensor2 == 0)
  {
    delay(1000);
    if(statusSensor1 == 0)
    {
      count = count-1; // PERSON LEAVES THE ROOM
      Serial.println("count-\t");
      Serial.println(count);
    }
  }
  
  if (count == 0){ 
    Serial.println("low");
    digitalWrite(5, LOW); // FAN LOW
    digitalWrite(12, LOW); // LIGHT LOW
    digitalWrite(7, LOW); // AC LOW
  }  
  else{
    Serial.println("high\t");
    //digitalWrite(7, HIGH); // LED High
    Serial.print("H: ");
    Serial.print(H);
    Serial.print("\tC: ");
    Serial.print(C);
    Serial.print("\tF: ");
    Serial.println(F);
    digitalWrite(5,HIGH);//FAN HIGH ALWAYS WHEN PERSON TRUE
    if(C>20){
      digitalWrite(7,HIGH);//AC
      
      digitalWrite(12,HIGH);//LIGHT
    }
    else if(C<20){
      digitalWrite(7,LOW);//AC
    }
  }
  delay(1000);                // Wait one second before get another temperature reading
}

void digitalClockDisplay(){
   // digital clock display of the time
   Serial.print(hour());
   printDigits(minute());
   printDigits(second());
   Serial.print(" ");
   Serial.print(day());
   Serial.print(" ");
   Serial.print(month());
   Serial.print(" ");
   Serial.print(year());
   Serial.println();
}

void printDigits(int digits) {
   // utility function for digital clock display: prints preceding colon and leading 0
   Serial.print(":");
   if(digits < 10)
      Serial.print('0');
      Serial.print(digits);
}
