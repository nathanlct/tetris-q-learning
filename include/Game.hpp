// Game.hpp

#ifndef GAME_H
#define GAME_H




#include <SFML/System.hpp>

#include "Board.hpp"

enum class GameState { running, paused, stopped };

class Game
{
public:
	Game(sf::Vector2i board_size);

	void init ();
	void stop ();
	void run ();
	void pause ();
	void resume ();
	void update (double dt);

	GameState get_current_state () const;

	void key_pressed (sf::Keyboard::Key key);
	void key_released (sf::Keyboard::Key key);

	const Board& get_board () const;

	float get_fps () const;


private:
	Board board;
	
	GameState state;

	float falling_timer;
	float falling_speed;

	static constexpr float normal_falling_speed = 300;
	static constexpr float fast_falling_speed = 100;

	float fps;
};

#endif
