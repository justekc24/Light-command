#pragma once
#include "def.h"
#include <Wire.h>
#include <RTClib.h>

void setupTimeToRTC(const Time &reelTime,RTC_DS3231 &rtc)
{
  // Extraire les heures, minutes et secondes
  int heure = reelTime.heure;
  int minute = reelTime.minute;
  int seconde = reelTime.seconde;
  // Date fixe (exemple : 2025-07-27)
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


