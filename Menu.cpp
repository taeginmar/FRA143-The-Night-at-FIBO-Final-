#include "Menu.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cctype>

bool Menu::showLobby() {
    system("cls");
    std::cout << "=========================================================\n";
    std::cout << "     FIBO SECURITY MANAGEMENT : NEW APPLICATION CENTER     \n";
    std::cout << "=========================================================\n\n";
    std::cout << " [1] ยื่นใบสมัครงานกะดึก (Start Game)\n";
    std::cout << " [2] ออกจากระบบ (Exit)\n\n";
    std::cout << "=========================================================\n";
    std::cout << "ระบุคำสั่ง (1-2): ";

    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == '1') {
                std::cout << "1\n\n>> กำลังเข้าสู่หน้าสมัครงาน..." << std::endl;
                Sleep(800);
                return true;  
            }
            if (ch == '2') {
                std::cout << "2\n\n>> ปิดระบบ..." << std::endl;
                Sleep(800);
                return false;
            }
        }
    }
}

GameConfig Menu::fillApplication() {
    GameConfig config;
    system("cls");

    std::cout << "=========================================================\n";
    std::cout << "           APPLICATION FORM : FIBO NIGHT SHIFT           \n";
    std::cout << "=========================================================\n\n";
    
    std::cout << " [1] คุณมีประวัติโรคหัวใจหรือไม่? (Y/N): ";
    while (true) {
        if (_kbhit()) {
            char ch = _getch();   
            ch = toupper(ch);      

            if (ch == 'N') {
                config.enableJumpscare = true; 
                std::cout << "N" << std::endl;
                std::cout << " -> ผ่านเกณฑ์: สภาพร่างกายปกติ" << std::endl;
                Sleep(500);
                break; 
            } 
            else if (ch == 'Y') {
                std::cout << "Y" << std::endl;
                std::cout << " -> บันทึกผล: ไม่ผ่านเกณฑ์ด้านสุขภาพสำหรับการทำงานกะดึก" << std::endl;
                std::cout << " >> ระบบกำลังปิดตัวลงเพื่อความปลอดภัยของคุณ <<" << std::endl;
                Sleep(2000); 
                exit(0); 
            }
        }
    }
    std::cout << "\n [2] ระบุประสบการณ์การทำงานของคุณเพื่อการจัดสรรทรัพยากร\n";
    std::cout <<   "[1] Intern มีประสบการณ์ด้านการทำงานกลางคืนน้อยกว่า 1 ปี " << std::endl 
                << "[2] Staff มีประสบการณ์ด้านการทำงานกลางคืนระหว่าง 1 - 3 ปี" << std::endl 
                << "[3] Senior มีประสบการณ์ด้านการทำงานกลางคืนมากกว่า 3 ปีขึ้นไป\n";
    
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == '1') {
                config.difficulty = "Intern";
                config.jumpscareThreshold = 4;
                break;

            } else if (ch == '2') {
                config.difficulty = "Staff";
                config.jumpscareThreshold = 3;
                break;

            } else if (ch == '3') {
                config.difficulty = "Senior";
                config.jumpscareThreshold = 2;
                break;
            }

        }
    }

    std::cout << "\n บันทึกข้อมูลเรียบร้อย... กำลังเตรียมเริ่มกะงาน\n";
    Sleep(1000);
    return config;
}