#include <Key.h>
#include <Keypad.h>
#include <SoftwareSerial.h> 
#define DEBUG true
#define RX 2
#define TX 3

SoftwareSerial esp8266(RX,TX);

const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {15, 14, 13, 12}; 
byte colPins[COLS] = {11, 10, 9, 8}; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//CHANGE THESE NETWORK SETTINGS
String HOST = "master ip";
String AP = "ssid";
String PASS = "password";

//SENSOR PINS
const int trigPin = 4;
const int echoPin = 5; 
const int tPin = 6;
const int ePin = 7;

float duration, distance, dur, dis;

//PROCESSING VARIABLES
String req="";
int countTrueCommand;
int countTimeCommand;
boolean found = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(tPin, OUTPUT);
  pinMode(ePin, INPUT);
  Serial.begin(9600);

  //ESTABLISH CONNECTION WITH MASTER
  esp8266.begin(115200);
  espCommand("AT",5,"OK");
  espCommand("AT+CWMODE=1",5,"OK");
  espCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",15,"OK");
  espCommand("AT",10,"OK");
  espCommand("AT+CIPSTART=\"TCP\",\""+ HOST +"\",8005",1,"OK");
  espCommand("AT+CIPSEND=20",1,">");
  esp8266.println("GET /Connected");
  delay(1000);
  espCommand("AT+CIPCLOSE",1,"OK");
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);

  //New Delhi
  if (distance >=0 and distance <7) {
    lg("GET /flyto/New%20Delhi");
    lg("GET /flyto/New%20Delhi");
    Serial.print("New Delhi");
  }
  //Santa Clara
  else if (distance >=7  and distance <10) {
    lg("GET /flyto/Santa%20Clara");
    lg("GET /flyto/Santa%20Clara");
    Serial.print("Santa Clara");
  }
  //Madrid
  else if (distance >=10 and distance <15) {
    lg("GET /flyto/Madrid");
    lg("GET /flyto/Madrid");
    Serial.print("Madrid");
  }
  //Vancouver
  else if (distance >=15 and distance <20) {
    lg("GET /flyto/Vancouver");
    lg("GET /flyto/Vancouver");
    Serial.print("Vancouver");
  }
  //Venice
  else if (distance >=20 and distance <25) {
    lg("GET /flyto/Venice");
    lg("GET /flyto/Venice");
    Serial.print("Venice");
  }
  else { 
  }
  delay(100);

  //Sens2
  digitalWrite(tPin, LOW);
  delayMicroseconds(2);
  digitalWrite(tPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin, LOW);
  
  dur = pulseIn(ePin, HIGH);
  dis = (dur*.0343)/2;
  Serial.print("Distance2: ");
  Serial.println(dis);

  while (distance>25 and dis<31){
     if (dis >=0 && dis <15) {
      lgudp("ZI");
      Serial.print("Zoom In");
      
    }
    else if (dis >=15 && dis <30) {
      lgudp("ZO");
      Serial.print("Zoom Out");
      
    }
    break;
  }

  //Keypad
  while (distance>25 and dis>30){
    char customKey = customKeypad.getKey();
    if (customKey){
      lgudp('B'+String(customKey));
    }
    break;
  }
}
 
//SENDING GET REQUESTS TO MASTER SERVER
void lg(String place){
  espCommand("AT+CIPSTART=\"TCP\",\""+ HOST +"\",8005",1,"OK");
  espCommand("AT+CIPSEND="+String(place.length()),1,">");
  esp8266.println(place);
  delay(50);
  espCommand("AT+CIPCLOSE",1,"OK");
}

//SENDING UDP MESSAGES TO MASTER SERVER
void lgudp(String place){
  espCommand("AT+CIPSTART=\"UDP\",\""+ HOST +"\",8085",1,"OK");
  esp8266.println("AT+CIPSEND=2");
  delay(50);
  //espCommand("AT+CIPSEND=2",1,">");
  esp8266.println(place);
  delay(50);
  espCommand("AT+CIPCLOSE",1,"OK");
}

//SENDING COMMANDS TO ESP8266
void espCommand(String command, int maxTime, char readReplay[]) {

Serial.print(countTrueCommand);
Serial.print(". at command => ");
Serial.print(command);
Serial.print(" ");
while(countTimeCommand < (maxTime*1))

{

esp8266.println(command);//at+cipsend
if(esp8266.find(readReplay))//ok
{

found = true;
break;

}
countTimeCommand++;

}
if(found == true)
{

Serial.println("PASS");

countTrueCommand++;
countTimeCommand = 0;

}
if(found == false)
{

Serial.println("Fail");
countTrueCommand = 0;
countTimeCommand = 0;

}
found = false;

}
