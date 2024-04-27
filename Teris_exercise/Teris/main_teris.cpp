#include"Game.h"
#include"Globals.h"
#include<iostream>
using namespace std;

int main() {
    Configure::init("config.txt");
    
    Game game;
    game.init();
    game.loop();
    game.writeMaxScore();

    return 0;
}