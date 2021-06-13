#include "gps.h"

GPS::GPS(int LPS_CS, long measurement_delay) : Task(TASK_MILLISECOND, TASK_FOREVER, &scheduler, false),
                                               measurement_delay(measurement_delay),
                                               previous_time(0),
                                               pressure(-1),
                                               temperature(-1)
{
    // this->spi_dev = SPIClass(LPS_MOSI, LPS_MISO, LPS_SCK);
    // this->spi_dev.begin();
    this->LPS_CS = LPS_CS;
    this->lps_driver = new Adafruit_LPS25();
}

GPS::~GPS() {}

float GPS::getTemperature()
{
    return this->temperature;
}

float GPS::getPressure()
{
    return this->pressure;
}

bool GPS::measurementReady()
{

    long current_time = millis();
    if (current_time - this->previous_time >= this->measurement_delay)
    {
        this->previous_time = current_time;
        return true;
    }
    return false;
}

bool GPS::Callback()
{
    // Serial.println("inside barometer callback");
    if (measurementReady())
    {
        sensors_event_t pressure;
        sensors_event_t temp;
        this->temp_driver->getEvent(&temp);
        this->pressure_driver->getEvent(&pressure);
        this->temperature = temp.temperature;
        this->pressure = pressure.pressure;
        Serial.println(this->pressure);
        return true;
    }
    return false;
}

bool GPS::OnEnable()
{
    this->temp_driver = this->lps_driver->getTemperatureSensor();
    this->pressure_driver = this->lps_driver->getPressureSensor();
    return true;
}

void GPS::OnDisable()
{
}

bool GPS::checkStatus()
{
    Serial.println("Barometer Checking status");
    return this->lps_driver->begin_SPI(this->LPS_CS, &this->spi_dev);
}