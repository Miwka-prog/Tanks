#include <SFML/Graphics.hpp>
#include<iostream>
#include "level.h"
#include <vector>
#include <list>
#include<ctime>

using namespace sf;


class Entity {
public:
    enum { left, right, up, down } state;
    enum { leftEnemy, rightEnemy, upEnemy, downEnemy } stateEnemy;
    std::vector<Object> obj;
    float dx, dy, x, y, speed, moveTimer;
    int w, h;
    bool isClick;
    bool life, isMove;
    bool lifeBullet;
    bool isShoot;
    bool tmp2;
    Texture texture;
    Sprite sprite;
    String name;
    Entity(Image& image, String Name, float X, float Y, int W, int H)
    {
        x = X;
        y = Y;
        w = W;
        h = H;
        name = Name;
        moveTimer = 0;
        speed = 0;
        dx = 0;
        dy = 0;
        life = true;
        isMove = false;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(w / 2, h / 2);
    }
    virtual void update(float time) = 0;

    FloatRect getRect() {
        return FloatRect(x, y, w, h);
    }
};


class Player :public Entity
{
public:
    int playerScore;
    bool tmp = true;
    float timerForSpawn = 0;
    int score = 0;
    Player(Image& image, String Name, Level& lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
    {
        state = up;
        playerScore = 0;
        obj = lvl.GetAllObjects();
        if (name == "Player") {
            sprite.setTextureRect(IntRect(0, 0, w, h));
        }

    }

    void control() {
        if (Keyboard::isKeyPressed) {
            if (Keyboard::isKeyPressed(Keyboard::Left)) 
            {
                state = left;
                speed = 0.1;
                sprite.setTextureRect(IntRect(163, 0, 76, 65));
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) 
            {
                state = right;
                speed = 0.1;
                sprite.setTextureRect(IntRect(465, 0, 76, 65));
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)) 
            {
                state = up;
                speed = 0.1;
                sprite.setTextureRect(IntRect(76, 0, 76, 65));
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) 
            {
                state = down;
                speed = 0.1;
                sprite.setTextureRect(IntRect(312, 0, 76, 65));
            }
            if (tmp == true)
            {
                if (Keyboard::isKeyPressed(Keyboard::Space))
                {
                    isShoot = true;
                }
            }
        }
    }

    void update(float time)
    {
        control();
        switch (state)
        {
        case right:
        {
            dx = speed;
            dy = 0;
            break;
        }
        case left:
        {
            dx = -speed;
            dy = 0;
            break;
        }
        case down:
        {
            dx = 0;
            dy = speed;
            break;
        }
        case up:
        {
            dx = 0;
            dy = -speed;
            break;
        }
        }
        x += dx * time;
        Collision(dx, 0);
        y += dy * time;
        Collision(0, dy);
        speed = 0;
        sprite.setPosition(x + w / 2, y + h / 2);
    }

    float GetPlayerCoordinateX()
    {
        return x;
    }
    float GetPlayerCoordinateY()
    {
        return y;
    }

