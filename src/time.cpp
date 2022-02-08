#include "time.hpp"

#include <Wire.h>
DS3231 rtc;

Time settingsTime;

void initTime(uint8_t hours, uint8_t mins, uint8_t seconds) {
    Wire.begin();
    rtc.setHour(hours);
    rtc.setMinute(mins);
    rtc.setSecond(seconds);
}

Time getTime() {
    bool h12Flag, pmFlag;
    Time currentTime = {
        .hours = rtc.getHour(h12Flag, pmFlag),
        .mins = rtc.getMinute(),
        .seconds = rtc.getSecond()};
    return currentTime;
}

void prepareSettingsTime() {
    settingsTime = getTime();
    settingsTime.seconds = 0;
}

void incrementHour() {
    settingsTime.hours = settingsTime.hours + 1 < HOURS_IN_DAY ? settingsTime.hours + 1 : 0;
}

void decrementHour() {
    settingsTime.hours = settingsTime.hours == 0 ? HOURS_IN_DAY - 1 : settingsTime.hours - 1;
}

void incrementMinute() {
    settingsTime.mins = settingsTime.mins + 1 < MINUTES_IN_HOUR ? settingsTime.mins + 1 : 0;
}

void decrementMinute() {
    settingsTime.mins = settingsTime.mins == 0 ? MINUTES_IN_HOUR - 1 : settingsTime.mins - 1;
}

Time getSettingsTime() {
    return settingsTime;
}

void setTime(Time time) {
    rtc.setHour(time.hours);
    rtc.setMinute(time.mins);
    rtc.setSecond(time.seconds);
}