#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "testcase.cpp"


bool PlayableTurn0 (RandomEvent& gameSystem) {

    SetTurn0(gameSystem);

    sf::RenderWindow window(sf::VideoMode({1200,800}),"Window");
    sf::Texture roomTexture;
    sf::Color BgColor = sf::Color::Black;


    if (!roomTexture.loadFromFile("BG.png")) {
        std::cout << "Warning: BG.png not found!" << std::endl;
    }

    int RoomIndexNow = 0;

    sf::Sprite roomSprite(roomTexture);
    sf::Vector2u textureSize = roomTexture.getSize();
    float sizeX = 1200.f / static_cast<float>(textureSize.x);
    float sizeY = 800.f / static_cast<float>(textureSize.y);
    roomSprite.setScale({sizeX,sizeY});

    sf::Font gameFont;
    if(!gameFont.openFromFile("fonts/VT323-Regular.ttf")){}

    std::vector<sf::RectangleShape> RoomButton(4);

    RoomButton[0].setSize({60.f,40.f});
    RoomButton[0].setPosition({100.f,670.f});
    RoomButton[0].setFillColor(sf::Color(128, 128, 128));

    RoomButton[1].setSize({60.f,40.f});
    RoomButton[1].setPosition({200.f,670.f});
    RoomButton[1].setFillColor(sf::Color(128, 128, 128));

    RoomButton[2].setSize({60.f,40.f});
    RoomButton[2].setPosition({100.f,720.f});
    RoomButton[2].setFillColor(sf::Color(128, 128, 128));

    RoomButton[3].setSize({60.f,40.f});
    RoomButton[3].setPosition({200.f,720.f});
    RoomButton[3].setFillColor(sf::Color(128, 128, 128));

    std::vector<sf::Text> roomText;
    std::vector<std::string> roomID = {"CAM 1", "CAM 2", "CAM 3", "CAM 4"};
    for(int j = 0; j < 4; ++j){

        sf::Text text(gameFont,roomID[j], 16);

        text.setFillColor(sf::Color::White);
        sf::Vector2f RoomButtonPosi = RoomButton[j].getPosition();
        text.setPosition({RoomButtonPosi.x +15.f, RoomButtonPosi.y + 10.f});
        
        roomText.push_back(text);

    }

    std::string Image = gameSystem.GetRoomIndex(RoomIndexNow);

    if(roomTexture.loadFromFile(Image)){
        textureSize = roomTexture.getSize();
        roomSprite.setTexture(roomTexture,true);
        float sizeX = 1200.f / static_cast<float>(textureSize.x);
        float sizeY = 800.f / static_cast<float>(textureSize.y);
        roomSprite.setScale({sizeX,sizeY});
    }

    sf::RectangleShape locker({120.f,40.f});
    locker.setPosition({650.f,520.f});
    locker.setFillColor(sf::Color(128,128,128));

    sf::Text roomlocker(gameFont,"UNLOCKED",30);
    roomlocker.setPosition({660.f,520.f});
    roomlocker.setFillColor(sf::Color::Green);

    sf::RectangleShape Skiped({40.f,40.f});
    Skiped.setPosition({800.f,750.f});
    Skiped.setFillColor(sf::Color(128,128,128));

    sf::Text skiptext(gameFont,"SKIP",16);
    skiptext.setPosition({810.f,755.f});
    skiptext.setFillColor(sf::Color::Black);

    while(window.isOpen()){

        bool IslockerChange = false;

        bool IsRoomChange = false;

        while (const std::optional event = window.pollEvent())
        {
            if(event->is< sf::Event::Closed>()){
                window.close();
                return false;
            }

            if(const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>() ) {
                if(mouseClick->button == sf::Mouse::Button::Left){
                    sf::Vector2f MousePosi = window.mapPixelToCoords(mouseClick->position);
                    for(int i = 0 ; i < RoomButton.size(); ++i ) {
                        if(RoomButton[i].getGlobalBounds().contains(MousePosi)){
                            RoomIndexNow = i;
                            IsRoomChange = true;
                            break;
                        }
                    } 
                }

                if(mouseClick->button == sf::Mouse::Button::Left){
                    sf::Vector2f MousePosi = window.mapPixelToCoords(mouseClick->position);
                    if(locker.getGlobalBounds().contains(MousePosi)){
                        bool key = gameSystem.GetRoomLocker(RoomIndexNow);
                        if(key == false) {
                            gameSystem.SetRoomLocker(RoomIndexNow,true);
                            
                        }else{
                            gameSystem.SetRoomLocker(RoomIndexNow,false);
                            
                            
                        }
                        
                    }
                }

                if(mouseClick->button == sf::Mouse::Button::Left) {
                    sf::Vector2f MousePosi = window.mapPixelToCoords(mouseClick->position);
                    if(Skiped.getGlobalBounds().contains(MousePosi)){
                        window.close();
                    }    
                }

                
            }

            if(const auto* keypress =  event->getIf<sf::Event::KeyPressed>()){
                if(keypress->code == sf::Keyboard::Key::Num1){
                    RoomIndexNow = 0;
                    std::string Image = gameSystem.GetRoomIndex(RoomIndexNow);

                    if(roomTexture.loadFromFile(Image)){
                        textureSize = roomTexture.getSize();
                        roomSprite.setTexture(roomTexture,true);
                        float sizeX = 1200.f / static_cast<float>(textureSize.x);
                        float sizeY = 800.f / static_cast<float>(textureSize.y);
                        roomSprite.setScale({sizeX,sizeY});
                    }
                }
                if(keypress->code == sf::Keyboard::Key::Num2){
                    RoomIndexNow = 1;
                    std::string Image = gameSystem.GetRoomIndex(RoomIndexNow);

                    if(roomTexture.loadFromFile(Image)){
                        textureSize = roomTexture.getSize();
                        roomSprite.setTexture(roomTexture,true);
                        float sizeX = 1200.f / static_cast<float>(textureSize.x);
                        float sizeY = 800.f / static_cast<float>(textureSize.y);
                        roomSprite.setScale({sizeX,sizeY});
                    }
                }
                if(keypress->code == sf::Keyboard::Key::Num3){
                    RoomIndexNow = 2;
                    std::string Image = gameSystem.GetRoomIndex(RoomIndexNow);

                    if(roomTexture.loadFromFile(Image)){
                        textureSize = roomTexture.getSize();
                        roomSprite.setTexture(roomTexture,true);
                        float sizeX = 1200.f / static_cast<float>(textureSize.x);
                        float sizeY = 800.f / static_cast<float>(textureSize.y);
                        roomSprite.setScale({sizeX,sizeY});
                    }
                }
                if(keypress->code == sf::Keyboard::Key::Num4){
                    RoomIndexNow = 3;
                    std::string Image = gameSystem.GetRoomIndex(RoomIndexNow);

                    if(roomTexture.loadFromFile(Image)){
                        textureSize = roomTexture.getSize();
                        roomSprite.setTexture(roomTexture,true);
                        float sizeX = 1200.f / static_cast<float>(textureSize.x);
                        float sizeY = 800.f / static_cast<float>(textureSize.y);
                        roomSprite.setScale({sizeX,sizeY});
                    }
                }
            }
            
        }
        if(IsRoomChange) {
            std::string Image = gameSystem.GetRoomIndex(RoomIndexNow);

            if(roomTexture.loadFromFile(Image)){
                textureSize = roomTexture.getSize();
                roomSprite.setTexture(roomTexture,true);
                float sizeX = 1200.f / static_cast<float>(textureSize.x);
                float sizeY = 800.f / static_cast<float>(textureSize.y);
                roomSprite.setScale({sizeX,sizeY});
            }
        }
        bool RoomLockerNow = gameSystem.GetRoomLocker(RoomIndexNow);
        if( RoomLockerNow == true) {
            roomlocker.setPosition({675.f,520.f});
            roomlocker.setString("LOCKED");
            roomlocker.setFillColor(sf::Color::Red);
        }else {
            roomlocker.setPosition({662.f,520.f});
            roomlocker.setString("UNLOCKED");
            roomlocker.setFillColor(sf::Color::Green);
        }

        window.clear(BgColor);
        window.draw(roomSprite);

        for(const auto& i : RoomButton){
            window.draw(i);
        }

        for(const auto& t : roomText){
            window.draw(t);
        }

        window.draw(Skiped);
        window.draw(skiptext);

        window.display();
    }
    return true;
} 

