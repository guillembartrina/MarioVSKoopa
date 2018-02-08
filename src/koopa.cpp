
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


    animations = std::vector<Animation>(Koopa::NUM_A);

    animations[Koopa::IDLE_RIGHT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 6; ++i) 
    {
	    animations[Koopa::IDLE_RIGHT_A].addFrame(sf::IntRect(i*koopaW, koopaH*0, koopaW, koopaH));
    }
    
    animations[Koopa::IDLE_RIGHT_A].stop();

    animations[Koopa::IDLE_LEFT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 6; ++i) 
    {
	    animations[Koopa::IDLE_LEFT_A].addFrame(sf::IntRect(i*koopaW, koopaH*1, koopaW, koopaH));
    }
    
    animations[Koopa::IDLE_LEFT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 10; ++i) 
    {
	    animations[Koopa::RIGHT_A].addFrame(sf::IntRect(i*koopaW, koopaH*2, koopaW, koopaH));
    }
    
    animations[Koopa::RIGHT_A].stop();

    animations[Koopa::LEFT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 10; ++i) 
    {
	    animations[Koopa::LEFT_A].addFrame(sf::IntRect(i*koopaW, koopaH*3, koopaW, koopaH));
    }
    
    animations[Koopa::LEFT_A].stop();

    koopa.setOrigin(sf::Vector2f(koopaW/2, koopaH));
    koopa.setPosition(sf::Vector2f(100.f, 400.f));
    koopa.setAnimation(&animations[IDLE_RIGHT_A]);
    animations[IDLE_RIGHT_A].play();

}

void Koopa::update(const sf::Time& deltatime)
{
    koopa.update(deltatime);

    //REMAKE!!

    vel.y += gravity * float(deltatime.asMilliseconds());

    koopa.move(vel * float(deltatime.asMilliseconds()));

    int colision = getCurrentColision();

    if(colision >= 0)
    {
        koopa.setPosition(koopa.getPosition().x, colisionRects[colision].top);
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

void Koopa::setColisions(const std::vector<sf::FloatRect>& colisions)
{
    colisionRects = colisions;
}

int Koopa::getCurrentColision() //REMOVE
{
    for(unsigned int i = 0; i < colisionRects.size(); ++i)
    {
        if(koopa.getGlobalBounds().intersects(colisionRects[i])) return i;
    }
    return -1;
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