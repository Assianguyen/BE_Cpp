#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
using namespace std;

class Display {

protected:

    bool displayOn;

public:

    //constructeurs
    Display();

    Display(bool state);

    //fonctions annexes 

    void setDisplayOn(bool state);

    bool isDisplayOn();

    //destructeur

};

#endif
