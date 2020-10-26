#include <SFML/Graphics.hpp>
#include<iostream>
#include "level.h"
#include "Classes.h"
#include "EndGame.h"
#include "menu.h"
#include <vector>
#include <list>
#include<ctime>
#include <sstream>
using namespace sf;
int main()
{
    srand(time(NULL));
    float timerForSpawnAfterDeath = 0;
    int i_second = 0;
    int i = 1;
    float timeForSpawn = 0;
    RenderWindow window(VideoMode(1940, 1080), "Dendi");
    menu(window);
    float currentFrame = 0;


    Font font;
    font.loadFromFile("19363.ttf");
    Text text("", font, 20);
    text.setStyle(Text::Bold);
    

    Level lvl;
    lvl.LoadFromFile("TileMap.tmx");

    Image heroImage;
    heroImage.loadFromFile("tanki.png");
    heroImage.createMaskFromColor(Color(0, 0, 1));

    Image easyEnemyImage;
    easyEnemyImage.loadFromFile("tanki.png");
    easyEnemyImage.createMaskFromColor(Color(0, 0, 1));

    Object player = lvl.GetObject("Player");

    Player p(heroImage, "Player", lvl, player.rect.left, player.rect.top, 76, 65);
    

    std::list<Entity*> entities;
    std::list<Entity*>::iterator  it;
    std::list<Entity*>::iterator  it2;

    std::vector<Object> e = lvl.GetObjects("EasyEnemy");

    entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[0].rect.left, e[0].rect.top, 77, 66));

    Image BulletImage;
    BulletImage.loadFromFile("bullet.png");
    BulletImage.createMaskFromColor(Color(0, 0, 1));
    Bullet bl(BulletImage, "bullet", lvl, p.x, p.y, 16, 16, p.state);

    Clock clock;
    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (p.isShoot == true) { p.isShoot = false; p.tmp = false; entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y, 16, 16, p.state)); }//если выстрелили, то появляется пуля. enum передаем как int 
            for (it = entities.begin(); it != entities.end(); it++) {
                if ((*it)->name == "EasyEnemy")
                {
                    if ((*it)->tmp2 == true) {
                        entities.push_back(new Bullet(BulletImage, "Bullet2", lvl, (*it)->x, (*it)->y, 10, 10, (*it)->stateEnemy));
                        (*it)->tmp2 = false;

                    }

                }
            }
        }
        p.update(time);
        window.clear(Color::Black);
        lvl.Draw(window);
        timeForSpawn += time;
        if (timeForSpawn > 3000 && i < 4) {
            entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 77, 66));
            i++;
            timeForSpawn = 0;
        }
        for (it = entities.begin(); it != entities.end();)
        {
            i_second++;
            Entity* b = *it;
            b->update(time);
            if (b->life == false) {
                if (b->name != "Bullet2")
                {
                    p.tmp = true;
                }
                it = entities.erase(it);
                delete b;
                


            }
            else it++;
        }

        for (it = entities.begin(); it != entities.end(); it++) {
            window.draw((*it)->sprite); 
        }
        for (it = entities.begin(); it != entities.end(); it++)
        {
            if ((*it)->name == "EasyEnemy")
            {

                Entity* enemy = *it;

                for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++)
                {
                    Entity* bullet = *it2;
                    if (bullet->name == "Bullet")

                        if (bullet->life == true)
                        {

                            if (bullet->getRect().intersects(enemy->getRect()))
                            {
                                bullet->life = false;
                                enemy->life = false;
                                p.score += 100;
                                if (i < 20) {
                                    i++;
                                    entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 77, 66));
                                }
                            }
                        }
                }
            }
        }

        for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++)
        {
            Entity* bullet = *it2;
            if (bullet->name == "Bullet2")

                if (bullet->life == true)
                {

                    if (bullet->getRect().intersects(p.getRect()))
                    {
                        bullet->life = false;
                        end(window);
                        
                        window.close();
                    }
                }
        }


        int tmp = 0;
        for (it2 = entities.begin(); it2 != entities.end(); it2++)
        {
            for (it = entities.begin(); it != entities.end(); it++)
            {
                if ((*it)->getRect() != (*it2)->getRect())
                {
                    if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))//если столкнулись два объекта и они враги
                    {
                        tmp = rand() % 6;
                        if (tmp == 1 || tmp == 3 || tmp == 5)
                        {
                            (*it)->dy = 1;
                            (*it2)->dy = -1;
                        }
                        if (tmp == 0 || tmp == 2 || tmp == 4)
                        {
                            (*it)->dx = 1;
                            (*it2)->dx = -1;
                        }

                    }

                }

            }

        }
        for (it = entities.begin(); it != entities.end(); it++)
        {
            if ((*it)->getRect().intersects(p.getRect()))
            {
                if ((*it)->name == "EasyEnemy") {

                    if (p.dx < 0) { p.x = (*it)->x + (*it)->w; }
                    if (p.dx > 0) { p.x = (*it)->x - p.w; }
                    if (p.dy < 0) { p.y = (*it)->y + (*it)->h; }
                    if (p.dy > 0) { p.y = (*it)->y - p.h; }

                    if ((*it)->dx > 0)
                    {
                        (*it)->x = p.x - (*it)->w; 
                        (*it)->dx = 0;
                    }
                    if ((*it)->dx < 0)
                    {
                        (*it)->x = p.x + p.w; 
                        (*it)->dx = 0;
                    }
                    if ((*it)->dy > 0)
                    {
                        (*it)->y = p.y - (*it)->h;
                        (*it)->dy = 0;
                    }
                    if ((*it)->dy < 0)
                    {
                        (*it)->y = p.y + p.h; 
                        (*it)->dy = 0;
                    }

                }
            }
        }
            
        std::ostringstream playerHealthString;    
        playerHealthString << p.score;      
        text.setString("Score: " + playerHealthString.str());
        text.setPosition(1800, 30);

        window.draw(text);
        window.draw(p.sprite);
        window.display();
    }

    return 0;
}