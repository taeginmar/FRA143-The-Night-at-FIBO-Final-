#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

//GameObject Constructor
std::string GameObject :: getName() {return name_;}

void Room::displayView(){
    if (hasAnomaly_) {
        std::cout << "สถานะ: [ตรวจพบความผิดปกติ ]" << std::endl; 
    } else {
        std::cout << "สถานะ: [ ปกติ ]" << std::endl;
    }

    if(isLocked_){
        std::cout << "ประตู:  [ ล็อก ]" << std::endl;
    }else{
        std::cout << "ประตู:  [ ปลดล็อก ]" << std::endl;
    }
}

void Room::UpdateState(){
    hasAnomaly_ = true;
}

//Player
bool Player::UseEnergy(){
    if(energy_ > 0){
        energy_ --;
        return true;
    }
    return false;
}

void Player::setCam(int index) {cam_number_ = index;}
int Player::getCam() {return cam_number_;}
int Player::getEnergy() {return energy_;}
void Player::UpdateState(){}

Game::Game(GameConfig _config) : player(1, "Guard", _config.maxEnergy), currentTurn(1), isRunning(true){
    std::srand(time(0));
    config = _config;

    maxTurns = 6;

    isPreparationPhase = true;
    turnDuration = 45;

    turnStartTime = time(0);
    ignoredAnomalyCount = 0;   
    jumpscareThreshold = config.jumpscareThreshold; 

    totalAnomaliesSpawned = 0;
    totalAnomaliesResolved = 0;
    totalAnomaliesMissed = 0;
    
    isJumpscarePending = false;
    cameraSwitchCountAfterPending = 0;
    jumpscareTriggerTarget = 0;
    lastRenderedSecond = -1;
    needsRedraw = true;

    // สุ่มโอกาสเกิดเหตุการณ์กล้องค้างหลอก (Fake Glitch)
    isFakeGlitchScheduled = false;
    fakeGlitchTriggered = false;

    // ตั้งชื่อห้องตามสถานที่จริงของตึก FIBO
    rooms_.push_back(Room(101, "ห้องแล็ปหมายเลย 162"));
    rooms_.push_back(Room(102, "โถงนั่งเล่น"));
    rooms_.push_back(Room(103, "ห้องประชุมหมายเลข 130"));
    rooms_.push_back(Room(104, "ชั้น 1 มุมตูู้กดน้ำ"));

    for (size_t i = 0; i < rooms_.size(); i++) {
        rooms_[i].setAnomaly(false);
        rooms_[i].setDoor(false);
    }
}

bool Game::getIsRunning() {return isRunning;}

void Game::executePolymorph(GameObject& obj){
    obj.UpdateState();
}

void Game::render(int remainingTime){
    if (!needsRedraw) return;

    system("cls"); 
    
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;

    std::cout << "========================================" << std::endl;
    // --- ปรับปรุงการแสดงผลส่วนหัว ---
    if (isPreparationPhase) {
        std::cout << " เวลา:   00:00 AM | [ ช่วงเตรียมตัวก่อนเริ่มงาน ]" << std::endl;
    } else {
        std::cout << " เวลา:   0" << currentTurn - 1 << ":00 AM | : " << currentTurn << " / " << maxTurns << std::endl;
    }
    std::cout << " เวลาที่เหลือ: 0" << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << std::endl;
    // ---------------------------------
    
    std::cout << " พลังงาน: [";
    for (int i = 0; i < player.getEnergy(); i++) std::cout << "-";
    for (int i = player.getEnergy(); i < config.maxEnergy; i++) std::cout << " ";
    std::cout << "] (" << player.getEnergy() << "/" << config.maxEnergy << ")" << std::endl;
    std::cout << "========================================" << std::endl;
    
    std::cout << " กล้องวงจรปิด: \n";
    for (size_t i = 0; i < rooms_.size(); i++) {
        if (i == (size_t)player.getCam()) std::cout << "  >[" << rooms_[i].getName() << "]< \n"; 
        else std::cout << "   [" << rooms_[i].getName() << "]  \n"; 
    }
    std::cout << "----------------------------------------" << std::endl;
    
    // ในช่วงเตรียมตัวจะแสดงคำเตือนพิเศษแทนสถานะปกติ/ผิดปกติ
    if (isPreparationPhase) {
        std::cout << "สถานะ: [ ตรวจสอบระบบ : โปรดจดจำสภาพแวดล้อม ]" << std::endl;
        std::cout << "ประตู:  [ ระบบพร้อมทำงาน ]" << std::endl;
    } else {
        rooms_[player.getCam()].displayView();
    }
    
    std::cout << "========================================" << std::endl;
    if (isPreparationPhase) {
        std::cout << "คำสั่ง: [A] กล้องก่อนหน้า | [D] กล้องถัดไป" << std::endl;
        std::cout << "       [S] ข้ามช่วงเตรียมตัว (เริ่มกะงานทันที)" << std::endl;
    } else {
        std::cout << "คำสั่ง: [A] กล้องก่อนหน้า | [D] กล้องถัดไป" << std::endl;
        std::cout << "       [F] ล็อกประตู     | [S] ข้ามเทิร์นนี้" << std::endl; 
    }
    std::cout << ">> กดปุ่มเพื่อสั่งการ <<" << std::endl;

    needsRedraw = false;
}