bool PlayableTurn (RandomEvent& gameSystem) {

    SetTurn(gameSystem);
    
    
    sf::RenderWindow window(sf::VideoMode({1200,800}),"Window");
    sf::Texture roomTexture;
    sf::Color BgColor = sf::Color::Black;


    if (!roomTexture.loadFromFile("BG.png")) {
        std::cout << "Warning: BG.png not found!" << std::endl;
    }

    int RoomIndexNow = 0;

    sf::Sprite roomSprite(roomTexture);
    sf::Vector2u textureSize = roomTexture.getSize();
    float sizeX = 1200.f / static_cast<float>(textureSize.x);
    float sizeY = 800.f / static_cast<float>(textureSize.y);
    roomSprite.setScale({sizeX,sizeY});

    sf::Font gameFont;
    if(!gameFont.openFromFile("fonts/VT323-Regular.ttf")){}



    std::vector<sf::RectangleShape> RoomButton(4);

    RoomButton[0].setSize({60.f,40.f});
    RoomButton[0].setPosition({100.f,670.f});
    RoomButton[0].setFillColor(sf::Color(128, 128, 128));

    RoomButton[1].setSize({60.f,40.f});
    RoomButton[1].setPosition({200.f,670.f});
    RoomButton[1].setFillColor(sf::Color(128, 128, 128));

    RoomButton[2].setSize({60.f,40.f});
    RoomButton[2].setPosition({100.f,720.f});
    RoomButton[2].setFillColor(sf::Color(128, 128, 128));

    RoomButton[3].setSize({60.f,40.f});
    RoomButton[3].setPosition({200.f,720.f});
    RoomButton[3].setFillColor(sf::Color(128, 128, 128));

    std::vector<sf::Text> roomText;
    std::vector<std::string> roomID = {"CAM 1", "CAM 2", "CAM 3", "CAM 4"};
    for(int j = 0; j < 4; ++j){

        sf::Text text(gameFont,roomID[j], 16);

        text.setFillColor(sf::Color::White);
        sf::Vector2f RoomButtonPosi = RoomButton[j].getPosition();
        text.setPosition({RoomButtonPosi.x +15.f, RoomButtonPosi.y + 10.f});
        
        roomText.push_back(text);

    }

    std::string Image = gameSystem.GetRoomIndex(RoomIndexNow);

    if(roomTexture.loadFromFile(Image)){
        textureSize = roomTexture.getSize();
        roomSprite.setTexture(roomTexture,true);
        float sizeX = 1200.f / static_cast<float>(textureSize.x);
        float sizeY = 800.f / static_cast<float>(textureSize.y);
        roomSprite.setScale({sizeX,sizeY});
    }

    sf::RectangleShape locker({120.f,40.f});
    locker.setPosition({1000.f,580.f});
    locker.setFillColor(sf::Color(128,128,128));

    sf::Text roomlocker(gameFont,"UNLOCKED",30);
    roomlocker.setPosition({1100.f,585.f});
    roomlocker.setFillColor(sf::Color::Green);

    sf::RectangleShape Skiped({40.f,40.f});
    Skiped.setPosition({800.f,750.f});
    Skiped.setFillColor(sf::Color(128,128,128));

    sf::Text skiptext(gameFont,"PASS",16);
    skiptext.setPosition({810.f,755.f});
    skiptext.setFillColor(sf::Color::Black);

    while(window.isOpen()){

        bool IslockerChange = false;

        bool IsRoomChange = false;

        while (const std::optional event = window.pollEvent())
        {
            if(event->is< sf::Event::Closed>()){
                window.close();
                return false;
            }

            if(const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>() ) {
                if(mouseClick->button == sf::Mouse::Button::Left){
                    sf::Vector2f MousePosi = window.mapPixelToCoords(mouseClick->position);
                    for(int i = 0 ; i < RoomButton.size(); ++i ) {
                        if(RoomButton[i].getGlobalBounds().contains(MousePosi)){
                            RoomIndexNow = i;
                            IsRoomChange = true;
                            break;
                        }
                    } 
                }

                if(mouseClick->button == sf::Mouse::Button::Left){
                    sf::Vector2f MousePosi = window.mapPixelToCoords(mouseClick->position);
                    if(locker.getGlobalBounds().contains(MousePosi)){
                        bool key = gameSystem.GetRoomLocker(RoomIndexNow);
                        if(key == false) {
                            gameSystem.SetRoomLocker(RoomIndexNow,true);
                            
                        }else{
                            gameSystem.SetRoomLocker(RoomIndexNow,false);
                            
                            
                        }
                        
                    }
                }

                if(mouseClick->button == sf::Mouse::Button::Left) {
                    sf::Vector2f MousePosi = window.mapPixelToCoords(mouseClick->position);
                    if(Skiped.getGlobalBounds().contains(MousePosi)){
                        window.close();
                    }    
                }

                
            }

            if(const auto* keypress =  event->getIf<sf::Event::KeyPressed>()){
                if(keypress->code == sf::Keyboard::Key::Num1){
                    RoomIndexNow = 0;
                    std::string Image = gameSystem.GetRoomIndex(RoomIndexNow);

                    if(roomTexture.loadFromFile(Image)){
                        textureSize = roomTexture.getSize();
                        roomSprite.setTexture(roomTexture,true);
                        float sizeX = 1200.f / static_cast<float>(textureSize.x);
                        float sizeY = 800.f / static_cast<float>(textureSize.y);
                        roomSprite.setScale({sizeX,sizeY});
                    }
                }
                if(keypress->code == sf::Keyboard::Key::Num2){
                    RoomIndexNow = 1;
                    std::string Image = gameSystem.GetRoomIndex(RoomIndexNow);

                    if(roomTexture.loadFromFile(Image)){
                        textureSize = roomTexture.getSize();
                        roomSprite.setTexture(roomTexture,true);
                        float sizeX = 1200.f / static_cast<float>(textureSize.x);
                        float sizeY = 800.f / static_cast<float>(textureSize.y);
                        roomSprite.setScale({sizeX,sizeY});
                    }
                }
                if(keypress->code == sf::Keyboard::Key::Num3){
                    RoomIndexNow = 2;
                    std::string Image = gameSystem.GetRoomIndex(RoomIndexNow);

                    if(roomTexture.loadFromFile(Image)){
                        textureSize = roomTexture.getSize();
                        roomSprite.setTexture(roomTexture,true);
                        float sizeX = 1200.f / static_cast<float>(textureSize.x);
                        float sizeY = 800.f / static_cast<float>(textureSize.y);
                        roomSprite.setScale({sizeX,sizeY});
                    }
                }
                if(keypress->code == sf::Keyboard::Key::Num4){
                    RoomIndexNow = 3;
                    std::string Image = gameSystem.GetRoomIndex(RoomIndexNow);

                    if(roomTexture.loadFromFile(Image)){
                        textureSize = roomTexture.getSize();
                        roomSprite.setTexture(roomTexture,true);
                        float sizeX = 1200.f / static_cast<float>(textureSize.x);
                        float sizeY = 800.f / static_cast<float>(textureSize.y);
                        roomSprite.setScale({sizeX,sizeY});
                    }
                }
            }
            
        }
        if(IsRoomChange) {
            std::string Image = gameSystem.GetRoomIndex(RoomIndexNow);

            if(roomTexture.loadFromFile(Image)){
                textureSize = roomTexture.getSize();
                roomSprite.setTexture(roomTexture,true);
                float sizeX = 1200.f / static_cast<float>(textureSize.x);
                float sizeY = 800.f / static_cast<float>(textureSize.y);
                roomSprite.setScale({sizeX,sizeY});
            }
        }
        bool RoomLockerNow = gameSystem.GetRoomLocker(RoomIndexNow);
        if( RoomLockerNow == true) {
            roomlocker.setPosition({1020.f,580.f});
            roomlocker.setString("LOCKED");
            roomlocker.setFillColor(sf::Color::Red);
        }else {
            roomlocker.setPosition({1015.f,580.f});
            roomlocker.setString("UNLOCKED");
            roomlocker.setFillColor(sf::Color::Green);
        }

        window.clear(BgColor);
        window.draw(roomSprite);

        for(const auto& i : RoomButton){
            window.draw(i);
        }

        for(const auto& t : roomText){
            window.draw(t);
        }

        window.draw(locker);
        window.draw(roomlocker);

        window.draw(Skiped);
        window.draw(skiptext);

        window.display();
    }
    return true;
} 

