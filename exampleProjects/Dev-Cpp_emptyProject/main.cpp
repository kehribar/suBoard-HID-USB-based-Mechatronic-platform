#include <cstdlib>
#include <iostream>
#include "hidLibrary/hidapi.h"
#include "suBoard/suBoard.h"

using namespace std;

int main(int argc, char *argv[])
{
    sendLcd("Dev-Cpp Works!",1,0,0);
    // configurePort('B',0b00000000);
    // writePort('B',0xFF);
    // attachServo(1,'B',0); // Just attaches servo1 to PORTB.0
    // writeServo(1,ACTIVE,4500); // Activates the servo1 and writes 4500 as value. In theory, equals to 1.5ms
                                  // onTime= ( value / 3*(10^3)) ms
    // ..
    
     system("PAUSE");
     return EXIT_SUCCESS;
}




