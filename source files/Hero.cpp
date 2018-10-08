#include <iostream>
#include "Hero.h"
#include "Enemy.h"
#include "Animation.h"
#include <Windows.h>


Hero::Hero(int indexX, int indexY, int sizex, int sizey, int health, int maxHealth, int damage, Maze *maze, sf::Texture *texture, sf::Texture *fightTexture, sf::Vector2u imageCount, float switchTime, float speed) :
	Character(indexX, indexY, sizex, sizey, health, maxHealth, damage, maze, texture, imageCount, switchTime, speed)
{
	this->textureFight = fightTexture;
	this->setAnimationFight(Animation(fightTexture, sf::Vector2u(6, 4), 0.07f));
}

void Hero::moveHero(sf::Keyboard::Key pressedKey, float deltaTime)
{
	if (IsMovePossible(pressedKey, deltaTime))
	{
		this->Update(deltaTime, pressedKey);
		this->setMazeIndex(sf::Vector2i((int)(this->getShape().getPosition().x + round(this->getShape().getLocalBounds().width / 2)) / this->getMaze()->getMazeCellSize(),
			(int)(this->getShape().getPosition().y + round(this->getShape().getLocalBounds().height / 2)) / this->getMaze()->getMazeCellSize()));
		this->setLastDeltaTime(deltaTime);
	}
}

