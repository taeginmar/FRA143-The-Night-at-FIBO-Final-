#include "config.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

class GameObject{
protected:
    int id_;
    std::string name_;
public:
    GameObject(): id_(0), name_(""){}

    virtual ~GameObject() {}
    virtual void UpdateState() = 0;
    std::string getName();
};

class Room : public GameObject{
private:
    bool hasAnomaly_;
public:
    Room(int id, std::string name) : GameObject(), hasAnomaly_(false){}
    void setAnomaly(bool status) {hasAnomaly_ = status;}
    bool getAnomaly() {return hasAnomaly_;}
    void displayView();

    bool isLocked_ = false;
    void toggleDoor() {isLocked_ = !isLocked_; }
    bool getIsLocked() {return isLocked_;}
    void setDoor(bool state) {isLocked_ = state;}
    void UpdateState() override;
};

class Player : public GameObject{
private:
    int energy_;
    int cam_number_;
public:
    Player(int id, std::string name, int energy) : GameObject(), energy_(energy), cam_number_(0){}
    bool UseEnergy();
    void setCam(int index);
    int getCam();
    int getEnergy();
    void UpdateState() override;
};

class Game{
private:
    Player player;
    std::vector<Room> rooms_;
    int currentTurn;
    int maxTurns;
    bool isRunning;

    bool isPreparationPhase = true;
    int prepDuration = 45;

    time_t turnStartTime;
    int turnDuration;
    int ignoredAnomalyCount;
    int jumpscareThreshold;

    int lastRenderedSecond;
    bool needsRedraw;

    bool isJumpscarePending;
    int cameraSwitchCountAfterPending;
    int jumpscareTriggerTarget; // จำนวนคลิกเป้าหมายที่จะเจอแจ็กพ็อต

    bool isFakeGlitchScheduled; 
    int fakeGlitchTimeTarget;   
    bool fakeGlitchTriggered;

    int totalAnomaliesSpawned;    // นับผีที่โผล่มาทั้งหมด
    int totalAnomaliesResolved;   // นับผีที่เราล็อกประตูขังไว้สำเร็จ
    int totalAnomaliesMissed;     // นับผีที่เราพลาดปล่อยหลุด

    GameConfig config;

public:
    Game(GameConfig _config);
    void render(int remainingTime);
    void processInput();
    void update();
    bool getIsRunning();
    void executePolymorph(GameObject& obj);
    
    void triggerJumpScare();
    void triggerMissionFailed();
    void triggerWinScreen();
};