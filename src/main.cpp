#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <RTClib.h>
#include "def.h"
#include "gsm_manager.h"
#include "page.h"
#include "rtc_horloge_manager.h"
#include "save.h"

#define INTERVALLE 1000
#define LAMP_PIN 16

const char *ssid = "esp8266 wifi";
const char *password = "isniis";

RTC_DS3231 rtc;
unsigned long now = 0;
Time t = {10,20,30,true};
ESP8266WebServer server;
TimeConfig config ;


void handleRoot()
{
  server.send_P(200, "text/html", code);
}

void configSetup()
{
  digitalWrite(LAMP_PIN,1);
  Serial.println("Requête effectué");
  if (server.hasArg("plain"))
  {
    String json = server.arg("plain");
    Serial.println(json);
    server.send(200, "application/json", "{\"status\" : \"succes\",\"Données\" : "+json+"}");
    config = convertToTimeConfig(json);
    saveTimeConfigToEEPROM(config);
    
  }
  else
  {
    server.send(404, "application/json", "{\"status\" : \"echec\"}");
  }
}

void timeGet()
{
  server.send(200, "application/json", "{\"heure\":" + String(t.heure) + ",\"minute\":" + String(t.minute) + ",\"seconde\":" + String(t.seconde) + "}");
}

void setup()
{
  //INIT du module horloge
  if(!rtc.begin())
  {
    Serial.println("Impossible de trouver le module RTC");
    while (1);
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  //init de la lampe
  pinMode(LAMP_PIN,OUTPUT);
  digitalWrite(LAMP_PIN,0);
  
  //init du port série
  Serial.begin(115200);
  Serial.println("\n\nStarting setup...");

  // Désactiver temporairement le WiFi
  WiFi.mode(WIFI_OFF);
  delay(1000);

  //Init de la configuration si elle est dans l'eeprom
  if(loadTimeCongigToEEPROM().isvalide)
  {
    config = loadTimeCongigToEEPROM();
  }
  else //sinon config par défaut
  {
    config.onTime = Time{19,0,0,true};
    config.ofTime = Time{7,0,0,true};
  }

  // INIT du temps grâce au gsm
  t = gsm::getNowTime();

  //initialisation manuelle de l'heure du module rtc grâce à l'heure que le module gsm
  setupTimeToRTC(t,rtc);

  Serial.print(t.heure);
  Serial.print("h ");
  Serial.print(t.minute);
  Serial.print("min ");
  Serial.print(t.seconde);
  Serial.print("s");

  // Réactiver le WiFi
  Serial.println("Starting WiFi AP...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress ip = WiFi.softAPIP();
  Serial.print("AP IP: ");
  Serial.println(ip);

  server.on("/", handleRoot);
  server.on("/config", HTTP_POST, configSetup);
  server.on("/time", HTTP_GET, timeGet);
  server.begin();
}

void loop()
{
  server.handleClient();
  if(millis() - now > INTERVALLE)
  {
    Serial.print(getHeureActuelleToRTC(rtc).heure);
    Serial.print(" h ");
    Serial.print(getHeureActuelleToRTC(rtc).minute);
    Serial.print(" min ");
    Serial.print(getHeureActuelleToRTC(rtc).seconde);
    Serial.println(" s");
    digitalWrite(LAMP_PIN,!digitalRead(LAMP_PIN));
    now = millis();
  }
}

