#ifndef BUZZER_H
#define BUZZER_H

#include <scheduler.h>
#include <Arduino.h>
#include <mario.h>
#include <takeonme.h>

enum tone_type
{
    SINGLE_TONE,
    SUCCESS_TONE,
    FAIL_TONE,
    MARIO_TONE,
    TAKE_ON_ME_TONE
};
class Buzzer : public Task
{

private:
    uint16_t pin;
    uint16_t frequency;
    tone_type which_tone;
    StatusRequest *request;
    uint16_t tone_counter;

public:
    Buzzer();
    Buzzer(StatusRequest *request);
    ~Buzzer();

    void signal(uint16_t frequency, uint16_t duration);
    void signalSuccess();
    void signalFail();
    void signalMario();
    void signalTakeOnMe();

    bool Callback();
    bool OnEnable();
    void OnDisable();
};

#endif