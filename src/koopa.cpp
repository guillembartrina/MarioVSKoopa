
#include "koopa.hpp"

Koopa::Koopa() : koopa(koopaTexture, &animations[0])
{
    velocities[Koopa::Velocity::STOP] = 0.f;
    velocities[Koopa::Velocity::WALK] = 0.3f;
    velocities[Koopa::Velocity::RUN] = 0.6f;

    updateColisions();

    inside = false;
    alive = true;
    dmg = false;

    life = maxLife;
    jumping = false;
    setMovement(Koopa::Direction::RIGHT, Koopa::Velocity::STOP);

    currentDist = 0.f;

    /*
    head.setSize(sf::Vector2f(bodyParts[Koopa::Body::HEAD].width, bodyParts[Koopa::Body::HEAD].height));
    feet.setSize(sf::Vector2f(bodyParts[Koopa::Body::FEET].width, bodyParts[Koopa::Body::FEET].height));
    l_body.setSize(sf::Vector2f(bodyParts[Koopa::Body::L_BODY].width, bodyParts[Koopa::Body::L_BODY].height));
    r_body.setSize(sf::Vector2f(bodyParts[Koopa::Body::R_BODY].width, bodyParts[Koopa::Body::R_BODY].height));
    */
}

Koopa::~Koopa()
{
}

void Koopa::init()
{
    //Koopa init
    if (!koopaTexture.loadFromFile("res/img/koopaTexture.png"))
    {
        std::cout << "Error loading <koopaTexture.png>." << std::endl;
    }

    koopa.setTexture(koopaTexture);

    animations[Koopa::Animations::IDLE_RIGHT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 6; ++i)
    {
        animations[Koopa::Animations::IDLE_RIGHT_A].addFrame(sf::IntRect(i * koopaW, koopaH * 1, koopaW, koopaH));
    }

    animations[Koopa::Animations::IDLE_LEFT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 6; ++i)
    {
        animations[Koopa::Animations::IDLE_LEFT_A].addFrame(sf::IntRect(i * koopaW, koopaH * 0, koopaW, koopaH));
    }

    animations[Koopa::Animations::RIGHT_A].setFrameTime(sf::seconds(0.075f));

    for (int i = 0; i < 10; ++i)
    {
        animations[Koopa::Animations::RIGHT_A].addFrame(sf::IntRect(i * koopaW, koopaH * 3, koopaW, koopaH));
    }

    animations[Koopa::Animations::LEFT_A].setFrameTime(sf::seconds(0.075f));

    for (int i = 0; i < 10; ++i)
    {
        animations[Koopa::Animations::LEFT_A].addFrame(sf::IntRect(i * koopaW, koopaH * 2, koopaW, koopaH));
    }

    //!!!!!!
    koopaW = 36;

    animations[Koopa::Animations::IN_A].setFrameTime(sf::seconds(0.075));

    for (int i = 0; i < 11; ++i)
    {
        animations[Koopa::Animations::IN_A].addFrame(sf::IntRect(i * koopaW, koopaH * 4, koopaW, koopaH));
    }

    animations[Koopa::Animations::IN_A].setRepeat(false);

    animations[Koopa::Animations::OUT_A].setFrameTime(sf::seconds(0.075f));

    for (int i = 0; i < 11; ++i)
    {
        animations[Koopa::Animations::OUT_A].addFrame(sf::IntRect(i * koopaW, koopaH * 5, koopaW, koopaH));
    }

    animations[Koopa::Animations::OUT_A].setRepeat(false);

    //!!!!!!
    koopaW = 32;

    animations[Koopa::Animations::STOP_A].setFrameTime(sf::seconds(0.075f));

    for (int i = 0; i < 7; ++i)
    {
        animations[Koopa::Animations::STOP_A].addFrame(sf::IntRect(i * koopaW, koopaH * 6, koopaW, 30));
    }

    koopa.setOrigin(sf::Vector2f(koopaW / 2, koopaH));
    koopa.setPosition(sf::Vector2f(100.f, 500.f));
    koopa.setAnimation(&animations[Koopa::Animations::IDLE_RIGHT_A]);
}

