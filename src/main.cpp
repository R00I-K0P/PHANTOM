#include "config.h"
 
#include <TinyGsmClient.h>
#include <PubSubClient.h>

TinyGsm        modem(SerialAT);
TinyGsmClient client(modem);
PubSubClient  mqtt(client);

void mqttCallback(char* topic, byte* payload, unsigned int len) {
  String msg;
  for(int i = 0; i < len; i++) {
    char c = (char)payload[i];
    msg += c;
  }

  Serial.print("Recived ");
  Serial.println(msg);
}

boolean network_connect(){
  if (!modem.isNetworkConnected()) {
    SerialMon.println("Connecting to network");
    if (!modem.waitForNetwork(180000L, true)) {
      return false;
    }
  }
  if (!modem.isGprsConnected()) {
    SerialMon.println("Connecting to "+ String(APN));
    if (!modem.gprsConnect(APN,"","")) {
      return false;
    }
  }
  if(!mqtt.connected()){
    SerialMon.println("Connecting to "+ String(BROKER));
    if (!mqtt.connect("kjdsahfgldsfgdfslkajh")) {
      return false;
    }
    mqtt.subscribe(SUBSCRIBE_TOPIC);
    Serial.println("CONNECTED");
  }
  return true;
}

void setup() {
  SerialMon.begin(115200);
  delay(1000);
  TinyGsmAutoBaud(SerialAT, 9600, 115200);
  delay(6000);
  SerialMon.println("Initializing modem...");
  modem.restart((char*)14);
  mqtt.setServer(BROKER, PORT);
  mqtt.setCallback(mqttCallback);
}

enum MAINSTATE{WARMUP,SEND};
MAINSTATE main_state = MAINSTATE::WARMUP;
unsigned long int timerr = 0;
void loop() {
    if(network_connect())
      mqtt.loop();  
} 