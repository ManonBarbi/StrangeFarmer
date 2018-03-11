#include "MapCreator.h"
#include <iostream>

MapCreator::MapCreator()
{
	srand(time(NULL));
	this->sizeX = 50;
	this->sizeY = 50;
	this->map = new Tile[sizeX * sizeY];
	for (size_t i = 0; i < 50; i++) {
		this->map[rand() % this->sizeY * this->sizeX + rand() % this->sizeX].status = BLOCK;
	}
	for (size_t i = 0; i < 7; ++i)
		for (size_t j = 21; j < 28; ++j)
			this->map[i * this->sizeX + j].status = BLOCK;
}


MapCreator::~MapCreator()
{
}

int MapCreator::getSizeX() {
	return this->sizeX;
}

int MapCreator::getSizeY() {
	return this->sizeY;
}

Tile *MapCreator::getMap() {
	return this->map;
}

void MapCreator::changeTileStatus(int x, int y, t_status status) {
	switch (status) {
	case PLOWED_LAND:
		if (this->map[y * this->sizeX + x].status == PLOWED_LAND) {
			this->map[y * this->sizeX + x].plowedChrono.restart();
			break;
		}
		if (this->map[y * this->sizeX + x].status == HUNTED_LAND || this->map[y * this->sizeX + x].status == WET_HUNTED_LAND) {
			break;
		}
		this->map[y * this->sizeX + x].status = PLOWED_LAND;
		this->map[y * this->sizeX + x].plowedChrono.restart();
		this->plowedTiles.push_back(&this->map[y * this->sizeX + x]);
		break;
	case WET_PLOWED_LAND:
		if (this->map[y * this->sizeX + x].status == WET_PLOWED_LAND) {
			this->map[y * this->sizeX + x].plowedChrono.restart();
			break;
		}
		if (this->map[y * this->sizeX + x].status == WET_HUNTED_LAND || this->map[y * this->sizeX + x].status == HUNTED_LAND) {
			break;
		}
		this->map[y * this->sizeX + x].status = WET_PLOWED_LAND;
		this->map[y * this->sizeX + x].wetChrono.restart();
		this->map[y * this->sizeX + x].plowedChrono.restart();
		this->plowedTiles.push_back(&this->map[y * this->sizeX + x]);
		this->wetTiles.push_back(&this->map[y * this->sizeX + x]);
		break;
	case HUNTED_LAND:
		this->map[y * this->sizeX + x].status = HUNTED_LAND;
		this->map[y * this->sizeX + x].huntedChrono.restart();
		this->huntedTiles.push_back(&this->map[y * this->sizeX + x]);
		break;
	case WET_HUNTED_LAND:
		this->map[y * this->sizeX + x].status = WET_HUNTED_LAND;
		this->map[y * this->sizeX + x].wetChrono.restart();
		this->map[y * this->sizeX + x].huntedChrono.restart();
		this->huntedTiles.push_back(&this->map[y * this->sizeX + x]);
		this->wetTiles.push_back(&this->map[y * this->sizeX + x]);
		break;
	default:
		break;
	}
}

std::vector<Tile*> MapCreator::getPlowedTiles() {
	return this->plowedTiles;
}

std::vector<Tile*> MapCreator::getHuntedTiles() {
	return this->huntedTiles;
}

std::vector<Tile*> MapCreator::getWetTiles() {
	return this->wetTiles;
}

std::vector<IPlant*> MapCreator::getPlants() {
	return this->plants;
}