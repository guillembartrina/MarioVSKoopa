
#include "colisions.hpp"

Colisions::Colisions() {}
Colisions::~Colisions()
{
    rects.clear();
}

void Colisions::addColision(const sf::FloatRect& colision)
{
    rects.push_back(colision);
}

void Colisions::clearColisions()
{
    rects.clear();
}

std::vector<sf::FloatRect> Colisions::getColisions()
{
    return rects;
}

sf::FloatRect Colisions::getColision(unsigned int num)
{
    if(num > rects.size())
    {
        return sf::FloatRect(0, 0, 0, 0);
    }
    else
    {
        return rects[num-1];
    }
}

int Colisions::checkColisions(const sf::FloatRect& obj)
{
    if(rects.empty()) 
    {
        return -1;
    }
    else
    {
        for(unsigned int i = 0; i < rects.size(); ++i)
        {
            if(rects[i].intersects(obj)) return i;
        }
    }

    return -1;
}