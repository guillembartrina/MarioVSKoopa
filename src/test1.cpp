#include "test1.hpp"

Test1::Test1(Game& game) : Scene(game), flag(flagTexture, &flagAnimation) {}
Test1::~Test1() {}

void Test1::onInit() {
	Scene::onInit();

	//Map init
	if(!colisionTexture.loadFromFile("res/img/colisionTexture.png"))
    {
        std::cout << "Error loading <colisionTexture.png>." << std::endl;
    }

	colision.setTexture(colisionTexture);

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
	floorC = sf::FloatRect(0, 800, 1000, 88);
	capC = sf::FloatRect(0, 500, 200, 100);

	colisions.addColision(floorC);
	colisions.addColision(capC);

	for(unsigned int i = 0; i < colisions.getNumColisions(); ++i)
	{
		sf::FloatRect tmp = colisions.getColision(i);
		colision.setPosition(tmp.left, tmp.top);
		colision.setTextureRect(sf::IntRect(0, 0, tmp.width, tmp.height));
		colisionsS.push_back(colision);
	}

	//Char init
	koopa.init();
	koopa.setColisions(colisions.getColisions());
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
	 Scene::event(event);
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

			case sf::Keyboard::D:
			koopa.debug = !koopa.debug;
			break;

			default:
			break;
		}
   }
}

void Test1::update(const sf::Time& deltatime)
{
	Scene::update(deltatime);
	flag.update(deltatime);
	koopa.update(deltatime);
}

void Test1::draw(sf::RenderWindow& window) const
{
	Scene::draw(window);
	window.draw(castle);
	window.draw(flag);
	for(const sf::Sprite& col : colisionsS)
	{
		window.draw(col);
	}
	koopa.draw(window);
}