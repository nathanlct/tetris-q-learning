#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode(768, 1024), "Tetris (Q-Learning)");

  constexpr float MAX_FPS = 60;
  const float time_between_frames = 1.0 / MAX_FPS;

  sf::Clock clock;

  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (clock.getElapsedTime().asSeconds() >= time_between_frames) {
      window.clear(sf::Color::White);
      sf::Time elapsed = clock.restart();;

  

      window.display();
    }
  }

  return 0;
}