bool Hero::IsMovePossible(sf::Keyboard::Key pressedKey, float deltaTime)
{
	int cellSize = this->getMaze()->getMazeCellSize();
	MazeCell *currCell = this->getMaze()->GetMazeCell(getMazeIndex());
	bool flaga_dosun = false;
	switch (pressedKey)
	{
	case sf::Keyboard::Left:
	{
		if ((this->getShape().getPosition().x - (this->getSpeed() * deltaTime)) < (this->getMazeIndex().x * cellSize + currCell->getWallWidth()))
		{
			if (!currCell->leftWall)
			{
				if (this->getMazeIndex().x - 1 <= this->getMaze()->getCollumns()) if (this->getMaze()->GetMazeCell(sf::Vector2i(this->getMazeIndex().x - 1, this->getMazeIndex().y))->isEnd) // if going to maze end
					if (!this->getMaze()->getExitOpened()) return false; // if exit is opened
						if ((this->getShape().getPosition().y - (this->getMazeIndex().y * cellSize)) < currCell->getWallWidth() ||	// ¿eby nie zahaczaæ u góry
							(this->getShape().getPosition().y - (this->getMazeIndex().y * cellSize)) > cellSize - currCell->getWallWidth())
							flaga_dosun = true;
						if (((this->getShape().getPosition().y + getSize().y) - (this->getMazeIndex().y * cellSize)) < currCell->getWallWidth() ||	// ¿eby nie zahaczaæ na dole
							((this->getShape().getPosition().y + getSize().y) - (this->getMazeIndex().y * cellSize)) > cellSize - currCell->getWallWidth())
							flaga_dosun = true;
						if (!flaga_dosun) return true;
			}
			this->getShape().setPosition(this->getMazeIndex().x * cellSize + currCell->getWallWidth(), this->getShape().getPosition().y);	// przesun do krawedzi
			return false;
		}
		else return true;
		break;
	}
	case sf::Keyboard::Right:
	{
		if ((this->getShape().getPosition().x + (this->getSpeed() * deltaTime) + this->getShape().getSize().x) > this->getMazeIndex().x * cellSize + cellSize - currCell->getWallWidth())
		{
			if (!currCell->rightWall)
			{
				if (this->getMazeIndex().x + 1 <= this->getMaze()->getCollumns()) if (this->getMaze()->GetMazeCell(sf::Vector2i(this->getMazeIndex().x + 1, this->getMazeIndex().y))->isEnd) // if going to maze end
					if (!this->getMaze()->getExitOpened()) return false; // if exit is opened
						if ((this->getShape().getPosition().y - (this->getMazeIndex().y * cellSize)) < currCell->getWallWidth() ||	// ¿eby nie zahaczaæ u góry
							(this->getShape().getPosition().y - (this->getMazeIndex().y * cellSize)) > cellSize - currCell->getWallWidth())
							flaga_dosun = true;
						if (((this->getShape().getPosition().y + getSize().y) - (this->getMazeIndex().y * cellSize)) < currCell->getWallWidth() ||	// ¿eby nie zahaczaæ na dole
							((this->getShape().getPosition().y + getSize().y) - (this->getMazeIndex().y * cellSize)) > cellSize - currCell->getWallWidth())
							flaga_dosun = true;
						if (!flaga_dosun) return true;
			}
			this->getShape().setPosition(this->getMazeIndex().x * cellSize + cellSize - this->getShape().getSize().x - currCell->getWallWidth(), this->getShape().getPosition().y);	// przesun do krawedzi
			return false;
		}
		else return true;
		break;
	}
	case sf::Keyboard::Up:
	{
		if ((this->getShape().getPosition().y - (getSpeed() * deltaTime)) < (this->getMazeIndex().y * cellSize + currCell->getWallWidth()))
		{
			if (!currCell->topWall)
			{
				if (this->getMazeIndex().y - 1 <= this->getMaze()->getRows()) if (this->getMaze()->GetMazeCell(sf::Vector2i(this->getMazeIndex().x, this->getMazeIndex().y - 1))->isEnd) // if going to maze end
					if (!this->getMaze()->getExitOpened()) return false; // if exit is opened
						if ((this->getShape().getPosition().x - (this->getMazeIndex().x * cellSize)) < currCell->getWallWidth() ||	// ¿eby nie zahaczaæ z lewej
							(this->getShape().getPosition().x - (this->getMazeIndex().x * cellSize)) > cellSize - currCell->getWallWidth())
							flaga_dosun = true;
						if (((this->getShape().getPosition().x + getSize().x) - (this->getMazeIndex().x * cellSize)) < currCell->getWallWidth() ||	// ¿eby nie zahaczaæ z prawej
							((this->getShape().getPosition().x + getSize().x) - (this->getMazeIndex().x * cellSize)) > cellSize - currCell->getWallWidth())
							flaga_dosun = true;
						if (!flaga_dosun) return true;
			}
			this->getShape().setPosition(this->getShape().getPosition().x, this->getMazeIndex().y * cellSize + currCell->getWallWidth()); // przesun do krawedzi
			return false;

		}
		else return true;
		break;
	}
	case sf::Keyboard::Down:
	{
		if ((this->getShape().getPosition().y + (getSpeed() * deltaTime) + this->getShape().getSize().y) > (this->getMazeIndex().y * cellSize) + cellSize - currCell->getWallWidth())
		{
			if (!currCell->bottomWall)
			{
				if (this->getMazeIndex().y + 1 <= this->getMaze()->getRows())
					if (this->getMaze()->GetMazeCell(sf::Vector2i(this->getMazeIndex().x, this->getMazeIndex().y + 1))->isEnd) // if going to maze end
						if (!this->getMaze()->getExitOpened()) return false; // if exit is opened
						if ((this->getShape().getPosition().x - (this->getMazeIndex().x * cellSize)) < currCell->getWallWidth() ||	// ¿eby nie zahaczaæ u góry
							(this->getShape().getPosition().x - (this->getMazeIndex().x * cellSize)) > cellSize - currCell->getWallWidth())
							flaga_dosun = true;
						if (((this->getShape().getPosition().x + getSize().x) - (this->getMazeIndex().x * cellSize)) < currCell->getWallWidth() ||	// ¿eby nie zahaczaæ na dole
							((this->getShape().getPosition().x + getSize().x) - (this->getMazeIndex().x * cellSize)) > cellSize - currCell->getWallWidth())
							flaga_dosun = true;
						if (!flaga_dosun) return true;
			}
			this->getShape().setPosition(this->getShape().getPosition().x, this->getMazeIndex().y * cellSize + cellSize - this->getShape().getSize().y - currCell->getWallWidth()); // przesun do krawedzi
			return false;
		}
		else return true;
		break;
	}
	}
}

