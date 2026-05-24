#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <String>
#include <vector>
#include <random>

sf::SoundBuffer Jump;

sf::Sound JumpScare(Jump);


bool BtwTurn(std::string Time ) {
    std::string setTime = Time; 
    sf::RenderWindow window(sf::VideoMode({1200,800}),"Window");
    sf::Texture roomTexture;
    sf::Color BgColor = sf::Color::Black;

    if (!roomTexture.loadFromFile("BG.png")) {
        std::cout << "Warning: BG.png not found!" << std::endl;
    }

    sf::Sprite roomSprite(roomTexture);
    sf::Vector2u textureSize = roomTexture.getSize();
    float sizeX = 1200.f / static_cast<float>(textureSize.x);
    float sizeY = 800.f / static_cast<float>(textureSize.y);
    roomSprite.setScale({sizeX,sizeY});

    sf::Font gameFont;
    if(!gameFont.openFromFile("fonts/VT323-Regular.ttf")){}

    sf::RectangleShape Next({40.f,40.f});
    Next.setPosition({1000.f,700.f});
    Next.setFillColor(sf::Color(128,128,128));

    sf::Text Nexttext(gameFont,"NEXT",16);
    Nexttext.setPosition({1005.f,705.f});
    Nexttext.setFillColor(sf::Color::Black);

    sf::Text AM(gameFont,setTime,100);
    AM.setPosition({500.f,300.f});
    AM.setFillColor(sf::Color::White);

    while(window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            if(event->is< sf::Event::Closed>()){
                window.close();
                return false;
            }
            if(const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>() ) {
                if(mouseClick->button == sf::Mouse::Button::Left){
                    sf::Vector2f MousePosi = window.mapPixelToCoords(mouseClick->position);
                    if(Next.getGlobalBounds().contains(MousePosi)){
                        return true;
                    }
                }
            }
   
        }
    
        window.clear(BgColor);
        window.draw(roomSprite);

        window.draw(Next);
        window.draw(Nexttext);
        
        window.draw(AM);

        window.display();
    }
    return true;
}


bool JumpAndOver() {
    sf::RenderWindow window(sf::VideoMode({1200,800}),"Window");
    sf::Texture roomTexture;
    sf::Color BgColor = sf::Color::Black;

    if(!Jump.loadFromFile("jumpscare-sound.wav")){return 0;}

    if (!roomTexture.loadFromFile("BG.png")) {
        std::cout << "Warning: BG.png not found!" << std::endl;
    }

    sf::Sprite roomSprite(roomTexture);
    sf::Vector2u textureSize = roomTexture.getSize();
    float sizeX = 1200.f / static_cast<float>(textureSize.x);
    float sizeY = 800.f / static_cast<float>(textureSize.y);
    roomSprite.setScale({sizeX,sizeY});

    sf::Clock GameTimer;

    std::random_device rd;
    std::mt19937 rng = std::mt19937(rd());

    std::vector<std::string> Phee_ = {"Ghost/Ghost_1.png","Ghost/Ghost_2.png","Ghost/Ghost_3.png","Ghost/Ghost_4.png","Ghost/Ghost_5.png"};
    std::uniform_int_distribution<int> PicDice(0,Phee_.size()-1);
    int PicIndex = PicDice(rng);
    std::string PicGhost = Phee_[PicIndex];

    if(roomTexture.loadFromFile(PicGhost)){
        textureSize = roomTexture.getSize();
        roomSprite.setTexture(roomTexture,true);
        float sizeX = 1200.f / static_cast<float>(textureSize.x);
        float sizeY = 800.f / static_cast<float>(textureSize.y);
        roomSprite.setScale({sizeX,sizeY});
    }

    GameTimer.restart();
    JumpScare.play();
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
            if (GameTimer.getElapsedTime().asSeconds() >= 3.0f) {
                JumpScare.stop();
                return true; 
            }
        }
    window.clear(BgColor);
    window.draw(roomSprite);
    window.display();
    }
    return true;
}

bool GameOver() {
    sf::RenderWindow window(sf::VideoMode({1200,800}),"Window");
    sf::Texture roomTexture;
    sf::Color BgColor = sf::Color::Black;

    if (!roomTexture.loadFromFile("BG.png")) {
        std::cout << "Warning: BG.png not found!" << std::endl;
    }

    sf::Sprite roomSprite(roomTexture);
    sf::Vector2u textureSize = roomTexture.getSize();
    float sizeX = 1200.f / static_cast<float>(textureSize.x);
    float sizeY = 800.f / static_cast<float>(textureSize.y);
    roomSprite.setScale({sizeX,sizeY});

    sf::Font gameFont;
    if(!gameFont.openFromFile("fonts/VT323-Regular.ttf")){}

    sf::RectangleShape Next({40.f,40.f});
    Next.setPosition({1000.f,700.f});
    Next.setFillColor(sf::Color(128,128,128));

    sf::Text Nexttext(gameFont,"NEXT",16);
    Nexttext.setPosition({1005.f,705.f});
    Nexttext.setFillColor(sf::Color::Black);

    sf::Text GOver(gameFont,"GAME  OVER",100);
    GOver.setPosition({400.f,250.f});
    GOver.setFillColor((sf::Color::Red));


    while(window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            if(event->is< sf::Event::Closed>()){
                window.close();
                return false;
            }
            if(const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>() ) {
                if(mouseClick->button == sf::Mouse::Button::Left){
                    sf::Vector2f MousePosi = window.mapPixelToCoords(mouseClick->position);
                    if(Next.getGlobalBounds().contains(MousePosi)){
                        return true;
                    }
                }
            }
   
        }
        window.clear(BgColor);
        window.draw(roomSprite);
        window.draw(Next);
        window.draw(Nexttext);
        window.draw(GOver);
        window.display();
    }
    return true;
}

bool YouWin() {
    sf::RenderWindow window(sf::VideoMode({1200,800}),"Window");
    sf::Texture roomTexture;
    sf::Color BgColor = sf::Color::Black;

    if (!roomTexture.loadFromFile("BG.png")) {
        std::cout << "Warning: BG.png not found!" << std::endl;
    }

    sf::Sprite roomSprite(roomTexture);
    sf::Vector2u textureSize = roomTexture.getSize();
    float sizeX = 1200.f / static_cast<float>(textureSize.x);
    float sizeY = 800.f / static_cast<float>(textureSize.y);
    roomSprite.setScale({sizeX,sizeY});

    sf::Font gameFont;
    if(!gameFont.openFromFile("fonts/VT323-Regular.ttf")){}

    sf::RectangleShape Next({40.f,40.f});
    Next.setPosition({1000.f,700.f});
    Next.setFillColor(sf::Color(128,128,128));

    sf::Text Nexttext(gameFont,"NEXT",16);
    Nexttext.setPosition({1005.f,705.f});
    Nexttext.setFillColor(sf::Color::Black);

    sf::Text con(gameFont,"CONGRATULATION",100);
    con.setPosition({400.f,250.f});
    con.setFillColor((sf::Color::Red));


    while(window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            if(event->is< sf::Event::Closed>()){
                window.close();
                return false;
            }
            if(const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>() ) {
                if(mouseClick->button == sf::Mouse::Button::Left){
                    sf::Vector2f MousePosi = window.mapPixelToCoords(mouseClick->position);
                    if(Next.getGlobalBounds().contains(MousePosi)){
                        return true;
                    }
                }
            }
   
        }
        window.clear(BgColor);
        window.draw(roomSprite);
        window.draw(Next);
        window.draw(Nexttext);
        window.draw(con);
        window.display();
    }
    return true;
}
