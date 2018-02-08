
#include "koopa.hpp"

Koopa::Koopa() : koopa(koopaTexture, &animations[0])
{
    velocities[STOP] = 0.f;
    velocities[WALK] = 0.3f;
    velocities[RUN] = 0.6f;

    bodyParts[HEAD] = sf::FloatRect(-koopaW/4.f, -koopaH, koopaW/2.f, koopaH/4.f);
    bodyParts[FEET] = sf::FloatRect(-koopaW/4.f, -koopaH/4.f, koopaW/2.f, koopaH/4.f);
    bodyParts[L_BODY] = sf::FloatRect(-koopaW/2.f, -koopaH*3/4.f, koopaW/4.f, koopaH/3.f);
    bodyParts[R_BODY] = sf::FloatRect(koopaW/4.f, -koopaH*3/4.f , koopaW/4.f, koopaH/3.f);

    life = maxLife;
    jumping = false;
    setMovement(Direction::RIGHT, Velocity::STOP);

    head.setSize(sf::Vector2f(bodyParts[HEAD].width, bodyParts[HEAD].height));
    feet.setSize(sf::Vector2f(bodyParts[FEET].width, bodyParts[FEET].height));
    l_body.setSize(sf::Vector2f(bodyParts[L_BODY].width, bodyParts[L_BODY].height));
    r_body.setSize(sf::Vector2f(bodyParts[R_BODY].width, bodyParts[R_BODY].height));
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

    animations[Koopa::IDLE_RIGHT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 6; ++i) 
    {
	    animations[Koopa::IDLE_RIGHT_A].addFrame(sf::IntRect(i*koopaW, koopaH*1, koopaW, koopaH));
    }

    animations[Koopa::IDLE_LEFT_A].setFrameTime(sf::seconds(0.125f));

    for (int i = 0; i < 6; ++i) 
    {
	    animations[Koopa::IDLE_LEFT_A].addFrame(sf::IntRect(i*koopaW, koopaH*0, koopaW, koopaH));
    }
    
    animations[Koopa::RIGHT_A].setFrameTime(sf::seconds(0.075f));

    for (int i = 0; i < 10; ++i) 
    {
	    animations[Koopa::RIGHT_A].addFrame(sf::IntRect(i*koopaW, koopaH*3, koopaW, koopaH));
    }

    animations[Koopa::LEFT_A].setFrameTime(sf::seconds(0.075f));

    for (int i = 0; i < 10; ++i) 
    {
	    animations[Koopa::LEFT_A].addFrame(sf::IntRect(i*koopaW, koopaH*2, koopaW, koopaH));
    }

    koopa.setOrigin(sf::Vector2f(koopaW/2, koopaH));
    koopa.setPosition(sf::Vector2f(100.f, 100.f));
    koopa.setAnimation(&animations[IDLE_RIGHT_A]);

}

void Koopa::update(const sf::Time& deltatime)
{
    koopa.update(deltatime);

    vel.y += gravity * float(deltatime.asMilliseconds());

    koopa.move(vel * float(deltatime.asMilliseconds()));

    if(debug)
    {
        head.setPosition(koopa.getPosition().x + bodyParts[HEAD].left, koopa.getPosition().y + bodyParts[HEAD].top);
        feet.setPosition(koopa.getPosition().x + bodyParts[FEET].left, koopa.getPosition().y + bodyParts[FEET].top);
        l_body.setPosition(koopa.getPosition().x + bodyParts[L_BODY].left, koopa.getPosition().y + bodyParts[L_BODY].top);
        r_body.setPosition(koopa.getPosition().x + bodyParts[R_BODY].left, koopa.getPosition().y + bodyParts[R_BODY].top);
    }

    checkColisions();
}

void Koopa::draw(sf::RenderWindow& window) const
{
    if(debug)
    {
        window.draw(head);
        window.draw(feet);
        window.draw(l_body);
        window.draw(r_body);
    }
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

unsigned int Koopa::getColisionIndex(const sf::FloatRect& box)
{
    for(unsigned int i = 0; i < colisionRects.size(); ++i)
    {
        if(box.intersects(colisionRects[i])) return i;
    }
    return -1;
}

void Koopa::checkColisions()
{
    float x = koopa.getPosition().x;
    float y = koopa.getPosition().y;

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
        koopa.setPosition(koopa.getPosition().x, colisionRects[hCol].top+colisionRects[hCol].height+koopaH);
        vel.y = 0;
    }

    if(bCol != -1)
    {
        if(debug) std::cout << "Feet colision!" << std::endl;
        koopa.setPosition(koopa.getPosition().x, colisionRects[bCol].top);
        jumping = false;
        vel.y = 0;
    }

    if(lCol != -1)
    {
        if(debug) std::cout << "Left colision!" << std::endl;
        koopa.setPosition(colisionRects[lCol].left+colisionRects[lCol].width+koopaW/2.f, koopa.getPosition().y);
    }

    if(rCol != -1)
    {
        if(debug) std::cout << "Right colision!" << std::endl;
        koopa.setPosition(colisionRects[rCol].left-koopaW/2.f, koopa.getPosition().y);
    }
    
}

int Koopa::getLifes()
{
    return life;
}

void Koopa::touched()
{
    --life;
    if(life <= 0) koopa.setRotation(90.f);
}

void Koopa::setMovement(Koopa::Direction direction, Koopa::Velocity velocity)
{
    switch(direction)
    {
        case Direction::RIGHT:
        vel.x = velocities[velocity];
        if(velocity == Velocity::WALK) koopa.setAnimation(&animations[RIGHT_A]);
        else if(velocity == Velocity::STOP) koopa.setAnimation(&animations[IDLE_RIGHT_A]);
        break;

        case Direction::LEFT:
        vel.x = -velocities[velocity];
        if(velocity == Velocity::WALK) koopa.setAnimation(&animations[LEFT_A]);
        else if(velocity == Velocity::STOP) koopa.setAnimation(&animations[IDLE_LEFT_A]);
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