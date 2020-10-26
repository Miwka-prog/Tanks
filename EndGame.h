#include <SFML/Graphics.hpp>
#include<iostream>
#include "level.h"
#include <vector>
#include <list>
#include<ctime>

using namespace sf;

void end(RenderWindow& window) 
{
    Texture textureEnd;
    textureEnd.loadFromFile("exit.png");
    Sprite end(textureEnd);
    bool isMenu = 1;
    int menuNum = 0;
    //////////////////////////////лемч///////////////////
    while (isMenu)
    {
        menuNum = 0;
        window.clear(Color(0, 0, 1));
        window.draw(end);
        window.display();
        sleep(milliseconds(2000));
        window.close();
    }

    ////////////////////////////////////////////////////
}