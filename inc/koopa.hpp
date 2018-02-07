#ifndef KOOPA_HPP
#define KOOPA_HPP

#include <vector>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "animation.hpp"
#include "animatedSprite.hpp"


class Koopa
{
    public:

    Koopa();
    ~Koopa();

    void init();
    void update(const sf::Time& deltatime, const sf::FloatRect floor);
    void draw(sf::RenderWindow& window) const;

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition();


    enum Direction { RIGHT, LEFT };
    enum Velocity { STOP = 0, WALK, RUN };

    void setMovement(Koopa::Direction direction, Koopa::Velocity velocity);
    void jump();


    private:

    const float gravity = 0.002f;

    //Koopa stats
    bool jumping;
    const int maxLife = 10;
    int life;
    const float jumpVel = 1.f;

    const std::vector<double> velocities = {
        0.f, //STOP 
        0.3f, //WALK
        0.6f //RUN
    };

    sf::Vector2f vel;

    //Koopa graphics
    sf::Texture koopaTexture;

    sf::Sprite koopa;

    /*
    AnimatedSprite koopa;

    enum Animations { IDLE_A, RIGHT_A, LEFT_A, IDLE_RUN_A, RUN_A };

    std::vector<Animation> animations;
    */


};

#endif