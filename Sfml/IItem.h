#pragma once
#include <iostream>

class IItem
{
public:
	virtual ~IItem() {};
	virtual void use() = 0;
	virtual int getId() = 0;
	virtual int getSellPrice() = 0;
	virtual int getBuyPrice() = 0;
	virtual std::string getName() = 0;
	virtual std::string getDescription() = 0;
	virtual IItem *getInstance() = 0;
};

