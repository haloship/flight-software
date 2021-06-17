#ifndef LPS25HB_H
#define LPS25HB_H

#include <scheduler.h>
#include <Adafruit_LPS2X.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <SPI.h>
#include "chip.h"

#if defined(HALOSHIP)
#define LPS_SCK PA5
#define LPS_MISO PA6
#define LPS_MOSI PA7
#endif

#if defined(FEATHER_BOARD)
#define LPS_SCK PB13
#define LPS_MISO PB14
#define LPS_MOSI PB15
#endif

class Barometer : public Task, public Chip
{
private:
    Adafruit_LPS25 *lps_driver;
    Adafruit_Sensor *temp_driver, *pressure_driver;
    SPIClass spi_dev;
    int LPS_CS;
    long measurement_delay;
    long previous_time = 0;
    float pressure;
    float temperature;

public:
    Barometer(int LPS_CS, long measurement_delay);
    ~Barometer();

    bool measurementReady();
    float getTemperature();
    float getPressure();

    // Task virtual methods
    bool Callback();
    bool OnEnable();
    void OnDisable();

    // Chip virtual methods
    bool checkStatus();
};

#endif