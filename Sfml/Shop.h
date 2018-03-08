#pragma once
#include <vector>
#include "Seed.h"

class Shop
{
private:
	std::vector<IItem*> shopVec;
public:
	Shop();
	~Shop();
	std::vector<IItem*> &getShopVec();
	IItem				*findItem(int id);
};

