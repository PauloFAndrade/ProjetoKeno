/*!
 *  This program implements the Keno game.
 *
 *  @file main.cpp
 *   
 *  @author Fernanda K. Lustosa
 *  @author Paulo V. Andrade
 */


#include <cstdlib> // EXIT_SUCCESS
#include <string.h>
#include <stdexcept>

#include "keno_common.h"
#include "keno_bet.h"

int main( int argc, char *argv[] )
{
    Keno::KenoBet player;

    if(argc==1){
        std::cout << "You forgot to put the bet file, please take this as an example:  ./keno ../../data/bet_01.dat\n";
        return 0;
    }

    bool key = player.readFile(argv[1]);

    if(key){
        player.initialText();
        player.startGame();
        player.endGame();
    }

    return EXIT_SUCCESS;
}
