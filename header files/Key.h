#pragma once
#include "Item.h"

class Maze;

class Key : public Item
{
public:
	Key(Maze *maze, Character *hero, sf::Vector2i pos);

	void loadTexture();
	void pickUpAction(Maze *maze);
	void onPickUp();
};