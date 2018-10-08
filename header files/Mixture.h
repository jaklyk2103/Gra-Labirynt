#pragma once
#include "Item.h"

class Character;

class Mixture : public Item
{
public:
	Mixture(Maze *maze, Character *hero, sf::Vector2i pos);

	void loadTexture();
	void onPickUp();
	void pickUpAction(Character *hero);

	virtual void ldTexture() = 0;
	virtual void effect(Character *hero) = 0;
};