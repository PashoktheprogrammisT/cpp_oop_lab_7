#include "utils.h"
#include <map>

namespace utils {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    int randomInt(int min, int max) {
        std::uniform_int_distribution<> dist(min, max);
        return dist(gen);
    }
    
    NPCType randomNPCType() {
        static const std::vector<NPCType> types = {
            NPCType::Orc, NPCType::Squirrel, NPCType::Druid,
            NPCType::Knight, NPCType::Elf, NPCType::Dragon,
            NPCType::Bear, NPCType::Bandit, NPCType::Werewolf,
            NPCType::Princess, NPCType::Toad, NPCType::Slaver,
            NPCType::Pegasus, NPCType::Bittern, NPCType::Desman,
            NPCType::Bull
        };
        return types[randomInt(0, types.size() - 1)];
    }
    
    std::string npcTypeToString(NPCType type) {
        static const std::map<NPCType, std::string> typeNames = {
            {NPCType::Orc, "Orc"},
            {NPCType::Squirrel, "Squirrel"},
            {NPCType::Druid, "Druid"},
            {NPCType::Knight, "Knight"},
            {NPCType::Elf, "Elf"},
            {NPCType::Dragon, "Dragon"},
            {NPCType::Bear, "Bear"},
            {NPCType::Bandit, "Bandit"},
            {NPCType::Werewolf, "Werewolf"},
            {NPCType::Princess, "Princess"},
            {NPCType::Toad, "Toad"},
            {NPCType::Slaver, "Slaver"},
            {NPCType::Pegasus, "Pegasus"},
            {NPCType::Bittern, "Bittern"},
            {NPCType::Desman, "Desman"},
            {NPCType::Bull, "Bull"}
        };
        return typeNames.at(type);
    }
    
    int getMoveDistance(NPCType type) {
        static const std::map<NPCType, int> moveDistances = {
            {NPCType::Orc, 20},
            {NPCType::Squirrel, 5},
            {NPCType::Druid, 10},
            {NPCType::Knight, 30},
            {NPCType::Elf, 10},
            {NPCType::Dragon, 50},
            {NPCType::Bear, 5},
            {NPCType::Bandit, 10},
            {NPCType::Werewolf, 40},
            {NPCType::Princess, 1},
            {NPCType::Toad, 1},
            {NPCType::Slaver, 10},
            {NPCType::Pegasus, 30},
            {NPCType::Bittern, 50},
            {NPCType::Desman, 5},
            {NPCType::Bull, 30}
        };
        return moveDistances.at(type);
    }
    
    int getKillDistance(NPCType type) {
        static const std::map<NPCType, int> killDistances = {
            {NPCType::Orc, 10},
            {NPCType::Squirrel, 5},
            {NPCType::Druid, 10},
            {NPCType::Knight, 10},
            {NPCType::Elf, 50},
            {NPCType::Dragon, 30},
            {NPCType::Bear, 10},
            {NPCType::Bandit, 10},
            {NPCType::Werewolf, 5},
            {NPCType::Princess, 1},
            {NPCType::Toad, 10},
            {NPCType::Slaver, 10},
            {NPCType::Pegasus, 10},
            {NPCType::Bittern, 10},
            {NPCType::Desman, 20},
            {NPCType::Bull, 10}
        };
        return killDistances.at(type);
    }
}
