#include "BasicFlower.h"



BasicFlower::BasicFlower(int x, int y, MapCreator &mp)
{
	this->id = 2;
	this->sellPrice = 5;
	this->name = "flower";
	this->description = "This is a basic flower.";
	this->state = SMALL;
	this->x = x;
	this->y = y;
	this->mp = mp;
	this->isDead = false;
	this->mut = NORMAL;
}


BasicFlower::~BasicFlower()
{
}

void BasicFlower::grow() {
	sf::Time time = this->growChrono.getElapsedTime();
	if (this->state == SMALL && time.asSeconds() >= 5 && this->mp.getMap()[this->y * this->mp.getSizeX() + this->x].status == WET_PLOWED_LAND) {
		this->state = MEDIUM;
		if (rand() % 10000 == 1) {
			this->mut = ISMUTATE;
		}
	}
	if (this->state == MEDIUM && time.asSeconds() >= 10 && this->mp.getMap()[this->y * this->mp.getSizeX() + this->x].status == WET_PLOWED_LAND) {
		this->state = TALL;
		this->mut = GOOD_MUTATION;
	}
}

void BasicFlower::death() {
	sf::Time time = this->mp.getMap()[this->y * this->mp.getSizeX() + this->x].wetChrono.getElapsedTime();
	if (time.asSeconds() >= 15) {
		this->isDead = true;
	}
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

bool BasicFlower::getIsDead() {
	return this->isDead;
}

t_mutation BasicFlower::getMutation() {
	return this->mut;
}