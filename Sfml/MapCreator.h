#pragma once
#include "Tile.h"

class MapCreator
{
private:
	int sizeX;
	int sizeY;
	Tile *map;
	std::vector<Tile*> plowedTiles;
	std::vector<Tile*> wetTiles;
	std::vector<Tile*> huntedTiles;
public:
	MapCreator();
	~MapCreator();
	int getSizeX();
	int getSizeY();
	Tile *getMap();
	bool changeTileStatus(int x, int y, t_status status);
};

