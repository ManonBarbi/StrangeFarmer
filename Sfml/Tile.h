#pragma once
#include <SFML\Graphics.hpp>

typedef enum e_status {
	LAND,
	PLOWED_LAND,
	WET_PLOWED_LAND,
	HUNTED_LAND,
	WET_HUNTED_LAND,
	DESTROY,
	BLOCK
} t_status;

class Tile
{
public:
	sf::Clock wetChrono;
	sf::Clock plowedChrono;
	sf::Clock huntedChrono;
	t_status status;
	int x;
	int y;

	Tile() {
		this->status = LAND;
	};
	~Tile() {};
};

