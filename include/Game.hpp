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

	Grid& get_grid ();


private:
	Grid grid;
	
	State state;

	float falling_timer;
	float falling_speed;
};

#endif
