#pragma once
#include "def.h"
#include <Wire.h>
#include <RTClib.h>

void setupTimeToRTC(const Time &reelTime,RTC_DS3231 &rtc)
{

}

Time nowTimeToRTC()
{
    Time t = {0,0,0,false};
    return t;
}

Time getHeureActuelleToRTC(RTC_DS3231 &rtc) {
    DateTime now = rtc.now();
    Time actuelle;
    actuelle.heure = now.hour();
    actuelle.minute = now.minute();
    actuelle.seconde = now.second();
    actuelle.valide = true;
    return actuelle;
}
