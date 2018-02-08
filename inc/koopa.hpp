#ifndef KOOPA_HPP
#define KOOPA_HPP

#include <vector>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "animation.hpp"
#include "animatedsprite.hpp"


class Koopa
{
    public:

    Koopa();
    ~Koopa();

    void init();
    void update(const sf::Time& deltatime);
    void draw(sf::RenderWindow& window) const;

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition();
    

    void setColisions(const std::vector<sf::FloatRect>& rects);
    unsigned int getColisionIndex(const sf::FloatRect& box);
    void checkColisions();

    int getLifes();
    void touched();


    enum Direction { RIGHT = 0, LEFT };
    enum Velocity { STOP = 0, WALK, RUN, NUM_V };

    void setMovement(Koopa::Direction direction, Koopa::Velocity velocity);
    void jump();

    bool debug = false;


    private:

    const float gravity = 0.002f;

    std::vector<sf::FloatRect> colisionRects;

    //Koopa stats
    const int koopaW = 32;
    const int koopaH = 48;

    enum Body { HEAD = 0, FEET, R_BODY, L_BODY, NUM_B };

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

    //Koopa graphics
    sf::Texture koopaTexture;
    
    AnimatedSprite koopa;
    enum Animations { IDLE_RIGHT_A = 0, IDLE_LEFT_A, RIGHT_A, LEFT_A, /*IDLE_RUN_A, RUN_A,*/ NUM_A };
    Animation animations[NUM_A];
    

};

#endif
