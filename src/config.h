#include <Arduino.h>
#define TINY_GSM_MODEM_SIM868
#define SerialMon Serial
#define SerialAT Serial1
#define TINY_GSM_DEBUG SerialMon

#define PUBLISH_TOPIC "0001/data"
#define SUBSCRIBE_TOPIC "0001/data"
#define SUBSCRIBE_RESPOND_TOPIC "0001/data"
#define APN "Vodacom"
#define BROKER "test.mosquitto.org"
#define PORT 1883
#define TOKEN "secret"
#define APP_VERSION "ccfccnadblapdp7slkg0-v1"
