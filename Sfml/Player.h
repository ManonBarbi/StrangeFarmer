#pragma once
#include <iostream>
#include <chrono>

typedef enum e_direction {
	NORTH,
	NORTHEST,
	EST,
	SOUTHEST,
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
	std::chrono::steady_clock::time_point chrono;

public:
	Player(int posx, int posy);
	~Player();
	void move(t_direction dir);
	int getPosX();
	int getPosY();
	void setPosX(int x);
	void setPosY(int y);
	void resetTimer();
};

