#include "Game.h"
#include <conio.h>
#include <windows.h>
#include <iostream>

Game::Game(GameConfig _config) : player(1, "Guard", 0) {
    config = _config;          
    currentTurn = 1;            
    maxTurns = 6;               
    isRunning = true;           
    isPreparationPhase = true;  
    remainingTime = 60;         
    needsRedraw = true;         
    
    totalAnomaliesInGame = 0;   
    totalAnomaliesSpawned = 0;
    totalAnomaliesResolved = 0;
    totalAnomaliesMissed = 0;

    rooms_.push_back(Room(1, "Lab 162"));
    rooms_.push_back(Room(2, "Student Lounge"));
    rooms_.push_back(Room(3, "Meeting Room 130"));
    rooms_.push_back(Room(4, "Water Cooler Area"));
}

void Game::processInput() {
    if (_kbhit()) {
        char ch = tolower(_getch()); 

        // ล้างปุ่มที่อาจจะกดเบิ้ลมา
        while (_kbhit()) _getch();

        if (ch == 'd') {
            player.setCam((player.getCam() + 1) % 4);
            needsRedraw = true;
        }
        else if (ch == 'a') {
            int currentCam = player.getCam();
            player.setCam(currentCam - 1 < 0 ? 3 : currentCam - 1);
            needsRedraw = true;
        }
        else if (ch == ' ') {
             if (player.useEnergy()) {
                rooms_[player.getCam()].toggleDoor();
                needsRedraw = true;
             }
        }
        else if (ch == 'e') {
            checkEndTurn();
            needsRedraw = true;
        }
    }
}

void Game::update() {
    static DWORD lastTick = GetTickCount();
    DWORD currentTick = GetTickCount();

    // ทำงานทุกๆ 1 วินาที (1000ms)
    if (currentTick - lastTick >= 1000) {
        if (remainingTime > 0) {
            remainingTime--;
            needsRedraw = true; // วาดใหม่เพื่ออัปเดตตัวเลขเวลา
        } else {
            checkEndTurn(); 
        }
        lastTick = currentTick;
    }
}

void Game::run() {
    while (isRunning) {
        render();       // วาดหน้าจอ (จะวาดเฉพาะเมื่อ needsRedraw = true)
        processInput(); // รับค่าปุ่ม
        update();       // อัปเดตเวลา
        Sleep(10);      // พักนิดเดียวเพื่อให้เกมตอบสนองไว
    }
}

bool Player::useEnergy() { 
    if (energy_ > 0) {
        energy_--;
        return true;
    }
    return false;
}

void Game::checkEndTurn() {
    currentTurn++;
    if (currentTurn > maxTurns) {
        triggerWinScreen();
    } else {
        remainingTime = 60; 
        spawnInRooms(turnAnomalyCount[currentTurn]); 
        needsRedraw = true;
    }
}