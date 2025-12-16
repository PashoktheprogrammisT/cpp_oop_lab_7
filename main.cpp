#include "Game.h"
#include <iostream>

int main() {
    std::cout << "=== NPC Battle Simulation (Lab 7) ===\n";
    std::cout << "Variant 3: Druid (Move: 10, Kill: 10)\n";
    std::cout << "Game duration: 30 seconds\n";
    
    Game game;
    game.initialize(50);
    game.start();
    
    std::cout << "\n=== Game Over ===\n";
    return 0;
}
