#pragma once

#include "ButtonPressHandler.h"
#include "SpaceshipDisplay.h"
#include "DateTime.h"
#include "ds1302.h"

class ClockAdjuster {
public:
    enum AdjustSection {
        HOUR,
        MINUTE
    };

    static constexpr uint16_t BLINK_PERIOD_TICKS = 20;

    ClockAdjuster(SpaceshipDisplay::Clock &clockDisplay, DateTime &dateTime, ButtonPressHandler &button, Ds1302 &rtc)
        : clock(clockDisplay), externalTime(dateTime), button(button), rtc(rtc),
          adjusting(false), section(HOUR) {}

    void update(uint16_t tick) {
        auto press = button.update();

        if (press == ButtonPressHandler::LONG) {
            if (!adjusting) {
                // Вход в режим настройки — копируем текущее время в локальный буфер
                bufferTime = externalTime;
                adjusting = true;
            } else {
                // Выход из режима настройки — сохраняем в RTC и обновляем внешнее время
                adjusting = false;
                externalTime = bufferTime;
                rtc.setWriteProtect(false);
                rtc.setClockHalt(false);
                rtc.setDateTime(bufferTime);
            }
        }

        if (!adjusting) return;

        if (press == ButtonPressHandler::MEDIUM) {
            section = (section == HOUR) ? MINUTE : HOUR;
        }

        if (press == ButtonPressHandler::SHORT) {
            increment();
        }

        // Отображение с миганием текущей секции
        bool blink = (tick % BLINK_PERIOD_TICKS) < (BLINK_PERIOD_TICKS / 2);

        if (section == HOUR) {
            clock.hour(blink ? SpaceshipDisplay::NUM_BLANK : bufferTime.time.hour);
            clock.minute(bufferTime.time.minute);
        } else {
            clock.hour(bufferTime.time.hour);
            clock.minute(blink ? SpaceshipDisplay::NUM_BLANK : bufferTime.time.minute);
        }

        clock.colon(false);
    }

    bool isAdjusting() const {
        return adjusting;
    }

private:
    SpaceshipDisplay::Clock &clock;
    DateTime &externalTime;   // Ссылка на время из вне (state.dateTime)
    ButtonPressHandler &button;
    Ds1302 &rtc;

    bool adjusting;
    AdjustSection section;

    DateTime bufferTime;  // Локальная копия времени для настройки

    void increment() {
        if (section == HOUR) {
            bufferTime.time.hour = (bufferTime.time.hour + 1) % 24;
        } else {
            bufferTime.time.minute = (bufferTime.time.minute + 1) % 60;
        }
    }
};
