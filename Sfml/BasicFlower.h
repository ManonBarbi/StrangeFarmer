#pragma once
#include <SFML\Graphics.hpp>
#include "IPlant.h"
#include "MapCreator.h"

typedef enum e_mutation {
	NORMAL,
	ISMUTATE,
	GOOD_MUTATION,
	BAD_MUTATION
} t_mutation;

class BasicFlower : public IPlant
{
private:
	int id;
	int sellPrice;
	std::string name;
	std::string description;
	sf::Clock growChrono;
	t_state state;
	int x;
	int y;
	MapCreator mp;
	bool isDead;
	t_mutation mut;
public:
	BasicFlower(int x, int y, MapCreator &mp);
	~BasicFlower();
	void grow();
	void death();
	int getId();
	int getSellPrice();
	std::string getName();
	std::string getDescription();
	bool getIsDead();
	t_mutation getMutation();
};

