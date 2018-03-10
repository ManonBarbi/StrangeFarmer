#include "Game.hh"

Game::Game(sf::RenderWindow *_window, std::map<std::string, sf::Keyboard::Key> *_keymapping)
{
	this->window = _window;
	this->keymapping = _keymapping;
	//Tile
	this->tileTexture.loadFromFile("ress\\ground.png");
	for (size_t i = 0; i < 9; ++i)
	{
		tilePositionTextureLand[i].width = 32;
		tilePositionTexturePlowedLand[i].width = 32;
		tilePositionTextureWetPlowedLand[i].width = 32;
		tilePositionTextureHuntedLand[i].width = 32;
		tilePositionTextureWetHuntedLand[i].width = 32;

		tilePositionTextureLand[i].height = 32;
		tilePositionTexturePlowedLand[i].height = 32;
		tilePositionTextureWetPlowedLand[i].height = 32;
		tilePositionTextureHuntedLand[i].height = 32;
		tilePositionTextureWetHuntedLand[i].height = 32;

		tilePositionTextureLand[i].left = (i * 32) % 96;
		tilePositionTexturePlowedLand[i].left = 192 + (i * 32) % 96;
		tilePositionTextureWetPlowedLand[i].left = 288 + (i * 32) % 96;
		tilePositionTextureHuntedLand[i].left = 96 + (i * 32) % 96;
		tilePositionTextureWetHuntedLand[i].left = 384 + (i * 32) % 96;

		tilePositionTextureLand[i].top = i / 3 * 32;
		tilePositionTexturePlowedLand[i].top = i / 3 * 32;
		tilePositionTextureWetPlowedLand[i].top = i / 3 * 32;
		tilePositionTextureHuntedLand[i].top = i / 3 * 32;
		tilePositionTextureWetHuntedLand[i].top = i / 3 * 32;

	}
	this->tile.setTexture(this->tileTexture);
	//Player
	this->playerTexture.loadFromFile("ress\\player.png");
	this->playerPositionTextureIdle[0].left = 9;
	this->playerPositionTextureIdle[0].top = 10;
	this->playerPositionTextureIdle[0].width = 32;
	this->playerPositionTextureIdle[0].height = 32;
	//+41
	this->playerPositionTextureIdle[1].left = 9;
	this->playerPositionTextureIdle[1].top = 54;
	this->playerPositionTextureIdle[1].width = 32;
	this->playerPositionTextureIdle[1].height = 32;
	//+41
	this->playerPositionTextureIdle[2].left = 9;
	this->playerPositionTextureIdle[2].top = 99;
	this->playerPositionTextureIdle[2].width = 25;
	this->playerPositionTextureIdle[2].height = 32;
	//+33
	this->playerPositionTextureIdle[3].left = 34;
	this->playerPositionTextureIdle[3].top = 99;
	this->playerPositionTextureIdle[3].width = -25;
	this->playerPositionTextureIdle[3].height = 32;
	//+33
	this->playerPositionTextureWalk[0].left = 13;
	this->playerPositionTextureWalk[0].top = 150;
	this->playerPositionTextureWalk[0].width = 32;
	this->playerPositionTextureWalk[0].height = 32;
	//+41
	this->playerPositionTextureWalk[1].left = 13;
	this->playerPositionTextureWalk[1].top = 196;
	this->playerPositionTextureWalk[1].width = 32;
	this->playerPositionTextureWalk[1].height = 32;
	//+41
	this->playerPositionTextureWalk[2].left = 13;
	this->playerPositionTextureWalk[2].top = 241;
	this->playerPositionTextureWalk[2].width = 32;
	this->playerPositionTextureWalk[2].height = 32;
	//+41
	this->playerPositionTextureWalk[3].left = 37;
	this->playerPositionTextureWalk[3].top = 241;
	this->playerPositionTextureWalk[3].width = -32;
	this->playerPositionTextureWalk[3].height = 32;
	//+41
	this->playerSprite.setTexture(this->playerTexture);
	this->playerSprite.setTextureRect(this->playerPositionTextureIdle[0]);
	this->playerDirection = 0;
	this->playerIsWalking = false;
	//house
	this->houseTexture.loadFromFile("ress\\house.png");
	this->house.setTexture(this->houseTexture);
	//Ratio Calcul
	this->ratioX = this->window->getSize().x / 1920.0;
	this->ratioY = this->window->getSize().y / 1080.0;
	this->tile.setScale(ratioX * 2, ratioY * 2);
	this->playerSprite.setScale(ratioX * 2, ratioY * 2);
	this->house.setScale(ratioX, ratioY);
	//creation du tabeau de pixel
	this->mapTexture.create(this->player.getMapCreator().getSizeX() * 64, this->player.getMapCreator().getSizeY() * 64);
}

