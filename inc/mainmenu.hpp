#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "scene.hpp"
#include "game.hpp"
#include <iostream>

class MainMenu : public Scene {
public:
	MainMenu(Game& game);
	~MainMenu() final;

	void onInit() final;
	void onResume() final;
	void onPause() final;
	void onEnd() final;

	void update(const sf::Time& deltatime) final;
	void draw(sf::RenderWindow& window) const final;
	void event(const sf::Event& event) final;

private:

  sf::Font font;

  sf::Texture textureCursor;

  enum CursorState {
    PLAY,
    ABOUT,
    EXIT,
    NUM_STATES
  };
  CursorState cursorState;

	void drawTexts(sf::RenderWindow& window) const;
	void drawCursor(sf::RenderWindow& window) const;
};

#endif