#include "Game.h"
#include <iostream>

#include "Game.h"
#include <iostream>
#include <windows.h>

#include "Game.h"
#include <iostream>
#include <windows.h>

void Game::render() {
    if (!needsRedraw) return; 

    system("cls"); 

    std::cout << "=========================================================\n";
    std::cout << " TIME: 0" << currentTurn << ":00 AM | ENERGY: " << player.getEnergy() << "/" << config.maxEnergy;
    std::cout << " | STATUS: " << (remainingTime > 0 ? "MONITORING" : "TRANSITION") << " (Time: " << remainingTime << "s)\n";
    std::cout << "=========================================================\n\n";

    int currentCam = player.getCam();
    Room& activeRoom = rooms_[currentCam];

    std::cout << " [ CAMERA 0" << currentCam + 1 << " : " << activeRoom.getName() << " ]\n";
    std::cout << " -----------------------------------------------------\n";
    
    if (activeRoom.getAnomaly()) {
        std::cout << " !! WARNING: UNKNOWN ENTITY DETECTED !!\n";
        std::cout << " [  @  @  ]  <-- Something is looking at you...\n";
        std::cout << " [  ----  ] \n";
    } else {
        std::cout << " > No anomaly detected.\n";
        std::cout << " > Room status: Normal\n\n";
    }
    
    std::cout << " -----------------------------------------------------\n";
    std::cout << " DOOR STATUS: " << (activeRoom.getIsLocked() ? "[ LOCKED ]" : "[ OPEN ]") << "\n\n";

    std::cout << "=========================================================\n";
    std::cout << " [A][D] Switch Camera  |  [Space] Toggle Door (Cost: 1 Energy)\n";
    std::cout << " [E] End Turn / Next Hour\n";
    std::cout << "=========================================================\n";

    needsRedraw = false; 
}

void Game::triggerWinScreen() {
    isRunning = false; // หยุด Loop เกม
    system("cls");
    std::cout << "=========================================================\n";
    std::cout << "        MISSION SUCCESS : 06:00 AM - MORNING LIGHT        \n";
    std::cout << "=========================================================\n\n";
    std::cout << " ยินดีด้วย! คุณปฏิบัติหน้าที่จนครบกำหนดเวลา\n";
    std::cout << " แสงอาทิตย์เริ่มส่องสว่าง... ความผิดปกติทั้งหมดกำลังจางหายไป\n\n";
    
    // แสดงผลประเมิน (Evaluation Report)
    std::cout << " >>> REPORT SUMMARY <<<\n";
    std::cout << " - ตำแหน่งงาน: " << config.difficulty << std::endl;
    std::cout << " - Anomaly ทั้งหมดที่พบ: " << totalAnomaliesSpawned << std::endl;
    std::cout << " - จัดการสำเร็จ: " << totalAnomaliesResolved << std::endl;
    std::cout << " - พลาด (Missed): " << totalAnomaliesMissed << std::endl;
    std::cout << " - พลังงานที่เหลือ: " << player.getEnergy() << std::endl;
    
    std::cout << "\n=========================================================\n";
    std::cout << " บันทึก: คุณได้รับอนุญาตให้ลงเวรและกลับบ้านได้โดยสวัสดิภาพ\n";
    std::cout << "=========================================================\n";
}

void Game::triggerMissionFailed() {
    isRunning = false;
    system("cls");
    std::cout << "#########################################################\n";
    std::cout << "           MISSION FAILED : SECURITY BREACHED           \n";
    std::cout << "#########################################################\n\n";
    std::cout << " ตรวจพบความผิดปกติระดับวิกฤต! ระบบความปลอดภัยล้มเหลว...\n";
    
    if (player.getEnergy() <= 0) {
        std::cout << " สาเหตุ: พลังงานสำรองหมด (System Blackout)\n";
    } else {
        std::cout << " สาเหตุ: เผชิญหน้ากับความผิดปกติโดยตรง (Fatal Encounter)\n";
    }

    std::cout << "\n [ สถานะ: ขาดการติดต่อจากเจ้าหน้าที่หน้าที่ ]\n";
    std::cout << "#########################################################\n";
}

// ฟังก์ชันนี้เรียกใช้ได้ทั้งตอนแพ้ หรือตอนจบโปรแกรม
void Game::showGameOver() {
    triggerMissionFailed();
}