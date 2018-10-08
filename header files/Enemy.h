#pragma once
#include "Character.h"

class Enemy : public Character
{
private:
enum Type { WARRIOR, KNIGHT, ASSASSIN };
Type type;

int enemyMoveLimit;
int enemyMoveLimiter;
int randomEnemyMove;
int enemyRetainDirection;

public:
	Enemy(int indexX, int indexY, int sizex, int sizey, int health, int damage, int moveLimit, Maze *maze, sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Enemy();

	void Enemy::randomizeMove(float deltaTime);
};

