// Game.cpp

#include "Game.hpp"

Game::Game (sf::Vector2i board_size) :
    board (board_size, score),
    state { GameState::stopped },
    falling_timer { 0 },
    falling_speed { normal_falling_speed },
    score { 0 },
    terminate { false }
{
	init();
}

void Game::init () {
    board.reset();
    score = 0;
}

void Game::stop () {
    state = GameState::stopped;
}

void Game::run () {
    state = GameState::running;
}

void Game::pause () {
    if (state == GameState::running) {
        state = GameState::paused;
    }
}

void Game::resume () {
    if (state == GameState::paused) {
        state = GameState::running;
    }
}

GameState Game::get_current_state () const {
    return state;
}


bool Game::update (double dt) {
    if (terminate) {
        return false;
    }

    fps = 1000. / dt;

    if (state == GameState::running) {
        falling_timer += dt;
        if (falling_timer >= falling_speed) {
            falling_timer = 0;
            
            if (!board.move_piece_down()) {
                if (!board.spawn_new_piece()) {
                    stop();
                }
            }
            else {
                if (falling_speed == fast_falling_speed) {
                    score += 1;
                }
            }
        }
    }

    return true;
}

void Game::key_pressed (sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::K:
            if (state == GameState::running) board.execute_action(Action::rotate_left);
            break;
        case sf::Keyboard::M:
            if (state == GameState::running) board.execute_action(Action::rotate_right);
            break;
        case sf::Keyboard::Q:
            if (state == GameState::running) board.execute_action(Action::move_left);
            break;
        case sf::Keyboard::D:
            if (state == GameState::running) board.execute_action(Action::move_right);
            break;
        case sf::Keyboard::Z:
            if (state == GameState::running) board.execute_action(Action::hard_drop);
            break;
        case sf::Keyboard::S:
            if (state == GameState::running) falling_speed = fast_falling_speed;
            break;
        case sf::Keyboard::Space:
            pause();
            break;
        case sf::Keyboard::Return:
            if (state == GameState::stopped) {
                init();
                run();
            }
            break;
        case sf::Keyboard::W:
            if (state != GameState::running) {
                terminate = true;
            }
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


const Board& Game::get_board () const {
    return board;
}

float Game::get_fps () const {
    return fps;
}

size_t Game::get_score () const {
    return score;
}