    void Collision(float dx, float dy)
    {
        for (int i = 0; i < obj.size(); i++)
        {
            if (getRect().intersects(obj[i].rect))
            {
                if (obj[i].name == "solid" || obj[i].name == "water")
                {
                    if (dy > 0) { y = obj[i].rect.top - h;  dy = 0; }
                    if (dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
                    if (dx > 0) { x = obj[i].rect.left - w; }
                    if (dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
                }

            }

        }


    }
};


class Enemy :public Entity {
public:
    float timertoSpawn = 0;
    int timertoSpawnBullet = 0;
    Enemy(Image& image, String Name, Level& lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
        obj = lvl.GetAllObjects();
        if (name == "EasyEnemy") 
        {
            sprite.setTextureRect(IntRect(692, 0, w, h));
            stateEnemy = upEnemy;
            sprite.setPosition(-100, -100);
        }
    }
    void Collision(float Dx, float Dy, float  Time)
    {

        moveTimer += Time;
        srand(time(NULL));
        int choose_state;
        if (moveTimer < 3000) 
        {
            choose_state = rand() % 4;
        }
        if (moveTimer > 3000) 
        {
            choose_state = rand() % 4;
            moveTimer = 0;
        }

        for (int i = 0; i < obj.size() || i < obj.size(); i++)
        {
            if (getRect().intersects(obj[i].rect))
            {
                if (obj[i].name == "solid" || obj[i].name == "water")
                {
                    if (Dy > 0)
                    {
                        y = obj[i].rect.top - h;
                        if (choose_state == 0) 
                        {
                            stateEnemy = leftEnemy;
                        }
                        else if (choose_state == 1)
                        {
                            stateEnemy = rightEnemy;
                        }
                        else if (choose_state == 2) 
                        {
                            stateEnemy = downEnemy;
                        }
                        else if (choose_state == 3) 
                        {
                            stateEnemy = upEnemy;
                        }

                    }
                    if (Dy < 0) {
                        y = obj[i].rect.top + obj[i].rect.height;
                        if (choose_state == 0) {
                            stateEnemy = leftEnemy;
                        }
                        else if (choose_state == 1) 
                        {
                            stateEnemy = rightEnemy;
                        }
                        else if (choose_state == 2)
                        {
                            stateEnemy = downEnemy;
                        }
                        else if (choose_state == 3)
                        {
                            stateEnemy = upEnemy;
                        }
                    }
                    if (Dx > 0) {
                        x = obj[i].rect.left - w;
                        if (choose_state == 0) 
                        {
                            stateEnemy = leftEnemy;
                        }
                        else if (choose_state == 1)
 {
                            stateEnemy = rightEnemy;
                        }
                        else if (choose_state == 2) 
                        {
                            stateEnemy = downEnemy;
                        }
                        else if (choose_state == 3) 
                        {
                            stateEnemy = upEnemy;
                        }
                    }
                    if (Dx < 0) {
                        x = obj[i].rect.left + obj[i].rect.width;
                        if (choose_state == 0) {
                            stateEnemy = leftEnemy;
                        }
                        else if (choose_state == 1) 
                        {
                            stateEnemy = rightEnemy;
                        }
                        else if (choose_state == 2) 
                        {
                            stateEnemy = downEnemy;
                        }
                        else if (choose_state == 3) 
                        {
                            stateEnemy = upEnemy;
                        }
                    }

                }

            }
        }

    }
    void update(float Time)
    {
        if (name == "EasyEnemy") 
        {
            timertoSpawn += Time;
            if (timertoSpawn > 1000) 
            {
                timertoSpawnBullet += Time;
                if (timertoSpawnBullet > 3000)
                {
                    timertoSpawnBullet = 0;
                    tmp2 = true;
                }

                x += dx * Time;
                Collision(dx, 0, Time);
                y += dy * Time;
                Collision(0, dy, Time);
                speed = 0;
                sprite.setPosition(x + w / 2, y + h / 2);
                speed = 0.1;

                switch (stateEnemy)
                {
                case rightEnemy:
                {
                    dx = speed;
                    dy = 0;
                    sprite.setTextureRect(IntRect(1088, 0, w, h));
                    break;
                }
                case leftEnemy:
                {
                    dx = -speed;
                    dy = 0;
                    sprite.setTextureRect(IntRect(783, 0, w, h));
                    break;
                }
                case downEnemy:
                {
                    dx = 0;
                    dy = speed;
                    sprite.setTextureRect(IntRect(933, 0, w, h));
                    break;
                }
                case upEnemy:
                {
                    dx = 0;
                    dy = -speed;
                    sprite.setTextureRect(IntRect(692, 0, w, h));
                    break;
                }
                }
            }

        }
    }
};
class Bullet :public Entity {
public:
    int direction;

    Bullet(Image& image, String Name, Level& lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H) {
        obj = lvl.GetObjects("solid");
        x = X;
        y = Y;
        direction = dir;
        speed = 0.3;
        w = h = 16;
        life = true;
    }


    void update(float time)
    {
        switch (direction)
        {
        case 0: dx = -speed; dy = 0;   break;
        case 1: dx = speed; dy = 0;   break;
        case 2: dx = 0; dy = -speed;   break;
        case 3: dx = 0; dy = speed;   break;
        }
        x += dx * time;
        y += dy * time;
        for (int i = 0; i < obj.size(); i++) {
            if (getRect().intersects(obj[i].rect)) 
            {
                life = false;
            }
        }
        if (direction == 2 || direction == 3) 
        {
            sprite.setPosition(x + 27 + w / 2, y + h / 2);

        }
        else
        {
            sprite.setPosition(x + w / 2, y + 10 + h / 2);
        }

    }
};