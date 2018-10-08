#include "Key.h"
#include "Maze.h"

Key::Key(Maze *maze, Character *hero, sf::Vector2i pos) : Item(maze, hero, pos)
{
	this->loadTexture();
	this->getImage().setTexture(getTexture());
}

void Key::onPickUp()
{
	this->pickUpAction(this->getMazePointer());
}

void Key::pickUpAction(Maze *maze)
{
	cout << "Podniesiono klucz! Wyjscie labiryntu otwarte!\n";
	maze->setExitOpened(true);
	this->destroy(maze);
}

void Key::loadTexture()
{
	sf::Texture text;
	if (!text.loadFromFile("../images/Key.png")) std::cout << "Could not load key texture.\n";
	this->setTexture(text);
}