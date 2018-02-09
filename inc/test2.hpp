#ifndef TEST2_HPP
#define TEST2_HPP

#include "scene.hpp"
#include "game.hpp"
#include <iostream>

class Test2 : public Scene {
public:
	Test2(Game& game);
	~Test2() final;

	void onInit() final;
	void onResume() final;
	void onPause() final;
	void onEnd() final;

	void event(const sf::Event& event) final;
	void draw(sf::RenderWindow& window) const final;
private:
	sf::Music music;
};

#endif
