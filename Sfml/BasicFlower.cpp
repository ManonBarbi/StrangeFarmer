#include "BasicFlower.h"



BasicFlower::BasicFlower()
{
	this->id = 2;
	this->sellPrice = 5;
	this->name = "flower";
	this->description = "This is a basic flower.";
}


BasicFlower::~BasicFlower()
{
}

void BasicFlower::grow() {
}

void BasicFlower::death() {
}

int BasicFlower::getId() {
	return this->id;
}

int BasicFlower::getSellPrice() {
	return this->sellPrice;
}

std::string BasicFlower::getName() {
	return this->name;
}

std::string BasicFlower::getDescription() {
	return this->description;
}
