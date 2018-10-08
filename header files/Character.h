#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "Animation.h"

using namespace std;

class Item;

class Character
{
private:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::RectangleShape shape;
	sf::IntRect charRect;
	sf::Texture *textureWalk;
	float speed;
	float switchTime;
	float lastDeltaTime;
	int maxHealth;
	int currHealth;
	int damage;
	Animation animationWalk;
	unsigned int animationRow;
public: enum Direction { LEFT, RIGHT, UP, DOWN };
private:
	Direction dir;
	bool fighting = false;

	sf::Vector2i mazeIndex;
	Maze *mazePtr;

public:
	Character(int indexX, int indexY, int sizex, int sizey, int health, int maxHealth, int damage, Maze *maze, sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed);

	// GETTERS/SETTERS
	Maze *getMaze() { return this->mazePtr; }
	sf::Vector2i getMazeIndex() { return mazeIndex; }
	sf::RectangleShape &getShape() { return shape; }
	float getSwitchTime() { return switchTime; }
	float getSpeed() { return speed; }
	float getLastDeltaTime() { return this->lastDeltaTime; }
	sf::Vector2f getSize() { return this->size; }
	int getCurrHealth() { return this->currHealth; }
	int getMaxHealth() { return this->maxHealth; }
	int getDamage() { return this->damage; }
	int getAnimationRow() { return this->animationRow; }
	bool getFighting() { return fighting; }
	sf::Vector2f getCenter() { return sf::Vector2f(this->getShape().getPosition().x + round(this->getShape().getSize().x / 2),
			this->getShape().getPosition().y + round(this->getShape().getSize().y / 2)); }
	Animation &getAnimationWalk() { return this->animationWalk; }
	sf::IntRect getWalkUVRect() { return this->animationWalk.uvRect; }
	sf::IntRect getCharRect() { return this->charRect; }
	sf::Texture *getTextureWalk() { return this->textureWalk; }
	Character::Direction getDirection() { return this->dir; }

	void setMaxHealth(int value) { this->maxHealth = value; }
	void setCurrHealth(int value) { this->currHealth = value; }
	void setDamage(int value) { this->damage = value; }
	void setAnimationRow(int value) { animationRow = value; }
	void setAnimationWalkUVRectTop(int value) { animationWalk.uvRect.top = value; }
	void setSpeed(float sp) { speed = sp; }
	void setSwitchTime(float st) { switchTime = st; }
	void setMazeIndex(sf::Vector2i index) { mazeIndex = index; }
	void setLastDeltaTime(float deltaTime) { lastDeltaTime = deltaTime; }
	void setFighting(bool value) { this->fighting = value;}
	void setDirection(Character::Direction dir) { this->dir = dir; }
	void setCharRectHeight(int value) { this->charRect.height = value; }
	void setCharRectWidth(int value) { this->charRect.width = value; }
	void setCharRectLeft(int value) { this->charRect.left = value; }
	void setCharRectTop(int value) { this->charRect.top = value; }

	void Update(float deltaTime, Character::Direction direction);
	void Draw() { this->getMaze()->getWindow()->draw(this->getShape()); }
	void Delete();

	void charRectNormalize();
	bool IsMovePossible(Character::Direction direction, float deltaTime);
	void moveCharacter(Character::Direction direction, float deltaTime);
};