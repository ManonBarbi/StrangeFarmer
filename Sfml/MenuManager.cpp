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
	this->frontgroundTexture.loadFromFile("ress\\menu_frontground.png");
	this->frontground.setTexture(this->frontgroundTexture);
	//Logo
	this->logoTexture.loadFromFile("ress\\logo.png");
	this->logo.setTexture(this->logoTexture);
	this->posYLogo = 75;
	this->varYLogo = 0.25;
	this->logoIsGoingDown = true;
	//Player
	this->playerTexture.loadFromFile("ress\\player_menu.png");
	this->playerAnimationPos.left = 0;
	this->playerAnimationPos.top = 0;
	this->playerAnimationPos.width = 28;
	this->playerAnimationPos.height = 28;
	this->player.setTexture(this->playerTexture);
	this->player.setTextureRect(this->playerAnimationPos);
	//Bird
	this->birdTexture.loadFromFile("ress\\bird_menu.png");
	this->bird.setTexture(this->birdTexture);
	this->timerBeforeNextBird = 1 + rand() % 14;
	//Leaf
	this->leafTexture.loadFromFile("ress\\leaf.png");
	this->leaf.setTexture(this->leafTexture);
	this->timerBeforeNextLeaf = 200 + rand() % 200;
	//Ratio Calcul
	this->ratioX = this->window->getSize().x / 1920.0;
	this->ratioY = this->window->getSize().y / 1080.0;
	this->background.setScale(ratioX, ratioY);
	this->frontground.setScale(ratioX, ratioY);
	this->logo.setScale(ratioX, ratioY);
	this->player.setScale(2 * ratioX, 2 * ratioY);
	this->bird.setScale(ratioX, ratioY);
	this->leaf.setScale(ratioX, ratioY);
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
	calcLogoPosition();
	calcAnimationPlayer();
	spawnBirdEvent();

	this->window->draw(this->background);
	this->window->draw(this->player);
	calcAnimationBird();
	spawnLeafEvent();
	this->window->draw(this->frontground);
	this->window->draw(this->logo);
}

void	MenuManager::calcLogoPosition()
{
	if (this->posYLogo <= 95)
		this->varYLogo = 0.25 + ((this->posYLogo - 75) * 5 / 100) * 0.50;
	else if (this->posYLogo >= 130)
		this->varYLogo = 0.25 + ((150 - this->posYLogo) * 5 / 100) * 0.50;
	else
		this->varYLogo = 0.75;
	if (this->logoIsGoingDown)
	{
		this->posYLogo += this->varYLogo;
	}
	else
	{
		this->posYLogo -= this->varYLogo;
	}
	if (this->posYLogo <= 75 && !this->logoIsGoingDown)
		this->logoIsGoingDown = true;
	else if (this->posYLogo >= 150 && this->logoIsGoingDown)
		this->logoIsGoingDown = false;
	this->logo.setPosition(this->window->getSize().x / 2 - (this->logo.getTexture()->getSize().x * ratioX / 2), this->posYLogo);
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
			this->bird.setTextureRect(i->birdAnimationPos);
		}
		this->bird.setPosition(i->posXBird / 100 * this->window->getSize().x, i->posYBird + i->angle * sin(i->posXBird / i->amplitude * this->window->getSize().x));
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
		newBird.amplitude = 2500 + rand() % 1500;
		newBird.posXBird = 100;
		newBird.posYBird = 30 + rand() % 200;
		this->birds.push_back(newBird);
		this->timerBeforeNextBird = 1 + rand() % 14;
		this->spawnBird.restart();
	}
}

void	MenuManager::spawnLeafEvent()
{
	if (this->spawnLeaf.getElapsedTime().asMilliseconds() >= this->timerBeforeNextLeaf)
	{
		t_leaf	newLeaf;

		newLeaf.posXLeaf = (rand() % 20000) / 100;
		newLeaf.posYLeaf = -3;
		this->leafs.push_back(newLeaf);
		this->timerBeforeNextLeaf = 200 + rand() % 200;
		this->spawnLeaf.restart();
	}
	for (std::vector<t_leaf>::iterator i = this->leafs.begin(); i != this->leafs.end();)
	{
		this->leaf.setPosition(i->posXLeaf / 100 * this->window->getSize().x, i->posYLeaf / 100 * this->window->getSize().y);
		this->window->draw(this->leaf);
		i->posYLeaf += 0.1;
		i->posXLeaf -= 0.075;
		if (i->posYLeaf >= 105 ||i->posXLeaf <= -5)
			i = this->leafs.erase(i);
		else
			++i;
	}
}