void Koopa::update(const sf::Time &deltatime)
{
    koopa.update(deltatime);

    vel.y += gravity * float(deltatime.asMilliseconds());

    if(dmg) vel.x = 0;
    koopa.move(vel * float(deltatime.asMilliseconds()));

    currentDist += vel.x * float(deltatime.asMilliseconds());

    if(dmg)
    {
        dmgTime += deltatime;
        if(dmgTime < maxDmgTime)
        {
            koopa.setColor(sf::Color::Red);
        }
        else
        {
            dmg = false;
            koopa.setColor(sf::Color::White);
        }
    }

    if(inside)
    {
        if(animations[Koopa::Animations::IN_A].hasEnded())
        {
            koopaW = 32; koopaH = 30;
            updateColisions();
            koopa.setOrigin(koopaW/2.f, koopaH);
            koopa.setAnimation(&animations[Koopa::Animations::STOP_A]);
        }

        insideTime += deltatime;
        if(insideTime > maxInsideTime)
        {
            inside = false;
            currentDist = 0.f;
            vel.x = 0;
        }
    }

    /*
    head.setPosition(koopa.getPosition().x + bodyParts[Koopa::Body::HEAD].left, koopa.getPosition().y + bodyParts[Koopa::Body::HEAD].top);
    feet.setPosition(koopa.getPosition().x + bodyParts[Koopa::Body::FEET].left, koopa.getPosition().y + bodyParts[Koopa::Body::FEET].top);
    l_body.setPosition(koopa.getPosition().x + bodyParts[Koopa::Body::L_BODY].left, koopa.getPosition().y + bodyParts[Koopa::Body::L_BODY].top);
    r_body.setPosition(koopa.getPosition().x + bodyParts[Koopa::Body::R_BODY].left, koopa.getPosition().y + bodyParts[Koopa::Body::R_BODY].top);
    */
    checkColisions();
}

void Koopa::draw(sf::RenderWindow &window) const
{
    window.draw(head);
    window.draw(feet);
    window.draw(l_body);
    window.draw(r_body);

    window.draw(koopa);
}

void Koopa::setPosition(const sf::Vector2f &position)
{
    koopa.setPosition(position);
}

sf::Vector2f Koopa::getPosition()
{
    return koopa.getPosition();
}

float Koopa::getVelY()
{
    return vel.y;
}

void Koopa::setColisions(const std::vector<sf::FloatRect> &colisions)
{
    colisionRects = colisions;
}

unsigned int Koopa::getColisionIndex(const sf::FloatRect &box)
{
    for (unsigned int i = 0; i < colisionRects.size(); ++i)
    {
        if (box.intersects(colisionRects[i]))
            return i;
    }
    return -1;
}

void Koopa::checkColisions()
{
    float x = koopa.getPosition().x;
    float y = koopa.getPosition().y;

    //std::cout << "X: " << x << ", Y:" << y << std::endl;

    sf::FloatRect headRect = bodyParts[Koopa::Body::HEAD];
    headRect.left += x;
    headRect.top += y;
    int hCol = getColisionIndex(headRect);
    if (hCol != -1)
    {
        //std::cout << "Head colision!" << std::endl;
        koopa.setPosition(koopa.getPosition().x, colisionRects[hCol].top + colisionRects[hCol].height + koopaH);
        vel.y = 0;
    }

    x = koopa.getPosition().x;
    y = koopa.getPosition().y;

    sf::FloatRect feetRect = bodyParts[Koopa::Body::FEET];
    feetRect.left += x;
    feetRect.top += y;
    int bCol = getColisionIndex(feetRect);
    if (bCol != -1)
    {
        //std::cout << "Feet colision!" << std::endl;
        koopa.setPosition(koopa.getPosition().x, colisionRects[bCol].top);
        jumping = false;
        vel.y = 0;
    }

    x = koopa.getPosition().x;
    y = koopa.getPosition().y;

    sf::FloatRect leftRect = bodyParts[Koopa::Body::L_BODY];
    leftRect.left += x;
    leftRect.top += y;
    int lCol = getColisionIndex(leftRect);
    if (lCol != -1)
    {
        //std::cout << "Left colision!" << std::endl;
        if(inside) vel.x = -vel.x;
        else koopa.setPosition(colisionRects[lCol].left + colisionRects[lCol].width + koopaW / 2.f, koopa.getPosition().y);
    }

    x = koopa.getPosition().x;
    y = koopa.getPosition().y;

    sf::FloatRect rightRect = bodyParts[Koopa::Body::R_BODY];
    rightRect.left += x;
    rightRect.top += y;
    int rCol = getColisionIndex(rightRect);
    if (rCol != -1)
    {
        //std::cout << "Right colision!" << std::endl;
        if(inside) vel.x = -vel.x;
        else koopa.setPosition(colisionRects[rCol].left - koopaW / 2.f, koopa.getPosition().y);
    }
}

