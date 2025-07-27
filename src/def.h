#pragma once

struct Time
{
    long heure;
    long minute;
    long seconde;    
    bool valide;
    bool operator==(const Time &other)
    {
        return false;
    }
} ;


struct TimeConfig
{
    Time onTime;
    Time ofTime;
    bool isvalide;
};



