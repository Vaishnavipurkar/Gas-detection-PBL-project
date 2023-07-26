#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2); 
#include <SoftwareSerial.h>
const int BUZZER =7 ;
const int LED_RED = 13;// pin 13 having inbuilt resistor
const int LED_GREEN =8; //pin 8
int motorPin = 6;
SoftwareSerial mySerial(9,10);
 
int COValue = A0; // smoke / gas sensor connected with analog pin A1 of the arduino / mega.
int PROPValue =A1;
int data1 = 0;
int data2 = 0;
 
void setup()
{
randomSeed(analogRead(0));
randomSeed(analogRead(1));
mySerial.begin(9600); // Setting the baud rate of GSM Module
  while(!Serial)
Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
lcd.begin(16,2);
pinMode(COValue, INPUT);
pinMode(PROPValue, INPUT);
pinMode(LED_RED, OUTPUT);
pinMode(LED_GREEN, OUTPUT);
pinMode (BUZZER, OUTPUT);
pinMode(motorPin, OUTPUT);
lcd.print (" Gas Leakage ");
lcd.setCursor(0,1);
lcd.print (" Detector Alarm ");
delay(3000);
lcd.clear();
}
 
void loop()
{
 {
  {
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}
  {
data1 = analogRead(COValue)/28.1;
data2 = analogRead(PROPValue)/44.097;
lcd.setCursor(0,0);
lcd.print("CO Gas Level: ");
lcd.setCursor(0,1);
lcd.print (data1);
delay(10000);
lcd.clear();
Serial.println(data1);
lcd.clear();
lcd.setCursor(0,0);
lcd.print ("Gas Scan is ON");
lcd.setCursor(0,1);
lcd.print ("Detecting..");
delay(1000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("PROPANE Gas Lvl: ");
lcd.setCursor(0,1);
lcd.print (data2);
delay(10000);
lcd.clear();
Serial.print(data2);
delay(1000);

  }
}
if ((data1 > 50) && (data2 <500))
{
SendMessage();
Serial.print("Gas detect alarm");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("CARBON MONOXIDE Gas Level Exceed");
lcd.setCursor(0,1);
lcd.print("SMS Sent");
delay(10000);
digitalWrite(LED_RED, HIGH);
digitalWrite(LED_GREEN, LOW);
digitalWrite(motorPin, HIGH);
digitalWrite(BUZZER, HIGH);
}
else if ((data1 < 50) && (data2 >500))

{
SendMessage2();
Serial.print("Gas detect alarm");
lcd.clear();
lcd.setCursor(0,0);
lcd.print(" PROPANE Gas Level Exceed");
lcd.setCursor(0,1);
lcd.print("SMS Sent");
delay(10000);
digitalWrite(LED_RED, LOW);
digitalWrite(LED_GREEN, HIGH);
digitalWrite(motorPin, HIGH);
digitalWrite(BUZZER, HIGH);
}

else if ((data1 > 50) && (data2 >500))
{
SendMessage3();
Serial.print("Gas detect alarm");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("BOTH Gas Exceed");
lcd.setCursor(0,1);
lcd.print("SMS Sent");
delay(10000);
digitalWrite(BUZZER, HIGH);
digitalWrite(LED_RED, HIGH);
digitalWrite(LED_GREEN, HIGH);
digitalWrite(motorPin, HIGH);
}
else
{
Serial.print("Gas Level Low");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Gas Level Normal");
delay(1000);
}
lcd.clear();
}
 
void SendMessage()
{
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+919767966853\"\r"); // Replace x with mobile number
delay(1000);
Serial.println("SHRI INDUSTRIES");
mySerial.println("Excess CARBON MONOXIDE Gas Detected. Open Windows-SHRI INDUSTRIES");// The SMS text you want to send
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}


void SendMessage2()
{
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+919767966853\"\r"); // Replace x with mobile number
delay(1000);
Serial.println("SHRI INDUSTRIES");
mySerial.println("Excess PROPANE Gas Detected. Open Windows-SHRI INDUSTRIES");// The SMS text you want to send
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}

void SendMessage3()
{
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+919767966853\"\r"); // Replace x with mobile number
delay(1000);
Serial.println("SHRI INDUSTRIES");
mySerial.println("Excess CO and PROPANE Gas Detected. Open Windows-");// The SMS text you want to send
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}
 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
