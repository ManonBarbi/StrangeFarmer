#include "Player.h"

Player::Player(int posx, int posy)
{
	this->posX = posx * 100;
	this->posY = posy * 100;
	this->chrono = std::chrono::steady_clock::now();
}

Player::~Player()
{
}

void Player::move(t_direction dir) {
	int secondPerUnit = 2500;
	if (dir % 2 != 0) {
		secondPerUnit = 3535;
	}
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	__int64 unit = std::chrono::duration_cast<std::chrono::microseconds>(now - this->chrono).count() / secondPerUnit;
	if (unit != 0) {
		switch (dir) {
		case NORTH:
			this->posY -= unit;
			break;
		case NORTHEAST:
			this->posY -= unit;
			this->posX += unit;
			break;
		case EAST:
			this->posX += unit;
			break;
		case SOUTHEAST:
			this->posY += unit;
			this->posX += unit;
			break;
		case SOUTH:
			this->posY += unit;
			break;
		case SOUTHWEST:
			this->posY += unit;
			this->posX -= unit;
			break;
		case WEST:
			this->posX -= unit;
			break;
		case NORTHWEST:
			this->posY -= unit;
			this->posX -= unit;
			break;
		default:
			break;
		}
		resetTimer();
	}
}

void Player::resetTimer() {
	this->chrono = std::chrono::steady_clock::now();
}

int Player::getPosX() {
	return this->posX;
}

int Player::getPosY() {
	return this->posY;
}

void Player::setPosX(int x) {
	this->posX = x;
}

void Player::setPosY(int y) {
	this->posY = y;
}