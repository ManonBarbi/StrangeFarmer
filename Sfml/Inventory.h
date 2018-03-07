#pragma once
#include <iostream>
#include <vector>
#include "IItem.h"

class Inventory
{
private:
	int money;
	std::vector<IItem*> inventoryVec;
public:
	Inventory();
	~Inventory();
	void addItemToInventory(IItem *i);
	void removeItemToInventory(IItem *i);
	std::vector<IItem*> getInventoryVec();
	int getMoney();
	void setMoney(int money);
	void setInventoryVec(std::vector<IItem*> vec);
};