void Hero::Update(float deltaTime, sf::Keyboard::Key pressedKey)
{
	sf::Vector2f movement(0.0f, 0.0f);

	switch (pressedKey)
	{
	case sf::Keyboard::Up:
	{
		if (this->getFighting()) this->getShape().setTexture(this->getTextureWalk());
		this->setFighting(false);
		movement.y -= this->getSpeed() * deltaTime;
		this->setAnimationRow(0);
		this->setDirection(UP);
		break;
	}
	case sf::Keyboard::Down:
	{
		if (this->getFighting()) this->getShape().setTexture(this->getTextureWalk());
		this->setFighting(false);
		movement.y += this->getSpeed() * deltaTime;
		this->setAnimationRow(2);
		this->setDirection(DOWN);
		break;
	}
	case sf::Keyboard::Right:
	{
		if (this->getFighting()) this->getShape().setTexture(this->getTextureWalk());
		this->setFighting(false);
		movement.x += this->getSpeed() * deltaTime;
		this->setAnimationRow(3);
		this->setDirection(RIGHT);
		break;
	}
	case sf::Keyboard::Left:
	{
		if (this->getFighting()) this->getShape().setTexture(this->getTextureWalk());
		this->setFighting(false);
		movement.x -= this->getSpeed() * deltaTime;
		this->setAnimationRow(1);
		this->setDirection(LEFT);
		break;
	}
	}

	this->getAnimationWalk().Update(this->getAnimationRow(), deltaTime);
	this->getShape().setTextureRect(this->getAnimationWalk().uvRect);
	this->getShape().move(movement);
	this->charRectNormalize();
}

void Hero::use_item(Item *it)
{
	it->onPickUp();
	delete(&it);
}

void Hero::check_collision(Enemy *enemy)
{
	if (this->getCharRect().intersects(enemy->getCharRect()))
	{
		this->setCurrHealth(this->getCurrHealth() - enemy->getDamage());

		if (this->getCenter().y > enemy->getCenter().y) // kolizja z gory gracza
		{
			this->moveCharacter(Hero::Direction::DOWN, this->getLastDeltaTime() * 3);
		}
		if (this->getCenter().y < enemy->getCenter().y) // kolizja z dolu gracza
		{
			this->moveCharacter(Hero::Direction::UP, this->getLastDeltaTime() * 3);
		}
		if (this->getCenter().x > enemy->getCenter().x) // kolizja z lewej strony gracza
		{
			this->moveCharacter(Hero::Direction::RIGHT, this->getLastDeltaTime() * 3);
		}
		if (this->getCenter().x < enemy->getCenter().x) // kolizja z prawej strony gracza
		{
			this->moveCharacter(Hero::Direction::LEFT, this->getLastDeltaTime() * 3);
		}
		cout << "Wykryto kolizje!\n";
	}
}

