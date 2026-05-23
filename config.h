#ifndef CONFIG_H
#define CONFIG_H

struct GameConfig {
    int anomalySpawnChance; // โอกาสเกิดผี (เปอร์เซ็นต์)
    int jumpscareThreshold; // พลาดได้กี่ครั้งก่อนโดนหมายหัว
    bool enableJumpscare;   // ยินยอมรับความเสี่ยงหรือไม่
    int maxEnergy;
};

#endif