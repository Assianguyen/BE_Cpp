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

    //methodes 

    void setDisplayOn(bool state);

    bool isDisplayOn();

    //destructeur

};

#endif
