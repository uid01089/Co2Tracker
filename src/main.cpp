#include <Arduino.h>
#include <KStandardCore.h>
#include "incredential.h"
#include <KBlink.h>
#include <Co2Tracker.h>

// https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
// https://unsinnsbasis.de/esp32-pin-belegung/

KStandardCore kStandardCore;
Co2Tracker co2Tracker(&kStandardCore);
KBlink kblink;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600); // Baudrate: 9600

  kStandardCore.setup("Co2Tracker", SSID, PSK, MQTT_BROKER, 1883);
  kblink.setup(kStandardCore.getKSchedule(), 2, 5000);
  co2Tracker.setup();
}

void loop()
{
  // put your main code here, to run repeatedly:
  kStandardCore.loop();
  kblink.loop();
  co2Tracker.loop();
}