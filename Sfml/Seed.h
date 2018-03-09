#pragma once
#include "IItem.h"

class Seed : public IItem
{
private:
	int id;
	int sellPrice;
	int buyPrice;
	std::string name;
	std::string description;
public:
	Seed();
	~Seed();
	bool use();
	int getId();
	int getSellPrice();
	int getBuyPrice();
	std::string getName();
	std::string getDescription();
	IItem *getInstance();
};