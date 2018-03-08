#pragma once
#include <iostream>
#include <vector>
#include "IItem.h"

class Inventory
{
private:
	std::vector<IItem*> inventoryVec;
public:
	Inventory();
	~Inventory();
	void addItemToInventory(IItem *i);
	void removeItemToInventory(IItem *i);
	IItem *findItem(int id);
	std::vector<IItem*>	&getInventoryVec();
};