void Koopa::updateColisions()
{
    bodyParts[Koopa::Body::HEAD] = sf::FloatRect(-koopaW / 4.f, -koopaH, koopaW / 2.f, koopaH / 4.f);
    bodyParts[Koopa::Body::FEET] = sf::FloatRect(-koopaW / 4.f, -koopaH / 4.f, koopaW / 2.f, koopaH / 4.f);
    bodyParts[Koopa::Body::L_BODY] = sf::FloatRect(-koopaW / 2.f, -koopaH * 3 / 4.f, koopaW / 4.f, koopaH * 2 / 5.f);
    bodyParts[Koopa::Body::R_BODY] = sf::FloatRect(koopaW / 4.f, -koopaH * 3 / 4.f, koopaW / 4.f, koopaH * 2 / 5.f);
}

int Koopa::getLifes()
{
    return life;
}

void Koopa::touched()
{
    --life;
    dmg = true;

    koopaW = 32; koopaH = 30;
    updateColisions();
    koopa.setOrigin(koopaW/2.f, koopaH);
    koopa.setAnimation(&animations[Koopa::Animations::STOP_A]);

    dmgTime = sf::Time::Zero;

    if (life <= 0)
    {
        alive = false;
    }
}

bool Koopa::getDmg()
{
    return dmg;
}

bool Koopa::isJumping()
{
    return jumping;
}

bool Koopa::isInside()
{
    return inside;
}

bool Koopa::isAlive() const
{
    return alive;
}

sf::FloatRect Koopa::getBodyPart(Koopa::Body bodyPart)
{
    sf::FloatRect tmp = bodyParts[bodyPart];
    tmp.left += koopa.getPosition().x;
    tmp.top += koopa.getPosition().y;
    return tmp;
}

void Koopa::setMovement(Koopa::Direction direction, Koopa::Velocity velocity)
{
    if(!inside)
    {
        switch (direction)
        {
        case Koopa::Direction::RIGHT:
            vel.x = velocities[velocity];
            if (!dmg && velocity == Koopa::Velocity::WALK)
            {
                koopaW = 32; koopaH = 48;
                updateColisions();
                koopa.setOrigin(koopaW/2.f, koopaH);
                koopa.setAnimation(&animations[Koopa::Animations::RIGHT_A]);
            }
            else if (!dmg && velocity == Koopa::Velocity::STOP)
            {
                koopaW = 32; koopaH = 48;
                updateColisions();
                koopa.setOrigin(koopaW/2.f, koopaH);
                koopa.setAnimation(&animations[Koopa::Animations::IDLE_RIGHT_A]);
            }
            break;

        case Koopa::Direction::LEFT:
            vel.x = -velocities[velocity];
            if (!dmg && velocity == Koopa::Velocity::WALK)
            {
                koopaW = 32; koopaH = 48;
                updateColisions();
                koopa.setOrigin(koopaW/2.f, koopaH);
                koopa.setAnimation(&animations[Koopa::Animations::LEFT_A]);
            }
            else if (!dmg && velocity == Koopa::Velocity::STOP)
            {
                koopaW = 32; koopaH = 48;
                updateColisions();
                koopa.setOrigin(koopaW/2.f, koopaH);
                koopa.setAnimation(&animations[Koopa::Animations::IDLE_LEFT_A]);
            }
            break;
        }
    }
}

void Koopa::jump()
{
    if (!jumping)
    {
        vel.y = -jumpVel;
        jumping = true;
    }
}

void Koopa::shell()
{
    if(currentDist >= distForAbility && vel.x != 0)
    {
        inside = true;
        insideTime = sf::Time::Zero;

        koopaW = 36; koopaH = 48;
        updateColisions();
        koopa.setOrigin(koopaW/2.f, koopaH);
        koopa.setAnimation(&animations[Koopa::Animations::IN_A]);
        animations[Koopa::Animations::IN_A].setCurrentFrame(0);

        if(vel.x > 0)
        {
            vel.x = velocities[Koopa::Velocity::WALK];
        }
        else if(vel.x < 0)
        {
            vel.x = -velocities[Koopa::Velocity::WALK];
        }
    }
}