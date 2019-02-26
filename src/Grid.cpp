// Grid.cpp

#include "Grid.hpp"


Grid::Grid (sf::Vector2i grid_size) :
    size { grid_size },
    current_piece { nullptr },
    next_pieces { next_pieces_size },
    next_pieces_idx { 0 },
    piece_types { PieceType::I, PieceType::J, PieceType::L, PieceType::O, 
                  PieceType::S, PieceType::T, PieceType::Z },
    spawn_pos { (size.x - Piece::box_size) / 2, - Piece::box_size },
    stack (size.y + Piece::box_size, std::vector<std::optional<PieceType>> (size.x, std::nullopt))
{
    generate_next_pieces();
}

bool Grid::spawn_new_piece () {
    PieceType type = next_piece();
    current_piece = std::unique_ptr<Piece>(new Piece(type, spawn_pos));

    if (!hay_collision(*current_piece)) {
        return true;
    }
    else {
        current_piece = nullptr;
        return false;
    }
}

bool Grid::hay_collision (Piece piece) {
    auto pattern = piece.get_pattern();

    for (auto i = 0; i < Piece::box_size; ++i) {
        for (auto j = 0; j < Piece::box_size; ++j) {
            if (pattern[j][i]) {
                sf::Vector2i pos = piece.get_pos() + sf::Vector2i(i, j);
                if (pos.y >= size.y || pos.x >= size.x || pos.x < 0 || stack[pos.y + Piece::box_size][pos.x]) {
                    return true;
                }
            }
        }
    }   

    return false;
}

bool Grid::move_piece_down () {

    if (current_piece) {
        Piece tmp_piece = *current_piece;
        tmp_piece.move_down();

        if (!hay_collision(tmp_piece)) {
            current_piece->move_down();
            return true;
        }

        add_piece_to_stack();
        current_piece = nullptr;
    }

    return false;    
}

bool Grid::execute_action (Action action) {

    if (current_piece) {

        if (action == Action::hard_drop) {
            while (current_piece) {
                move_piece_down();
            }
            return true;
        }

        Piece tmp_piece = *current_piece;
        
        switch (action) {
            case Action::rotate_left: tmp_piece.rotate_left(); break;
            case Action::rotate_right: tmp_piece.rotate_right(); break;
            case Action::move_left: tmp_piece.move_left(); break;
            case Action::move_right: tmp_piece.move_right(); break;
            default: return false;
        }

        if (!hay_collision(tmp_piece)) {
            switch (action) {
                case Action::rotate_left: current_piece->rotate_left(); break;
                case Action::rotate_right: current_piece->rotate_right(); break;
                case Action::move_left: current_piece->move_left(); break;
                case Action::move_right: current_piece->move_right(); break;
                default: return false;
            }   
            return true;       
        }
    }

    return false;
}

void Grid::add_piece_to_stack () {
    if (current_piece) {
        auto pattern = current_piece->get_pattern();

        for (auto i = 0; i < Piece::box_size; ++i) {
            for (auto j = 0; j < Piece::box_size; ++j) {
                if (pattern[j][i]) {
                    sf::Vector2i pos = current_piece->get_pos() + sf::Vector2i(i, j);
                    stack[pos.y + Piece::box_size][pos.x] = current_piece->get_type();
                }
            }
        }    
    }
}

void Grid::generate_next_pieces () {    

    std::sample (piece_types.begin(), piece_types.end(), 
                next_pieces.begin(), next_pieces_size, 
                std::mt19937{std::random_device{}()});

}

PieceType Grid::next_piece () {
    PieceType type = next_pieces[next_pieces_idx];

    if (++next_pieces_idx == next_pieces_size) {
        next_pieces_idx = 0;
        generate_next_pieces();
    }

    return type;
}

void Grid::reset () {
    // TODO
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // TODO no need to compute shapes at each iteration

    // draw background
    sf::RectangleShape background ({ cell_size.x * size.x, cell_size.y * size.y });
    background.setFillColor(sf::Color::White);
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(3.0);

    target.draw(background, states);



    // draw background tetriminos (stack)
    for (auto i = 0; i < size.y; ++i) {
        for (auto j = 0; j < size.x; ++j) {
            if (auto type = stack[i + Piece::box_size][j]) {
                sf::RectangleShape cell (cell_size);
                cell.setPosition(cell_size.x * j, cell_size.y * i);
                cell.setFillColor(piece_color.at(*type));
                target.draw(cell, states);
            }
        }
    }

    // draw current tetrimino
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
                        target.draw(cell, states);
                    }
                }
            }
        }
    }


    // draw grid 
    sf::VertexArray vertex_grid (sf::Lines);

    for (auto x = 0; x <= size.x; ++x) {
        sf::Vertex top (cell_size.x * sf::Vector2f(x, 0), grid_color);
        sf::Vertex bottom (cell_size.x * sf::Vector2f(x, size.y), grid_color);
        vertex_grid.append(top);
        vertex_grid.append(bottom);
    }

    for (auto y = 0; y <= size.y; ++y) {
        sf::Vertex left (cell_size.y * sf::Vector2f(0, y), grid_color);
        sf::Vertex right (cell_size.y * sf::Vector2f(size.x, y), grid_color);
        vertex_grid.append(left);
        vertex_grid.append(right);
    }

    target.draw(vertex_grid, states);

}