Game::~Game()
{

}

void	Game::handleEvent(sf::Event &event)
{
	if (event.type == sf::Event::Resized)
	{
		this->ratioX = this->window->getSize().x / 1920.0;
		this->ratioY = this->window->getSize().y / 1080.0;
		this->tile.setScale(ratioX * 2, ratioY * 2);
		this->playerSprite.setScale(ratioX * 2, ratioY * 2);
		this->house.setScale(ratioX, ratioY);
		window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
		this->mapTexture.clear();
		this->refreshMap();
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		window->close();
	}
}

void	Game::run(t_menu &stateGame)
{
	handleKeyboard();
	displayMap();
	displayHouse();
	displayPlayer();
}

void	Game::handleKeyboard()
{
	int	code = 0;

	if (sf::Keyboard::isKeyPressed((*keymapping)["Up"]))
		code += 1000;
	if (sf::Keyboard::isKeyPressed((*keymapping)["Right"]))
		code += 100;
	if (sf::Keyboard::isKeyPressed((*keymapping)["Down"]))
		code += 10;
	if (sf::Keyboard::isKeyPressed((*keymapping)["Left"]))
		code += 1;

	switch (code)
	{
	case 1000:
	{
		player.move(NORTH);
		this->playerDirection = 1;
		this->playerIsWalking = true;
		break;
	}
	case 1100:
	{
		player.move(NORTHEAST);
		this->playerDirection = 1;
		this->playerIsWalking = true;
		break;
	}
	case 100:
	{
		player.move(EAST);
		this->playerDirection = 2;
		this->playerIsWalking = true;
		break;
	}
	case 110:
	{
		player.move(SOUTHEAST);
		this->playerDirection = 0;
		this->playerIsWalking = true;
		break;
	}
	case 10:
	{
		player.move(SOUTH);
		this->playerDirection = 0;
		this->playerIsWalking = true;
		break;
	}
	case 11:
	{
		player.move(SOUTHWEST);
		this->playerDirection = 0;
		this->playerIsWalking = true;
		break;
	}
	case 1:
	{
		player.move(WEST);
		this->playerDirection = 3;
		this->playerIsWalking = true;
		break;
	}
	case 1001:
	{
		player.move(NORTHWEST);
		this->playerDirection = 1;
		this->playerIsWalking = true;
		break;
	}
	default:
	{
		this->playerIsWalking = false;
		player.resetTimer();
		break;
	}
	}
}

void	Game::refreshMap()
{
	for (size_t i = 0; i < this->player.getMapCreator().getSizeY(); ++i)
		for (size_t j = 0; j < this->player.getMapCreator().getSizeX(); ++j)
		{
			this->tile.setPosition(j * 64.0 * ratioX, (this->player.getMapCreator().getSizeY() - 1) * 64.0 - (i * 64.0 * ratioY));
			switch (this->player.getMapCreator().getMap()[i * 100 + j].status)
			{
			case LAND:
			{
				this->tile.setTextureRect(this->tilePositionTextureLand[this->getOffsetTile(j, i)]);
				this->mapTexture.draw(this->tile);
				break;
			}
			case PLOWED_LAND:
			{
				this->tile.setTextureRect(this->tilePositionTexturePlowedLand[this->getOffsetTile(j, i)]);
				this->mapTexture.draw(this->tile);
				break;
			}
			case WET_PLOWED_LAND:
			{
				this->tile.setTextureRect(this->tilePositionTextureWetPlowedLand[this->getOffsetTile(j, i)]);
				this->mapTexture.draw(this->tile);
				break;
			}
			case HUNTED_LAND:
			{
				this->tile.setTextureRect(this->tilePositionTextureHuntedLand[this->getOffsetTile(j, i)]);
				this->mapTexture.draw(this->tile);
				break;
			}
			case WET_HUNTED_LAND:
			{
				this->tile.setTextureRect(this->tilePositionTextureWetHuntedLand[this->getOffsetTile(j, i)]);
				this->mapTexture.draw(this->tile);
				break;
			}
			default:
				break;
			}
		}
	this->mapSprite.setTexture(this->mapTexture.getTexture());
	this->clockDrawMap.restart();
}

