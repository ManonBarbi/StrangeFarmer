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
	fillKeyMapping();
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

void	Displayer::fillKeyMapping()
{
	keymapping["Up"] = sf::Keyboard::Up;
	keymapping["Down"] = sf::Keyboard::Down;
	keymapping["Left"] = sf::Keyboard::Left;
	keymapping["Right"] = sf::Keyboard::Right;
}

void	Displayer::handleEvent(sf::Event &event)
{
	int	code = 0;

	if (sf::Keyboard::isKeyPressed(keymapping["Up"]))
		code += 1000;
	if (sf::Keyboard::isKeyPressed(keymapping["Right"]))
		code += 100;
	if (sf::Keyboard::isKeyPressed(keymapping["Down"]))
		code += 10;
	if (sf::Keyboard::isKeyPressed(keymapping["Left"]))
		code += 1;
	
	switch (code)
	{
	case 1000:
	{
		player->move(NORTH);
		break;
	}
	case 1100:
	{
		player->move(NORTHEAST);
		break;
	}
	case 100:
	{
		player->move(EAST);
		break;
	}
	case 110:
	{
		player->move(SOUTHEAST);
		break;
	}
	case 10:
	{
		player->move(SOUTH);
		break;
	}
	case 11:
	{
		player->move(SOUTHWEST);
		break;
	}
	case 1:
	{
		player->move(WEST);
		break;
	}
	case 1001:
	{
		player->move(NORTHWEST);
		break;
	}
	default:
	{
		player->resetTimer();
		break;
	}
	}
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
