// UI.cpp

#include "UI.hpp"

const sf::Vector2i UI::win_size { 1000, 1200 };
const sf::Color UI::bg_color { 130, 200, 250 };


UI::UI (const Game& game) :
    game (game),
    board_size (game.get_board().get_size()),
    board_transform {},
    info_transform {},
    board_background {{ cell_size.x * board_size.x, cell_size.y * board_size.y }},
    board_grid { sf::Lines }
{
    board_transform.translate(400, 100);
    info_transform.translate(50, 100);

    board_background.setFillColor(sf::Color::White);
    board_background.setOutlineColor(sf::Color::Black);
    board_background.setOutlineThickness(3.0);

    for (auto x = 0; x <= board_size.x; ++x) {
        sf::Vertex top (cell_size.x * sf::Vector2f(x, 0), board_color);
        sf::Vertex bottom (cell_size.x * sf::Vector2f(x, board_size.y), board_color);
        board_grid.append(top);
        board_grid.append(bottom);
    }

    for (auto y = 0; y <= board_size.y; ++y) {
        sf::Vertex left (cell_size.y * sf::Vector2f(0, y), board_color);
        sf::Vertex right (cell_size.y * sf::Vector2f(board_size.x, y), board_color);
        board_grid.append(left);
        board_grid.append(right);
    }
}

void UI::draw (sf::RenderTarget& target, sf::RenderStates states) const {
    draw_board (target, states);

    sf::Font font;
    font.loadFromFile("res/vcr_osd_mono.ttf");

    sf::Text tetris ("Tetris", font, 50);
    tetris.setPosition({ 60, 0 });
    tetris.setFillColor({ 255, 0, 0 });
    target.draw(tetris, info_transform);

    GameState state = game.get_current_state();
    std::string state_txt;
    switch (state) {
        case GameState::paused: state_txt = "Paused"; break;
        case GameState::running: state_txt = "Running"; break;
        case GameState::stopped: state_txt = "Stopped"; break;        
    }

    sf::Text game_state (state_txt, font, 30);
    game_state.setPosition({ 0, 100 });
    target.draw(game_state, info_transform);

    size_t score_val = game.get_score();
    sf::Text score ("Score: " + std::to_string(score_val), font, 30);
    score.setPosition({ 0, 150 });
    target.draw(score, info_transform);

    int fps_val = (int)game.get_fps();
    sf::Text fps (std::to_string(fps_val) + " FPS", font, 30);
    fps.setPosition({ 0, 250 });
    target.draw(fps, info_transform);
}


void UI::draw_board(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(board_background, board_transform);

    // draw background tetriminos (stack)
    for (auto i = 0; i < board_size.y; ++i) {
        for (auto j = 0; j < board_size.x; ++j) {
            auto stack = game.get_board().get_stack();
            if (auto type = stack[i + Piece::box_size][j]) {
                sf::RectangleShape cell (cell_size);
                cell.setPosition(cell_size.x * j, cell_size.y * i);
                cell.setFillColor(piece_color.at(*type));
                target.draw(cell, board_transform);
            }
        }
    }

    // draw current tetrimino
    auto& current_piece = game.get_board().get_current_piece();
    if (current_piece) {
        auto pattern = current_piece->get_pattern();
        for (auto i = 0; i < Piece::box_size; ++i) {
            for (auto j = 0; j < Piece::box_size; ++j) {
                if (pattern[j][i]) {
                    sf::RectangleShape cell (cell_size);
                    sf::Vector2i pos = current_piece->get_pos() + sf::Vector2i(i, j);
                    if (pos.y >= 0) {
                        cell.setPosition(cell_size.x * pos.x, cell_size.y * pos.y);
                        cell.setFillColor(piece_color.at(current_piece->get_type()));
                        target.draw(cell, board_transform);
                    }
                }
            }
        }
    }

    target.draw(board_grid, board_transform);
}