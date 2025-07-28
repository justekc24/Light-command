#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "def.h"
#include "gsm_manager.h"
#include "page.h"
#include "rtc_horloge_manager.h"
#define LAMP_PIN 5

const char *ssid = "esp8266 wifi";
const char *password = "isniis";

Time t = {10,20,30,true};
ESP8266WebServer server;
TimeConfig config;

void handleRoot()
{
  server.send_P(200, "text/html", code);
}

void configSetup()
{
  if (server.hasArg("plain"))
  {
    String json = server.arg("plain");
    Serial.println(json);
    server.send(200, "application/json", "{\"status\" : \"succes\"}");
  }
  else
  {
    server.send(404, "application/json", "{\"status\" : \"echec\"}");
  }
}

bool compareTime(const Time &t1, const Time &t2)
{
  return false;
}

Time convertToTime(const String &timeStr)
{
  Time t;
  return t;
}

void timeGet()
{
  server.send(200, "application/json", "{\"heure\":" + String(t.heure) + ",\"minute\":" + String(t.minute) + ",\"seconde\":" + String(t.seconde) + "}");
}

void setup()
{
  pinMode(LAMP_PIN,OUTPUT);
  Serial.begin(115200);
  Serial.println("\n\nStarting setup...");

  // Désactiver temporairement le WiFi
  WiFi.mode(WIFI_OFF);
  delay(1000);

  // INIT DU GSM
  t = gsm::getNowTime();
  //setupTime(gsm_time);

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
}