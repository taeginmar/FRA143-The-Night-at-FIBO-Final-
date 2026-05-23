# 🏢 FRA143 The Night at FIBO - Developer Guide

นี่คือเอกสารสำหรับนักพัฒนา (Developer Guide) ของเกม **"The Night at FIBO"** เกมสยองขวัญ Text-based บน Terminal ที่ใช้ภาษา C++ ในการพัฒนา โปรเจกต์นี้ใช้โครงสร้าง Object-Oriented Programming (OOP) เช่น Inheritance และ Polymorphism อย่างเต็มรูปแบบ

---

## 💻 1. System Requirements & Dependencies (ข้อจำกัดระบบ)

โปรเจกต์นี้ถูกออกแบบมาเพื่อรันบนระบบปฏิบัติการ **Windows** เท่านั้น เนื่องจากการแสดงผลและการรับค่าผ่าน Terminal มีการใช้ไลบรารีเฉพาะของ Windows ดังนี้:
* `<windows.h>` : ใช้สำหรับคำสั่ง `Sleep()` เพื่อหน่วงเวลา และ `system("cls")` เพื่อล้างหน้าจอ
* `<conio.h>` : ใช้สำหรับคำสั่ง `_getch()` เพื่อรับค่าการกดคีย์บอร์ดแบบเรียลไทม์โดยไม่ต้องกด Enter
*(หากผู้พัฒนาคนอื่นใช้ macOS หรือ Linux จะต้องปรับแก้ไลบรารี 2 ตัวนี้ก่อนทำการคอมไพล์)*

---

## 📂 2. โครงสร้างไฟล์ คลาส และฟังก์ชัน (Architecture & API)

### 📄 `ส่วนที่ 1 Config.h`
ทำหน้าที่เป็น Data Structure สำหรับส่งผ่านค่า Setting ไปยังระบบต่างๆ
* **`struct GameConfig`**: 
  * `anomalySpawnChance` (int): โอกาส (%) ที่จะสุ่มเกิดความผิดปกติ
  * `jumpscareThreshold` (int): จำนวนครั้งที่ปล่อยผีหลุดได้ก่อนจะตาย
  * `enableJumpscare` (bool): เปิด/ปิด ฉากตกใจตอนตาย
  * `maxEnergy` (int): พลังงานแบตเตอรี่สูงสุดสำหรับค่ำคืนนั้น

### 📄 `ส่วนที่ 2 Menu.h` และ `Menu.cpp`
จัดการหน้าจอ UI ก่อนเข้าเกม (Pre-game flow)
* **`class Menu`**
  * `displayLobby()`: แสดงผลหน้า Title Screen รอรับคำสั่ง
  * `fillApplication()`: จำลองระบบ HR Form ถามคำถามเพื่อเซ็ตระดับความยาก และคืนค่าเป็น `GameConfig`

### 📄 `ส่วนที่ 3 Game.h` และ `Game.cpp`
หัวใจหลักของเกมเพลย์ 
* **`class GameObject`** (Base Class)
  * `getId()`, `getName()`: จัดการข้อมูลพื้นฐานของ Entity
* **`class Player : public GameObject`** * `setCamera()`, `getCurrentCamera()`: จัดการเรื่องตำแหน่งกล้องวงจรปิด
  * `useEnergy()`, `getEnergy()`: จัดการระบบแบตเตอรี่
* **`class Room : public GameObject`** * `setAnomaly()`, `getAnomaly()`: เปลี่ยนและเช็คสถานะความผิดปกติของห้องนั้นๆ
  * `updateState()`: ฟังก์ชัน (Polymorphism) สำหรับรองรับการใส่รูประบบ Anomaly
* **`class Game`** (Controller)
  * `Game(GameConfig _config)`: Constructor รับตั้งค่าความยาก
  * `render(int remainingTime)`: วาดหน้าจอ UI, กล้องวงจรปิด, และแจ้งเตือน
  * `processInput()`: รับค่าคีย์บอร์ด (A, D, F, S)
  * `update()`: จัดการ Game Loop, เวลา, สุ่ม Anomaly, และเช็คเงื่อนไขแพ้/ชนะ

### 📄 `ส่วนที่ 4 main.cpp`
* **`int main()`**: จุดเริ่มต้นโปรแกรม เรียก Menu รับค่า Config ส่งให้ Game และรันวนลูปหลัก

---

## 🔄 3. Flow การเล่นของโปรแกรม

1. **Lobby & Setup:** ผู้เล่นเริ่มจากหน้าจอ Title เข้าสู่การกรอกใบสมัครงานเพื่อกำหนด `GameConfig`
2. **Gameplay Loop (00:00 - 06:00 AM):** * เทิร์นละ 2 นาทีในโลกจริง
   * ระบบสุ่ม Anomaly ตามเปอร์เซ็นต์ความยาก
   * ผู้เล่นคุมกล้องวงจรปิดและใช้พลังงานล็อกประตูห้องที่มี Anomaly
3. **Turn Check:** หากหมดเวลา/ข้ามเทิร์น แล้วมี Anomaly หลุด ระบบจะบวกค่าความผิดพลาด (Ignored Anomaly)
4. **Resolution:** * หากค่าความผิดพลาดถึงขีดจำกัด -> Jumpscare & Game Over
   * หากรอดถึง 06:00 AM -> Win

---

## 🛠️ 4. วิธีการคอมไพล์และทดสอบ (How to Compile & Run)

**การคอมไพล์:** เปิด Terminal ในโฟลเดอร์โปรเจกต์ แล้วใช้คำสั่งเพื่อมัดรวมไฟล์:
```bash
g++ main.cpp Game.cpp Menu.cpp -o game