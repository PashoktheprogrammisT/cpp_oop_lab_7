#ifndef NPC_H
#define NPC_H

#include <mutex>
#include <memory>
#include <string>

enum class NPCType {
    Orc, Squirrel, Druid, Knight, Elf, Dragon, Bear,
    Bandit, Werewolf, Princess, Toad, Slaver, Pegasus,
    Bittern, Desman, Bull
};

class NPC {
private:
    int id;
    NPCType type;
    std::string name;
    int x, y;
    bool alive;
    static int next_id;
    
    mutable std::mutex mtx;  // Для потокобезопасности

public:
    NPC(NPCType t, int startX, int startY);
    ~NPC() = default;

    int getX() const;
    int getY() const;
    bool isAlive() const;
    NPCType getType() const;
    int getId() const;
    std::string getTypeName() const;
    std::string getName() const;

    void move(int newX, int newY);
    void kill();
    
    void randomMove(int mapWidth, int mapHeight);
    
    int getMoveDistance() const;  // Расстояние хода из таблицы
    int getKillDistance() const;  // Расстояние убийства из таблицы
    
    int rollDice() const;  // Бросок 6-гранного кубика
};

#endif
