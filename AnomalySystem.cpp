#include "Game.h"
#include <cstdlib>
#include <ctime>

void Game::setupAnomalyPlan() {
    std::srand(std::time(0));

    int totalAnomalies = (std::rand() % 15) + 10; // สุ่มระหว่าง 10 - 24 ครั้ง
    
    int buffer = 0;
    if (config.difficulty == "Intern") buffer = 5;
    else if (config.difficulty == "Staff") buffer = 3;
    else buffer = 1;

    player.setEnergy(totalAnomalies + buffer);
    config.maxEnergy = totalAnomalies + buffer; // เก็บค่าสูงสุดไว้แสดงผล UI

    for (int i = 1; i <= 6; i++) {
        turnAnomalyCount[i] = totalAnomalies / 6; // แบ่งเฉลี่ยเบื้องต้น
    }
}

void Game::spawnInRooms(int count) {
    int spawned = 0;
    while (spawned < count) {
        int roomIdx = std::rand() % 4; // สุ่มเลข 0-3 (index ของห้อง)

        if (!rooms_[roomIdx].getAnomaly()) { // ถ้าห้องนั้นยังไม่มีผี
            rooms_[roomIdx].setAnomaly(true); // สั่งให้มีผี
            spawned++;
        }
        
    }
}