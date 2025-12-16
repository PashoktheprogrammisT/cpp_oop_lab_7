#ifndef UTILS_H
#define UTILS_H

#include "NPC.h"
#include <random>
#include <string>

namespace utils {
    int randomInt(int min, int max);
    NPCType randomNPCType();  // Случайный тип NPC
    std::string npcTypeToString(NPCType type);
    int getMoveDistance(NPCType type);  // Получить расстояние хода по таблице
    int getKillDistance(NPCType type);  // Получить расстояние убийства по таблице
}

#endif
