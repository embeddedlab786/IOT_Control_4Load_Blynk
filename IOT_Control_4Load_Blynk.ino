/* 
 https://arduino.esp8266.com/stable/package_esp8266com_index.json
 */
 
 #define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <EEPROM.h>

char auth[] = "gKH6G4SYni_1aemSqZQEy_ib0o4JzeJg"; //Auth code sent via Email
char ssid[] = "M.Ansar"; //Wifi name
char pass[] = "78612345";  //Wifi Password

uint8_t Relay1 = D0;
uint8_t Relay2 = D1;
uint8_t Relay3 = D2;
uint8_t Relay4 = D3;

uint8_t LED = D4;

int load1, load2, load3, load4;

void setup() {  
EEPROM.begin(512);
  
load1 = EEPROM.read(1);
load2 = EEPROM.read(2);
load3 = EEPROM.read(3);
load4 = EEPROM.read(4);

pinMode(Relay1, OUTPUT); digitalWrite(Relay1, HIGH);  
pinMode(Relay2, OUTPUT); digitalWrite(Relay2, HIGH);
pinMode(Relay3, OUTPUT); digitalWrite(Relay3, HIGH);
pinMode(Relay4, OUTPUT); digitalWrite(Relay4, HIGH);

pinMode(LED, OUTPUT); 
Serial.begin(9600);
delay(100);
Blynk.begin(auth, ssid, pass);//You can also specify server:
digitalWrite(LED,HIGH);
delay(100);
Relays();
}

void loop() {
Blynk.run();
}

BLYNK_WRITE(V0){
  load1 = param.asInt();
  Relays();
}

BLYNK_WRITE(V1){
  load2 = param.asInt(); 
  Relays();
}

BLYNK_WRITE(V2){
  load3 = param.asInt(); 
  Relays();
}

BLYNK_WRITE(V3){
  load4 = param.asInt();
  Relays(); 
}

void Relays(){
digitalWrite(Relay1, load1);  
digitalWrite(Relay2, load2);
digitalWrite(Relay3, load3);
digitalWrite(Relay4, load4);
update_blynk();
write_eeprom();
}

void update_blynk(){
Blynk.virtualWrite(V0, load1);  
Blynk.virtualWrite(V1, load2);
Blynk.virtualWrite(V2, load3);
Blynk.virtualWrite(V3, load4);
}

void write_eeprom(){
EEPROM.write(1, load1);
EEPROM.write(2, load2);
EEPROM.write(3, load3);
EEPROM.write(4, load4);  
EEPROM.commit(); 
}
