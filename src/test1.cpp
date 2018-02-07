#include "test1.hpp"

Test1::Test1(Game& game) : Scene(game)
{

}
Test1::~Test1() {}

void Test1::onInit() {
	Scene::onInit();

	//Char init
	koopa.init();
	
	//Map init
	floor = sf::FloatRect(0, 500, 1000, 100);
}

void Test1::onResume() {
	Scene::onResume();
}

void Test1::onPause()  {
	Scene::onPause();
}

void Test1::onEnd()    {
	Scene::onEnd();
}

void Test1::event(const sf::Event& event)
 {
	if (event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Q:
			end();
			break;

			case sf::Keyboard::Right:
			koopa.setMovement(Koopa::Direction::RIGHT, Koopa::Velocity::WALK);
			break;

			case sf::Keyboard::Left:
			koopa.setMovement(Koopa::Direction::LEFT, Koopa::Velocity::WALK);
			break;

			case sf::Keyboard::Up:
			koopa.jump();
			break;

			default:
			break;
		}
    }
   else if (event.type == sf::Event::KeyReleased)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Q:
			end();
			break;

			case sf::Keyboard::Right:
			koopa.setMovement(Koopa::Direction::RIGHT, Koopa::Velocity::STOP);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) koopa.setMovement(Koopa::Direction::LEFT, Koopa::Velocity::WALK);
			break;

			case sf::Keyboard::Left:
			koopa.setMovement(Koopa::Direction::LEFT, Koopa::Velocity::STOP);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) koopa.setMovement(Koopa::Direction::RIGHT, Koopa::Velocity::WALK);
			break;

			default:
			break;
		}
   }
}

void Test1::update(const sf::Time& deltatime)
{
	koopa.update(deltatime, floor);
}

void Test1::draw(sf::RenderWindow& window) const
{
	koopa.draw(window);
}