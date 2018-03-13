#pragma once
#include "IItem.h"
#include "MapCreator.h"
#include "BasicFlower.h"

class Seed : public IItem
{
private:
	int id;
	int sellPrice;
	int buyPrice;
	std::string name;
	std::string description;
	MapCreator mp;
public:
	Seed();
	Seed(MapCreator &mp);
	~Seed();
	bool use(int x, int y, int playerX, int playerY);
	int getId();
	int getSellPrice();
	int getBuyPrice();
	std::string getName();
	std::string getDescription();
	IItem *getInstance();
};