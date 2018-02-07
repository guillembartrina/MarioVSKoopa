
#include "koopa.hpp"

Koopa::Koopa()
{
    life = maxLife;
    jumping = false;
    setMovement(Direction::RIGHT, Velocity::STOP);
}

Koopa::~Koopa()
{
}

void Koopa::init()
{
    //Koopa init
    if(!koopaTexture.loadFromFile("res/img/koopaTexture.png"))
    {
        std::cout << "Error loading <koopaTexture.png>." << std::endl;
    }

    koopa.setTexture(koopaTexture);
    koopa.setTextureRect(sf::IntRect(0, 0, 43, 55));
    koopa.setOrigin(21, 55);
    koopa.setPosition(100, 100);
}

void Koopa::update(const sf::Time& deltatime, const sf::FloatRect floor)
{
    if(jumping)
    {
        vel.y += gravity * float(deltatime.asMilliseconds());
    }

    if(!koopa.getGlobalBounds().intersects(floor))
    {
        koopa.move(vel * float(deltatime.asMilliseconds()));
    }
    else
    {
        koopa.setPosition(koopa.getPosition().x, floor.top);
        jumping = false;
        vel.y = 0.f;
    }

}

void Koopa::draw(sf::RenderWindow& window) const
{
    window.draw(koopa);
}

void Koopa::setPosition(const sf::Vector2f& position)
{
    koopa.setPosition(position);
}

sf::Vector2f Koopa::getPosition()
{
    return koopa.getPosition();
}

void Koopa::setMovement(Koopa::Direction direction, Koopa::Velocity velocity)
{
    switch(direction)
    {
        case Direction::RIGHT:
        vel.x = velocities[velocity];
        break;

        case Direction::LEFT:
        vel.x = -velocities[velocity];
        break;
    }
}

void Koopa::jump()
{
    if(!jumping)
    {
        vel.y = -jumpVel;
        jumping = true;
    }
}