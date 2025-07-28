#pragma once
#define TINY_GSM_MODEM_SIM800
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include "secret.h"
#include "def.h"

#define RX 14 // GPIO14 = D5
#define TX 12 // GPIO12 = D6

const char apn[] = "internet.mtn.bj";
const  String url ="/v2.1/get-time-zone?key="+API_KEY+"&format=json&by=zone&zone=Africa/Porto-Novo";


namespace gsm
{
    
    Time getNowTime()
    {
        Time now = {0,0,0,false};
        SoftwareSerial gsm_module(RX, TX);
        TinyGsm modem(gsm_module);
        TinyGsmClient client(modem);
        HttpClient http(client, "api.timezonedb.com", 80);
        gsm_module.begin(9600);
        Serial.println("Initialisation du modem...");
        modem.restart();
        delay(3000);
        Serial.println("Connexion au réseau...");
        if (!modem.gprsConnect(apn, "", "")) {
            Serial.println("Échec GPRS");
            now.valide = false;
            return now;
        }

        Serial.println("Requête HTTP...");
        http.get(url);

        int statusCode = http.responseStatusCode();
        String response = http.responseBody();

/*         Serial.print("Code HTTP: ");
        Serial.println(statusCode);
        Serial.println("Réponse JSON:");
        Serial.println(response); */

        modem.gprsDisconnect();
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc,response);
        if(error)
        {
            now.valide = false;
            return now;
        }
        String data = doc["formatted"];
        data = data.substring(11,19);
        String para;
        String dataLists[3];
        byte pos = 0;
        for(byte i = 0; i < data.length() ; i++)
        {
            if(data[i] == ':' || (i+1 == data.length())) 
            {
                para += (i+1 == data.length()) ? data[i] : ' ';
                //Serial.println(para);
                dataLists[pos] = para;
                pos ++; 
                para = "";
            }
            else
              para += data[i];
        }
        now = {dataLists[0].toInt(),dataLists[1].toInt(),dataLists[2].toInt(),true};
        //Serial.println(data);
        return now;
    }

}//end gsm