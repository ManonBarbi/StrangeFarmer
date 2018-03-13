#include "Seed.h"


Seed::Seed() {}

Seed::Seed(MapCreator &mp)
{
	this->id = 1;
	this->sellPrice = 1;
	this->buyPrice = 2;
	this->name = "Seed";
	this->description = "This is a basic seed. Plant it to see what is it.";
	this->mp = mp;
}


Seed::~Seed()
{
}

int Seed::getId() {
	return this->id;
}

int Seed::getSellPrice() {
	return this->sellPrice;
}

int Seed::getBuyPrice() {
	return this->buyPrice;
}

std::string Seed::getName() {
	return this->name;
}

std::string Seed::getDescription() {
	return this->description;
}

IItem *Seed::getInstance() {
	return new Seed(this->mp);
}

bool Seed::use(int x, int y, int playerX, int playerY) {
	if ((abs(playerX - x * 100) <= 150 && abs(playerY - y * 100) <= 150) && (this->mp.getMap()->status == WET_PLOWED_LAND || this->mp.getMap()->status == PLOWED_LAND)) {
		new BasicFlower(x, y, mp);
		return true;
	}
	return false;
}