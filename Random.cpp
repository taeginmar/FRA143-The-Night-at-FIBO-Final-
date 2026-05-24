#include <string>
#include <vector>
#include <random>
#include <memory>
#include <iostream>

class Room {
    public:
        Room(int id_, bool IsAnamoly_, double anachang_, std::string normalpic_, std::vector<std::string> anamolypic_,std::string PicNow_, bool lock_)
        : id(id_) ,IsAnamoly(IsAnamoly_), anachang(anachang_), normalpic(normalpic_), anamolypic(anamolypic_), PicNow(PicNow_),lock(lock_) {
        }

        int GetId() const {return id;}
        bool GetIsAnamoly() const {return IsAnamoly;}
        double GetChang() const {return anachang;}
        std::string GetNormalPic() const {return normalpic;}
        std::vector<std::string> GetAnamolyPic() const {return anamolypic;}
        std::string GetPicNow() const {return PicNow;}
        bool GetLock() const {return lock;}

        void SetIsAnamoly(bool status) {
            IsAnamoly = status;
        } 

        void SetPicNow(std::string PicSelected) {
            PicNow = PicSelected;
        }

        void SetLock(bool jj) {
            lock = jj;
        }

    private:
        int id;
        bool IsAnamoly;
        double anachang;
        std::string normalpic;
        std::vector<std::string> anamolypic;
        std::string PicNow;
        bool lock;
};

class SetRoom : public Room {
    public:
        SetRoom(int id_, bool IsAnamoly_, double anachang_, std::string normalpic_, std::vector<std::string> anamolypic_,std::string PicNow_, bool lock_):Room(id_, anachang_, normalpic_, anamolypic_) {
        }

        bool GetIsAnamoly() const {return IsAnamoly;}
        std::string GetPicNow() const {return PicNow;}
        bool GetLock() const {return lock;}

        void SetIsAnamoly(bool status) {
            IsAnamoly = status;
        } 

        void SetPicNow(std::string PicSelected) {
            PicNow = PicSelected;
        }

        void SetLock(bool jj) {
            lock = jj;
        }
    private:
        bool IsAnamoly;
        std::string PicNow;
        bool lock;
};

class RandomEvent {
    public:
        RandomEvent() {
            std::random_device rd;
            rng = std::mt19937(rd());
            
        }

        void addroom(int id_, bool IsAnamoly, double anachang, std::string normalpic, std::vector<std::string> anamolypic,std::string PicNow, bool lock) {
            allrooms_.emplace_back(std::make_unique<Room>(id_, IsAnamoly, anachang,  normalpic, anamolypic, PicNow, lock));
        }

        void RunRandom() {
            std::string PicSelected = "none";
            for(auto r = allrooms_.begin(); r != allrooms_.end(); ++r){
                std::bernoulli_distribution dice((*r)->GetChang());
                bool fate = dice(rng); // ทอยลูกเต๋าเพื่อกำหนดสถานะ Anomaly ของห้อง โดยใช้ความน่าจะเป็นที่กำหนดในแต่ละห้อง 0.0 - 1.0
                (*r)->SetIsAnamoly(fate); // กำหนดสถานะ Anomaly ตามผลลัพธ์ของการทอยลูกเต๋า

                if (fate == true) {
                    std::vector<std::string> pic_ = ((*r)->GetAnamolyPic()); //ดึงชื่อภาพ Anomaly ที่เป็นไปได้ของห้องนั้นๆ มาเก็บไว้ในตัวแปร pic_
                    if(pic_.size() != 0){ //ตรวจสอบว่ามีภาพ Anomaly รึเปล่า
                        std::uniform_int_distribution<int> PicDice(0,pic_.size()-1);//กำหนดขอบเขตการสุ่ม
                        int RandomPicIndex = PicDice(rng); //ใช้ rng เป็นตัวสุ่มค่า index
                        PicSelected = pic_[RandomPicIndex];
                        (*r)->SetPicNow(PicSelected);

                    }
                }

                else {
                    PicSelected = (*r)->GetNormalPic();
                    (*r)->SetPicNow(PicSelected);
                }

            }
        }

        void ShowResults() {
            for (auto r = allrooms_.begin(); r != allrooms_.end(); ++r ) {
            std::cout << "Room ID: " << (*r)->GetId() 
                  << " | IsAnomaly: " << ((*r)->GetIsAnamoly() ? "TRUE " : "FALSE") 
                  << " | Image: " << (*r)->GetPicNow() << std::endl;
            }
        }

        std::string GetRoomIndex(int index) const {
            auto& targetRoom = allrooms_.at(index);
            std::string ImageName = targetRoom->GetPicNow();
            
            return ImageName;
        }

        bool GetRoomLocker(int index) const {
            return allrooms_.at(index)->GetLock();
        }

        bool SetRoomLocker(int index, bool status) {
            allrooms_.at(index)->SetLock(status);
            return -1;
        }

       bool Checker() {
        for (const auto& room : allrooms_) {
            if (room->GetIsAnamoly() == true && room->GetLock() == false) {
                std::cout<<"NGO";
                return false; // แพ้ทันที!
                }
            }
            return true;
        }

        void ClearRoom() {
            allrooms_.clear();
        }
    private:
        std::vector<std::unique_ptr<Room>> allrooms_;
        std::mt19937 rng;
        
};