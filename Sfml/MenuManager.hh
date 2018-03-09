#pragma once

#include <vector>
#include "Displayer.hh"

typedef enum	e_typeMenu
{
	MAIN,
	OPTION,
	EXIT
}				t_typeMenu;

typedef struct			s_bird
{
	sf::IntRect			birdAnimationPos;
	sf::Clock			clockAnimationBird;
	double				posXBird;
	double				posYBird;
	double				amplitude;
	double				angle;
}						t_bird;

typedef struct			s_pos
{
	double				posX;
	double				posY;
}						t_pos;

class MenuManager
{
public:
	MenuManager(sf::RenderWindow *_window, std::map<std::string, sf::Keyboard::Key> *_keymapping);
	~MenuManager();
	void	run(t_menu &stateGame);
	void	handleEvent(sf::Event &event);

private:
	void				calcLogoPosition();
	void				calcAnimationPlayer(t_menu &stateGame);
	void				calcAnimationBird();
	void				spawnBirdEvent();
	void				spawnLeafEvent();
	void				drawButton();
	void				eventMouse();

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
	sf::Texture			playerTextureRun;
	sf::IntRect			playerAnimationPosRunLeft;
	sf::IntRect			playerAnimationPosRunRight;
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
	std::vector<t_pos>	leafs;
	sf::Int32			timerBeforeNextLeaf;
	sf::Clock			spawnLeaf;
	//Button Farm
	sf::Texture			buttonFarmTexture;
	sf::Texture			buttonFarmGreyTexture;
	sf::Sprite			buttonFarm;
	t_pos				buttonFarmPosition;
	bool				buttonFarmIsClicked;
	//Button Farm
	sf::Texture			buttonExitTexture;
	sf::Texture			buttonExitGreyTexture;
	sf::Sprite			buttonExit;
	t_pos				buttonExitPosition;
	bool				buttonExitIsClicked;
	//Ratio calcul
	double				ratioX;
	double				ratioY;
	//Menu state
	t_typeMenu			state;
	//Bool deplacement player
	bool				playerFarmMove;
	bool				playerOptionMove;
	bool				playerExitMove;
	t_pos				playerPosition;
	double				playerMoveVar;
	std::map<std::string, sf::Keyboard::Key>	*keymapping;
};