#include "Armor.h"
#include "Maze.h"
#include "Character.h"

Armor::Armor(Maze *maze, Character *hero, sf::Vector2i pos) : Item(maze, hero, pos)
{
	this->loadTexture();
	this->getImage().setTexture(getTexture());
}

void Armor::onPickUp()
{
	this->pickUpAction(this->getMazePointer());
}

void Armor::pickUpAction(Maze *maze)
{
	cout << "Podniesiono zbroje! Wytrzymalosc zwiekszona!\n";
	maze->getHeroPointer()->setMaxHealth(maze->getHeroPointer()->getMaxHealth() + 5);
	maze->getHeroPointer()->setCurrHealth(maze->getHeroPointer()->getCurrHealth() + 5);
	this->destroy(maze);
}

void Armor::loadTexture()
{
	sf::Texture text;
	if (!text.loadFromFile("../images/armor1.png")) std::cout << "Could not load armor texture.\n";
	this->setTexture(text);
}