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
    Time onTime ;
    Time ofTime;
    bool isvalide;
};
// 
//"{on_heure: 3, on_minute: 2, on_seconde: 2, off_heure: 2, off_minute: 2, on_seconde : 2}"



TimeConfig convertToTimeConfig(const String &str)
{
    TimeConfig cfg;
    cfg.onTime.heure = 3;
    cfg.onTime.minute = 2;
    cfg.onTime.seconde = 2;
    cfg.ofTime.heure = 2;
    cfg.ofTime.minute = 2;
    cfg.ofTime.seconde = 2;
    return cfg;
}



