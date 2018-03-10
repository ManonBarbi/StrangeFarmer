#include "Displayer.hh"
#include "MenuManager.hh"
#include "Game.hh"

Displayer::Displayer(const std::string &_nameWindow)
{
	this->nameWindow = _nameWindow;
	this->sizeXWindow = 1920;
	this->sizeYWindow = 1080;
	this->stateGame = MENU;
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080, 32), this->nameWindow.c_str(), sf::Style::Fullscreen);
	this->menu = new MenuManager(this->window, &this->keymapping);
	this->game = new Game(this->window, &this->keymapping);
}

Displayer::Displayer(const std::string &_nameWindow, size_t _sizeXWindow, size_t _sizeYWindow)
{
	this->nameWindow = _nameWindow;
	this->sizeXWindow = _sizeXWindow;
	this->sizeYWindow = _sizeYWindow;
	this->stateGame = MENU;
	this->window = new sf::RenderWindow(sf::VideoMode(this->sizeXWindow, this->sizeYWindow, 32), this->nameWindow.c_str());
	this->menu = new MenuManager(this->window, &this->keymapping);
	this->game = new Game(this->window, &this->keymapping);
}

Displayer::~Displayer()
{
	delete this->window;
	delete this->menu;
}

void	Displayer::run()
{
	fillKeyMapping();
	window->setFramerateLimit(60);
	while (window->isOpen())
	{
		sf::Event event;

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			switch (this->stateGame)
			{
			case MENU:
			{
				this->menu->handleEvent(event);
				break;
			}
			case GAME:
			{
				this->game->handleEvent(event);
				break;
			}
			case GAMEOVER:
			{
				break;
			}
			default:
				break;
			}
		}
		window->clear();
		handleDisplayGame();
		window->display();
	}
}

void	Displayer::fillKeyMapping()
{
	keymapping["Up"] = sf::Keyboard::Up;
	keymapping["Down"] = sf::Keyboard::Down;
	keymapping["Left"] = sf::Keyboard::Left;
	keymapping["Right"] = sf::Keyboard::Right;
}

void	Displayer::handleDisplayGame()
{
	switch (this->stateGame)
	{
	case MENU:
	{
		displayMenu();
		break;
	}
	case GAME:
	{
		displayGame();
		break;
	}
	case GAMEOVER:
	{
		displayGameOver();
		break;
	}
	default:
		break;
	}
}

void	Displayer::displayMenu()
{
	this->menu->run(this->stateGame);
}

void	Displayer::displayGame()
{
	this->game->run(this->stateGame);
}

void	Displayer::displayGameOver()
{

}
