#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

#include "Game.hpp"

int main () {
  sf::RenderWindow window(sf::VideoMode(1000, 1200), "Tetris (Q-Learning)");

  constexpr float MAX_FPS = 60;
  const float time_between_frames = 1.0 / MAX_FPS;

  sf::Clock clock;

  sf::Vector2i grid_size { 10, 20 };
  Game game(grid_size);

  game.run();

  sf::Transform grid_transform;
  grid_transform.translate(400, 100);

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
      window.clear(sf::Color(130, 200, 250));
      sf::Time elapsed = clock.restart();;

      game.update(elapsed.asMilliseconds());
      window.draw(game.get_grid(), grid_transform);

      window.display();
    }
  }

  return 0;
}
