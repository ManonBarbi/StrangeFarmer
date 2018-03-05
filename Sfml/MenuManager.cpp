#include <windows.h>
#include <string>
#include "MenuManager.hh"

MenuManager::MenuManager(sf::RenderWindow *_window)
{
	this->window = _window;
	this->backgroundTexture.loadFromFile("ress\\menu_background.png");
	this->background.setTexture(this->backgroundTexture);
	this->logoTexture.loadFromFile("ress\\logo.png");
	this->logo.setTexture(this->logoTexture);
	this->playerTexture.loadFromFile("ress\\player_menu.png");
	this->playerAnimationPos.left = 0;
	this->playerAnimationPos.top = 0;
	this->playerAnimationPos.width = 28;
	this->playerAnimationPos.height = 28;
	this->player.setTexture(this->playerTexture);
	this->player.setTextureRect(this->playerAnimationPos);
	this->posYLogo = 75;
	this->varYLogo = 0.25;
	this->logoIsGoingDown = true;
	this->ratioX = this->window->getSize().x / 1920.0;
	this->ratioY = this->window->getSize().y / 1080.0;
	this->background.setScale(ratioX, ratioY);
	this->logo.setScale(ratioX, ratioY);
	this->player.setScale(2 * ratioX, 2 * ratioY);
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
		this->logo.setScale(ratioX, ratioY);
		this->player.setScale(2 * ratioX, 2 * ratioY);
		window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
	}
	calcLogoPosition();
	calcAnimationPlayer();
	this->logo.setPosition(this->window->getSize().x / 2 - (this->logo.getTexture()->getSize().x * ratioX / 2), this->posYLogo);
	this->player.setPosition(675 * ratioX, 823 * ratioY);
	this->window->draw(this->background);
	this->window->draw(this->logo);
	this->window->draw(this->player);
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
}