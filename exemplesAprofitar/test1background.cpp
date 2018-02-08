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
	
	
	if (!texCastell.loadFromFile("res/img/castellPeach.png")) {		
        std::cout << "Error loading <castellPeach.png>." << std::endl;
	}	
	
    std::cout << "Error loading" << std::endl;
	spCastell.setTexture(texCastell);	
    spCastell.setTextureRect(sf::IntRect(0, 0, 1000, 888));
	
	if (!texBand.loadFromFile("res/img/banderesPeach.png")) {		
        std::cout << "Error loading <banderesPeach.png>." << std::endl;
	}	
	
	for (int i = 0; i < 3; i++) {
		int posX1 = i * 1000;
		banderesOnejant.addFrame({posX1, 0, 1000, 888});
	}
	
	banderesOnejant.setFrameTime(sf::seconds(0.2f));
	banderesOnejant.play();
	spBand.setTexture(texBand);
	spBand.setAnimation(&banderesOnejant);
	
	
	
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
	std::cout << "peta 1 " << std::endl;
	spBand.update(deltatime);
	std::cout << "peta 2 " << std::endl;
}

void Test1::draw(sf::RenderWindow& window) const
{
	window.draw(spCastell);
	window.draw(spBand);
	koopa.draw(window);
	
	
	
    window.display();
}
