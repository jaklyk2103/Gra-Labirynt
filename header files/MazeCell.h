#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>

class Item;
class Maze;

class MazeCell
{
private:
	int collumn, row;
	int size;
	int wallWidth = 2;

	Maze *mazePtr;

	sf::Color cellColor = sf::Color(255, 255, 255, 255);
	sf::Color wallColor = sf::Color(0, 0, 0, 255);
	sf::Color visitedColor;

	sf::Color inStackColor;
	sf::Color endColor = sf::Color(255, 0, 255, 255);
	sf::Color startColor = sf::Color(0, 255, 0, 255);

	sf::RectangleShape cellShape;
	sf::RectangleShape leftWallShape, rightWallShape, topWallShape, bottomWallShape;

	sf::RenderWindow *window;
	Item *item = nullptr;

public:
	MazeCell(int collumn, int row, int size, Maze *maze, sf::RenderWindow *window);
	~MazeCell();

	bool isVisited = false, inStack = false, isStart = false, isEnd = false;
	bool leftWall = true, rightWall = true, topWall = true, bottomWall = true;
	sf::RectangleShape getLeftWallShape() { return leftWallShape; }
	sf::RectangleShape getRightWallShape() { return rightWallShape; }
	sf::RectangleShape getTopWallShape() { return topWallShape; }
	sf::RectangleShape getBottomWallShape() { return bottomWallShape; }
	bool isDeadEnd();
	bool hasItem = false;
	void sethasItem(bool value) { hasItem = value; }
	bool gethasItem() { return hasItem; }

	void Draw();
	void Delete();

	int getWallWidth() { return wallWidth; }
	int GetCollumn() { return collumn; }
	int GetRow() { return row; }
	sf::Vector2i getIndex() { return sf::Vector2i(this->GetCollumn(), this->GetRow()); }
	int getSize() { return size; }
	Item *getItem() { if (item != nullptr) return item; else return nullptr; }
	void setItem(Item *it) { this->item = it; }
	void setVisitedColor(sf::Color color) { visitedColor = color; }
	void setInStackColor(sf::Color color) { inStackColor = color; }

	void SetColor(sf::Color color);
};