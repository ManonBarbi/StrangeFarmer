#pragma once
#include <iostream>

class IPlant
{
public:
	virtual ~IPlant() {};
	virtual void grow() = 0;
	virtual void death() = 0;
	virtual int getId() = 0;
	virtual int getSellPrice() = 0;
	virtual std::string getName() = 0;
	virtual std::string getDescription() = 0;
};