void Hero::attack(float deltaTime)
{
	if (this->getAnimationFight().getAnimationEnd()) this->getAnimationFight().setAnimationEnd(false);
	
	if (!this->getFighting()) this->getShape().setTexture(this->getTextureFight());
	
	this->setFighting(true);
	switch (this->getDirection())
	{
	case Character::Direction::UP:
	{
		this->setAnimationRow(0);
		this->charRectNormalize();
		if ((this->getMaze()->GetMazeCell(this->getMazeIndex())->topWall) && // Jezeli jest sciana i...
			this->getShape().getPosition().y - round(this->getShape().getSize().y / 4) <= this->getMazeIndex().y * this->getMaze()->getMazeCellSize()) // je¿eli wyszedlby poza ta sciane
		{
			this->setCharRectHeight(this->getCharRect().height + abs(this->getMazeIndex().y * this->getMaze()->getMazeCellSize() - this->getCharRect().top));
			this->setCharRectTop(this->getMazeIndex().y * this->getMaze()->getMazeCellSize());
		}
		else
		{
			this->setCharRectHeight(this->getCharRect().height + abs((this->getShape().getPosition().y - round(this->getShape().getSize().y / 4)) - this->getCharRect().top));
			this->setCharRectTop(this->getShape().getPosition().y - round(this->getShape().getSize().y / 4));
		}
		break;
	}
	case Character::Direction::DOWN:
	{
		this->charRectNormalize();
		if ((this->getMaze()->GetMazeCell(this->getMazeIndex())->bottomWall) && // Jezeli jest sciana i...
			this->getShape().getPosition().y + this->getShape().getSize().y + round(this->getShape().getSize().y / 4) >= (this->getMazeIndex().y * this->getMaze()->getMazeCellSize() + this->getMaze()->getMazeCellSize())) // je¿eli wyszedlby poza ta sciane
		{
			this->setCharRectHeight(abs(this->getMazeIndex().y * this->getMaze()->getMazeCellSize() + this->getMaze()->getMazeCellSize() - this->getCharRect().top));
		}
		else
		{
			this->setCharRectHeight(this->getShape().getSize().y + round(this->getShape().getSize().y / 4));
		}
		this->setAnimationRow(2);
		break;
	}
	case Character::Direction::RIGHT:
	{
		this->charRectNormalize();

		if ((this->getMaze()->GetMazeCell(this->getMazeIndex())->rightWall) && // Jezeli jest sciana i...
			this->getShape().getPosition().x + this->getShape().getSize().x + round(this->getShape().getSize().x / 4) >= (this->getMazeIndex().x * this->getMaze()->getMazeCellSize() + this->getMaze()->getMazeCellSize())) // je¿eli wyszedlby poza ta sciane
		{
			this->setCharRectWidth(abs(this->getMazeIndex().x * this->getMaze()->getMazeCellSize() + this->getMaze()->getMazeCellSize() - this->getCharRect().left));
		}
		else
		{
			this->setCharRectWidth(this->getShape().getSize().x + round(this->getShape().getSize().x / 4));
		}

		this->setAnimationRow(3);
		break;
	}
	case Character::Direction::LEFT:
	{
		this->charRectNormalize();

		if ((this->getMaze()->GetMazeCell(this->getMazeIndex())->leftWall) && // Jezeli jest sciana i...
			this->getShape().getPosition().x - round(this->getShape().getSize().x / 4) <= (this->getMazeIndex().x * this->getMaze()->getMazeCellSize())) // je¿eli wyszedlby poza ta sciane
		{
			this->setCharRectWidth(this->getCharRect().width + abs(this->getMazeIndex().x * this->getMaze()->getMazeCellSize() - this->getCharRect().left));
			//				charRect.width = abs(this->getMazeIndex().x * this->getMaze()->getMazeCellSize() - charRect.left);
			this->setCharRectLeft(this->getMazeIndex().x * this->getMaze()->getMazeCellSize());
		}
		else
		{
			this->setCharRectWidth(this->getShape().getSize().x + round(this->getShape().getSize().x / 4));
			this->setCharRectLeft(this->getCharRect().left - round(this->getShape().getSize().x / 4));
		}

		this->setAnimationRow(1);
		break;
	}
	}

	this->getAnimationFight().Update(this->getAnimationRow(), deltaTime);
	this->getShape().setTextureRect(this->getAnimationFight().uvRect);

	// KOLIZJA
	std::list <Enemy *>::iterator it;
	for (it = this->getMaze()->getEnemiesList().begin(); it != this->getMaze()->getEnemiesList().end(); it++)
	{
		if (this->getCharRect().intersects((*it)->getCharRect()))
		{
			(*it)->setCurrHealth((*it)->getCurrHealth() - this->getDamage());

			if ((*it)->getCenter().y > this->getCenter().y) // kolizja z gory przeciwnika
			{
				(*it)->moveCharacter(Enemy::Direction::DOWN, this->getLastDeltaTime() * 5);
			}
			if ((*it)->getCenter().y < this->getCenter().y) // kolizja z dolu przeciwnika
			{
				(*it)->moveCharacter(Enemy::Direction::UP, this->getLastDeltaTime() * 5);
			}
			if ((*it)->getCenter().x > this->getCenter().x) // kolizja z lewej strony przeciwnika
			{
				(*it)->moveCharacter(Enemy::Direction::RIGHT, this->getLastDeltaTime() * 5);
			}
			if ((*it)->getCenter().x < this->getCenter().x) // kolizja z prawej strony przeciwnika
			{
				(*it)->moveCharacter(Enemy::Direction::LEFT, this->getLastDeltaTime() * 5);
			}
			cout << "Wykryto kolizje (atak gracza)!\n";
		}
	}

	this->charRectNormalize();
}