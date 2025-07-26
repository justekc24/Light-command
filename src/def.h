#pragma once

struct Time
{
    long heure;
    long minute;
    long seconde;    
    bool valide;
} ;

struct TimeConfig
{
    Time onTime;
    Time ofTime;
    bool isvalide;
};



