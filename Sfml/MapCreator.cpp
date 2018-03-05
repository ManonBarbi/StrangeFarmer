#include "MapCreator.h"
#include <iostream>

MapCreator::MapCreator(int sizex, int sizey)
{
	this->sizeX = sizex;
	this->sizeY = sizey;
	this->map = new int[sizeX * sizeY]();
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

int *MapCreator::getMap() {
	return this->map;
}
