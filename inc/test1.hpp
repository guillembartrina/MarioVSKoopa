#ifndef TEST1_HPP
#define TEST1_HPP

#include <iostream>

#include "scene.hpp"
#include "game.hpp"
#include "colisions.hpp"
#include "koopa.hpp"
#include "mario.hpp"

class Test1 : public Scene
{
  public:
	Test1(Game &game);
	~Test1() final;

	void onInit() final;
	void onResume() final;
	void onPause() final;
	void onEnd() final;

	void event(const sf::Event &event) final;
	void update(const sf::Time &deltatime);
	void draw(sf::RenderWindow &window) const;

  private:
	sf::Font font;

	sf::Text charLife;
	sf::Text charLifeN;

	//Characters
	Koopa koopa;
	Mario mario;

	sf::Text koopaWin;
	sf::Text marioWin;

	//Map
	sf::Texture colisionTexture;
	sf::Sprite colision;
	std::vector<sf::Sprite> colisionsS;
	Colisions colisions;
	sf::FloatRect floorC;

	sf::Texture castleTexture;
	sf::Texture flagTexture;
	sf::Sprite castle;
	Animation flagAnimation;
	AnimatedSprite flag;
};

#endif