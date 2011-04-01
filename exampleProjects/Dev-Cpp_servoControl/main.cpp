#include <cstdlib>
#include <iostream>
#include "hidLibrary/hidapi.h"
#include "suBoard/suBoard.h"

using namespace std;
int newNumber;

int main(int argc, char *argv[])
{
    sendLcd("Servo App.      ",1,0,0);
    configurePort('B',0);
    attachServo(1,'B',0); // Just attaches servo1 to PORTB.0
    while(1)
    {
            cin>>newNumber;
            writeServo(1,ACTIVE,newNumber); // Activates the servo1 and writes newNumber as value. 
											// Ex: In theory, 4500 value equals to 1.5ms
                                            // onTime= ( value / 3000) ms
    }
    return EXIT_SUCCESS;
}




