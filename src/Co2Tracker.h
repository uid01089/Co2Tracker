#ifndef CO2TRACKER_H
#define CO2TRACKER_H

#include <Arduino.h>
#include <MHZ19.h>

#include <KStandardCore.h>

class Co2Tracker
{

public:
    Co2Tracker(KStandardCore *kStandardCore);
    ~Co2Tracker();
    void setup();
    void loop();

private:
    KStandardCore *kStandardCore;
    HardwareSerial mySerial;
    MHZ19 myMHZ19;
    void clcCO2Detection_5s();
};

#endif