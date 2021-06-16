#include "gps.h";

GPS::GPS(long measurement_delay) : Task(TASK_MILLISECOND, TASK_FOREVER, &scheduler, false),
                                   measurement_delay(measurement_delay),
                                   previous_time(0),
                                   altitudeMSL(-1),
                                   latitude(-1),
                                   longitude(-1)
{
    // this->spi_dev = SPIClass(LPS_MOSI, LPS_MISO, LPS_SCK);
    // this->spi_dev.begin();
    // this->LPS_CS = LPS_CS;
    this->gps_driver = new SFE_UBLOX_GNSS();
}

GPS::~GPS() {}

long GPS::getAltitude()
{
    return this->altitudeMSL;
}

long GPS::getLatitude()
{
    return this->latitude;
}

long GPS::getLongitude()
{
    return this->longitude;
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
    this->gps_driver->checkUblox();
    if (measurementReady())
    {
        this->altitudeMSL = this->gps_driver->getAltitudeMSL();
        this->latitude = this->gps_driver->getLatitude();
        this->longitude = this->gps_driver->getLongitude();
        return true;
    }
    return false;
}

bool GPS::OnEnable()
{
    return true;
}

void GPS::OnDisable()
{
}

bool GPS::checkStatus()
{
    Serial.println("gps Checking status");
    return this->gps_driver->begin();
}