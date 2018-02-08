
#include "mario.hpp"

Mario::Mario() : mario(marioTexture, &animations[0])
{
    velocities[STOP] = 0.f;
    velocities[WALK] = 0.3f;
    velocities[RUN] = 0.6f;

    bodyParts[HEAD] = sf::FloatRect(-marioW/4.f, -marioH, marioW/2.f, marioH/4.f);
    bodyParts[FEET] = sf::FloatRect(-marioW/4.f, -marioH/4.f, marioW/2.f, marioH/4.f);
    bodyParts[L_BODY] = sf::FloatRect(-marioW/2.f, -marioH*3/4.f, marioW/4.f, marioH/2.f);
    bodyParts[R_BODY] = sf::FloatRect(marioW/4.f, -marioH*3/4.f , marioW/4.f, marioH/2.f);

    life = maxLife;
    jumping = false;
    setMovement(Direction::RIGHT, Velocity::STOP);
}

Mario::~Mario()
{
}

void Mario::init()
{
    //Mario init
    if(!marioTexture.loadFromFile("res/img/marioTexture.png"))
    {
        std::cout << "Error loading <marioTexture.png>." << std::endl;
    }

    mario.setTexture(marioTexture);


    //animations = std::vector<Animation>(Mario::NUM_A);

    animations[Mario::IDLE_RIGHT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 11; ++i) 
    {
	    animations[Mario::IDLE_RIGHT_A].addFrame(sf::IntRect(i*marioW, marioH*2, marioW, marioH));
    }
    
    animations[Mario::IDLE_RIGHT_A].stop();

    animations[Mario::IDLE_LEFT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 11; ++i) 
    {
	    animations[Mario::IDLE_LEFT_A].addFrame(sf::IntRect(i*marioW, marioH*3, marioW, marioH));
    }
    
    animations[Mario::IDLE_LEFT_A].stop();
    

    for (int i = 0; i < 12; ++i) 
    {
	    animations[Mario::RIGHT_A].addFrame(sf::IntRect(i*marioW, marioH*0, marioW, marioH));
    }
    
    animations[Mario::RIGHT_A].stop();

    animations[Mario::LEFT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 12; ++i) 
    {
	    animations[Mario::LEFT_A].addFrame(sf::IntRect(i*marioW, marioH*1, marioW, marioH));
    }
    
    animations[Mario::LEFT_A].stop();

    mario.setOrigin(sf::Vector2f(marioW/2, marioH));
    mario.setPosition(sf::Vector2f(100.f, 400.f));
    mario.setAnimation(&animations[IDLE_RIGHT_A]);
    animations[IDLE_RIGHT_A].play();

}

void Mario::update(const sf::Time& deltatime)
{
    mario.update(deltatime);

    vel.y += gravity * float(deltatime.asMilliseconds());

    mario.move(vel * float(deltatime.asMilliseconds()));

    checkColisions();
}

void Mario::draw(sf::RenderWindow& window) const
{
    window.draw(mario);
}

void Mario::setPosition(const sf::Vector2f& position)
{
    mario.setPosition(position);
}

sf::Vector2f Mario::getPosition()
{
    return mario.getPosition();
}

void Mario::setColisions(const std::vector<sf::FloatRect>& colisions)
{
    colisionRects = colisions;
}

void Mario::checkColisions()
{
    
}

void Mario::setMovement(Mario::Direction direction, Mario::Velocity velocity)
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

void Mario::jump()
{
    if(!jumping)
    {
        vel.y = -jumpVel;
        jumping = true;
    }
}
