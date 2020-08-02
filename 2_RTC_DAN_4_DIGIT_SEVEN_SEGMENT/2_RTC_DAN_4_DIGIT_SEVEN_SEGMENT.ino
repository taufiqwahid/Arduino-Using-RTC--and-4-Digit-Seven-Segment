/* Arduino example code to display a 24 hour time format clock on a TM1637 4 digit 7 segment display with a DS32321 RTC. More info: www.makerguides.com */
// Include the libraries:
#include "RTClib.h"
#include <TM1637Display.h>
// Define the connections pins:
#define CLK 2
#define DIO 3
// Create rtc and display object:
RTC_DS3231 rtc;
TM1637Display display = TM1637Display(CLK, DIO);
int RELAY_1 = 4;
int RELAY_2 = 5;
int RELAY_3 = 6;
int RELAY_4 = 7;
int suaraAlarm = 11;
int setWaktuAlarm = 522;
char val;

void setup() {
  pinMode(RELAY_1,OUTPUT);
  pinMode(RELAY_2,OUTPUT);
  pinMode(RELAY_3,OUTPUT);
  pinMode(RELAY_4,OUTPUT);
  pinMode(suaraAlarm,OUTPUT);

  digitalWrite(RELAY_1,HIGH);
  digitalWrite(RELAY_2,HIGH);
  digitalWrite(RELAY_3,HIGH);
  digitalWrite(RELAY_4,HIGH);
  Serial.begin(38400);  
  delay(1000);
  if (! rtc.begin()) {
    Serial.println("RTC TIDAK DI TEMUKAN!!");
    while (1);
  }else{
    Serial.println("RTC AKTIF");
    }
  if (rtc.lostPower()) {
    Serial.println("RTC Kehabisan Waktu,Kemungkinan waktu akan kembali semula!!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  display.setBrightness(5);
  display.clear();
}
void loop() {
  DateTime now = rtc.now();
  int displaytime = (now.hour() * 100) + now.minute();
  Serial.println(displaytime);
 
  display.showNumberDecEx(displaytime, 0b11100000, true);
  delay(1000);
  display.showNumberDec(displaytime, true);
  delay(1000);
  Serial.print("Tanggal : ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  if( Serial.available() > 0 ){
    val=Serial.read();
    Serial.println(val);   
  }
    
  if(val=='1'){
  digitalWrite(RELAY_1,LOW);}
  else if(val=='2'){
  digitalWrite(RELAY_2,LOW);}
  else if(val=='3'){
  digitalWrite(RELAY_3,LOW);}
  else if(val=='4'){
  digitalWrite(RELAY_4,LOW);}
  else if(val=='5'){
    digitalWrite(RELAY_1,LOW);
    digitalWrite(RELAY_2,LOW);
    digitalWrite(RELAY_3,LOW);
    digitalWrite(RELAY_4,LOW);
  }
  
  else if(val=='A'){
  digitalWrite(RELAY_1,HIGH);}
  else if(val=='B'){
  digitalWrite(RELAY_2,HIGH);}
  else if(val=='C'){
  digitalWrite(RELAY_3,HIGH);}
  else if(val=='D'){
  digitalWrite(RELAY_4,HIGH);}
  else if(val=='E'){
    digitalWrite(RELAY_1,HIGH);
    digitalWrite(RELAY_2,HIGH);
    digitalWrite(RELAY_3,HIGH);
    digitalWrite(RELAY_4,HIGH);
 }  
}
