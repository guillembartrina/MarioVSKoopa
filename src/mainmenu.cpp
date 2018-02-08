#include "mainmenu.hpp"

	MainMenu::MainMenu(Game& game) : Scene(game) {}
	MainMenu::~MainMenu() {}

	void MainMenu::onInit() 
	{
		Scene::onInit();
		if(!font.loadFromFile("res/fonts/font.ttf"))
		{
			std::cout << "Error loading <font.ttf>." << std::endl;
		}

		if(!textureCursor.loadFromFile("res/img/cursor.png"))
		{
			std::cout << "Error loading <cursor.png>." << std::endl;
		}

		if(!castleTexture.loadFromFile("res/img/castleTexture.png"))
		{
			std::cout << "Error loading <castleTexture.png>." << std::endl;	
		}

		castle.setTexture(castleTexture);
		castle.setColor(sf::Color(128, 128, 128));

	  cursorState = MainMenu::PLAY;
	}

	void MainMenu::onResume() 
	{
		Scene::onResume();
	}

	void MainMenu::onPause()  
	{
		Scene::onPause();
	}

	void MainMenu::onEnd() 
	{
		Scene::onEnd();
	}

	void MainMenu::update(const sf::Time& deltatime) 
	{

	}

	void MainMenu::draw(sf::RenderWindow& window) const 
	{
		window.draw(castle);
		drawTexts(window);
		drawCursor(window);
	}

	void MainMenu::event(const sf::Event& event) 
	{
		if (event.type == sf::Event::KeyPressed) 
	  {
	    switch (event.key.code) 
	    {
	      case sf::Keyboard::Up:
		if (cursorState == MainMenu::PLAY)
		  cursorState = MainMenu::EXIT;
		else if (cursorState == MainMenu::ABOUT)
		  cursorState = MainMenu::PLAY;
		else if (cursorState == MainMenu::EXIT)
		  cursorState = MainMenu::ABOUT;
		break;

	      case sf::Keyboard::Down:
		if (cursorState == MainMenu::PLAY)
		  cursorState = MainMenu::ABOUT;
		else if (cursorState == MainMenu::ABOUT)
		  cursorState = MainMenu::EXIT;
		else if (cursorState == MainMenu::EXIT)
		  cursorState = MainMenu::PLAY;
		break;

	      case sf::Keyboard::Return:
		if (cursorState == MainMenu::PLAY) 
		{
			game.setBackgroundScene(Scene::create(game, Scene::TEST_1));
			pause();
		} else if (cursorState == MainMenu::ABOUT) 
		{
			game.setBackgroundScene(Scene::create(game, Scene::TEST_2));
			pause();
		} else if (cursorState == MainMenu::EXIT) 
		{
		  end();
		}
		break;

	      default:
		break;
	    }
	  }
	}

	void MainMenu::drawTexts(sf::RenderWindow& window) const 
	{
	  sf::Text text;
	  text.setFont(font);
	  text.setColor(sf::Color::Green);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(0.2f);
		text.setStyle(sf::Text::Bold && sf::Text::Underlined);
  	text.setScale(3.5f, 3.5f);

  	// Draw title
  	text.setPosition(40, 100);
  	text.setString("KOOPA VS MARIO");
  	window.draw(text);

		// Draw options
		text.setColor(sf::Color::White);
		text.setStyle(sf::Text::Bold);
		text.setScale(3.f, 3.f);
		text.setPosition(300, 370);
		text.setString("PLAY");
		window.draw(text);
		text.move(0, 100.f);
		text.setString("ABOUT");
		window.draw(text);
		text.move(0, 100.f);
		text.setString("EXIT");
		window.draw(text);
}

void MainMenu::drawCursor(sf::RenderWindow& window) const 
{
  sf::Sprite sprite(textureCursor);
  sprite.setColor(sf::Color::Black);
	sprite.setScale(1.5f, 1.5f);

  sprite.setPosition(230, 415);

  if (cursorState == MainMenu::ABOUT) {
    sprite.move(0, 100.f);
  } else if (cursorState == MainMenu::EXIT) {
    sprite.move(0, 200.f);
  }

  window.draw(sprite);
}
