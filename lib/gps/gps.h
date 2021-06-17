// #ifndef LPS25HB_H
// #define LPS25HB_H

#include <scheduler.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
// #include <Adafruit_LPS2X.h>
// #include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <SPI.h>
#include "chip.h"

// #if defined(FEATHER_BOARD)
// #define LPS_SCK PA5
// #define LPS_MISO PA6
// #define LPS_MOSI PA7
// #endif

// #if defined(FEATHER_BOARD)
// #define LPS_SCK PB13
// #define LPS_MISO PB14
// #define LPS_MOSI PB15
// #endif

class GPS : public Task, public Chip
{
private:
    SFE_UBLOX_GNSS *gps_driver;
    // Adafruit_Sensor *temp_driver, *pressure_driver;
    // SPIClass spi_dev;
    // int LPS_CS;
    long measurement_delay;
    long previous_time = 0;
    long altitudeMSL;
    long latitude;
    long longitude;

public:
    GPS(long measurement_delay);
    ~GPS();

    bool measurementReady();
    long getAltitude();
    long getLatitude();
    long getLongitude();

    // Task virtual methods
    bool Callback();
    bool OnEnable();
    void OnDisable();

    // Chip virtual methods
    bool checkStatus();
};

// #endif