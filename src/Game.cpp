// Game.cpp

#include "Game.hpp"

Game::Game (sf::Vector2i grid_size) :
    grid (grid_size),
    state { State::stopped },
    falling_timer { 0 },
    falling_speed { 100 }
{
	init();
}

void Game::init () {
    // grid.reset(); 
}

void Game::stop () {
    state = State::stopped;
}

void Game::run () {
    state = State::running;
}

void Game::pause () {
    if (state == State::running) {
        state = State::paused;
    }
}

void Game::resume () {
    if (state == State::paused) {
        state = State::running;
    }
}

void Game::update (double dt) {
    if (state == State::running) {
        falling_timer += dt;
        if (falling_timer >= falling_speed) {
            falling_timer = 0;
            
            if (!grid.move_piece_down()) {
                if (!grid.spawn_new_piece()) {
                    stop();
                }
            }
        }
    }
}

Grid& Game::get_grid () {
    return grid;
}