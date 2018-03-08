#include <algorithm>
#include "Inventory.h"


Inventory::Inventory()
{

}


Inventory::~Inventory()
{
}

void Inventory::addItemToInventory(IItem *i) {
	this->inventoryVec.push_back(i);
}

void Inventory::removeItemToInventory(IItem *i) {
	this->inventoryVec.erase(std::remove(this->inventoryVec.begin(), this->inventoryVec.end(), i), this->inventoryVec.end());
}

std::vector<IItem*>	&Inventory::getInventoryVec()
{
	return (this->inventoryVec);
}

IItem *Inventory::findItem(int id)
{
	for (size_t i = 0; i < this->inventoryVec.size(); ++i)
	{
		if (this->inventoryVec[i]->getId() == id)
			return (this->inventoryVec[i]);
	}
	return (NULL);
}
