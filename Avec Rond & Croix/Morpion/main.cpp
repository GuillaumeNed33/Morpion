#include <SFML/Graphics.hpp>
#include <iostream>


#include "Appli.h"

int main ()
{
    Appli a;
    bool replay;
    a.run(replay);

    while(replay)
        a.run(replay);

    return 0;
}

