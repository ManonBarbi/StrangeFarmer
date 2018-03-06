#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

typedef struct			s_bird
{
	sf::IntRect			birdAnimationPos;
	sf::Clock			clockAnimationBird;
	double				posXBird;
	double				posYBird;
	double				amplitude;
	double				angle;
}						t_bird;

typedef struct			s_leaf
{
	double				posXLeaf;
	double				posYLeaf;
}						t_leaf;

class MenuManager
{
public:
	MenuManager(sf::RenderWindow *_window);
	~MenuManager();
	void	run(sf::Event &event);

private:
	void				calcLogoPosition();
	void				calcAnimationPlayer();
	void				calcAnimationBird();
	void				spawnBirdEvent();
	void				spawnLeafEvent();

	sf::RenderWindow	*window;
	//Background
	sf::Texture			backgroundTexture;
	sf::Sprite			background;
	//Frontground
	sf::Texture			frontgroundTexture;
	sf::Sprite			frontground;
	//Logo
	sf::Texture			logoTexture;
	sf::Sprite			logo;
	double				posYLogo;
	double				varYLogo;
	bool				logoIsGoingDown;
	//Player
	sf::Texture			playerTexture;
	sf::Sprite			player;
	sf::IntRect			playerAnimationPos;
	sf::Clock			clockAnimationPlayer;
	//Bird
	sf::Texture			birdTexture;
	sf::Sprite			bird;
	std::vector<t_bird>	birds;
	sf::Int32			timerBeforeNextBird;
	sf::Clock			spawnBird;
	//leaf
	sf::Texture			leafTexture;
	sf::Sprite			leaf;
	std::vector<t_leaf>	leafs;
	sf::Int32			timerBeforeNextLeaf;
	sf::Clock			spawnLeaf;
	//Ration calcul
	double				ratioX;
	double				ratioY;
};