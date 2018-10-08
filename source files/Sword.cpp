#include "Sword.h"
#include "Maze.h"
#include "Character.h"

Sword::Sword(Maze *maze, Character *hero, sf::Vector2i pos) : Item(maze, hero, pos)
{
	this->loadTexture();
	this->getImage().setTexture(getTexture());
}

void Sword::onPickUp()
{
	this->pickUpAction(this->getMazePointer());
}

void Sword::pickUpAction(Maze *maze)
{
	cout << "Podniesiono miecz! Obrazenia zwiekszone!\n";
	maze->getHeroPointer()->setDamage(maze->getHeroPointer()->getDamage() + 2);
	this->destroy(maze);
}

void Sword::loadTexture()
{
	sf::Texture text;
	if (!text.loadFromFile("../images/sword1.png")) std::cout << "Could not load sword texture.\n";
	this->setTexture(text);
}