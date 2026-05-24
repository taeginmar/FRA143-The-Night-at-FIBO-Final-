#include <string>
#include <vector>
#include <random>
#include <memory>
#include <iostream>

class Player {
private:
    int energy_;
    bool IsAlive_;
public:
    Player(int energy,bool IsAlive) : energy_(energy), IsAlive_(IsAlive) {
        this-> energy_ = 0;
        this-> IsAlive_ = true;
    }

    void setEnergy(int val) { energy_ = val; }


    int getEnergy() { return energy_; } 
    
};

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
                bool fate = dice(rng);
                (*r)->SetIsAnamoly(fate);
                if (fate == true) {
                    std::vector<std::string> pic_ = ((*r)->GetAnamolyPic());
                    if(pic_.size() != 0){
                        std::uniform_int_distribution<int> PicDice(0,pic_.size()-1);
                        int RandomPicIndex = PicDice(rng);
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