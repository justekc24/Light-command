#pragma once

struct Time
{
    long heure;
    long minute;
    long seconde;    
    bool valide;
    bool operator==(const Time &other)
    {
        if (other.heure == heure &&
            other.minute == minute &&
            other.seconde == seconde &&
            other.valide == valide)
        {
        return 1;
        } else {
            return 0; 
        }
    }
} ;


struct TimeConfig
{
    Time onTime;
    Time ofTime;
    bool isvalide;
};



