
#include "mario.hpp"

Mario::Mario() : mario(marioTexture, &animations[0])
{
    velocities[Mario::Velocity::STOP] = 0.f;
    velocities[Mario::Velocity::WALK] = 0.3f;
    velocities[Mario::Velocity::RUN] = 0.6f;

    bodyParts[Mario::Body::HEAD] = sf::FloatRect(-marioW / 4.f, -marioH, marioW / 2.f, marioH / 4.f);
    bodyParts[Mario::Body::FEET] = sf::FloatRect(-marioW / 4.f, -marioH / 4.f, marioW / 2.f, marioH / 4.f);
    bodyParts[Mario::Body::L_BODY] = sf::FloatRect(-marioW / 2.f, -marioH * 3 / 4.f, marioW / 4.f, marioH / 3.f);
    bodyParts[Mario::Body::R_BODY] = sf::FloatRect(marioW / 4.f, -marioH * 3 / 4.f, marioW / 4.f, marioH / 3.f);

    alive = true;
    dmg = false;

    life = maxLife;
    jumping = false;
    setMovement(Mario::Direction::RIGHT, Mario::Velocity::STOP);

    head.setSize(sf::Vector2f(bodyParts[Mario::Body::HEAD].width, bodyParts[Mario::Body::HEAD].height));
    feet.setSize(sf::Vector2f(bodyParts[Mario::Body::FEET].width, bodyParts[Mario::Body::FEET].height));
    l_body.setSize(sf::Vector2f(bodyParts[Mario::Body::L_BODY].width, bodyParts[Mario::Body::L_BODY].height));
    r_body.setSize(sf::Vector2f(bodyParts[Mario::Body::R_BODY].width, bodyParts[Mario::Body::R_BODY].height));
}

Mario::~Mario()
{
}

void Mario::init()
{
    //Mario init
    if (!marioTexture.loadFromFile("res/img/marioTexture.png"))
    {
        std::cout << "Error loading <marioTexture.png>." << std::endl;
    }

    mario.setTexture(marioTexture);

    animations[Mario::Animations::IDLE_RIGHT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 10; ++i)
    {
        animations[Mario::Animations::IDLE_RIGHT_A].addFrame(sf::IntRect(i * marioW, marioH * 2, marioW, marioH));
    }

    animations[Mario::Animations::IDLE_LEFT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 10; ++i)
    {
        animations[Mario::Animations::IDLE_LEFT_A].addFrame(sf::IntRect(i * marioW, marioH * 3, marioW, marioH));
    }

    animations[Mario::Animations::RIGHT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 12; ++i)
    {
        animations[Mario::Animations::RIGHT_A].addFrame(sf::IntRect(i * marioW, marioH * 0, marioW, marioH));
    }

    animations[Mario::Animations::LEFT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 12; ++i)
    {
        animations[Mario::Animations::LEFT_A].addFrame(sf::IntRect(i * marioW, marioH * 1, marioW, marioH));
    }

    animations[Mario::Animations::STOP_A].setFrameTime(sf::seconds(0.125f));
    
    //!!!!!!!!!!!
    marioW = 46;

    for (int i = 0; i < 11; ++i)
    {
        animations[Mario::Animations::STOP_A].addFrame(sf::IntRect(i * marioW, marioH * 4, marioW, marioH));
    }

    //!!!!!!!!!!!
    marioW = 42;

    mario.setOrigin(sf::Vector2f(marioW / 2, marioH));
    mario.setPosition(sf::Vector2f(500.f, 400.f));
    mario.setAnimation(&animations[Mario::Animations::IDLE_RIGHT_A]);
}

void Mario::update(const sf::Time &deltatime)
{
    mario.update(deltatime);

    vel.y += gravity * float(deltatime.asMilliseconds());

    if(dmg) vel.x = 0;
    
    mario.move(vel * float(deltatime.asMilliseconds()));

    if(dmg)
    {
        dmgTime += deltatime;
        if(dmgTime < maxDmgTime)
        {
            mario.setColor(sf::Color::Red);
        }
        else
        {
            dmg = false;
            mario.setColor(sf::Color::White);
        }
    }

    head.setPosition(mario.getPosition().x + bodyParts[Mario::Body::HEAD].left, mario.getPosition().y + bodyParts[Mario::Body::HEAD].top);
    feet.setPosition(mario.getPosition().x + bodyParts[Mario::Body::FEET].left, mario.getPosition().y + bodyParts[Mario::Body::FEET].top);
    l_body.setPosition(mario.getPosition().x + bodyParts[Mario::Body::L_BODY].left, mario.getPosition().y + bodyParts[Mario::Body::L_BODY].top);
    r_body.setPosition(mario.getPosition().x + bodyParts[Mario::Body::R_BODY].left, mario.getPosition().y + bodyParts[Mario::Body::R_BODY].top);

    checkColisions();
}

