#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "MazeCell.h"
#include "Item.h"

class Enemy;
class Character;
class Hero;

class Maze
{
private:
	int width, height;
	int collumns, rows;
	sf::Color visitedCellColor;
	sf::Color inStackCellColor;
	sf::Texture *gateOpenedTexture;
	sf::Texture *gateClosedTexture;

	bool generatingCompleted = false;
	bool exitOpened = false;
	sf::RenderWindow *window;
	std::vector<MazeCell *> stack;
	std::vector<MazeCell *> cells;
	sf::Vector2i endIndex;
	MazeCell *currentCell;
	std::list <Item *> items;
	std::list <Enemy *> enemies;
	Character *hero;

public:
	Maze(const int width, const int height, int collumns, int rows, sf::Texture *gateOpen, sf::Texture *gateClosed, sf::RenderWindow *window);
	~Maze();

	void Init(sf::Vector2f start);
	void Generate();
	bool Generated();
	void Draw();
	void DrawItems();
	void DrawEnemies();
	void Delete();
	void DeleteEnemies();

	// GETTERS / SETTERS
	bool getExitOpened() { return this->exitOpened; }
	int getGenerationStepSpeed() { return generationStepSpeed; }
	std::list<Item *> &getItems() { return this->items; }
	std::list<Enemy *> &getEnemiesList() { return this->enemies; }
	int getCollumns() { return collumns; }
	int getRows() { return rows; }
	sf::Vector2i getEndIndex() { return endIndex; }
	sf::Color getVisitedCellColor() { return visitedCellColor; }
	sf::Color getInStackCellColor() { return inStackCellColor; }
	int getMazeCellSize() {return cells[0]->getSize(); }
	sf::RenderWindow *getWindow() { return this->window; }
	MazeCell *GetMazeCell(sf::Vector2i index) { return cells[index.x*this->collumns + index.y]; }
	int GetMazeCellIndexByPosition(int x, int y);
	sf::Texture *getGateOpenedTexture() { return this->gateOpenedTexture; }
	sf::Texture *getGateClosedTexture() { return this->gateClosedTexture; }
	Character *getHeroPointer() { return this->hero; }

	void setGenerationStepSpeed(int sp) { generationStepSpeed = sp; }
	void setExitOpened(bool value) { this->exitOpened = value; }
	void setHeroPointer(Character *hr) { this->hero = hr; }

	MazeCell *GetRandomNeighbor(MazeCell *cell);
	void RemoveWalls(MazeCell *cell1, MazeCell *cell2);
	void drawEnterAndExit();
	sf::Vector2i searchEnd(sf::Vector2i startCell);
	void PlaceItems();

	int generationStepSpeed = 1;
};