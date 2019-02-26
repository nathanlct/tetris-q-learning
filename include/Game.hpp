// Game.hpp

#ifndef GAME_H
#define GAME_H




#include <SFML/System.hpp>

#include "Grid.hpp"

enum class State { running, paused, stopped };

class Game
{
public:
	Game(sf::Vector2i grid_size);

	void init ();
	void stop ();
	void run ();
	void pause ();
	void resume ();
	void update (double dt);

	void key_pressed (sf::Keyboard::Key key);
	void key_released (sf::Keyboard::Key key);

	Grid& get_grid ();


private:
	Grid grid;
	
	State state;

	float falling_timer;
	float falling_speed;

	static constexpr float normal_falling_speed = 300;
	static constexpr float fast_falling_speed = 100;
};

#endif
