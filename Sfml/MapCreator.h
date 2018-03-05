#pragma once
class MapCreator
{
private:
	int sizeX;
	int sizeY;
	int *map;
public:
	MapCreator(int sizex, int sizey);
	~MapCreator();
	int getSizeX();
	int getSizeY();
	int *getMap();
};

