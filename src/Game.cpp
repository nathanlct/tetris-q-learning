// Game.cpp

#include "Game.hpp"

Game::Game (sf::Vector2i grid_size) :
    grid (grid_size),
    state { State::stopped },
    falling_timer { 0 },
    falling_speed { normal_falling_speed }
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

void Game::key_pressed (sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::A:
            if (state == State::running) grid.execute_action(Action::rotate_left);
            break;
        case sf::Keyboard::E:
            if (state == State::running) grid.execute_action(Action::rotate_right);
            break;
        case sf::Keyboard::Q:
            if (state == State::running) grid.execute_action(Action::move_left);
            break;
        case sf::Keyboard::D:
            if (state == State::running) grid.execute_action(Action::move_right);
            break;
        case sf::Keyboard::Z:
            if (state == State::running) grid.execute_action(Action::hard_drop);
            break;
        case sf::Keyboard::S:
            if (state == State::running) falling_speed = fast_falling_speed;
            break;
        case sf::Keyboard::Space:
            pause();
            break;
        default:
            break;
    }
}

void Game::key_released (sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::S:
            falling_speed = normal_falling_speed;
            break;
        case sf::Keyboard::Space:
            resume();
            break;
        default:
            break;
    }
}


Grid& Game::get_grid () {
    return grid;
}