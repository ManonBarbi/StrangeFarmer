#pragma once
#include <iostream>
#include <chrono>
#include "Inventory.h"
#include "Shop.h"

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

public:
	Player(int posx, int posy);
	~Player();
	void move(t_direction dir);
	int getPosX();
	int getPosY();
	void setPosX(int x);
	void setPosY(int y);
	void resetTimer();
	Inventory getInventory();
	void Sell(int id);
	bool Buy(int id);
};

