
#include "mario.hpp"

Mario::Mario() : mario(marioTexture, &animations[0])
{
    velocities[STOP] = 0.f;
    velocities[WALK] = 0.3f;
    velocities[RUN] = 0.6f;

    bodyParts[HEAD] = sf::FloatRect(-marioW/4.f, -marioH, marioW/2.f, marioH/4.f);
    bodyParts[FEET] = sf::FloatRect(-marioW/4.f, -marioH/4.f, marioW/2.f, marioH/4.f);
    bodyParts[L_BODY] = sf::FloatRect(-marioW/2.f, -marioH*3/4.f, marioW/4.f, marioH/3.f);
    bodyParts[R_BODY] = sf::FloatRect(marioW/4.f, -marioH*3/4.f , marioW/4.f, marioH/3.f);

    life = maxLife;
    jumping = false;
    setMovement(Direction::RIGHT, Velocity::STOP);

    head.setSize(sf::Vector2f(bodyParts[HEAD].width, bodyParts[HEAD].height));
    feet.setSize(sf::Vector2f(bodyParts[FEET].width, bodyParts[FEET].height));
    l_body.setSize(sf::Vector2f(bodyParts[L_BODY].width, bodyParts[L_BODY].height));
    r_body.setSize(sf::Vector2f(bodyParts[R_BODY].width, bodyParts[R_BODY].height));
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

    animations[Mario::IDLE_RIGHT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 10; ++i) 
    {
	    animations[Mario::IDLE_RIGHT_A].addFrame(sf::IntRect(i*marioW, marioH*2, marioW, marioH));
    }

    animations[Mario::IDLE_LEFT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 10; ++i) 
    {
	    animations[Mario::IDLE_LEFT_A].addFrame(sf::IntRect(i*marioW, marioH*3, marioW, marioH));
    }

    animations[Mario::RIGHT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 12; ++i) 
    {
	    animations[Mario::RIGHT_A].addFrame(sf::IntRect(i*marioW, marioH*0, marioW, marioH));
    }

    animations[Mario::LEFT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 12; ++i) 
    {
	    animations[Mario::LEFT_A].addFrame(sf::IntRect(i*marioW, marioH*1, marioW, marioH));
    }

    mario.setOrigin(sf::Vector2f(marioW/2, marioH));
    mario.setPosition(sf::Vector2f(500.f, 400.f));
    mario.setAnimation(&animations[IDLE_RIGHT_A]);

}

void Mario::update(const sf::Time& deltatime)
{
    mario.update(deltatime);

    vel.y += gravity * float(deltatime.asMilliseconds());

    mario.move(vel * float(deltatime.asMilliseconds()));

    if(debug)
    {
        head.setPosition(mario.getPosition().x + bodyParts[HEAD].left, mario.getPosition().y + bodyParts[HEAD].top);
        feet.setPosition(mario.getPosition().x + bodyParts[FEET].left, mario.getPosition().y + bodyParts[FEET].top);
        l_body.setPosition(mario.getPosition().x + bodyParts[L_BODY].left, mario.getPosition().y + bodyParts[L_BODY].top);
        r_body.setPosition(mario.getPosition().x + bodyParts[R_BODY].left, mario.getPosition().y + bodyParts[R_BODY].top);
    }

    checkColisions();
}

void Mario::draw(sf::RenderWindow& window) const
{
    if(debug)
    {
        window.draw(head);
        window.draw(feet);
        window.draw(l_body);
        window.draw(r_body);
    }
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

unsigned int Mario::getColisionIndex(const sf::FloatRect& box)
{
    for(unsigned int i = 0; i < colisionRects.size(); ++i)
    {
        if(box.intersects(colisionRects[i])) return i;
    }
    return -1;
}

void Mario::checkColisions()
{
    float x = mario.getPosition().x;
    float y = mario.getPosition().y;

    if(debug) std::cout << "X: " << x << ", Y:" << y << std::endl;

    sf::FloatRect headRect = bodyParts[HEAD];
    headRect.left += x;
    headRect.top += y;
    sf::FloatRect feetRect = bodyParts[FEET];
    feetRect.left += x;
    feetRect.top += y;
    sf::FloatRect leftRect = bodyParts[L_BODY];
    leftRect.left += x;
    leftRect.top += y;
    sf::FloatRect rightRect = bodyParts[R_BODY];
    rightRect.left += x;
    rightRect.top += y;

    int hCol = getColisionIndex(headRect);
    int bCol = getColisionIndex(feetRect);
    int lCol = getColisionIndex(leftRect);
    int rCol = getColisionIndex(rightRect);

    if(hCol != -1)
    {
        if(debug) std::cout << "Head colision!" << std::endl;
        mario.setPosition(mario.getPosition().x, colisionRects[hCol].top+colisionRects[hCol].height+marioH);
        vel.y = 0;
    }

    if(bCol != -1)
    {
        if(debug) std::cout << "Feet colision!" << std::endl;
        mario.setPosition(mario.getPosition().x, colisionRects[bCol].top);
        jumping = false;
        vel.y = 0;
    }

    if(lCol != -1)
    {
        if(debug) std::cout << "Left colision!" << std::endl;
        mario.setPosition(colisionRects[lCol].left+colisionRects[lCol].width+marioW/2.f, mario.getPosition().y);
    }

    if(rCol != -1)
    {
        if(debug) std::cout << "Right colision!" << std::endl;
        mario.setPosition(colisionRects[rCol].left-marioW/2.f, mario.getPosition().y);
    }
}

int Mario::getLifes()
{
    return life;
}

void Mario::touched()
{
    --life;
    if(life <= 0) mario.setRotation(90.f);
}

void Mario::setMovement(Mario::Direction direction, Mario::Velocity velocity)
{
    switch(direction)
    {
        case Direction::RIGHT:
        vel.x = velocities[velocity];
        if(velocity == Velocity::WALK) mario.setAnimation(&animations[RIGHT_A]);
        else if(velocity == Velocity::STOP) mario.setAnimation(&animations[IDLE_RIGHT_A]);
        break;

        case Direction::LEFT:
        vel.x = -velocities[velocity];
        if(velocity == Velocity::WALK) mario.setAnimation(&animations[LEFT_A]);
        else if(velocity == Velocity::STOP) mario.setAnimation(&animations[IDLE_LEFT_A]);
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
