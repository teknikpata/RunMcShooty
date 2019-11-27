#include "Game.h"

int main() {
	Game game;
    try {
        game.run();
    }
    catch(...){
        printf("Caught unhandled exception \n");
    }
	return 0;
}
