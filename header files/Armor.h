#pragma once
#include "Item.h"

class Maze;

class Armor : public Item
{
public:
	Armor(Maze *maze, Character *hero, sf::Vector2i pos);
	
	void loadTexture();
	void pickUpAction(Maze *maze);
	void onPickUp();
};