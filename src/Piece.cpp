// Piece.cpp

#include "Piece.hpp"

Piece::Piece (PieceType type, sf::Vector2i pos, int rotation) :
    type { type },
    pos { pos },
    rotation { rotation }
{
	
}


piece_pattern Piece::get_pattern () const {
    return piece_rotation_pattern.at(type)[rotation];
}

sf::Vector2i Piece::get_pos () const {
    return pos;
}

PieceType Piece::get_type () const {
    return type;
}

void Piece::move_down () {
    pos.y++;
}

void Piece::rotate_right () {
    rotation = (rotation + 1) % 4;
}

void Piece::rotate_left () {
    rotation = (rotation + 3) % 4;
}