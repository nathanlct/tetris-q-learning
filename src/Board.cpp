// Board.cpp

#include "Board.hpp"


Board::Board (sf::Vector2i board_size, size_t& game_score) :
    size { board_size },
    current_piece { nullptr },
    next_pieces { next_pieces_size },
    next_pieces_idx { 0 },
    piece_types { PieceType::I, PieceType::J, PieceType::L, PieceType::O, 
                  PieceType::S, PieceType::T, PieceType::Z },
    spawn_pos { (size.x - Piece::box_size) / 2, - Piece::box_size },
    stack (size.y + Piece::box_size, std::vector<std::optional<PieceType>> (size.x, std::nullopt)),
    game_score { game_score }
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
            auto score = 0;
            while (current_piece) {
                move_piece_down();
                score += 2;
            }
            game_score += score;
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

        try_clearing_lines (current_piece->get_pos().y + Piece::box_size, 
                            std::min(current_piece->get_pos().y + 2 * Piece::box_size, size.y));  
    }
}

void Board::try_clearing_lines (int start, int end) {
    auto nb_cleared = 0;

    for (auto it = stack.begin(); it != stack.end(); ++it) {
        bool filled = true;
        for (auto x = 0; x < size.x; ++x) {
            filled &= (*it)[x].has_value();
        }

        if (filled) {
            stack.erase (it);
            std::vector<std::optional<PieceType>> empty_line (size.x, std::nullopt);
            stack.insert(stack.begin(), empty_line);
            nb_cleared++;
        }
    }

    switch (nb_cleared) {
        case 1: game_score += 100; break;
        case 2: game_score += 300; break;
        case 3: game_score += 500; break;
        case 4: game_score += 800; break;
        default: break;
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
