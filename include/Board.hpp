// Board.hpp

#ifndef BOARD_H
#define BOARD_H

#include <random>
#include <vector>
#include <optional>
#include <algorithm>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Piece.hpp"




/* 
top-left corner is (0, 0), right/bottom are increasing x/y values respectively
*/


enum class Action {
	rotate_left, rotate_right, move_left, move_right, hard_drop
};



class Board 
{
public:
	Board (sf::Vector2i board_size);

	bool spawn_new_piece ();
	bool move_piece_down ();

	bool execute_action (Action action);

	void reset ();

	sf::Vector2i get_size () const;
	const std::unique_ptr<Piece>& get_current_piece () const;
	const std::vector<std::vector<std::optional<PieceType>>>& get_stack () const;

private:

	void generate_next_pieces ();
	PieceType next_piece ();

	void add_piece_to_stack ();
	bool hay_collision (Piece piece);

	sf::Vector2i size;
	sf::Vector2i spawn_pos;

	std::unique_ptr<Piece> current_piece;

	std::vector<PieceType> piece_types;

	static constexpr size_t next_pieces_size { 10 };
	std::vector<PieceType> next_pieces;
	size_t next_pieces_idx;

	std::vector<std::vector<std::optional<PieceType>>> stack;



};

#endif
