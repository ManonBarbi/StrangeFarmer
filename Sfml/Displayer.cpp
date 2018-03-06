#include "Displayer.hh"

Displayer::Displayer(const std::string &_nameWindow)
{
	this->nameWindow = _nameWindow;
	this->sizeXWindow = 1920;
	this->sizeYWindow = 1080;
	this->stateGame = MENU;
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080, 32), this->nameWindow.c_str(), sf::Style::Fullscreen);
	this->menu = new MenuManager(this->window);
	this->player = new Player(5, 5);
}

Displayer::Displayer(const std::string &_nameWindow, size_t _sizeXWindow, size_t _sizeYWindow)
{
	this->nameWindow = _nameWindow;
	this->sizeXWindow = _sizeXWindow;
	this->sizeYWindow = _sizeYWindow;
	this->stateGame = MENU;
	this->window = new sf::RenderWindow(sf::VideoMode(this->sizeXWindow, this->sizeYWindow, 32), this->nameWindow.c_str());
	this->menu = new MenuManager(this->window);
	this->player = new Player(5, 5);
}

Displayer::~Displayer()
{
	delete this->window;
	delete this->menu;
	delete this->player;
}

void	Displayer::run()
{
	window->setFramerateLimit(60);
	while (window->isOpen())
	{
		sf::Event event;

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			else if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
				{
					window->close();
					break;
				}
				default:
					break;
				}
			}
		}
		handleEvent(event);
		window->clear();
		handleDisplayGame(event);
		window->display();
	}
}

void	Displayer::handleEvent(sf::Event &event)
{
	if (event.type != sf::Event::KeyPressed)
		player->resetTimer();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		player->move(NORTH);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		player->move(SOUTH);
	std::cout << player->getPosY() << std::endl;
}

void	Displayer::handleDisplayGame(sf::Event &event)
{
	switch (this->stateGame)
	{
	case MENU:
	{
		displayMenu(event);
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

void	Displayer::displayMenu(sf::Event &event)
{
	this->menu->run(event);
}

void	Displayer::displayGame()
{

}

void	Displayer::displayGameOver()
{

}