void Game::processInput() {
    if (_kbhit()) {
        char input = _getch(); 
        input = toupper(input);

        if (isJumpscarePending && (input == 'A' || input == 'D')) {
            cameraSwitchCountAfterPending++;
            if (cameraSwitchCountAfterPending >= jumpscareTriggerTarget) {
                triggerJumpScare(); 
                isJumpscarePending = false;
                needsRedraw = true;
                return; 
            }
        }

        if (input == 'A'){
            int currentCam = player.getCam();
            if (currentCam == 0) player.setCam(rooms_.size() - 1);
            else player.setCam(currentCam - 1);
            needsRedraw = true; 
        }
        else if (input == 'D') {
            int nextCam = (player.getCam() + 1) % rooms_.size();
            player.setCam(nextCam);
            needsRedraw = true; 
        }
        else if (input == 'F') {
            needsRedraw = true; 

            rooms_[player.getCam()].toggleDoor();

            if (rooms_[player.getCam()].getIsLocked()) {
                if (player.UseEnergy()) {
                    std::cout << "\n>> ล็อกประตูสำเร็จ <<" << std::endl;
                    Sleep(800);
                } else {
                    std::cout << "\n>> พลังงานไม่เพียงพอ <<" << std::endl;
                    rooms_[player.getCam()].toggleDoor(); // พลังงานไม่พอ ประตูเด้งกลับไปปลดล็อก
                    Sleep(800);
                }
            } else {
                std::cout << "\n>> ปลดล็อกประตู <<" << std::endl;
                Sleep(800);
            }
        }
        else if (input == 'S') {
            turnStartTime = 1; 
        }
    }
}

