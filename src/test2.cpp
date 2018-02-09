#include "test2.hpp"

Test2::Test2(Game& game) : Scene(game) {}
Test2::~Test2() {}

void Test2::onInit() {
	Scene::onInit();
	std::cout << "onInit: Test2" << std::endl;
}

void Test2::onResume() {
	Scene::onResume();
	std::cout << "onResume: Test2" << std::endl;
}

void Test2::onPause()  {
	Scene::onPause();
	std::cout << "onPause: Test2" << std::endl;
}

void Test2::onEnd()    {
	Scene::onEnd();
	std::cout << "onEnd: Test2" << std::endl;
}

void Test2::event(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Q) {
        end();
    }
  }
}
void Test2::draw(sf::RenderWindow& window) const {
	sf::Text credits;
	sf::Font font;
	font.loadFromFile("res/fonts/font.ttf");
	credits.setFont(font);
	credits.setString("Ponc, Guillem and Marc crafted this wonderful masterpiece");
	credits.setPosition(20,333);
	credits.setFillColor(sf::Color::Red);
	sf::Text SS;
        SS.setFont(font);
        SS.setString("SLAVA STALIN");
        SS.setPosition(400,444);
        SS.setFillColor(sf::Color::Red);
	SS.setCharacterSize(68);
	window.draw(credits);
	window.draw(SS);

}
