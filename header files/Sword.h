#pragma once
#include "Item.h"

class Maze;

class Sword : public Item
{
public:
	Sword(Maze *maze, Character *hero, sf::Vector2i pos);

	void loadTexture();
	void pickUpAction(Maze *maze);
	void onPickUp();
};