void Game::update() {
    if (!isRunning) return;

    time_t currentTime = time(0);
    int elapsedTime = (turnStartTime == 0 || turnStartTime == 1) ? turnDuration : (currentTime - turnStartTime);
    int remainingTime = turnDuration - elapsedTime;
 
    if (!isPreparationPhase && isFakeGlitchScheduled && !fakeGlitchTriggered && remainingTime <= fakeGlitchTimeTarget && turnStartTime != 0 && turnStartTime != 1) {
        fakeGlitchTriggered = true; 

        system("cls");
        std::cout << " [ข้อผิดพลาดร้ายแรง] : ระบบกล้องค้าง" << std::endl;
        std::cout << ">> ไม่พบสัญญาณตอบรับ กำลังพยายามเชื่อมต่อใหม่..." << std::endl;
        std::cout << "################################################" << std::endl;
        std::cout << "# ( ) ( ) #" << std::endl;
        std::cout << "# > [ กำลังรีบูตระบบ... ] < #" << std::endl;
        std::cout << "# ################################################" << std::endl;
        std::cout << "\a"; 
        
        Sleep(1500); 

        needsRedraw = true;
        lastRenderedSecond = -1;
        return;
    }

    if (remainingTime != lastRenderedSecond && turnStartTime != 0 && turnStartTime != 1) {
        lastRenderedSecond = remainingTime;
        needsRedraw = true;
    }

    if (turnStartTime == 0 || turnStartTime == 1 || remainingTime <= 0) {
        if (isPreparationPhase) {
            isPreparationPhase = false; // ปิดโหมดเตรียมตัว
            
            system("cls");
            std::cout << "========================================" << std::endl;
            std::cout << " [ประกาศจากระบบ] : หมดเวลาเตรียมตัว" << std::endl;
            std::cout << " >> กะดึกของคุณได้เริ่มต้นขึ้นหลังจากนี้ << " << std::endl;
            std::cout << "========================================" << std::endl;
            Sleep(2500);

            currentTurn = 1;
            turnDuration = 60; // ปรับให้เหลือ 60 วิ ตามเอกสารของคุณ
            turnStartTime = time(0);
            lastRenderedSecond = -1;
            needsRedraw = true;

            for (size_t i = 0; i < rooms_.size(); i++) {
                if (rand() % 100 < config.anomalySpawnChance) {
                    executePolymorph(rooms_[i]); 
                    totalAnomaliesSpawned++;
                }
            }
            return;
        }

        if (isJumpscarePending) {
            triggerJumpScare();
            isJumpscarePending = false;
            return;
        }

        system("cls");
        std::cout << "========================================" << std::endl;
        if (turnStartTime == 0) {
            std::cout << " [แจ้งเตือนระบบ] : เคลียร์ความผิดปกติเรียบร้อย" << std::endl;
            std::cout << " ระบบประตูกำลังรีเซ็ตสำหรับชั่วโมงถัดไป..." << std::endl;
        } else if (turnStartTime == 1) {
            std::cout << " [ประกาศจากระบบ] : กำลังข้ามเวลา..." << std::endl;
            std::cout << " คุณข้ามเวลาการเฝ้าระวังที่เหลือในชั่วโมงนี้" << std::endl;
        } else {
            std::cout << " [คำเตือนระบบ] : หมดเวลา" << std::endl;
            std::cout << " กำลังสลับไปยังกะการเฝ้าระวังถัดไป..." << std::endl;
        }
        std::cout << "========================================" << std::endl;
        Sleep(2000);

        int missedThisTurn = 0;

        for (size_t i = 0; i < rooms_.size(); i++) {
            if (rooms_[i].getAnomaly()) {
                if(!rooms_[i].getIsLocked() && turnStartTime != 0){
                    missedThisTurn++;
                    totalAnomaliesMissed++;
                }
                else if(rooms_[i].getIsLocked() && turnStartTime != 0){
                    totalAnomaliesResolved++;
                }
                rooms_[i].setAnomaly(false);
            }
            rooms_[i].setDoor(false);
        }

        if (missedThisTurn > 0) {
            ignoredAnomalyCount += missedThisTurn;

            if (ignoredAnomalyCount >= jumpscareThreshold) {
                triggerJumpScare();
                triggerMissionFailed();
                return;
            }
            else if(!isJumpscarePending){
                isJumpscarePending = true;
                jumpscareTriggerTarget = (rand() % 4) + 2;
                cameraSwitchCountAfterPending = 0;
            }
        }

        currentTurn++;
    
        turnStartTime = time(0);
        lastRenderedSecond = -1;
        needsRedraw = true;

        if (currentTurn > maxTurns) {
            triggerWinScreen();
            return;
        }

        isFakeGlitchScheduled = (rand() % 100 < 35); 
        fakeGlitchTimeTarget = (rand() % 40) + 10;   
        fakeGlitchTriggered = false;

        for (size_t i = 0; i < rooms_.size(); i++) {
            if (rand() % 100 < config.anomalySpawnChance) {
                executePolymorph(rooms_[i]); 
                totalAnomaliesSpawned++;
            }
        }
    } else {
        render(remainingTime);
    }
}

void Game::triggerJumpScare() {
    system("cls");
    std::cout << " [ข้อผิดพลาดร้ายแรง] : ระบบกล้องค้าง" << std::endl;
    std::cout << ">> ไม่พบสัญญาณตอบรับ กำลังพยายามเชื่อมต่อใหม่..." << std::endl;
    std::cout << "################################################" << std::endl;
    std::cout << "# ( ) ( ) #" << std::endl;
    std::cout << "# > [ Main Hall ] < ระบบขัดข้อง #" << std::endl;
    std::cout << "# ################################################" << std::endl;
    
    Sleep(1500); // 1.5 วินาทีมรณะที่ผู้เล่นจะจ้องหน้าจองงๆ ว่า "บัคเหรอ?"
    
    std::cout << "\a"; 
    system("cls");
    std::cout << "#################################################" << std::endl;
    std::cout << "#                                               #" << std::endl;
    std::cout << "#                                               #" << std::endl;
    std::cout << "# (X) (X) #" << std::endl;
    std::cout << "# A #" << std::endl;
    std::cout << "# \\_________________/ #" << std::endl;
    std::cout << "#                                               #" << std::endl;
    std::cout << "# >> กำลังกู้คืนสัญญาณ... << #" << std::endl;
    std::cout << "#################################################" << std::endl;
    Sleep(2000);
}

