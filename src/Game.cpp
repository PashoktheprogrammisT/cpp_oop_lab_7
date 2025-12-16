#include "Game.h"
#include "utils.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <shared_mutex>

Game::Game() : running(false) {}

Game::~Game() {
    stop();
}

void Game::initialize(int npcCount) {
    std::unique_lock<std::shared_mutex> lock(npcs_mtx);
    npcs.clear();
    
    for (int i = 0; i < npcCount; ++i) {
        NPCType type = utils::randomNPCType();
        int x = utils::randomInt(0, MAP_WIDTH - 1);
        int y = utils::randomInt(0, MAP_HEIGHT - 1);
        npcs.push_back(std::make_shared<NPC>(type, x, y));
    }
    
    std::cout << "Game initialized with " << npcs.size() << " NPCs\n";
}

void Game::movementWorker() {
    while (running) {
        {
            std::shared_lock<std::shared_mutex> lock(npcs_mtx);
            for (auto& npc : npcs) {
                if (npc->isAlive()) {
                    npc->randomMove(MAP_WIDTH, MAP_HEIGHT);
                }
            }
        }
        
        checkFights();  // Проверить бои после движения
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Game::fightWorker() {
    while (running) {
        std::vector<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> local_queue;
        
        {
            std::lock_guard<std::mutex> lock(fight_queue_mtx);
            local_queue.swap(fight_queue);  // Забираем все бои из очереди
        }
        
        for (auto& fight : local_queue) {
            if (fight.first->isAlive() && fight.second->isAlive()) {
                resolveFight(fight.first, fight.second);
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void Game::printWorker() {
    while (running) {
        {
            std::lock_guard<std::mutex> lock(cout_mtx);  // Защита std::cout
            printMap();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Раз в секунду
    }
}

void Game::checkFights() {
    std::shared_lock<std::shared_mutex> lock(npcs_mtx);
    
    for (size_t i = 0; i < npcs.size(); ++i) {
        if (!npcs[i]->isAlive()) continue;
        
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            if (!npcs[j]->isAlive()) continue;
            
            int dx = npcs[i]->getX() - npcs[j]->getX();
            int dy = npcs[i]->getY() - npcs[j]->getY();
            int distance = std::max(std::abs(dx), std::abs(dy));
            
            // Если NPC в зоне убийства друг друга
            if (distance <= npcs[i]->getKillDistance() || 
                distance <= npcs[j]->getKillDistance()) {
                
                std::lock_guard<std::mutex> lock(fight_queue_mtx);
                fight_queue.emplace_back(npcs[i], npcs[j]);
            }
        }
    }
}

void Game::resolveFight(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender) {
    // Бросок кубиков: атака и защита для каждого
    int attack1 = attacker->rollDice();
    int defense1 = attacker->rollDice();
    int attack2 = defender->rollDice();
    int defense2 = defender->rollDice();
    
    bool kill1 = (attack1 > defense2);
    bool kill2 = (attack2 > defense1);
    
    {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << "FIGHT: " << attacker->getName() 
                  << " vs " << defender->getName() 
                  << " | A1:" << attack1 << " D1:" << defense1
                  << " A2:" << attack2 << " D2:" << defense2 << "\n";
    }
    
    if (kill1 && kill2) {
        attacker->kill();
        defender->kill();
    } else if (kill1) {
        defender->kill();
    } else if (kill2) {
        attacker->kill();
    }
}

void Game::printMap() const {
    std::cout << "\n=== MAP (" << MAP_WIDTH << "x" << MAP_HEIGHT << ") ===\n";
    
    std::vector<std::vector<char>> grid(MAP_HEIGHT, std::vector<char>(MAP_WIDTH, '.'));
    
    std::shared_lock<std::shared_mutex> lock(npcs_mtx);
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            int x = npc->getX();
            int y = npc->getY();
            if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
                char symbol = npc->getTypeName()[0];
                grid[y][x] = symbol;  // Первая буква типа NPC
            }
        }
    }
    
    // Выводим только часть карты 20x20 для наглядности
    for (int y = 0; y < std::min(20, MAP_HEIGHT); ++y) {
        for (int x = 0; x < std::min(20, MAP_WIDTH); ++x) {
            std::cout << grid[y][x] << " ";
        }
        std::cout << "\n";
    }
    
    // Статистика живых
    int alive_count = 0;
    for (const auto& npc : npcs) {
        if (npc->isAlive()) ++alive_count;
    }
    std::cout << "Alive: " << alive_count << "/" << npcs.size() << "\n";
}

void Game::printSurvivors() const {
    std::shared_lock<std::shared_mutex> lock(npcs_mtx);
    
    std::cout << "\n=== SURVIVORS ===\n";
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            std::cout << npc->getName() 
                      << " [" << npc->getTypeName() << "]"
                      << " at (" << npc->getX() << "," << npc->getY() << ")\n";
        }
    }
}

void Game::start() {
    running = true;
    
    // Запускаем три потока
    movement_thread = std::thread(&Game::movementWorker, this);
    fight_thread = std::thread(&Game::fightWorker, this);
    print_thread = std::thread(&Game::printWorker, this);
    
    // Игра длится GAME_DURATION секунд
    std::this_thread::sleep_for(std::chrono::seconds(GAME_DURATION));
    
    stop();
}

void Game::stop() {
    running = false;
    
    if (movement_thread.joinable()) movement_thread.join();
    if (fight_thread.joinable()) fight_thread.join();
    if (print_thread.joinable()) print_thread.join();
    
    printSurvivors();  // Вывод выживших в конце
}