// int main() {
//     sf::RenderWindow window(sf::VideoMode({800,600}), "SFML Image Viwer");

//     sf::Texture roomTexture;
//     if(!roomTexture.loadFromFile("RobloxScreenShot20260101_213158829.png")) {
//         std::cout<<"Error : File not found : RobloxScreenShot20260101_213158829.png" << std::endl;
//         return -1; 
//     }

//     sf::Sprite roomSprite(roomTexture);

//     sf::Vector2u texturesize = roomTexture.getSize();
//     float scaleX  = 800.f / static_cast<float>(texturesize.x);
//     float scaleY  = 600.f / static_cast<float>(texturesize.y);
//     roomSprite.setScale({scaleX,scaleY});
//     while(window.isOpen()) {
//         while (const std::optional event = window.pollEvent()){
//             if(event->is<sf::Event::Closed>()) {
//                 window.close();
//             }
//         }
//         window.clear(sf::Color::Black);
//         window.draw(roomSprite);
//         window.display();

//     }
//     return 0;
// }


// // sf::Color currentBgColor = sf::Color::Black;
// //     while(window.isOpen()) {
// //         while(const std::optional event = window.pollEvent()) {

// //             if(event->is<sf::Event::Closed>()) {
// //                 window.close();
// //             }
// //             if(const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()){

// //                 sf::Vector2f mousePos({static_cast<float>(mousePressed->position.x),
// //                                       static_cast<float>(mousePressed->position.y)});

// //                 if(button.getGlobalBounds().contains(mousePos)) {
// //                     if(currentBgColor == sf::Color::Black) {
// //                         currentBgColor = sf::Color({100,100,100});
// //                         button.setFillColor(sf::Color::Green);
// //                     }else {
// //                         currentBgColor = sf::Color::Black;
// //                         button.setFillColor(sf::Color::Blue);
// //                     }
// //                 }

// //                 if(mousePressed->button == sf::Mouse::Button::Left) {
// //                     if(currentBgColor == sf::Color::Black) {
// //                         currentBgColor = sf::Color({100,100,100});
// //                     }else {
// //                         currentBgColor = sf::Color::Black;
// //                     }
// //                 }
// //             }
// //         }
// //         window.clear(currentBgColor);
// //         window.draw(button);
// //         window.display();
// //     }