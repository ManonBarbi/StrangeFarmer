#include <algorithm>
#include "Inventory.h"


Inventory::Inventory()
{
	this->money = 10;
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

std::vector<IItem*> Inventory::getInventoryVec() {
	return this->inventoryVec;
}

int Inventory::getMoney() {
	return this->money;
}

void Inventory::setMoney(int money) {
	this->money = money;
}

void Inventory::setInventoryVec(std::vector<IItem*> vec) {
	this->inventoryVec = vec;
}