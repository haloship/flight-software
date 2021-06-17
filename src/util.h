#ifndef UTIL_H
#define UTIL_H

#include "config.h"

bool check_sensors(PWMControl *pwm,
                   Barometer *barometer,
                   Transceiver *transceiver,
                   IMU *imu,
                   Flash *flash,
                   GPS *gps)
{
    Serial.println("************************************");
    Serial.println("Conducting status check on all ICs...");
    Serial.println("************************************");

    bool error = true;

    // Check status of PCA9635 PWM driver
    if (pwm->checkStatus())
    {
        Serial.println("PWM connection success! \xE2\x9C\x93");
    }

    else
    {
        Serial.println("PWM connection failed \xE2\x9C\x97");
        error = false;
    }

    // Check status of LPS25HB Barometer
    if (barometer->checkStatus())
    {
        Serial.println("Barometer connection success! \xE2\x9C\x93");
    }
    else
    {
        Serial.println("Barometer connection failed \xE2\x9C\x97");
        error = false;
    }

    // Check status of RFM69HW Transceiver
    if (transceiver->checkStatus())
    {
        Serial.println("Transceiver connection success! \xE2\x9C\x93");
    }
    else
    {
        Serial.println("Transceiver connection failed \xE2\x9C\x97");
        error = false;
    }

    // Check status of BMX055 IMU
    if (imu->checkStatus())
    {
        Serial.println("IMU connection success! \xE2\x9C\x93");
    }
    else
    {
        Serial.println("IMU connection failed \xE2\x9C\x97");
        error = false;
    }

    // Check status of WINBOND Flash
    if (flash->checkStatus())
    {
        Serial.println("Flash connection success! \xE2\x9C\x93");
    }
    else
    {
        Serial.println("Flash connection failed \xE2\x9C\x97");
        error = false;
    }

    if (gps->checkStatus())
    {
        Serial.println("GPS connection success! \xE2\x9C\x93");
    }
    else
    {
        Serial.println("GPS connection failed \xE2\x9C\x97");
        error = false;
    }

    return error;
}

#endif