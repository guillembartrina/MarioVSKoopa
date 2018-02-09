#include "test1.hpp"

Test1::Test1(Game &game) : Scene(game), flag(flagTexture, &flagAnimation) {}
Test1::~Test1() {}

	sf::FloatRect plat1 = sf::FloatRect(0,400,400,40);
	sf::FloatRect plat2 = sf::FloatRect(600,250,80,40);
	sf::FloatRect plat3 = sf::FloatRect(800,350,100,50);
	sf::FloatRect plat4 = sf::FloatRect(600,450,80,40);
	sf::FloatRect plat5 = sf::FloatRect(350,500,120,50);
	sf::FloatRect plat6 = sf::FloatRect(600,600,200,50);
	sf::FloatRect plat7 = sf::FloatRect(0,650,150,50);

	sf::FloatRect leftW = sf::FloatRect(0,0, 15, 888);
	sf::FloatRect rightW = sf::FloatRect(985,0, 50 ,888);



void Test1::onInit()
{
	Scene::onInit();

	if (!font.loadFromFile("res/fonts/font.ttf"))
	{
		std::cout << "Error loading <font.ttf>." << std::endl;
	}

	charLife.setFont(font);
	charLifeN.setFont(font);
	koopaWin.setFont(font);
	marioWin.setFont(font);

	charLife.setPosition(700, 30);
	charLife.setFillColor(sf::Color::Black);
	charLife.setString("KOOPA  -  MARIO");

	charLifeN.setPosition(750, 70);
	charLifeN.setString("-");

	koopaWin.setPosition(150, 300);
	koopaWin.setFillColor(sf::Color::Blue);
	koopaWin.setOutlineThickness(0.2f);
	koopaWin.setCharacterSize(120);
	koopaWin.setString("KOOPA WINS!");

	marioWin.setPosition(150, 300);
	marioWin.setFillColor(sf::Color::Blue);
	marioWin.setOutlineThickness(0.2f);
	marioWin.setCharacterSize(120);
	marioWin.setString("MARIO WINS!");

	
	if (!playingMusic.openFromFile("res/audio/playingM.ogg"))
	{
		std::cout << "Error loading <playingM.ogg>." << std::endl;
	}
	

	
	if (!koopaWinMusic.openFromFile("res/audio/koopaM.ogg"))
	{
		std::cout << "Error loading <koopaM.ogg>." << std::endl;
	}

	if (!marioWinMusic.openFromFile("res/audio/marioM.ogg"))
	{
		std::cout << "Error loading <marioM.ogg>." << std::endl;
	}
	

	//Map init
	if (!colisionTexture.loadFromFile("res/img/colisionTexture.png"))
	{
		std::cout << "Error loading <colisionTexture.png>." << std::endl;
	}

	colision.setTexture(colisionTexture);

	if (!castleTexture.loadFromFile("res/img/castleTexture.png"))
	{
		std::cout << "Error loading <castleTexture.png>." << std::endl;
	}

	castle.setTexture(castleTexture);
	castle.setTextureRect(sf::IntRect(0, 0, 1000, 888));

	if (!flagTexture.loadFromFile("res/img/flagTexture.png"))
	{
		std::cout << "Error loading <flagTexture.png>." << std::endl;
	}

	for (int i = 0; i < 3; ++i)
	{
		flagAnimation.addFrame(sf::IntRect(i * 1000, 0, 1000, 888));
	}

	flagAnimation.setFrameTime(sf::seconds(0.2f));

	flag.setTexture(flagTexture);
	flag.setAnimation(&flagAnimation);

	//Colisions

	floorC = sf::FloatRect(0, 800, 1000, 88);
	colisions.addColision(floorC);
	colisions.addColision(plat1);
	colisions.addColision(plat2);
	colisions.addColision(plat3);
	colisions.addColision(plat4);
	colisions.addColision(plat5);
	colisions.addColision(plat6);
	colisions.addColision(plat7);
	colisions.addColision(leftW);
	colisions.addColision(rightW);


	for (unsigned int i = 0; i < colisions.getNumColisions(); ++i)
	{
		sf::FloatRect tmp = colisions.getColision(i);
		colision.setPosition(tmp.left, tmp.top - 4);
		colision.setTextureRect(sf::IntRect(0, 0, tmp.width, tmp.height + 4));
		colisionsS.push_back(colision);
	}

	//Char init
	koopa.init();
	koopa.setColisions(colisions.getColisions());

	mario.init();
	mario.setColisions(colisions.getColisions());

	playingMusic.play();
}

void Test1::onResume()
{
	Scene::onResume();
}

void Test1::onPause()
{
	Scene::onPause();
}

void Test1::onEnd()
{
	Scene::onEnd();
}

