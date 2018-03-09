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
	Shop shop;
	MapCreator map;

public:
	Player();
	~Player();
	void move(t_direction dir);
	int getPosX();
	int getPosY();
	void resetTimer();
	Inventory &getInventory();
	void sell(int id);
	bool buy(int id);
	bool plowed(int x, int y);
	MapCreator &getMapCreator();
};

