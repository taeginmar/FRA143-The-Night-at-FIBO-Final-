#include <vector>
#include <string>
#include <iostream>
#include "Random.cpp"

bool Checker(RandomEvent& gameSystem) {
    std::cout << "--- DEBUG: CHECKER IS RUNNING FROM SEPARATE FILE ---" << std::endl;

    // วนลูปตรวจทีละห้อง (0 ถึง 3 รวมเป็น 4 ห้องตามที่ระบบของนายเซ็ตไว้)
    for () {
        // ใช้ฟังก์ชันดึงสถานะที่นายสร้างไว้ในคลาสมาเช็กค่า
        bool isAnomaly = gameSystem.allrooms_.at(i)->GetIsAnamoly(); // (ถ้าติด private ให้สร้าง Getter ในคลาสดึงค่าออกมาก่อนนะครับ)
        bool isLocked = gameSystem.GetRoomLocker(i);

        std::cout << "Room " << i + 1 << " -> Anomaly: " << isAnomaly << " | Lock: " << isLocked << std::endl;

        // ลอจิกจับผิด: ถ้าห้องไหนสถานะไม่ตรงกัน ปรับแพ้ทันที!
        if (isAnomaly != isLocked) {
            return false;
        }
    }
    return true; // ผ่านฉลุยทุกห้อง
}