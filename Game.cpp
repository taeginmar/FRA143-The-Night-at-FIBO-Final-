#include "testSFML.cpp"
#include "BtwTurn.cpp"
#include <string>

bool Play() {
    RandomEvent gameSystem;
    bool Jump = false;
    bool GO = false;
    std::string Time = "11 PM";
    bool Btw = BtwTurn(Time);
    if(Btw == false) {
        return false;
    }
    bool status = PlayableTurn0(gameSystem);
    if(status == false) {
        return false;
    }

    Time = "0 AM";
    Btw = BtwTurn(Time);
    if(Btw == false) {
        return false;
    }
    status = PlayableTurn(gameSystem);
    if(status == false) {
        return false;
    }
    
    //-------------------------------------
    
   bool isPassed = gameSystem.Checker(); 

    if (!isPassed) {
        Jump = JumpAndOver();
        GO = GameOver();
        return false; 
    }


    Time = "1 AM";
    Btw = BtwTurn(Time);
    if(Btw == false) {
        return false;
    }
    status = PlayableTurn(gameSystem);
    if(status == false) {
        return false;
    }

    isPassed = gameSystem.Checker(); 

    if (!isPassed) {
        Jump = JumpAndOver();
        GO = GameOver();
        return false; 
    }

    //-------------------------------------

    Time = "2 AM";
    Btw = BtwTurn(Time);
    if(Btw == false) {
        return false;
    }
    status = PlayableTurn(gameSystem);
    if(status == false) {
        return false;
    }

    isPassed = gameSystem.Checker(); 

    if (!isPassed) { 
        Jump = JumpAndOver();
        GO = GameOver(); 
        return false; 
    }

    //------------------------------------------

    Time = "3 AM";
    Btw = BtwTurn(Time);
    if(Btw == false) {
        return false;
    }
    status = PlayableTurn(gameSystem);
    if(status == false) {
        return false;
    }

    isPassed = gameSystem.Checker(); 

    if (!isPassed) {
        Jump = JumpAndOver();
        GO = GameOver(); 
        return false; 
    }

    //------------------------------------------

    Time = "4 AM";
    Btw = BtwTurn(Time);
    if(Btw == false) {
        return false;
    }
    status = PlayableTurn(gameSystem);
    if(status == false) {
        return false;
    }

    isPassed = gameSystem.Checker(); 

    if (!isPassed) { 
        Jump = JumpAndOver();
        GO = GameOver(); 
        return false; 
    }

    //------------------------------------------    

    Time = "5 AM";
    Btw = BtwTurn(Time);
    if(Btw == false) {
        return false;
    }
    status = PlayableTurn(gameSystem);
    if(status == false) {
        return false;
    }

    isPassed = gameSystem.Checker(); 

    if (!isPassed) { 
        Jump = JumpAndOver();
        GO = GameOver(); 
        return false; 
    }

    //------------------------------------------

    Time = "6 AM";
    Btw = BtwTurn(Time);
    if(Btw == false) {
        return false;
    }
    Btw = YouWin();
    if(Btw == false) {
        return false;
    }
    return false;
}