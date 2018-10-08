#include <iterator>
#include <list>
#include "Item.h"
#include "Maze.h"
#include "Hero.h"

Item::Item(Maze *maze, Character *hero, sf::Vector2i pos)
{
	this->hero = hero;
	this->maze = maze;
	position = pos;
	id = itemCounter;
	itemCounter++;
}


void Item::destroy(Maze *maze)
{
	maze->GetMazeCell(this->getPosition())->sethasItem(false);
	maze->GetMazeCell(this->getPosition())->setItem(nullptr);
	delete(this);
}

int Item::itemCounter = 0;