// Grid.hpp

#ifndef GRID_H
#define GRID_H

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



class Grid : public sf::Drawable
{
public:
	Grid (sf::Vector2i grid_size);

	bool spawn_new_piece ();
	bool move_piece_down ();

	bool execute_action (Action action);

	void reset ();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void generate_next_pieces ();
	PieceType next_piece ();

	void add_piece_to_stack ();
	bool hay_collision (Piece piece);

	sf::Vector2i size;
	sf::Vector2i spawn_pos;

	std::unique_ptr<Piece> current_piece;

	std::vector<PieceType> piece_types;

	static constexpr size_t next_pieces_size { 1 };
	std::vector<PieceType> next_pieces;
	size_t next_pieces_idx;

	std::vector<std::vector<std::optional<PieceType>>> stack;


	const sf::Color grid_color { 0, 0, 0, 150 };
	sf::Vector2f cell_size = {50, 50};


	const std::unordered_map<PieceType, sf::Color> piece_color {
		{ PieceType::I, sf::Color::Cyan },
		{ PieceType::J, sf::Color::Blue },
		{ PieceType::L, sf::Color(255, 165, 0) }, // orange
		{ PieceType::O, sf::Color::Yellow },
		{ PieceType::S, sf::Color::Green },
		{ PieceType::T, sf::Color::Magenta },
		{ PieceType::Z, sf::Color::Red }
	};

};

#endif
