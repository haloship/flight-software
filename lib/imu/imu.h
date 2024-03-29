#ifndef IMU_H
#define IMU_H

#include <scheduler.h>
#include <Arduino.h>
#include <SPI.h>
#include <chip.h>
#include <bmx055.h>

#define BMX_SCK PB13
#define BMX_MISO PB14
#define BMX_MOSI PB15

#define GYR_CS PC4

class IMU : public Task, public Chip
{

private:
    BMX055 *driver;
    long measurement_delay;
    long previous_time = 0;
    float acc_x, acc_y, acc_z;
    float acc_offset_x, acc_offset_y, acc_offset_z;

public:
    IMU(long measurement_delay);
    ~IMU();

    bool measurementReady();

    float getAccelerationX();
    float getAccelerationY();
    float getAccelerationZ();

    void calibrateAccelerometer();

    // Task virtual methods
    bool Callback();
    bool OnEnable();
    void OnDisable();

    // Chip virtual methods
    bool checkStatus();
};

#endif