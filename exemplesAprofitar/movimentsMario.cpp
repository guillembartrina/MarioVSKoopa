#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "animation.hpp"
#include "animatedsprite.hpp"

/**
  Ejemplo 2 - Animaciones
  Crea una ventana SFML con unas dimensiones y titulo determinado
  Carga una textura, la aplica sobre un AnimatedSprite
  Declara e inicializa una animación y la asocia al sprite
  Muestra el AnimatedSprite
*/



int main() {
  const int screenWidth  = 480;
  const int screenHeight = 480;
  const std::string screenTitle = "Koopa Troopa";

  const char TEXTURE_FILE[] = "res/img/MarioTexture.png";
  int etapa = 0;
  //0 parat <    1 parat  >      2 caminant <
  //3 caminant >    4 caminant <    5 amagant closca
  //6 sortint closca   7 closca

  sf::RenderWindow window;
  window.create(sf::VideoMode(screenWidth, screenHeight), screenTitle);

  sf::Clock clk;

  sf::Texture texture;
  if (!texture.loadFromFile(TEXTURE_FILE)) {
    return 1;
  }

  // stand left
  Animation animation;
  animation.setFrameTime(sf::seconds(0.125f));
  
  int ampImatge = 84;
  int altImatge = 51;
  
  for (int i = 33; i < 43; i++) {
    int posX1 = i * ampImatge % (11 * ampImatge);
	int posY1 = altImatge * int(i / 11);
	animation.addFrame({16+posX1, 11 + posY1, 30, 51});
  }
  for (int i = 42; i > 34; i--) {
    int posX1 = i * ampImatge % (11 * ampImatge);
	int posY1 = altImatge * int(i / 11);
	animation.addFrame({16+posX1, 11 + posY1, 30, 51});
  }
  animation.play();
  
  // stand right
  Animation standR;
  standR.setFrameTime(sf::seconds(0.125f));
  
  for (int i = 22; i < 32; i++) {
    int posX1 = i * ampImatge % (11 * ampImatge);
	int posY1 = altImatge * int(i / 11);
	standR.addFrame({16+posX1, 11 + posY1, 30, 51});
  }
  for (int i = 31; i > 23; i--) {
    int posX1 = i * ampImatge % (11 * ampImatge);
	int posY1 = altImatge * int(i / 11);
	standR.addFrame({16+posX1, 11 + posY1, 30, 51});
  }
  standR.play();
  
  
  //walking right
  Animation walkingR;
  walkingR.setFrameTime(sf::seconds(0.125f));
  
  
  for (int i = 0; i < 11; i++) {
    int posX1 = i * ampImatge % (11 * ampImatge);
	int posY1 = altImatge * int(i / 11);
	walkingR.addFrame({16+posX1, 11 + posY1, 38, 51});
  }
  walkingR.play();
  
  //walking left
  Animation walkingL;
  walkingL.setFrameTime(sf::seconds(0.125f));
  
  
  for (int i = 11; i < 22; i++) {
    int posX1 = i * ampImatge % (11 * ampImatge);
	int posY1 = altImatge * int(i / 11);
	walkingL.addFrame({16+posX1, 11 + posY1, 38, 51});
  }
  walkingL.play();
  
  
  //amagar closca
  Animation amagarClosca;
  amagarClosca.setFrameTime(sf::seconds(0.05f));  
  
  int ampClosca = 42;
  for (int i = 2369; i < 2383; i++) {

    int posX1 = (i * ampClosca % (23 * ampClosca));
	int posY1 = altImatge * int(i / 23);
	amagarClosca.addFrame({posX1, posY1-14, 40, altImatge});
  }
  amagarClosca.play();
  amagarClosca.setRepeat(true);
  
  //sortir closca
  Animation sortirClosca;
  sortirClosca.setFrameTime(sf::seconds(0.05f));
  
  
  for (int i = 2382; i > 2368; i--) {
    int posX1 = (i * ampClosca % (23 * ampClosca));
	int posY1 = altImatge * int(i / 23);
	sortirClosca.addFrame({posX1, -14 + posY1, 40, altImatge});
  }
  sortirClosca.setRepeat(true);
  sortirClosca.play();
  
  // closca girant
  Animation girClosca;
  girClosca.setFrameTime(sf::seconds(0.075f));
  
  
  for (int i = 2300; i < 2307; i++) {
    int posX1 = (i * 35 % (23 * 35));
	int posY1 = altImatge * int(i / 23);
	girClosca.addFrame({posX1,-15 + posY1, 40, altImatge-10});
  }
  girClosca.play();

  AnimatedSprite sprite(texture, &standR);
  sprite.setPosition(screenWidth/2 + 20.0f, screenHeight/2);
  sprite.setScale(1.2f, 1.2f);
  sprite.setOrigin(ampImatge/2, altImatge*3/4);

  sf::Event event;
  sf::Time deltatime;

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::Escape:
            window.close();
            break;
          case sf::Keyboard::Up:
            sprite.move(0, -3);
            break;
          case sf::Keyboard::Left:
			if (etapa != 5 and etapa != 7 and etapa != 6) {
				etapa = 2;
				sprite.move(-3, 0);
				sprite.setAnimation(&walkingL);
				sprite.setOrigin(ampImatge/2, altImatge*3/4);
				
			}
            break;
          case sf::Keyboard::Down:
			if (etapa != 5 and etapa != 6 and etapa != 7) {
				amagarClosca.play();
				etapa = 5;
				sprite.setAnimation(&amagarClosca);
				sprite.setOrigin(ampImatge/2, altImatge*3/4);
			} else if (etapa == 6) {
				sortirClosca.play();
				etapa = 7;
				sprite.setAnimation(&sortirClosca);
				sprite.setOrigin(ampImatge/2, altImatge*3/4);
			}
				
            break;
          case sf::Keyboard::Right:
			if (etapa != 5 and etapa != 7 and etapa != 6) {
				etapa = 3;
				sprite.move(3, 0);
				sprite.setAnimation(&walkingR);
				sprite.setOrigin(ampImatge/2, altImatge*3/4);
			}
            break;

          default:
            break;
        }
      } else if (event.type == sf::Event::KeyReleased) {
		  switch (event.key.code) {
			  case sf::Keyboard::Up:
				  animation.play();
				  break;
			  
			  case sf::Keyboard::Down:
				  break;
			  
			  case sf::Keyboard::Right:
				if (etapa != 5 and etapa != 7 and etapa != 6) {
				  etapa = 1;
				  sprite.setAnimation(&standR);
				}
				  break;
			  
			  case sf::Keyboard::Left:
				if (etapa != 5 and etapa != 7 and etapa != 6) {
				  etapa = 0;
				  sprite.setAnimation(&animation);
				}
				  break;
			  default:
			  break;
			  
		  }
	  }
    }
    
    if (amagarClosca.hasended() and etapa == 5) {
		etapa = 6;
		amagarClosca.stop();
		girClosca.play();
		sprite.setAnimation(&girClosca);
		sprite.setOrigin(ampImatge/3, (altImatge-10)*2/3);
	} else if (sortirClosca.hasended() and etapa == 7) {
		etapa = 0;
		sprite.setOrigin(ampImatge/2, altImatge*3/4);
		sprite.setAnimation(&standR);
	}
	    
    deltatime = clk.restart();
    sprite.update(deltatime);

    window.clear(sf::Color::Magenta);
    window.draw(sprite);
    window.display();
  }

  return 0;
}