void	Game::displayMap()
{
	if (this->clockDrawMap.getElapsedTime().asSeconds() >= 1)
		this->refreshMap();
	double	x = static_cast<double>(this->player.getPosX()) / 100.0;
	double	y = static_cast<double>(this->player.getPosY()) / 100.0;
	this->mapSprite.setPosition(-x * 64.0 * ratioX + this->window->getSize().x / 2.0, -y * 64.0 * ratioY + this->window->getSize().y / 2.0);
	//this->mapSprite.setPosition(-5000, -5000);
	this->window->draw(this->mapSprite);
}

int		Game::getOffsetTile(int x, int y)
{
	if (x == 0 && y == 0)
		return (6);
	else if (x > 0 && x < this->player.getMapCreator().getSizeX() - 1 && y == 0)
		return (7);
	else if (x == this->player.getMapCreator().getSizeX() - 1 && y == 0)
		return (8);
	else if (y > 0 && y < this->player.getMapCreator().getSizeY() - 1 && x == 0)
		return (3);
	else if (x == this->player.getMapCreator().getSizeX() - 1 &&
		y > 0 && y < this->player.getMapCreator().getSizeY() - 1)
		return (5);
	else if (x == 0 && y == this->player.getMapCreator().getSizeY() - 1)
		return (0);
	else if (y == this->player.getMapCreator().getSizeY() - 1 && x > 0 && x < this->player.getMapCreator().getSizeX() - 1)
		return (1);
	else if (y == this->player.getMapCreator().getSizeY() - 1 && x == this->player.getMapCreator().getSizeX() - 1)
		return (2);
	return (4);
}

void	Game::displayPlayer()
{
	if (this->playerClockAnimation.getElapsedTime().asMilliseconds() >= sf::Int32(100))
	{
		if (!this->playerIsWalking)
		{
			if (this->playerDirection == 0 || this->playerDirection == 1)
			{
				this->playerPositionTextureIdle[this->playerDirection].left += 41;
				if (this->playerPositionTextureIdle[this->playerDirection].left >= 297)
					this->playerPositionTextureIdle[this->playerDirection].left = 9;
			}
			else
			{
				this->playerPositionTextureIdle[this->playerDirection].left += 33;
				if (this->playerPositionTextureIdle[this->playerDirection].left >= 209)
				{
					if (this->playerDirection == 2)
						this->playerPositionTextureIdle[this->playerDirection].left = 9;
					else
						this->playerPositionTextureIdle[this->playerDirection].left = 34;
				}
			}
		}
		else
		{
			this->playerPositionTextureWalk[this->playerDirection].left += 41;
			if (this->playerPositionTextureWalk[this->playerDirection].left >= 341)
			{
				if (this->playerDirection == 3)
					this->playerPositionTextureWalk[this->playerDirection].left = 37;
				else
					this->playerPositionTextureWalk[this->playerDirection].left = 13;
			}
		}
		this->playerClockAnimation.restart();
	}
	if (this->playerIsWalking)
		this->playerSprite.setTextureRect(this->playerPositionTextureWalk[this->playerDirection]);
	else
		this->playerSprite.setTextureRect(this->playerPositionTextureIdle[this->playerDirection]);
	this->playerSprite.setPosition(this->window->getSize().x / 2 - (this->playerPositionTextureIdle[0].width / 2) * ratioX, this->window->getSize().y / 2 - (this->playerPositionTextureIdle[0].height / 2) * ratioY);
	this->window->draw(this->playerSprite);
}

void	Game::displayHouse()
{
	this->house.setPosition(this->player.getMapCreator().getSizeX() / 2 * 64.0 * ratioX - (this->player.getPosX() / 100.0 * 64.0 * ratioX) + this->window->getSize().x / 2 - this->houseTexture.getSize().x * ratioX / 2, 64.0 * ratioY - (this->player.getPosY() / 100.0 * 64.0 * ratioY) + this->window->getSize().y / 2);
	this->window->draw(this->house);
}