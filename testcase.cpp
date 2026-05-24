#include <iostream>
#include <vector>
#include <string>
#include "Random.cpp" 

void SetTurn0 (RandomEvent& gameSystem) {

    gameSystem.ClearRoom();

    //addroom(int id_, bool IsAnamoly, double anachang, std::string normalpic, std::vector<std::string> anamolypic,std::string PicNow, bool lock)
    gameSystem.addroom(1, false, 0.0, "Room1/A_Normal.png", {"Room1/Doll_Appear.png","Room1/Object_Appear.png","Room1/Table_Disappear.png","Room1/Table_Turn.png","Room1/Table_Used.png"}, "Room1/A_Normal.png", false);
    gameSystem.addroom(2, false, 0.0, "Room2/A_Normal.png", {"Room2/Object_Appear.png", "Room2/Showdow_Appear.png","Room2/Who_.png","Room2/Who2_.png","Room2/Who3_.png"}, "Room2/A_Normal.png", false);
    gameSystem.addroom(3, false, 0.0, "Room3/A_Normal.png", {"Room3/Door_Open.png","Room3/Object_Drop.png","Room3/Object_Move.png","Room3/Who_.png","Room3/Who2_.png"}, "Room3/A_Normal.png", false);
    gameSystem.addroom(4, false, 0.0, "Room4/A_Normal.png", {"Room4/Paper_Move.png", "Room4/PingPong_.png", "Room4/Shoe_Appear.png", "Room4/Shoe2_Appear.png","Room4/Who_.png"},"Room4/A_Normal.png", false);

    //std::cout << "--- STARTING RANDOM EVENT TURN 0 TEST ---" << std::endl;
    gameSystem.RunRandom();
    //gameSystem.ShowResults();

}

void SetTurn (RandomEvent& gameSystem) {

    gameSystem.ClearRoom();

    //addroom(int id_, bool IsAnamoly, double anachang, std::string normalpic, std::vector<std::string> anamolypic,std::string PicNow, bool lock)
    gameSystem.addroom(1, false, 0.65, "Room1/A_Normal.png", {"Room1/Doll_Appear.png","Room1/Object_Appear.png","Room1/Table_Disappear.png","Room1/Table_Turn.png","Room1/Table_Used.png"}, "Room1/A_Normal.png", false);
    gameSystem.addroom(2, false, 0.65, "Room2/A_Normal.png", {"Room2/Object_Appear.png", "Room2/Showdow_Appear.png","Room2/Who_.png","Room2/Who2_.png","Room2/Who3_.png"}, "Room2/A_Normal.png", false);
    gameSystem.addroom(3, false, 0.65, "Room3/A_Normal.png", {"Room3/Door_Open.png","Room3/Object_Drop.png","Room3/Object_Move.png","Room3/Who_.png","Room3/Who2_.png"}, "Room3/A_Normal.png", false);
    gameSystem.addroom(4, false, 0.65, "Room4/A_Normal.png", {"Room4/Paper_Move.png", "Room4/PingPong_.png", "Room4/Shoe_Appear.png", "Room4/Shoe2_Appear.png","Room4/Who_.png"},"Room4/A_Normal.png", false);

    //std::cout << "--- STARTING RANDOM EVENT TEST 1 - 6  ---" << std::endl;
    gameSystem.RunRandom();
    //gameSystem.ShowResults();

}