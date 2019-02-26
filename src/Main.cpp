#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

#include "Game.hpp"
#include "UI.hpp"

int main () {
  sf::RenderWindow window(sf::VideoMode(UI::win_size.x, UI::win_size.y), "Tetris (Q-Learning)");

  constexpr float MAX_FPS = 60;
  const float time_between_frames = 1.0 / MAX_FPS;

  sf::Clock clock;

  sf::Vector2i board_size { 10, 20 };
  Game game(board_size);
  UI ui(game);

  game.run();


  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
          game.key_pressed(event.key.code);
          break;

        case sf::Event::KeyReleased:
          game.key_released(event.key.code);
          break;

        default:
          break;
      }
    }

    if (clock.getElapsedTime().asSeconds() >= time_between_frames) {
      window.clear(UI::bg_color);
      sf::Time elapsed = clock.restart();;

      if (!game.update(elapsed.asMilliseconds())) {
        window.close();
      }

      window.draw(ui);
      window.display();
    }
  }

  return 0;
}
