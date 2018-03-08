#include <windows.h>
#include <string>
#include "MenuManager.hh"

MenuManager::MenuManager(sf::RenderWindow *_window)
{
	srand(time(NULL));
	this->window = _window;
	//Background
	this->backgroundTexture.loadFromFile("ress\\menu_background.png");
	this->background.setTexture(this->backgroundTexture);
	//Frontground
	this->frontgroundTexture.loadFromFile("ress\\menu_frontground_test.png");
	this->frontground.setTexture(this->frontgroundTexture);
	//Logo
	this->logoTexture.loadFromFile("ress\\logo.png");
	this->logo.setTexture(this->logoTexture);
	this->posYLogo = 6.944444;
	this->varYLogo = 0.023148;
	this->logoIsGoingDown = true;
	//Player
	this->playerTexture.loadFromFile("ress\\player_menu.png");
	this->playerAnimationPos.left = 0;
	this->playerAnimationPos.top = 0;
	this->playerAnimationPos.width = 28;
	this->playerAnimationPos.height = 28;
	this->player.setTexture(this->playerTexture);
	this->player.setTextureRect(this->playerAnimationPos);
	//PlayerRun
	this->playerTextureRun.loadFromFile("ress\\player_menu_run.png");
	this->playerAnimationPosRunLeft.left = 25;
	this->playerAnimationPosRunLeft.top = 0;
	this->playerAnimationPosRunLeft.width = -25;
	this->playerAnimationPosRunLeft.height = 28;

	this->playerAnimationPosRunRight.left = 0;
	this->playerAnimationPosRunRight.top = 0;
	this->playerAnimationPosRunRight.width = 25;
	this->playerAnimationPosRunRight.height = 28;

	//Bird
	this->birdTexture.loadFromFile("ress\\bird_menu.png");
	this->bird.setTexture(this->birdTexture);
	this->timerBeforeNextBird = 1 + rand() % 14;
	//Leaf
	this->leafTexture.loadFromFile("ress\\leaf.png");
	this->leaf.setTexture(this->leafTexture);
	this->timerBeforeNextLeaf = 200 + rand() % 200;
	//Button Farm
	this->buttonFarmTexture.loadFromFile("ress\\farm.png");
	this->buttonFarmGreyTexture.loadFromFile("ress\\farm_grey.png");
	this->buttonFarm.setTexture(this->buttonFarmTexture);
	this->buttonFarm.setRotation(6);
	this->buttonFarmPosition.posX = 1.4;
	this->buttonFarmPosition.posY = 64;
	this->buttonFarmIsClicked = false;
	//Button Farm
	this->buttonExitTexture.loadFromFile("ress\\exit.png");
	this->buttonExitGreyTexture.loadFromFile("ress\\exit_grey.png");
	this->buttonExit.setTexture(this->buttonExitTexture);
	this->buttonExit.setRotation(-6);
	this->buttonExitPosition.posX = 93;
	this->buttonExitPosition.posY = 65;
	this->buttonExitIsClicked = false;

	//Ratio Calcul
	this->ratioX = this->window->getSize().x / 1920.0;
	this->ratioY = this->window->getSize().y / 1080.0;
	this->background.setScale(ratioX, ratioY);
	this->frontground.setScale(ratioX, ratioY);
	this->logo.setScale(ratioX, ratioY);
	this->player.setScale(2 * ratioX, 2 * ratioY);
	this->bird.setScale(ratioX, ratioY);
	this->leaf.setScale(ratioX, ratioY);
	this->buttonFarm.setScale(ratioX * 0.45, ratioY * 0.45);
	this->buttonExit.setScale(ratioX * 0.45, ratioY * 0.45);
	//Menu State
	this->state = MAIN;
	//Bool deplacement joueur
	this->playerFarmMove = false;
	this->playerOptionMove = false;
	this->playerExitMove = false;
	this->playerPosition.posX = 35.1562;
	this->playerPosition.posY = 76.5;
	this->playerMoveVar = -0.1;
}

MenuManager::~MenuManager()
{
}

void	MenuManager::run(sf::Event &event, t_menu &stateGame)
{

	if (event.type == sf::Event::Resized)
	{
		this->ratioX = this->window->getSize().x / 1920.0;
		this->ratioY = this->window->getSize().y / 1080.0;
		this->background.setScale(ratioX, ratioY);
		this->frontground.setScale(ratioX, ratioY);
		this->logo.setScale(ratioX, ratioY);
		this->player.setScale(2 * ratioX, 2 * ratioY);
		this->bird.setScale(ratioX, ratioY);
		this->leaf.setScale(ratioX, ratioY);
		window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
	}
	eventMouse();
	calcLogoPosition();
	calcAnimationPlayer(stateGame);
	spawnBirdEvent();

	this->window->draw(this->background);
	calcAnimationBird();
	spawnLeafEvent();
	this->window->draw(this->frontground);
	this->window->draw(this->logo);
	this->window->draw(this->player);
	drawButton();
}

