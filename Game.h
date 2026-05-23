#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <ctime>

//Fundamental Parameters and Configurations
struct GameConfig {
    std::string difficulty;  
    bool enableJumpscare;   
    int maxEnergy;           
    int anomalySpawnChance;   
    int jumpscareThreshold;  
};

class GameObject {
protected:
    std::string name_;
public:
    GameObject(std::string name) : name_(name) {}
    virtual void UpdateState() = 0; // Pure Virtual Function
    std::string getName() { return name_; }
};

class Room : public GameObject {
private:
    int id_;
    bool hasAnomaly_;
    bool isLocked_;
public:
    Room(int id, std::string name) : GameObject(name), id_(id), hasAnomaly_(false), isLocked_(false) {}
    
    void UpdateState() override { hasAnomaly_ = true; }
    void setAnomaly(bool status) { hasAnomaly_ = status; }
    bool getAnomaly() { return hasAnomaly_; }
    
    void toggleDoor() { isLocked_ = !isLocked_; }
    void setDoor(bool status) { isLocked_ = status; }
    bool getIsLocked() { return isLocked_; }
    
    void displayView(); //show view of the room 
};

class Player : public GameObject {
private:
    int energy_;
    int cam_number_;
public:
    Player(int id, std::string name, int energy) : GameObject(name), energy_(energy), cam_number_(0) {}
    
    void UpdateState() override {}
    void setEnergy(int val) { energy_ = val; }
    int getEnergy() { return energy_; }
    bool useEnergy(); 
    
    void setCam(int index) { cam_number_ = index; }
    int getCam() { return cam_number_; }
};

class Game {
private:
    Player player;
    std::vector<Room> rooms_;
    GameConfig config;
    
    int currentTurn;
    int maxTurns;
    int remainingTime;
    bool isRunning;
    bool needsRedraw;
    bool isPreparationPhase;

    int turnAnomalyCount[7];     // Number of anomalies for each turn (index 1-6)
    int totalAnomaliesInGame;    // Total anomalies 

    int totalAnomaliesSpawned;
    int totalAnomaliesResolved;
    int totalAnomaliesMissed;

public:
    Game(GameConfig _config);
    
    void run();
    void update();
    void processInput();
    bool getIsRunning() { return isRunning; }

    // AnomalySystem
    void setupAnomalyPlan();     // สุ่มความผิดปกดิล่วงหน้า
    void spawnInRooms(int count); // Spawn Anomaly ในแต่ละห้อง
    void checkEndTurn();         // สรุปผลท้ายเทิร์น
    void executePolymorph(GameObject& obj);

    // ShowAction
    void render();               // วาดหน้าจอ Terminal
    void showFakeGlitch();       // เอฟเฟกต์กล้องค้าง
    void triggerJumpScare();     // ฉากผีหลอก

    void triggerWinScreen();
    void triggerMissionFailed();
    void showGameOver();         // ฉากจบเกม
};

#endif