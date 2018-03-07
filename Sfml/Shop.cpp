#include "Shop.h"



Shop::Shop()
{
	this->shopVec.push_back(new Seed());
}


Shop::~Shop()
{
}

std::vector<IItem*> Shop::getShopVec() {
	return this->shopVec;
}