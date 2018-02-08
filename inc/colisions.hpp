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

	std::vector<sf::FloatRect> getColisions();
	sf::FloatRect getColision(unsigned int num);
	int checkColisions(const sf::FloatRect& obj);

private:
	std::vector<sf::FloatRect> rects;
};

#endif