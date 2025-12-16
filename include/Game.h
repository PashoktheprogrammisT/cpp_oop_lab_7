#ifndef GAME_H
#define GAME_H

#include "NPC.h"
#include <vector>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <atomic>

class Game {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    mutable std::shared_mutex npcs_mtx;  // Для shared доступа
    
    std::mutex cout_mtx;  // Защита вывода в консоль
    std::mutex fight_queue_mtx;
    std::vector<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> fight_queue;
    
    std::atomic<bool> running;  // Флаг работы игры
    
    // Три потока по заданию
    std::thread movement_thread;  // Поток движения
    std::thread fight_thread;     // Поток боев
    std::thread print_thread;     // Поток вывода карты
    
    const int MAP_WIDTH = 100;
    const int MAP_HEIGHT = 100;
    const int GAME_DURATION = 30;  // 30 секунд игры
    
    void movementWorker();  // Рабочая функция потока движения
    void fightWorker();     // Рабочая функция потока боев
    void printWorker();     // Рабочая функция потока вывода
    
    void checkFights();  // Проверка NPC на расстояние убийства
    void resolveFight(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender);
    
public:
    Game();
    ~Game();
    
    void initialize(int npcCount);  // Создание NPC
    void start();    // Запуск игры
    void stop();     // Остановка игры
    
    void printMap() const;        // Вывод карты
    void printSurvivors() const;  // Вывод выживших
};

#endif
