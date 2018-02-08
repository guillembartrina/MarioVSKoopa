#include "mainmenu.hpp"

	MainMenu::MainMenu(Game& game) : Scene(game) {}
	MainMenu::~MainMenu() {}

	void MainMenu::onInit() 
	{
		Scene::onInit();
		font.loadFromFile("res/fonts/font.ttf");
		textureCursor.loadFromFile("res/img/cursor.png");

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
	  text.setColor(sf::Color::White);
  text.setScale(2.f, 2.f);

  // Draw title
  text.setPosition(200, 100);
  text.setString("KOOPA VS MARIO");
  window.draw(text);

  // Draw options
  text.setPosition(300, 200);
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
  sprite.setColor(sf::Color::Magenta);

  sprite.setPosition(250, 200);

  if (cursorState == MainMenu::ABOUT) {
    sprite.move(0, 100);
  } else if (cursorState == MainMenu::EXIT) {
    sprite.move(0, 200);
  }

  window.draw(sprite);
}
