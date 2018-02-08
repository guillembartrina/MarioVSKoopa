#ifndef MARIO_HPP
#define MARIO_HPP

#include <vector>
#include <iostream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "animation.hpp"
#include "animatedsprite.hpp"

class Mario
{
  public:
    Mario();
    ~Mario();

    void init();
    void update(const sf::Time &deltatime);
    void draw(sf::RenderWindow &window) const;

    void setPosition(const sf::Vector2f &position);
    sf::Vector2f getPosition();
    
    float getVelY();

    void setColisions(const std::vector<sf::FloatRect> &rects);
    unsigned int getColisionIndex(const sf::FloatRect &box);
    void checkColisions();

    int getLifes();
    void touched();
    bool getDmg();

    bool isAlive() const;

    sf::FloatRect getHead();
    sf::FloatRect getFeet();

    enum Direction
    {
        RIGHT = 0,
        LEFT
    };
    enum Velocity
    {
        STOP = 0,
        WALK,
        RUN,
        NUM_V
    };

    void setMovement(Mario::Direction direction, Mario::Velocity velocity);
    void jump();

  private:
    const float gravity = 0.002f;

    std::vector<sf::FloatRect> colisionRects;

    //Mario stats

    bool alive;
    bool dmg;
    sf::Time dmgTime;
    sf::Time maxDmgTime = sf::seconds(1.5f);

    const int marioW = 42;
    const int marioH = 54;

    enum Body
    {
        HEAD = 0,
        FEET,
        R_BODY,
        L_BODY,
        NUM_B
    };

    sf::FloatRect bodyParts[NUM_B];

    sf::RectangleShape head;
    sf::RectangleShape feet;
    sf::RectangleShape l_body;
    sf::RectangleShape r_body;

    const int maxLife = 10;
    int life;

    bool jumping;

    const float jumpVel = 1.f;
    double velocities[NUM_V];
    sf::Vector2f vel;

    //Mario graphics
    sf::Texture marioTexture;

    AnimatedSprite mario;
    enum Animations
    {
        IDLE_RIGHT_A = 0,
        IDLE_LEFT_A,
        RIGHT_A,
        LEFT_A,
        /*IDLE_RUN_A, RUN_A,*/ NUM_A
    };
    Animation animations[NUM_A];
};

#endif
