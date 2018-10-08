#include <SFML/Graphics.hpp>
#include <iostream>
#include "MazeCell.h"
#include "Maze.h"

MazeCell::MazeCell(int collumn, int row, int size, Maze *maze, sf::RenderWindow *window) : collumn(collumn), row(row), size(size), window(window)
{
	this->mazePtr = maze;
	sf::Vector2f cellPosition = sf::Vector2f(size * collumn, size * row);
	this->setVisitedColor(maze->getVisitedCellColor());
	this->setInStackColor(maze->getInStackCellColor());

	// Cell
	cellShape = sf::RectangleShape(sf::Vector2f(size, size));
	cellShape.setPosition(cellPosition.x, cellPosition.y);
	cellShape.setFillColor(cellColor);

	// Walls
	leftWallShape = sf::RectangleShape(sf::Vector2f(wallWidth, size));
	leftWallShape.setPosition(cellPosition.x, cellPosition.y);
	leftWallShape.setOutlineColor(wallColor);
	leftWallShape.setFillColor(wallColor);

	rightWallShape = sf::RectangleShape(sf::Vector2f(wallWidth, size));
	rightWallShape.setPosition(cellPosition.x + size - wallWidth, cellPosition.y);
	rightWallShape.setOutlineColor(wallColor);
	rightWallShape.setFillColor(wallColor);

	topWallShape = sf::RectangleShape(sf::Vector2f(size, wallWidth));
	topWallShape.setPosition(cellPosition.x, cellPosition.y);
	topWallShape.setOutlineColor(wallColor);
	topWallShape.setFillColor(wallColor);

	bottomWallShape = sf::RectangleShape(sf::Vector2f(size, wallWidth));
	bottomWallShape.setPosition(cellPosition.x, cellPosition.y+size - wallWidth);
	bottomWallShape.setOutlineColor(wallColor);
	bottomWallShape.setFillColor(wallColor);
}

MazeCell::~MazeCell()
{

}

void MazeCell::SetColor(sf::Color color)
{
	if (this->cellShape.getFillColor() != color)
	{
		this->cellShape.setFillColor(color);
	}
}

void MazeCell::Draw()
{
	if(isStart)
	{
		SetColor(visitedColor);
	}
	else if (inStack)
	{
		SetColor(inStackColor);
	}
	else if (isVisited)
	{
		SetColor(visitedColor);
	}

	window->draw(this->cellShape);

	if (leftWall)
	{
		window->draw(leftWallShape);
	}
	if (rightWall)
	{
		window->draw(rightWallShape);
	}
	if (topWall)
	{
		window->draw(topWallShape);
	}
	if (bottomWall)
	{
		window->draw(bottomWallShape);
	}
}

bool MazeCell::isDeadEnd()
{
	int wallCounter = 0;

	if (this->leftWall) wallCounter++;
	if (this->rightWall) wallCounter++;
	if (this->topWall) wallCounter++;
	if (this->bottomWall) wallCounter++;

	if (wallCounter == 3) return true;
	else return false;
}

void MazeCell::Delete()
{
	delete(this);
}