void	MenuManager::calcLogoPosition()
{
	if (this->posYLogo <= 8.79629)
		this->varYLogo = 0.023148 + ((this->posYLogo - 6.944444) * 5 / 100) * 0.50;
	else if (this->posYLogo >= 12.03703)
		this->varYLogo = 0.023148 + ((13.888888 - this->posYLogo) * 5 / 100) * 0.50;
	else
		this->varYLogo = 0.06944444;
	if (this->logoIsGoingDown)
	{
		this->posYLogo += this->varYLogo;
	}
	else
	{
		this->posYLogo -= this->varYLogo;
	}
	if (this->posYLogo <= 6.944444 && !this->logoIsGoingDown)
		this->logoIsGoingDown = true;
	else if (this->posYLogo >= 13.888888 && this->logoIsGoingDown)
		this->logoIsGoingDown = false;
	this->logo.setPosition(this->window->getSize().x / 2 - (this->logo.getTexture()->getSize().x * ratioX / 2), this->posYLogo / 100 * this->window->getSize().y);
}

void	MenuManager::calcAnimationPlayer(t_menu &stateGame)
{
	if (this->clockAnimationPlayer.getElapsedTime().asMilliseconds() >= sf::Int32(75))
	{
		std::cout << this->playerFarmMove << std::endl;
		if (!this->playerExitMove && !this->playerFarmMove && !this->playerOptionMove)
		{
			this->playerAnimationPos.left += 41;
			if (this->playerAnimationPos.left >= 328)
				this->playerAnimationPos.left = 0;
			this->clockAnimationPlayer.restart();
			this->player.setTextureRect(this->playerAnimationPos);
		}
		else if (this->playerFarmMove)
		{
			this->playerAnimationPosRunLeft.left += 41;
			if (this->playerAnimationPosRunLeft.left > 328)
				this->playerAnimationPosRunLeft.left = 25;
			this->clockAnimationPlayer.restart();
			this->player.setTextureRect(this->playerAnimationPosRunLeft);
		}
		else if (this->playerExitMove)
		{
			this->playerAnimationPosRunRight.left += 41;
			if (this->playerAnimationPosRunRight.left >= 328)
				this->playerAnimationPosRunRight.left = 0;
			this->clockAnimationPlayer.restart();
			this->player.setTextureRect(this->playerAnimationPosRunRight);
		}
	}
	if (this->playerFarmMove || this->playerExitMove)
		this->playerPosition.posX += this->playerMoveVar;
	this->player.setPosition(this->playerPosition.posX / 100 * ratioX * this->window->getSize().x, this->playerPosition.posY / 100 * ratioY * this->window->getSize().y);
	if (this->playerPosition.posX > 105)
		this->window->close();
	else if (this->playerPosition.posX < -5)
		stateGame = GAME;
}

void	MenuManager::calcAnimationBird()
{
	for (std::vector<t_bird>::iterator i = this->birds.begin(); i != this->birds.end();)
	{
		if (i->clockAnimationBird.getElapsedTime().asMilliseconds() >= sf::Int32(75))
		{
			i->birdAnimationPos.left += 33;
			if (i->birdAnimationPos.left >= 132)
				i->birdAnimationPos.left = 0;
			i->clockAnimationBird.restart();
		}
		this->bird.setTextureRect(i->birdAnimationPos);
		this->bird.setPosition(i->posXBird / 100 * this->window->getSize().x, i->posYBird / 100 * this->window->getSize().y + i->angle * sin((i->posXBird / 100 * this->window->getSize().x) / i->amplitude));
		i->posXBird -= 0.1;
		this->window->draw(this->bird);
		if (i->posXBird <= -5)
			i = this->birds.erase(i);
		else
			++i;
	}
}

void	MenuManager::spawnBirdEvent()
{
	if (this->spawnBird.getElapsedTime().asSeconds() >= this->timerBeforeNextBird)
	{
		t_bird	newBird;

		newBird.birdAnimationPos.left = 0;
		newBird.birdAnimationPos.top = 0;
		newBird.birdAnimationPos.width = 30;
		newBird.birdAnimationPos.height = 28;
		newBird.angle = 20 + rand() % 30;
		newBird.amplitude = 35 + rand() % 25;
		newBird.posXBird = 100;
		newBird.posYBird = 3 + rand() % 22;
		this->birds.push_back(newBird);
		this->timerBeforeNextBird = 1 + rand() % 14;
		this->spawnBird.restart();
	}
}

