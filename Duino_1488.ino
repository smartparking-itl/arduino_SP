#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x4C, 0xFB };
byte ip[] = { 192, 168, 178, 107 };
byte server[] = { 31, 170, 163, 186 }; 
EthernetClient client;
int BD[] = { 3, 6, 7 };
int VL[] = { 0, 0, 0 };
int NUM = 3;
int i;

void setup()
{
  NUM = NUM - 1;
  for (i = 0; i <= NUM; i++) {
  pinMode ( BD[i], INPUT); 
  }
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Ethernet.begin(mac, ip);
  }
  delay(1000);
}

void loop()
{
  Serial.println("connecting...");
  for ( i = 0; i <= NUM; i ++){
    if(digitalRead( BD[i] ) == LOW){
      VL[i] = 1;
    } else {
      VL[i] = 0;
      }
  }
  if (client.connect(server, 80)) {
    Serial.println("connected");
    Serial.println("making HTTP request...");
    for ( i = 0; i <= NUM; i++ ){
        client.connect(server, 80);
        client.println("GET /?nom=" + String(i+1) + "&val=" + String(VL[i]) + " HTTP/1.1");
        client.println("HOST: testing44.rurs.net");
        Serial.println(" TEST      GET /?nom=" + String(i+1) + "&val=" + String(VL[i]) + " HTTP/1.1");
        Serial.println();
        client.println();
        client.stop();
    }
  } else {
  Serial.println();
    Serial.println("disconnected");
    client.stop();
    while (true);
  }
  delay (5000);
}

