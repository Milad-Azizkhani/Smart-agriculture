#include <ESP8266WiFi.h>




int sensor = A0;
int value;
long myChannelNumber = 2628757;
String apiKey = "XMBQZRGTX5U32UVU";
const char* ssid = "Redmi Note 8";
const char* password = "milmilmil";
const char* server = "api.thingspeak.com";
 


WiFiClient client;
 
void setup() 
{
Serial.begin(9600);
delay(10);
pinMode(sensor, INPUT);
WiFi.begin(ssid, password);
 
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
 
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) 
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
 
}
 
void loop() 
{
value = analogRead(sensor);
value = constrain(value, 400, 1023); // keep the range 400 to 1023
value = map(value, 400, 1023, 100, 0); // mapping the rrange to 0-100
if (client.connect(server,80)) {
String postStr = apiKey;
postStr +="&field1=";
postStr += String(value);// add the value to send to things peak
postStr += "\r\n\r\n";
 
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);
 
//display
Serial.println("Soil mositure is:   "+value);
Serial.println(value);
Serial.println("Sending data to Thingspeak");
if (value <= 10 ){
  Serial.println("Alarm!!!");
}
if (value > 10 ){
  Serial.println("Thanks for watering !");
}
}
client.stop();
 
Serial.println("Waiting 20 secs");
// thingspeak needs at least a 15 sec delay between updates
// 10 seconds to be safe
delay(80000);
}
