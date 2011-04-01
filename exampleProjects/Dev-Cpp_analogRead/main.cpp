#include <cstdlib>
#include <iostream>
#include "hidLibrary/hidapi.h"
#include "suBoard/suBoard.h"

using namespace std;
int value;

int main(int argc, char *argv[])
{
    while(1)
    {
            value=readAdc(7);
            cout<<value<<endl;
    }
    return EXIT_SUCCESS;
}




