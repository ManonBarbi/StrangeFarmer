#include "Seed.h"



Seed::Seed()
{
	this->id = 1;
	this->sellPrice = 1;
	this->buyPrice = 2;
	this->name = "Seed";
	this->description = "This is a basic seed. Plant it to see what is it.";
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
	return new Seed();
}

bool Seed::use() {
	return true;
}