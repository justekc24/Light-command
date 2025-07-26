#pragma once

#include <EEPROM.h>
#include "def.h"


const int EEPROM_SIZE = 512;
const int CONFIG_ADDRESS = 0;

void saveTimeConfig(const TimeConfig &config)
{
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.put(CONFIG_ADDRESS,config);
    EEPROM.commit();
    EEPROM.end();
}

TimeConfig loadTimeCongig()
{
    TimeConfig config;
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.get(CONFIG_ADDRESS,config);
    EEPROM.end();
    return config;
}