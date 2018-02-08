#ifndef COLISIONS_HPP
#define COLISIONS_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

class Colisions{
public:
	Colisions();
	~Colisions();

	void addColision(const sf::FloatRect& colision);
	void clearColisions();
	unsigned int getNumColisions();

	std::vector<sf::FloatRect> getColisions();
	sf::FloatRect getColision(unsigned int num);

private:
	std::vector<sf::FloatRect> rects;
};

#endif