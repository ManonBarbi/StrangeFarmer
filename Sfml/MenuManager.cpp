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
	this->playerAnimationPosRun.left = 0;
	this->playerAnimationPosRun.top = 0;
	this->playerAnimationPosRun.width = 28;
	this->playerAnimationPosRun.height = 28;
	//Bird
	this->birdTexture.loadFromFile("ress\\bird_menu.png");
	this->bird.setTexture(this->birdTexture);
	this->timerBeforeNextBird = 1 + rand() % 14;
	//Leaf
	this->leafTexture.loadFromFile("ress\\leaf.png");
	this->leaf.setTexture(this->leafTexture);
	this->timerBeforeNextLeaf = 200 + rand() % 200;
	//Button
	this->buttonFarmTexture.loadFromFile("ress\\farm.png");
	this->buttonFarmGreyTexture.loadFromFile("ress\\farm_grey.png");
	this->buttonFarm.setTexture(this->buttonFarmTexture);
	this->buttonFarm.setRotation(6);
	this->buttonPosition.posX = 1.4;
	this->buttonPosition.posY = 64;
	this->buttonFarmIsClicked = false;
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
	//Menu State
	this->state = MAIN;
	//Bool deplacement joueur
	this->playerFarmMove = false;
	this->playerOptionMove = false;
	this->playerExitMove = false;
}

MenuManager::~MenuManager()
{
}

void	MenuManager::run(sf::Event &event)
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
	calcAnimationPlayer();
	spawnBirdEvent();

	this->window->draw(this->background);
	this->window->draw(this->player);
	calcAnimationBird();
	spawnLeafEvent();
	this->window->draw(this->frontground);
	this->window->draw(this->logo);
	drawMenuType();
	drawButtonFarm();
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

void	MenuManager::calcAnimationPlayer()
{
	if (this->clockAnimationPlayer.getElapsedTime().asMilliseconds() >= sf::Int32(75))
	{
		this->playerAnimationPos.left += 41;
		if (this->playerAnimationPos.left >= 328)
			this->playerAnimationPos.left = 0;
		this->clockAnimationPlayer.restart();
		this->player.setTextureRect(this->playerAnimationPos);
	}
	this->player.setPosition(675 * ratioX, 823 * ratioY);
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

void	MenuManager::drawMenuType()
{
	switch (this->state)
	{
	case MAIN:
	{
		this->playerFarmMove = false;
		this->playerOptionMove = false;
		this->playerExitMove = false;
		break;
	}
	case OPTION:
	{
		//drawOptionMenu();
		break;
	}
	case EXIT:
	{
		break;
	}
	}
}

void	MenuManager::drawButtonFarm()
{
	this->buttonFarm.setPosition(this->buttonPosition.posX / 100 * this->window->getSize().x, this->buttonPosition.posY / 100 * this->window->getSize().y);
	this->window->draw(this->buttonFarm);
}

void	MenuManager::eventMouse()
{
	sf::Vector2i	position = sf::Mouse::getPosition(*this->window);
	double			minX = this->buttonPosition.posX / 100 * this->window->getSize().x;
	double			maxX = this->buttonPosition.posX / 100 * this->window->getSize().x + ratioX * this->buttonFarmTexture.getSize().x;
	double			minY = this->buttonPosition.posY / 100 * this->window->getSize().y;
	double			maxY = this->buttonPosition.posY / 100 * this->window->getSize().y + ratioY * this->buttonFarmTexture.getSize().y;

	if (!this->buttonFarmIsClicked &&
		position.x >= minX && position.x <= maxX &&
		position.y >= minY && position.y <= maxY &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->buttonFarm.setTexture(this->buttonFarmGreyTexture);
		this->buttonFarm.setScale(ratioX * 0.4, ratioY * 0.4);
		this->buttonFarmIsClicked = true;
	}
	else if (this->buttonFarmIsClicked && !sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		position.x >= minX && position.x <= maxX &&
		position.y >= minY && position.y <= maxY)
	{
		this->buttonFarm.setTexture(this->buttonFarmTexture);
		this->buttonFarm.setScale(ratioX * 0.45, ratioY * 0.45);
		this->buttonFarmIsClicked = false;
		this->playerFarmMove = true;
		this->playerOptionMove = false;
		this->playerExitMove = false;
	}
	else if (this->buttonFarmIsClicked && 
		!(position.x >= minX && position.x <= maxX &&
		position.y >= minY && position.y <= maxY))
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