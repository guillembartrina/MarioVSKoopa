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
    int getCurrentColision();     //REMOVE 


    enum Direction { RIGHT = 0, LEFT };
    enum Velocity { STOP = 0, WALK, RUN };

    void setMovement(Koopa::Direction direction, Koopa::Velocity velocity);
    void jump();


    private:

    const float gravity = 0.002f;

    std::vector<sf::FloatRect> colisionRects;

    //Koopa stats
    const int koopaW = 32;
    const int koopaH = 48;

    enum Body { HEAD = 0, FEET, R_BODY, L_BODY };

    const std::vector<sf::FloatRect> bodyParts = {
        sf::FloatRect(-koopaW/4.f, -koopaH, koopaW/2.f, koopaH/4.f),
        sf::FloatRect(-koopaW/4.f, -koopaH/4.f, koopaW/2.f, koopaH/4.f),
        sf::FloatRect(-koopaW/2.f, -koopaH*3/4.f, koopaW/4.f, koopaH/2.f),
        sf::FloatRect(koopaW/4.f, -koopaH*3/4.f , koopaW/4.f, koopaH/2.f)
    };

    const int maxLife = 10;
    int life;

    bool jumping;

    const float jumpVel = 1.f;
    const std::vector<double> velocities = {
        0.f, //STOP 
        0.3f, //WALK
        0.6f //RUN
    };
    sf::Vector2f vel;

    //Koopa graphics
    sf::Texture koopaTexture;
    
    AnimatedSprite koopa;
    enum Animations { IDLE_RIGHT_A = 0, IDLE_LEFT_A, RIGHT_A, LEFT_A, /*IDLE_RUN_A, RUN_A,*/ NUM_A };
    std::vector<Animation> animations;
    

};

#endif