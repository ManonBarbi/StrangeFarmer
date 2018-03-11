#include "Player.h"

Player::Player()
{
	this->posX = 50 * 100;
	this->posY = 50 * 100;
	this->money = 10;
	this->chrono = std::chrono::steady_clock::now();
}

Player::~Player()
{
}

void Player::move(t_direction dir) {
	int secondPerUnit = 2500;
	int	tmpPosX = this->posX;
	int	tmpPosY = this->posY;
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
		if (this->map.getMap()[this->posY * this->map.getSizeX() + this->posX].status == BLOCK) {
			this->posX = tmpPosX;
			this->posY = tmpPosY;
		}
		resetTimer();
	}
}

bool Player::buy(int id) {
	IItem *buyItem = this->shop.findItem(id);

	if (this->money - buyItem->getBuyPrice() < 0) {
		return false;
	}
	this->money -= buyItem->getBuyPrice();
	this->inventory.addItemToInventory(buyItem->getInstance());
	return true;
}

void Player::sell(int id) {
	IItem *sellItem = this->inventory.findItem(id);

	this->money += sellItem->getSellPrice();
	this->inventory.removeItemToInventory(sellItem);
	delete (sellItem);
}

void Player::plowed(int x, int y) {
	this->map.changeTileStatus(x, y, PLOWED_LAND);
}

bool Player::isDead() {
	if (this->map.getPlants().size == 0 && this->inventory.getInventoryVec().size == 0 && this->money <= 1) {
		return true;
	}
	return false;
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

Inventory &Player::getInventory() {
	return this->inventory;
}

MapCreator &Player::getMapCreator() {
	return this->map;
}

Shop &Player::getShop() {
	return this->shop;
}