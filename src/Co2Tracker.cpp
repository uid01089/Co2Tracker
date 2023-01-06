#include <Co2Tracker.h>
#include <functional>

#define RX_PIN D1     // Rx pin which the MHZ19 Tx pin is attached to
#define TX_PIN D2     // Tx pin which the MHZ19 Rx pin is attached to
#define BAUDRATE 9600 // Device to MH-Z19 Serial baudrate (should not be changed)

Co2Tracker::Co2Tracker(KStandardCore *kStandardCore) : mySerial(2)
{
    this->kStandardCore = kStandardCore;
}
Co2Tracker::~Co2Tracker() {}

void Co2Tracker::setup()
{

    Serial.println("+ Co2Tracker::setup()");

    mySerial.begin(BAUDRATE); // (Uno example) device to MH-Z19 serial start
    myMHZ19.begin(mySerial);  // *Serial(Stream) reference must be passed to library begin().

    myMHZ19.autoCalibration(); // Turn auto calibration ON (OFF autoCalibration(false))

    clcCO2Detection_5s();

    Serial.println("- Co2Tracker::setup()");
}
void Co2Tracker::loop()
{
}

void Co2Tracker::clcCO2Detection_5s()
{
    int CO2 = myMHZ19.getCO2();            // Request CO2 (as ppm)
    float Temp = myMHZ19.getTemperature(); // Request Temperature (as Celsius)

    Serial.print("CO2 (ppm): ");
    Serial.println(CO2);

    Serial.print("Temperature (C): ");
    Serial.println(Temp);

    kStandardCore->getKMqtt()->publishOnChange("/" + kStandardCore->getHostname() + "/co2", String(CO2).c_str());
    kStandardCore->getKMqtt()->publishOnChange("/" + kStandardCore->getHostname() + "/temp", String(Temp).c_str());

    // Reschedule it again
    kStandardCore->getKSchedule()->schedule(std::bind(&Co2Tracker::clcCO2Detection_5s, this), 5000);
}
