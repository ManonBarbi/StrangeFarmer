#pragma once

#include "Displayer.hh"
#include "Player.h"

class Game
{
public:
	Game(sf::RenderWindow *_window, std::map<std::string, sf::Keyboard::Key> *_keymapping);
	~Game();
	void	run(t_menu &stateGame);
	void	handleEvent(sf::Event &event);

private:
	void	handleKeyboard();
	void	displayMap();
	void	displayPlayer();
	void	displayHouse();
	void	displaySky();
	int		getOffsetTile(int x, int y);
	void	refreshMap();

	sf::RenderWindow *window;
	std::map<std::string, sf::Keyboard::Key>	*keymapping;
	Player										player;
	//TileMap
	sf::Texture			tileTexture;
	sf::IntRect			tilePositionTextureLand[9];
	sf::IntRect			tilePositionTexturePlowedLand[9];
	sf::IntRect			tilePositionTextureWetPlowedLand[9];
	sf::IntRect			tilePositionTextureHuntedLand[9];
	sf::IntRect			tilePositionTextureWetHuntedLand[9];
	sf::Sprite			tile;
	//Optimisation de l'affichage de la map
	sf::Clock			clockDrawMap;
	sf::RenderTexture	mapTexture;
	sf::Sprite			mapSprite;
	//Player
	sf::Texture			playerTexture;
	sf::IntRect			playerPositionTextureIdle[4];
	sf::IntRect			playerPositionTextureWalk[4];
	sf::Sprite			playerSprite;
	int					playerDirection;
	bool				playerIsWalking;
	sf::Clock			playerClockAnimation;
	//house
	sf::Texture			houseTexture;
	sf::Sprite			house;
	//sky
	sf::Texture			skyTexture;
	sf::Sprite			sky;
	//Ratio calcul
	double				ratioX;
	double				ratioY;
};