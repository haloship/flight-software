#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Wire.h>
// #include <Servo.h>
#include <buzzer.h>
// #include <pwm.h>
#include <lps25hb.h>
// #include <gps.h>
#include <rfm69.h>
// #include <blink.h>
// // #include <imu.h>
// #include <flash.h>
#include <TaskScheduler.h>

// #define BUZZER PC3

#if defined(HALOSHIP)

#if !defined(STM32F4)
#define STM32F4
#endif

/*** LPS25HB Barometer ***/
#define LPS_CS PC6
#define LPS_SCK PA5
#define LPS_MISO PA6
#define LPS_MOSI PA7

/*** RFM69HW Transceiver ***/
#define RFM69_INT PB4
#define RFM69_CS PC13

/*** Exposed Digital Pin ***/
#define LED USER_PIN_1

/*** PCA9635 PWM Driver ***/
#define PWM_DRIVER_ADDRESS 0x70

/*** W25Q128JV SPI FLASH ***/
#define FLASH_CS PC2
#define FLASH_SCK PC10
#define FLASH_MISO PC11
#define FLASH_MOSI PC12

/*** Servo Motor ***/
#define DROGUE_CHUTE_SERVO_PIN PA4
#define MAIN_CHUTE_SERVO_PIN PC15

#endif

// // RFM69 pin definition for stm32F4
#if defined(FEATHER_BOARD) // Defined in Arduino framework
#define RFM69_INT PC6      //
#define RFM69_CS PB9       //
#define RFM69_RST PB8      // "A"
#define LPS_CS PC7
#define LPS_SCK PB13
#define LPS_MISO PB14
#define LPS_MOSI PB15
#endif

//   #define LED           PC1

// // LPS25 pin definition
// // #define LPS_CS PC7

// //BMX055 I2C address (JP1,JP2,JP3 = Open)
// // BMX055　I2C address of acceleration sensor
// #define Addr_Accl 0x19
// // BMX055　I2C address of gyro sensor
// #define Addr_Gyro 0x69
// // BMX055　I2C adress of magnetic sensor
// #define Addr_Mag 0x13
// #endif

#endif