#include "Game.h"
#include "Menu.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

int main() {
    system("chcp 65001 > nul");

    Menu gameMenu;
    if (!gameMenu.showLobby()) {
        return 0; 
    }

    GameConfig config = gameMenu.fillApplication();

    while (_kbhit()) _getch(); 

  
    Game game(config);
    game.setupAnomalyPlan(); // ตั้งค่าพลังงานและสุ่มผี
    game.run();              // เข้าสู่ Loop เกม (มี processInput/update/render ข้างในแล้ว)

    std::cout << "\n>> ระบบปิดการทำงาน ขอบคุณที่ปฏิบัติหน้าที่ที่ FIBO <<" << std::endl;
    std::cout << "กดปุ่มใดๆ เพื่อออกจากโปรแกรม..." << std::endl;
    
    while (_kbhit()) _getch();
    _getch();

    return 0;
}