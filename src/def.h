#pragma once
#include <string>
#include <ArduinoJson.h>

/*
{
  "allumage": {"annee":2025,"mois":7,"jour":30,"heure":10,"minute":59,"seconde":0},
  "extinction": {"annee":2025,"mois":7,"jour":30,"heure":11,"minute":0,"seconde":0}
}
*/
struct Time
{
    long annee;
    long mois;
    long jour;
    long heure;
    long minute;
    long seconde;    
    bool valide;

    bool operator<(const Time &other) const
    {
        if (heure < other.heure) return 1;
        if (heure > other.heure) return 0;

        if (minute < other.minute) return 1;
        if (minute > other.minute) return 0;

        if (seconde < other.seconde) return 1;
        return 0;
    }

    bool operator>(const Time &other) const
    {
        if (heure < other.heure) return 0;
        if (heure > other.heure) return 1;

        if (minute < other.minute) return 0;
        if (minute > other.minute) return 1;

        if (seconde < other.seconde) return 0;
        return 1;
    }

    bool operator==(const Time &other) const
    {
        return (heure == other.heure && minute == other.minute && seconde == other.seconde);
    }
} ;


struct TimeConfig
{
    Time onTime ;
    Time ofTime;
    bool isvalide = false;
};

// Fonction qui convertit une chaîne JSON en structure TimeConfig
TimeConfig convertToTimeConfig(const String &str) {
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, str);

  TimeConfig cfg;

  if (error) {
    Serial.print("Erreur JSON : ");
    Serial.println(error.f_str());
    return cfg;
  }

  cfg.onTime.heure   = doc["on_heure"] | 0;
  cfg.onTime.minute  = doc["on_minute"] | 0;
  cfg.onTime.seconde = doc["on_seconde"] | 0;

  cfg.ofTime.heure   = doc["off_heure"] | 0;
  cfg.ofTime.minute  = doc["off_minute"] | 0;
  cfg.ofTime.seconde = doc["off_seconde"] | 0;

  return cfg;
}


