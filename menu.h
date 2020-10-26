#include <SFML/Graphics.hpp>
#include<iostream>
#include "level.h"
#include <vector>
#include <list>
#include<ctime>

using namespace sf;

void menu(RenderWindow& window)
{
    Texture menuTexture1, menuTexture2, menuBackground, tank;
    menuTexture1.loadFromFile("start.png");
    menuTexture2.loadFromFile("end.png");
    menuBackground.loadFromFile("fon.png");
    tank.loadFromFile("tanki.png");
    Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground), tank_(tank);
    bool isMenu = 1;
    int menuNum = 0;
    menu1.setPosition(875, 480);
    menu2.setPosition(875, 560);
    tank_.setTextureRect(IntRect(465, 0, 76, 65));
    tank_.setPosition(800, 480);
    //////////////////////////////лемч///////////////////
    while (isMenu)
    {
        menu1.setColor(Color::White);
        menu2.setColor(Color::White);
        menuNum = 0;
        window.clear(Color(0, 0, 1));

       
        if (Keyboard::isKeyPressed(Keyboard::Down)) 
        {
            tank_.setPosition(800, 560);

        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) 
        {
            tank_.setPosition(800, 480);
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter)) 
        {
            if (tank_.getPosition().y == 480) 
            {
                isMenu = false;
            }
            else
            {
                window.close();
                isMenu = false;
            }

        }
        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(tank_);
        window.display();
    }
    ////////////////////////////////////////////////////
}