void	MenuManager::spawnLeafEvent()
{
	if (this->spawnLeaf.getElapsedTime().asMilliseconds() >= this->timerBeforeNextLeaf)
	{
		t_pos	newLeaf;

		newLeaf.posX = (rand() % 20000) / 100;
		newLeaf.posY = -3;
		this->leafs.push_back(newLeaf);
		this->timerBeforeNextLeaf = 200 + rand() % 200;
		this->spawnLeaf.restart();
	}
	for (std::vector<t_pos>::iterator i = this->leafs.begin(); i != this->leafs.end();)
	{
		this->leaf.setPosition(i->posX / 100 * this->window->getSize().x, i->posY / 100 * this->window->getSize().y);
		this->window->draw(this->leaf);
		i->posY += 0.1;
		i->posX -= 0.075;
		if (i->posY >= 105 ||i->posX <= -5)
			i = this->leafs.erase(i);
		else
			++i;
	}
}

void	MenuManager::drawButton()
{
	this->buttonFarm.setPosition(this->buttonFarmPosition.posX / 100 * this->window->getSize().x, this->buttonFarmPosition.posY / 100 * this->window->getSize().y);
	this->window->draw(this->buttonFarm);
	this->buttonExit.setPosition(this->buttonExitPosition.posX / 100 * this->window->getSize().x, this->buttonExitPosition.posY / 100 * this->window->getSize().y);
	this->window->draw(this->buttonExit);
}

void	MenuManager::eventMouse()
{
	sf::Vector2i	position = sf::Mouse::getPosition(*this->window);
	double			minXFarm = this->buttonFarmPosition.posX / 100 * this->window->getSize().x;
	double			maxXFarm = this->buttonFarmPosition.posX / 100 * this->window->getSize().x + ratioX * this->buttonFarmTexture.getSize().x;
	double			minYFarm = this->buttonFarmPosition.posY / 100 * this->window->getSize().y;
	double			maxYFarm = this->buttonFarmPosition.posY / 100 * this->window->getSize().y + ratioY * this->buttonFarmTexture.getSize().y;

	double			minXExit = this->buttonExitPosition.posX / 100 * this->window->getSize().x;
	double			maxXExit = this->buttonExitPosition.posX / 100 * this->window->getSize().x + ratioX * this->buttonExitTexture.getSize().x;
	double			minYExit = this->buttonExitPosition.posY / 100 * this->window->getSize().y;
	double			maxYExit = this->buttonExitPosition.posY / 100 * this->window->getSize().y + ratioY * this->buttonExitTexture.getSize().y;

	if (!this->buttonFarmIsClicked &&
		position.x >= minXFarm && position.x <= maxXFarm &&
		position.y >= minYFarm && position.y <= maxYFarm &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->buttonFarm.setTexture(this->buttonFarmGreyTexture);
		this->buttonFarm.setScale(ratioX * 0.4, ratioY * 0.4);
		this->buttonFarmIsClicked = true;
	}
	else if (!this->buttonExitIsClicked &&
		position.x >= minXExit && position.x <= maxXExit &&
		position.y >= minYExit && position.y <= maxYExit &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->buttonExit.setTexture(this->buttonExitGreyTexture);
		this->buttonExit.setScale(ratioX * 0.4, ratioY * 0.4);
		this->buttonExitIsClicked = true;
	}
	else if (this->buttonFarmIsClicked && !sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		position.x >= minXFarm && position.x <= maxXFarm &&
		position.y >= minYFarm && position.y <= maxYFarm)
	{
		this->buttonFarm.setTexture(this->buttonFarmTexture);
		this->buttonFarm.setScale(ratioX * 0.45, ratioY * 0.45);
		this->buttonFarmIsClicked = false;
		this->playerFarmMove = true;
		this->playerOptionMove = false;
		this->playerExitMove = false;
		this->player.setTexture(this->playerTextureRun);
		this->player.setTextureRect(this->playerAnimationPosRunLeft);
		this->playerMoveVar = -0.1;
	}
	else if (this->buttonExitIsClicked && !sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		position.x >= minXExit && position.x <= maxXExit &&
		position.y >= minYExit && position.y <= maxYExit)
	{
		this->buttonExit.setTexture(this->buttonExitTexture);
		this->buttonExit.setScale(ratioX * 0.45, ratioY * 0.45);
		this->buttonExitIsClicked = false;
		this->playerFarmMove = false;
		this->playerOptionMove = false;
		this->playerExitMove = true;
		this->player.setTexture(this->playerTextureRun);
		this->player.setTextureRect(this->playerAnimationPosRunRight);
		this->playerMoveVar = 0.1;
	}
	else if (this->buttonFarmIsClicked && 
		!(position.x >= minXFarm && position.x <= maxXFarm &&
		position.y >= minYFarm && position.y <= maxYFarm))
	{
		this->buttonFarm.setTexture(this->buttonFarmTexture);
		this->buttonFarm.setScale(ratioX * 0.45, ratioY * 0.45);
		this->buttonFarmIsClicked = false;
	}
	if (this->buttonFarmIsClicked)
		this->buttonFarm.setScale(ratioX * 0.4, ratioY * 0.4);
	else
		this->buttonFarm.setScale(ratioX * 0.45, ratioY * 0.45);
}