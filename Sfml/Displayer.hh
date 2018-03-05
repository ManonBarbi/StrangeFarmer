#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "MenuManager.hh"

typedef	enum e_menu
{
	MENU,
	GAME,
	GAMEOVER
}			t_menu;

class Displayer
{
public:
	Displayer(const std::string &_nameWindow);
	Displayer(const std::string &_nameWindow, size_t _sizeXWindow, size_t _sizeYWindow);
	~Displayer();
	void	run();

private:
	void	handleEvent();
	void	handleDisplayGame(sf::Event &event);
	void	displayMenu(sf::Event &event);
	void	displayGame();
	void	displayGameOver();


	size_t				sizeXWindow;
	size_t				sizeYWindow;
	std::string			nameWindow;
	sf::RenderWindow	*window;
	t_menu				stateGame;
	MenuManager			*menu;
	Player				*player;
	bool				timer;
};