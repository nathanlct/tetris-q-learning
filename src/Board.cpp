// Board.cpp

#include "Board.hpp"


Board::Board (sf::Vector2i board_size) :
    size { board_size },
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

bool Board::spawn_new_piece () {
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

bool Board::hay_collision (Piece piece) {
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

bool Board::move_piece_down () {

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

bool Board::execute_action (Action action) {

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

void Board::add_piece_to_stack () {
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

void Board::generate_next_pieces () {    

    std::sample (piece_types.begin(), piece_types.end(), 
                next_pieces.begin(), next_pieces_size, 
                std::mt19937{std::random_device{}()});

}

PieceType Board::next_piece () {
    PieceType type = next_pieces[next_pieces_idx];

    if (++next_pieces_idx == next_pieces_size) {
        next_pieces_idx = 0;
        generate_next_pieces();
    }

    return type;
}

void Board::reset () {
    // TODO
}

sf::Vector2i Board::get_size () const {
    return size;
}

const std::unique_ptr<Piece>& Board::get_current_piece () const {
    return current_piece;
}

const std::vector<std::vector<std::optional<PieceType>>>& Board::get_stack () const {
    return stack;
}