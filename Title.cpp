#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

int Title() {
    sf::RenderWindow window(sf::VideoMode({1200,800}),"Window");
    sf::Texture roomTexture;
    sf::Color BgColor = sf::Color::Black;

    if (!roomTexture.loadFromFile("FiBo.png")) {
        std::cout << "Warning: FiBo.png not found!" << std::endl;
    }

    sf::Sprite roomSprite(roomTexture);
    sf::Vector2u textureSize = roomTexture.getSize();
    float sizeX = 1200.f / static_cast<float>(textureSize.x);
    float sizeY = 800.f / static_cast<float>(textureSize.y);
    roomSprite.setScale({sizeX,sizeY});


    sf::Font gameFont;
    if(!gameFont.openFromFile("fonts/VT323-Regular.ttf")){}

    sf::RectangleShape Start({100.f,60.f});
    Start.setPosition({1000.f,200.f});
    Start.setFillColor(sf::Color(128,128,128));

    sf::Text starttext(gameFont,"START",30);
    starttext.setPosition({1010.f,210.f});
    starttext.setFillColor(sf::Color::Black);

    sf::RectangleShape Quit({100.f,60.f});
    Quit.setPosition({1000.f,450.f});
    Quit.setFillColor(sf::Color(128,128,128));

    sf::Text Quittext(gameFont,"QUIT",30);
    Quittext.setPosition({1010.f,460.f});
    Quittext.setFillColor(sf::Color::Black);

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent())
        {
            if(event->is< sf::Event::Closed>()){
                window.close();
                return 3;
            }
            if(const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>() ) {
                if(mouseClick->button == sf::Mouse::Button::Left){
                    sf::Vector2f MousePosi = window.mapPixelToCoords(mouseClick->position);
                    if(Quit.getGlobalBounds().contains(MousePosi)){
                        window.close();
                        return 3;
                    }

                    if(Start.getGlobalBounds().contains(MousePosi)){
                        std::cout<< 1;
                        return 1;
                    }
                }
            }
   
        }
    
        window.clear(BgColor);
        window.draw(roomSprite);

        window.draw(Start);
        window.draw(starttext);

        window.draw(Quit);
        window.draw(Quittext);

        window.display();
    }
    return 4;
}