#pragma once
#include <iostream>
#include <chrono>
#include "Inventory.h"
#include "Shop.h"
#include "MapCreator.h"

typedef enum e_direction {
	NORTH,
	NORTHEAST,
	EAST,
	SOUTHEAST,
	SOUTH,
	SOUTHWEST,
	WEST,
	NORTHWEST
}			t_direction;


class Player
{
private:
	int posX;
	int posY;
	int money;
	std::chrono::steady_clock::time_point chrono;
	Inventory inventory;
	MapCreator map;
	Shop shop;

public:
	Player();
	~Player();
	void move(t_direction dir);
	int getPosX();
	int getPosY();
	void resetTimer();
	Inventory &getInventory();
	Shop &getShop();
	void sell(int id);
	bool buy(int id);
	void plowed(int x, int y);
	MapCreator &getMapCreator();
	bool isDead();
	void water(int x, int y);
};

