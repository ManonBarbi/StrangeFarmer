#pragma once
#include "Tile.h"
#include "IPlant.h"

class MapCreator
{
private:
	int sizeX;
	int sizeY;
	Tile *map;
	std::vector<Tile*> plowedTiles;
	std::vector<Tile*> wetTiles;
	std::vector<Tile*> huntedTiles;
	std::vector<IPlant *> plants;

public:
	MapCreator();
	~MapCreator();
	int getSizeX();
	int getSizeY();
	Tile *getMap();
	void changeTileStatus(int x, int y, t_status status);
	std::vector<Tile*> getPlowedTiles();
	std::vector<Tile*> getWetTiles();
	std::vector<Tile*> getHuntedTiles();
	std::vector<IPlant*> getPlants();
};

