#pragma once
#include "IPlant.h"

class BasicFlower : public IPlant
{
private:
	int id;
	int sellPrice;
	std::string name;
	std::string description;
public:
	BasicFlower();
	~BasicFlower();
	void grow();
	void death();
	int getId();
	int getSellPrice();
	std::string getName();
	std::string getDescription();
};

