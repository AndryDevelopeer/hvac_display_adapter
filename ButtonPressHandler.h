#pragma once
#include <Arduino.h>

class ButtonPressHandler {
public:
    enum PressType {
        NONE,
        SHORT,
        MEDIUM,
        LONG
    };

    ButtonPressHandler(uint8_t pin)
        : pin(pin), state(HIGH), lastState(HIGH),
          pressStartTime(0), triggered(false) {}

    void begin() {
        pinMode(pin, INPUT_PULLUP);
    }

    PressType update() {
        state = digitalRead(pin);
        bool pressed = (state == LOW);
        unsigned long currentMillis = millis();

        if (!pressed) {
            if (pressStartTime != 0 && !triggered) {
                unsigned long duration = currentMillis - pressStartTime;
                pressStartTime = 0;
                switch (duration / 1000) {
                    case 0:
                    case 1:
                        return SHORT;
                    case 2:
                    case 3:
                        return MEDIUM;
                    default:
                        return LONG;
                }
            }
            triggered = false;
            pressStartTime = 0;
            lastState = state;
            return NONE;
        }

        // Нажата
        if (pressStartTime == 0) {
            pressStartTime = currentMillis;
        }

        lastState = state;
        return NONE;
    }

private:
    uint8_t pin;
    int state;
    int lastState;
    unsigned long pressStartTime;
    bool triggered;
};
