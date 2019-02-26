// UI.hpp

#ifndef UI_H
#define UI_H


#include "Game.hpp"

#include <string>

#include <SFML/Graphics.hpp>

class UI : public sf::Drawable
{
public:
	UI (const Game& game);


	static const sf::Vector2i win_size;
	static const sf::Color bg_color;

private:

	const Game& game;
	const sf::Vector2i board_size;

	sf::Transform board_transform;
	sf::Transform info_transform;

	sf::RectangleShape board_background;
	sf::VertexArray board_grid;


	virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;
	void draw_board (sf::RenderTarget& target, sf::RenderStates states) const;

	inline static const sf::Color board_color { 0, 0, 0, 150 };
	inline static const sf::Vector2f cell_size { 50, 50 };

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
