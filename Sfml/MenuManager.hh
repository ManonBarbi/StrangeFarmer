#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class MenuManager
{
public:
	MenuManager(sf::RenderWindow *_window);
	~MenuManager();
	void	run(sf::Event &event);

private:
	void				calcLogoPosition();
	void				calcAnimationPlayer();

	sf::RenderWindow	*window;
	sf::Texture			backgroundTexture;
	sf::Sprite			background;
	sf::Texture			logoTexture;
	sf::Sprite			logo;
	sf::Texture			playerTexture;
	sf::Sprite			player;
	sf::IntRect			playerAnimationPos;
	sf::Clock			clockAnimationPlayer;
	float				posYLogo;
	float				varYLogo;
	bool				logoIsGoingDown;
	float				ratioX;
	float				ratioY;
};