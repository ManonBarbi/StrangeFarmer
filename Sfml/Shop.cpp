#include "Shop.h"



Shop::Shop()
{
	this->shopVec.push_back(new Seed());
}


Shop::~Shop()
{
}

std::vector<IItem*> &Shop::getShopVec() {
	return this->shopVec;
}

IItem				*Shop::findItem(int id)
{
	for (size_t i = 0; i < this->shopVec.size(); ++i)
	{
		if (this->shopVec[i]->getId() == id)
			return (this->shopVec[i]);
	}
	return (NULL);
}