#include "NPC.h"
#include "utils.h"
#include <iostream>
#include <random>

int NPC::next_id = 1;

NPC::NPC(NPCType t, int startX, int startY) 
    : id(next_id++), type(t), x(startX), y(startY), alive(true) {
    name = utils::npcTypeToString(t) + "_" + std::to_string(id);
}

int NPC::getX() const {
    std::lock_guard<std::mutex> lock(mtx);
    return x;
}

int NPC::getY() const {
    std::lock_guard<std::mutex> lock(mtx);
    return y;
}

bool NPC::isAlive() const {
    std::lock_guard<std::mutex> lock(mtx);
    return alive;
}

NPCType NPC::getType() const {
    return type;
}

int NPC::getId() const {
    return id;
}

std::string NPC::getTypeName() const {
    return utils::npcTypeToString(type);
}

std::string NPC::getName() const {
    return name;
}

void NPC::move(int newX, int newY) {
    std::lock_guard<std::mutex> lock(mtx);
    x = newX;
    y = newY;
}

void NPC::kill() {
    std::lock_guard<std::mutex> lock(mtx);
    alive = false;
}

void NPC::randomMove(int mapWidth, int mapHeight) {
    if (!isAlive()) return;  // Мертвые не двигаются
    
    int moveDist = getMoveDistance();
    int newX = getX() + utils::randomInt(-moveDist, moveDist);
    int newY = getY() + utils::randomInt(-moveDist, moveDist);
    
    // Не выходить за границы карты
    if (newX < 0) newX = 0;
    if (newX >= mapWidth) newX = mapWidth - 1;
    if (newY < 0) newY = 0;
    if (newY >= mapHeight) newY = mapHeight - 1;
    
    move(newX, newY);
}

int NPC::getMoveDistance() const {
    return utils::getMoveDistance(type);
}

int NPC::getKillDistance() const {
    return utils::getKillDistance(type);
}

int NPC::rollDice() const {
    return utils::randomInt(1, 6);  // 6-гранный кубик
}