void Mario::draw(sf::RenderWindow &window) const
{

    window.draw(head);
    window.draw(feet);
    window.draw(l_body);
    window.draw(r_body);

    window.draw(mario);
}

void Mario::setPosition(const sf::Vector2f &position)
{
    mario.setPosition(position);
}

sf::Vector2f Mario::getPosition()
{
    return mario.getPosition();
}

float Mario::getVelY()
{
    return vel.y;
}

void Mario::setColisions(const std::vector<sf::FloatRect> &colisions)
{
    colisionRects = colisions;
}

unsigned int Mario::getColisionIndex(const sf::FloatRect &box)
{
    for (unsigned int i = 0; i < colisionRects.size(); ++i)
    {
        if (box.intersects(colisionRects[i]))
            return i;
    }
    return -1;
}

void Mario::checkColisions()
{
    float x = mario.getPosition().x;
    float y = mario.getPosition().y;

    //std::cout << "X: " << x << ", Y:" << y << std::endl;

    sf::FloatRect headRect = bodyParts[Mario::Body::HEAD];
    headRect.left += x;
    headRect.top += y;
    sf::FloatRect feetRect = bodyParts[Mario::Body::FEET];
    feetRect.left += x;
    feetRect.top += y;
    sf::FloatRect leftRect = bodyParts[Mario::Body::L_BODY];
    leftRect.left += x;
    leftRect.top += y;
    sf::FloatRect rightRect = bodyParts[Mario::Body::R_BODY];
    rightRect.left += x;
    rightRect.top += y;

    int hCol = getColisionIndex(headRect);
    int bCol = getColisionIndex(feetRect);
    int lCol = getColisionIndex(leftRect);
    int rCol = getColisionIndex(rightRect);

    if (hCol != -1)
    {
        //std::cout << "Head colision!" << std::endl;
        mario.setPosition(mario.getPosition().x, colisionRects[hCol].top + colisionRects[hCol].height + marioH);
        vel.y = 0;
    }

    if (bCol != -1)
    {
        //std::cout << "Feet colision!" << std::endl;
        mario.setPosition(mario.getPosition().x, colisionRects[bCol].top);
        jumping = false;
        vel.y = 0;
    }

    if (lCol != -1)
    {
        //std::cout << "Left colision!" << std::endl;
        mario.setPosition(colisionRects[lCol].left + colisionRects[lCol].width + marioW / 2.f, mario.getPosition().y);
    }

    if (rCol != -1)
    {
        //std::cout << "Right colision!" << std::endl;
        mario.setPosition(colisionRects[rCol].left - marioW / 2.f, mario.getPosition().y);
    }
}

int Mario::getLifes()
{
    return life;
}

void Mario::touched()
{
    --life;
    dmg = true;

    mario.setAnimation(&animations[Mario::Animations::STOP_A]);

    dmgTime = sf::Time::Zero;
    if (life <= 0)
    {
        alive = false;
    }
}

bool Mario::getDmg()
{
    return dmg;
}

bool Mario::isJumping()
{
    return jumping;
}

bool Mario::isAlive() const
{
    return alive;
}

sf::FloatRect Mario::getBodyPart(Mario::Body bodyPart)
{
    sf::FloatRect tmp = bodyParts[bodyPart];
    tmp.left += mario.getPosition().x;
    tmp.top += mario.getPosition().y;
    return tmp;
}

void Mario::setMovement(Mario::Direction direction, Mario::Velocity velocity)
{
    switch (direction)
    {
    case Mario::Direction::RIGHT:
        vel.x = velocities[velocity];
        if (velocity == Mario::Velocity::WALK)
            mario.setAnimation(&animations[Mario::Animations::RIGHT_A]);
        else if (velocity == Mario::Velocity::STOP)
            mario.setAnimation(&animations[Mario::Animations::IDLE_RIGHT_A]);
        break;

    case Mario::Direction::LEFT:
        vel.x = -velocities[velocity];
        if (velocity == Mario::Velocity::WALK)
            mario.setAnimation(&animations[Mario::Animations::LEFT_A]);
        else if (velocity == Mario::Velocity::STOP)
            mario.setAnimation(&animations[Mario::Animations::IDLE_LEFT_A]);
        break;
    }
}

void Mario::jump()
{
    if (!jumping)
    {
        vel.y = -jumpVel;
        jumping = true;
    }
}
