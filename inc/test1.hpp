#ifndef TEST1_HPP
#define TEST1_HPP

#include <iostream>

#include "scene.hpp"
#include "game.hpp"
#include "koopa.hpp"

class Test1 : public Scene {
	public:
	Test1(Game& game);
	~Test1() final;

	void onInit() final;
	void onResume() final;
	void onPause() final;
	void onEnd() final;

	void event(const sf::Event& event) final;
	void update(const sf::Time& deltatime);
	void draw(sf::RenderWindow& window) const;

	private:

	//Characters	
	Koopa koopa;

	//Map
	sf::FloatRect floor;

};

#endif