void Game::triggerMissionFailed(){
    system("cls");
    std::cout << "=========================================================\n";
    std::cout << "              [ REJECTED : DEAD RAGDOLL ]                \n";
    std::cout << "=========================================================\n\n";
    std::cout << " ระบบรักษาความปลอดภัยของตึก FIBO ล้มเหลว\n";
    std::cout << " --- STATUS: REJECTED FROM LIVING --- \n";
    std::cout << "=========================================================\n";
    isRunning = false; // อันนี้คือตายของจริง เกมจบ
}

void Game::triggerWinScreen() {
    system("cls");
    
    // คำนวณคะแนนประสิทธิภาพ
    int score = 0;
    if (totalAnomaliesSpawned > 0) {
        score = (totalAnomaliesResolved * 100) / totalAnomaliesSpawned;
    } else {
        score = 100; // ถ้าผีไม่ออกเลย ถือว่าดวงดี ได้ 100%
    }

    // ตัดเกรด
    char grade = 'F';
    if (score == 100) grade = 'A';
    else if (score >= 80) grade = 'B';
    else if (score >= 60) grade = 'C';
    else if (score >= 50) grade = 'D';

    // ตั้งเกณฑ์ผ่านที่ 70% ขึ้นไปถึงจะได้เงิน
    bool isPassed = (score >= 70); 

    std::cout << "=========================================================\n";
    std::cout << "             [ CERTIFICATE OF EVALUATION ]               \n";
    std::cout << "=========================================================\n\n";
    std::cout << " เอกสารประเมินผลการปฏิบัติงานประจำกะดึก (00:00 - 06:00 AM)\n";
    std::cout << " หน่วยงาน: อาคารสถาบันวิทยาการหุ่นยนต์ภาคสนาม (FIBO)\n\n";
    
    std::cout << " สรุปผลการปฏิบัติการ:\n";
    std::cout << " - ความผิดปกติที่เกิดขึ้นทั้งหมด:         " << totalAnomaliesSpawned << " เหตุการณ์\n";
    std::cout << " - ตรวจพบและควบคุมสำเร็จ:            " << totalAnomaliesResolved << " เหตุการณ์\n";
    std::cout << " - ความผิดปกติที่เล็ดลอดระบบ:           " << totalAnomaliesMissed << " เหตุการณ์\n";
    std::cout << " -------------------------------------------------------\n";
    std::cout << " ประสิทธิภาพการทำงานสุทธิ: " << score << "% (ประเมินเกรด: " << grade << ")\n\n";
    
    if (isPassed) {
        std::cout << " [ ข้อสรุปจากฝ่ายทรัพยากรบุคคล: ผ่านเกณฑ์การประเมิน (70%) ]\n";
        std::cout << " -> อนุมัติการเบิกจ่ายค่าตอบแทนตามสัญญาจ้างครบถ้วน\n";
        std::cout << " -> ผู้ปฏิบัติงานมีคุณสมบัติเหมาะสมสำหรับกะงานถัดไป\n";
    } else {
        std::cout << " [ ข้อสรุปจากฝ่ายทรัพยากรบุคคล: ไม่ผ่านเกณฑ์ขั้นต่ำขององค์กร ]\n";
        std::cout << " -> ผู้ปฏิบัติงานเอาชีวิตรอดได้ แต่อัตราความผิดพลาดเกินมาตรฐานความปลอดภัย\n";
        std::cout << " -> ระงับการจ่ายค่าตอบแทนทั้งหมด ตามมาตราการความปลอดภัย\n";
        std::cout << " -> เพิกถอนสิทธิการปฏิบัติงานในพื้นที่ FIBO ถาวร\n";
    }

    std::cout << "\n=========================================================\n";
    std::cout << " --- STATUS: SHIFT CONCLUDED --- \n";
    std::cout << "=========================================================\n";
    isRunning = false; 
}