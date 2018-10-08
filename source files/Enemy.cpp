#include "Enemy.h"
#include "Animation.h"

Enemy::Enemy(int indexX, int indexY, int sizex, int sizey, int health, int damage, int moveLimit, Maze *maze, sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed) :
	Character(indexX, indexY, sizex, sizey, health, health, damage, maze, texture, imageCount, switchTime, speed)
{
	this->setAnimationWalkUVRectTop(0);
	this->getShape().setTextureRect(this->getWalkUVRect());
	this->enemyMoveLimit = moveLimit;
	this->enemyMoveLimiter = 0;
}

Enemy::~Enemy()
{

}

void Enemy::randomizeMove(float deltaTime)
{
	if (this->enemyMoveLimiter > this->enemyMoveLimit)
	{
		randomEnemyMove = rand() % 100;
		enemyRetainDirection = rand() % 100;
		if (enemyRetainDirection > 75)
		{
			if (randomEnemyMove >= 0 && randomEnemyMove < 25) this->setDirection(Enemy::Direction::UP);
			else if (randomEnemyMove >= 25 && randomEnemyMove < 50) this->setDirection(Enemy::Direction::DOWN);
			else if (randomEnemyMove >= 50 && randomEnemyMove < 75) this->setDirection(Enemy::Direction::RIGHT);
			else if (randomEnemyMove >= 75 && randomEnemyMove < 100) this->setDirection(Enemy::Direction::LEFT);
		}
		this->moveCharacter(this->getDirection(), deltaTime);
		this->enemyMoveLimiter = 0;
	}
	this->enemyMoveLimiter++;
}