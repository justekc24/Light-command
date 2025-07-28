#include <Arduino.h>
#include <Wire.h>    // Bibliothèque pour la communication I2C
#include <RTClib.h>  // Bibliothèque pour le module RTC DS3231

// Structure Time
struct Time {
  long heure;     // Heure 
  long minute;    // Minute 
  long seconde;   // Seconde
  bool valide;    // Indicateur de validité
};

class RTCTrigger {
  private:
    RTC_DS3231 rtc;      // Module RTC
    Time heureCible;      // Heure cible pour déclenchement
    bool declenche;   // Anti-rebond
    
    // Vérifie si l'heure actuelle correspond à la cible
    bool verifierDeclenchement(Time actuelle, Time cible) {
      return (actuelle.valide && cible.valide &&
              actuelle.heure == cible.heure &&
              actuelle.minute == cible.minute &&
              actuelle.seconde == cible.seconde);
    }
    
  public:
    // Constructeur
    RTCTrigger() : declenche(false) {
      Wire.begin();      // Initialisation I2C
      rtc.begin();       // Initialisation RTC
    }
    
    // Définit l'heure cible
    void setHeureCible(long h, long m, long s, bool valide = true) {
      heureCible.heure = h;
      heureCible.minute = m;
      heureCible.seconde = s;
      heureCible.valide = valide;
      declenche = false;
    }
    
    // Obtient l'heure actuelle depuis le RTC
    Time getHeureActuelle() {
      DateTime now = rtc.now();
      Time actuelle;
      actuelle.heure = now.hour();
      actuelle.minute = now.minute();
      actuelle.seconde = now.second();
      actuelle.valide = true;
      return actuelle;
    }
    
    // Vérifie et déclenche le callback si nécessaire
    void verifierEtDeclencher(void (*callback)()) {
      Time actuelle = getHeureActuelle();
      
      if (!declenche && verifierDeclenchement(actuelle, heureCible)) {
        declenche = true;
        if (callback != nullptr) {
          callback();
        }
      }
    }
    
    // Affichage debug
    void afficherHeure(Time t) {
      Serial.print("Heure actuelle : ");
      Serial.print(t.heure);
      Serial.print(":");
      Serial.print(t.minute);
      Serial.print(":");
      Serial.println(t.seconde);
    }
};

// Instance globale
RTCTrigger rtcTrigger;

// Callback exemple
void monAction() {
  Serial.println("Déclenchement à l'heure cible !");
}

void setup() {
  Serial.begin(115200);
  rtcTrigger.setHeureCible(18, 0, 0); // Définir l'heure cible 
}

void loop() {
  rtcTrigger.verifierEtDeclencher(monAction);
  delay(1000); // Vérification toutes les secondes
}