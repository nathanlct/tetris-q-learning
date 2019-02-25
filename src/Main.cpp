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
      if (event.type == sf::Event::Closed)
        window.close();
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
