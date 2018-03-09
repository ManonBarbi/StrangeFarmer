#include "MapCreator.h"
#include <iostream>

MapCreator::MapCreator()
{
	this->sizeX = 100;
	this->sizeY = 100;
	this->map = new Tile[sizeX * sizeY];
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

bool MapCreator::changeTileStatus(int x, int y, t_status status) {
	switch (status) {
	case PLOWED_LAND:
		this->map[y * this->sizeX + x].status = PLOWED_LAND;
		this->map[y * this->sizeX + x].plowedChrono.restart();
		this->plowedTiles.push_back(&this->map[y * this->sizeX + x]);
		return true;
	case WET_PLOWED_LAND:
		this->map[y * this->sizeX + x].status = WET_PLOWED_LAND;
		this->map[y * this->sizeX + x].wetChrono.restart();
		this->map[y * this->sizeX + x].plowedChrono.restart();
		this->plowedTiles.push_back(&this->map[y * this->sizeX + x]);
		this->wetTiles.push_back(&this->map[y * this->sizeX + x]);
		return true;
	case HUNTED_LAND:
		this->map[y * this->sizeX + x].status = HUNTED_LAND;
		this->map[y * this->sizeX + x].huntedChrono.restart();
		this->huntedTiles.push_back(&this->map[y * this->sizeX + x]);
		return true;
	case WET_HUNTED_LAND:
		this->map[y * this->sizeX + x].status = WET_HUNTED_LAND;
		this->map[y * this->sizeX + x].wetChrono.restart();
		this->map[y * this->sizeX + x].huntedChrono.restart();
		this->huntedTiles.push_back(&this->map[y * this->sizeX + x]);
		this->wetTiles.push_back(&this->map[y * this->sizeX + x]);
		return true;
	default:
		return false;
	}
	return false;
}

