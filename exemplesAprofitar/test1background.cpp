#include "test1.hpp"

Test1::Test1(Game& game) : Scene(game) {}
Test1::~Test1() {}

void Test1::onInit() {
	Scene::onInit();

	//Map init
    if(!castleTexture.loadFromFile("res/img/castleTexture.png"))
    {
        std::cout << "Error loading <castleTexture.png>." << std::endl;
    }

    castle.setTexture(castleTexture);
    castle.setTextureRect(sf::IntRect(0, 0, 1000, 888));

	if(!flagTexture.loadFromFile("res/img/flagTexture.png"))
    {
        std::cout << "Error loading <flagTexture.png>." << std::endl;
    }

	for(int i = 0; i < 3; ++i)
	{
		flagAnimation.addFrame(sf::IntRect(i*1000, 0, 1000, 888));
	}

	flagAnimation.setFrameTime(sf::seconds(0.2f));

	flag.setTexture(flagTexture);
	flag.setAnimation(&flagAnimation);
	
	//Colisions
	floor = sf::FloatRect(0, 500, 1000, 100);
<<<<<<< HEAD:src/test1.cpp
	cap = sf::FloatRect(0, 400, 200, 100);

	colisions.addColision(floor);
	colisions.addColision(cap);

	//Char init
	koopa.init();
	koopa.setColisions(colisions.getColisions());
=======
	
	
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
	
	
	
>>>>>>> 84a4e9ddd82636999fe8f4af3c4a7f1a228ceac8:exemplesAprofitar/test1background.cpp
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
<<<<<<< HEAD:src/test1.cpp
	koopa.update(deltatime);
	flag.update(deltatime);
=======
	koopa.update(deltatime, floor);
	std::cout << "peta 1 " << std::endl;
	spBand.update(deltatime);
	std::cout << "peta 2 " << std::endl;
>>>>>>> 84a4e9ddd82636999fe8f4af3c4a7f1a228ceac8:exemplesAprofitar/test1background.cpp
}

void Test1::draw(sf::RenderWindow& window) const
{
<<<<<<< HEAD:src/test1.cpp
	window.draw(castle);
	window.draw(flag);
=======
	window.draw(spCastell);
	window.draw(spBand);
>>>>>>> 84a4e9ddd82636999fe8f4af3c4a7f1a228ceac8:exemplesAprofitar/test1background.cpp
	koopa.draw(window);
	
	
	
    window.display();
}
