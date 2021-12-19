#ifndef PING_PONG_H
#define PING_PONG_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>

class Game
{
private:
    struct Velocity
    {
        double x, y;
    }; 
    Velocity velocity;
    
    sf::RenderWindow *window;
    sf::Event event;

    std::random_device dev;
    std::default_random_engine gen{dev()};

    sf::RectangleShape player;
    sf::RectangleShape enemy;
    sf::CircleShape ball;

    float angle;

    void initWindow();
    void initVariables();
    void initBall();
    void initPlayer();
    void initEnemy();

    Velocity normalize(double pos1, double pos2);

public:
    Game();
    virtual ~Game();
    bool isWinOpen;
    bool isCollision;
    char moveDirec;

    void updateBall();
    void updateEnemy();
    void updatePlayer();
    void updateEvents();

    void render();
    void update();
};

#endif