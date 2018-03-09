#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

class MenuManager;
class Game;

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
	void	handleDisplayGame();
	void	displayMenu();
	void	displayGame();
	void	displayGameOver();
	void	fillKeyMapping();


	size_t										sizeXWindow;
	size_t										sizeYWindow;
	std::string									nameWindow;
	sf::RenderWindow							*window;
	t_menu										stateGame;
	MenuManager									*menu;
	Game										*game;
	std::map<std::string, sf::Keyboard::Key>	keymapping;
};