void Test1::event(const sf::Event &event)
{
	Scene::event(event);
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
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
			if(!koopa.getDmg()) koopa.jump();
			break;

		case sf::Keyboard::D:
			mario.setMovement(Mario::Direction::RIGHT, Mario::Velocity::WALK);
			break;

		case sf::Keyboard::A:
			mario.setMovement(Mario::Direction::LEFT, Mario::Velocity::WALK);
			break;

		case sf::Keyboard::W:
			if(!mario.getDmg()) mario.jump();
			break;

		case sf::Keyboard::Down:
			koopa.shell();
			break;
		

		default:
			break;
		}
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Q:
			end();
			break;

		case sf::Keyboard::Right:
			koopa.setMovement(Koopa::Direction::RIGHT, Koopa::Velocity::STOP);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				koopa.setMovement(Koopa::Direction::LEFT, Koopa::Velocity::WALK);
			break;

		case sf::Keyboard::Left:
			koopa.setMovement(Koopa::Direction::LEFT, Koopa::Velocity::STOP);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				koopa.setMovement(Koopa::Direction::RIGHT, Koopa::Velocity::WALK);
			break;

		case sf::Keyboard::D:
			mario.setMovement(Mario::Direction::RIGHT, Mario::Velocity::STOP);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				mario.setMovement(Mario::Direction::LEFT, Mario::Velocity::WALK);
			break;

		case sf::Keyboard::A:
			mario.setMovement(Mario::Direction::LEFT, Mario::Velocity::STOP);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				mario.setMovement(Mario::Direction::RIGHT, Mario::Velocity::WALK);
			break;

		default:
			break;
		}
	}
}

void Test1::update(const sf::Time &deltatime)
{
	Scene::update(deltatime);
	flag.update(deltatime);
	if (koopa.isAlive() && mario.isAlive())
	{
		std::string pre = std::to_string(koopa.getLifes()) + "      " + std::to_string(mario.getLifes());
		charLifeN.setString(pre);
		koopa.update(deltatime);
		mario.update(deltatime);
	}
	else
	{
		castle.setColor(sf::Color(128, 128, 128));
		flag.setColor(sf::Color(128, 128, 128));
		for (sf::Sprite &col : colisionsS)
		{
			col.setColor(sf::Color(128, 128, 128));
		}
	}

	bool koopaCond = (mario.getVelY() > 0) || (mario.isJumping() && koopa.isJumping() && mario.getPosition().y < koopa.getPosition().y);
	if(!koopa.getDmg() && koopaCond && mario.getBodyPart(Mario::Body::FEET).intersects(koopa.getBodyPart(Koopa::Body::HEAD)))
	{
		koopa.touched();
	}

	bool marioCond = koopa.isInside();
	bool koopaHitbox = false;
	if(marioCond)
	{
	koopaHitbox = 		koopa.getBodyPart(Koopa::Body::R_BODY).intersects(mario.getBodyPart(Mario::Body::R_BODY)) ||
						koopa.getBodyPart(Koopa::Body::R_BODY).intersects(mario.getBodyPart(Mario::Body::L_BODY)) ||
						koopa.getBodyPart(Koopa::Body::R_BODY).intersects(mario.getBodyPart(Mario::Body::HEAD)) ||
						koopa.getBodyPart(Koopa::Body::L_BODY).intersects(mario.getBodyPart(Mario::Body::R_BODY)) ||
						koopa.getBodyPart(Koopa::Body::L_BODY).intersects(mario.getBodyPart(Mario::Body::L_BODY)) ||
						koopa.getBodyPart(Koopa::Body::L_BODY).intersects(mario.getBodyPart(Mario::Body::HEAD)) ||
						koopa.getBodyPart(Koopa::Body::FEET).intersects(mario.getBodyPart(Mario::Body::R_BODY)) ||
						koopa.getBodyPart(Koopa::Body::FEET).intersects(mario.getBodyPart(Mario::Body::L_BODY)) ||
						koopa.getBodyPart(Koopa::Body::FEET).intersects(mario.getBodyPart(Mario::Body::HEAD));
	}

	std::cout << koopaHitbox << std::endl;

	if(!mario.getDmg() && marioCond && koopaHitbox)
	{
		mario.touched();
	}

	if(!koopa.isAlive())
	{
		playingMusic.stop();
		marioWinMusic.play();
	}

	if(!mario.isAlive())
	{
		playingMusic.stop();
		koopaWinMusic.play();
	}
}

void Test1::draw(sf::RenderWindow &window) const
{
	Scene::draw(window);

	window.draw(castle);
	window.draw(flag);
	for (const sf::Sprite &col : colisionsS)
	{
		window.draw(col);
	}

	koopa.draw(window);
	mario.draw(window);

	window.draw(charLife);
	window.draw(charLifeN);

	if (!koopa.isAlive())
	{
		window.draw(marioWin);
	}

	if (!mario.isAlive())
	{
		window.draw(koopaWin);
	}
}
