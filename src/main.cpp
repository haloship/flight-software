#include "config.h"
// #include "util.h"

// Instantiate objects
Buzzer *buzzer;
// PWMControl *pwm;
Barometer *barometer;
// Blink *blinker;
Transceiver *transceiver;
// IMU *imu;
// Flash *flash;
// Servo main_chute_servo;
// Servo drogue_chute_servo;

// SERVO USES STM32F4 TIMER 1 THAT OPERATES AT TWICE THE EXPECTED FREQUENCY
// HENCE WRITE ALL MICROSECONDS IN DOUBLE
// 2000 MICROSECONDS --> 1 MILLISECOND
// 4000 MICROSECONDS --> 2 MILLISECOND

enum state
{
    PRELAUNCH,
    LAUNCH_READY,
    MOTOR_BURN,
    BURNOUT,
    APOGEE,
    POST_DROGUE,
    POST_MAIN,
    END
};

bool check_sensors_feather(
    Barometer *barometer,
    Transceiver *transceiver)
{
    Serial.println("************************************");
    Serial.println("Conducting status check on all ICs...");
    Serial.println("************************************");

    bool error = true;

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

    return error;
}

void setup()
{
    // Initialize communication
    Wire.begin();
    Serial.begin(115200);
    // main_chute_servo.attach(MAIN_CHUTE_SERVO_PIN);
    // drogue_chute_servo.attach(DROGUE_CHUTE_SERVO_PIN);

    // Wait until serial console is open, remove if not tethered to computer
    while (!Serial)
    {
        delay(1);
    }

    // Define all needed submodules
    buzzer = new Buzzer();
    // pwm = new PWMControl();
    barometer = new Barometer(LPS_CS, 500);
    transceiver = new Transceiver(RFM69_CS, RFM69_INT);
    // imu = new IMU(500);
    // flash = new Flash(FLASH_CS);

    // blinker = new Blink(pwm);

    // Run sensor check
    // check_sensors(pwm, barometer, transceiver, imu, flash)
    //     ? buzzer->signalSuccess()
    //     : buzzer->signalFail();
    check_sensors_feather(barometer, transceiver)
        ? Serial.println("sensors success")
        : Serial.println("sensors failed");

    // // Enable chips
    barometer->enable();
    // imu->enable();
    // transceiver->enable();
}

void loop()
{
    scheduler.execute();
}