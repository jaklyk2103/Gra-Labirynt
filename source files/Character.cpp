#include "Character.h"
#include "Item.h"

Character::Character(int indexX, int indexY, int sizex, int sizey, int health, int maxHealth, int damage, Maze *maze, sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed) : 
	animationWalk(texture, imageCount, switchTime)
{
	this->switchTime = switchTime;
	this->position = sf::Vector2f(indexX*maze->getMazeCellSize() + (maze->getMazeCellSize()/4), indexY*maze->getMazeCellSize() + (maze->getMazeCellSize() / 5));
	this->animationRow = 0;
	this->size = sf::Vector2f(sizex, sizey);
	this->shape.setSize(size);
	this->shape.setPosition(position);
	this->animationWalk.uvRect.left = 0;
	this->animationWalk.uvRect.top = 2 * animationWalk.uvRect.height;
	this->textureWalk = texture;
	this->shape.setTexture(texture);
	this->shape.setTextureRect(animationWalk.uvRect);
	this->charRect.left = shape.getPosition().x;
	this->charRect.top = shape.getPosition().y;
	this->charRect.height = shape.getSize().y;
	this->charRect.width = shape.getSize().x;
	this->lastDeltaTime = 0;
	this->dir = DOWN;

	this->damage = damage;
	this->maxHealth = maxHealth;
	this->currHealth = health;
	this->mazePtr = maze;
	this->mazeIndex = sf::Vector2i(indexX, indexY);
	this->speed = speed;
}


void Character::Update(float deltaTime, Character::Direction direction)
{
	sf::Vector2f movement(0.0f, 0.0f);

	switch (direction)
	{
	case Character::Direction::UP:
	{
		movement.y -= speed * deltaTime;
		animationRow = 3;
		//dir = UP;
		break;
	}
	case Character::Direction::DOWN:
	{
		movement.y += speed * deltaTime;
		animationRow = 0;
		//dir = DOWN;
		break;
	}
	case Character::Direction::RIGHT:
	{
		movement.x += speed * deltaTime;
		animationRow = 2;
		//dir = RIGHT;
		break;
	}
	case Character::Direction::LEFT:
	{
		movement.x -= speed * deltaTime;
		animationRow = 1;
		//dir = LEFT;
		break;
	}
	}

	animationWalk.Update(animationRow, deltaTime);
	shape.setTextureRect(animationWalk.uvRect);
	shape.move(movement);
	this->charRectNormalize();
}

bool Character::IsMovePossible(Character::Direction direction, float deltaTime)
{
	int cellSize = this->getMaze()->getMazeCellSize();
	MazeCell *currCell = this->getMaze()->GetMazeCell(getMazeIndex());
	bool flaga_dosun = false;
	switch (direction)
	{
	case Character::Direction::LEFT:
	{
		if ((this->getShape().getPosition().x - (this->getSpeed() * deltaTime)) < (this->getMazeIndex().x * cellSize + currCell->getWallWidth()))
		{
			if (!currCell->leftWall)
			{
				if (this->getMazeIndex().x - 1 <= this->getMaze()->getCollumns()) if (this->getMaze()->GetMazeCell(sf::Vector2i(this->getMazeIndex().x - 1, this->getMazeIndex().y))->isEnd) // if going to maze end
					if (this->getMaze()->getExitOpened()) return false; // if exit is opened
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
	case Character::Direction::RIGHT:
	{
		if ((this->getShape().getPosition().x + (this->getSpeed() * deltaTime) + this->getShape().getSize().x) > this->getMazeIndex().x * cellSize + cellSize - currCell->getWallWidth())
		{
			if (!currCell->rightWall)
			{
				if (this->getMazeIndex().x + 1 <= this->getMaze()->getCollumns()) if (this->getMaze()->GetMazeCell(sf::Vector2i(this->getMazeIndex().x + 1, this->getMazeIndex().y))->isEnd) // if going to maze end
					if (this->getMaze()->getExitOpened()) return false; // if exit is opened
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
	case Character::Direction::UP:
	{
		if ((this->getShape().getPosition().y - (getSpeed() * deltaTime)) < (this->getMazeIndex().y * cellSize + currCell->getWallWidth()))
		{
			if (!currCell->topWall)
			{
				if (this->getMazeIndex().y - 1 <= this->getMaze()->getRows()) if (this->getMaze()->GetMazeCell(sf::Vector2i(this->getMazeIndex().x, this->getMazeIndex().y - 1))->isEnd) // if going to maze end
					if (this->getMaze()->getExitOpened()) return false; // if exit is opened
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
	case Character::Direction::DOWN:
	{
		if ((this->getShape().getPosition().y + (getSpeed() * deltaTime) + this->getShape().getSize().y) > (this->getMazeIndex().y * cellSize) + cellSize - currCell->getWallWidth())
		{
			if (!currCell->bottomWall)
			{
				if (this->getMazeIndex().y + 1 <= this->getMaze()->getRows()) if (this->getMaze()->GetMazeCell(sf::Vector2i(this->getMazeIndex().x, this->getMazeIndex().y + 1))->isEnd) // if going to maze end
					if (this->getMaze()->getExitOpened()) return false; // if exit is opened
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

void Character::moveCharacter(Character::Direction direction, float deltaTime)
{
	if (IsMovePossible(direction, deltaTime))
	{
		this->Update(deltaTime, direction);
		this->setMazeIndex(sf::Vector2i((int)(this->getShape().getPosition().x + round(this->getShape().getLocalBounds().width / 2)) / this->getMaze()->getMazeCellSize(),
			(int)(this->getShape().getPosition().y + round(this->getShape().getLocalBounds().height / 2)) / this->getMaze()->getMazeCellSize()));
	}
}

void Character::charRectNormalize()
{
	this->charRect.left = this->getShape().getPosition().x;
	this->charRect.top = this->getShape().getPosition().y;
	this->charRect.height = this->getShape().getSize().y;
	this->charRect.width = this->getShape().getSize().x;
}

void Character::Delete()
{
	delete(this);
}