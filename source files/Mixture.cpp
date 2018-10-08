#include "Mixture.h"
#include "Character.h"

Mixture::Mixture(Maze *maze, Character *hero, sf::Vector2i pos) : Item(maze, hero, pos)
{
}

void Mixture::onPickUp()
{
	this->pickUpAction(this->getHeroPointer());
}

void Mixture::pickUpAction(Character *hero)
{
	this->effect(hero);
}

void Mixture::loadTexture()
{
	this->ldTexture();
}