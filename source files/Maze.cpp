#include <iostream>
#include <iterator>
#include "time.h"
#include "Maze.h"
#include "Mixture.h"
#include "MixtureHP.h"
#include "MixtureSpeed.h"
#include "Key.h"
#include "Item.h";
#include "Enemy.h"
#include "Hero.h"
#include "Armor.h"
#include "Sword.h"

Maze::Maze(int width, int height, int collumns, int rows, sf::Texture *gateOpened, sf::Texture *gateClosed, sf::RenderWindow *window) : width(width), height(height), collumns(collumns), rows(rows), window(window)
{
	srand(time(0));
	this->gateOpenedTexture = gateOpened;
	this->gateClosedTexture = gateClosed;
	int differ = (rand() % 50) + 50;
	int rgb = (rand() % (255 - differ)) + differ;
	visitedCellColor = sf::Color(rgb - differ, rgb - (differ / 2), rgb, 255);
	inStackCellColor = sf::Color(200, (differ/2), (differ / 2), 255);
	Init(sf::Vector2f(0,0));
}

Maze::~Maze()
{

}

bool Maze::Generated()
{
	if (generatingCompleted) return true;
	else return false;
}

void Maze::Init(sf::Vector2f startPos)
{
	generatingCompleted = false;
	cells.clear();
	stack.clear();
	enemies.clear();
	
	int size = (int)(width / collumns);

	for (int x = 0; x < collumns; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			cells.push_back(new MazeCell(x, y, size, this, window));

			if (sf::Vector2f(x, y) == startPos)
			{
				cells[cells.size() - 1]->isStart = true;
			}
		}
	}
	currentCell = cells[0];
}

void Maze::Generate()
{
	int it = 0;
	while (it < generationStepSpeed)
	{
		it++;
		currentCell->isVisited = true;
		currentCell->inStack = true;

		MazeCell *nextCell = GetRandomNeighbor(currentCell);
		if (nextCell != nullptr)
		{
			RemoveWalls(currentCell, nextCell);

			currentCell = nextCell;

			stack.push_back(currentCell);
		}
		else
		{
			if (stack.size() > 1)
			{
				stack[stack.size() - 1]->inStack = false;
				stack.pop_back();
				currentCell = stack[stack.size() - 1];
			}

			if (stack.size() == 1)
			{
				stack[stack.size() - 1]->inStack = false;
				stack.clear();
				generatingCompleted = true;



				this->endIndex = this->searchEnd(sf::Vector2i(this->getCollumns() - 1, this->getRows() - 1)); // znalezienie komorki koncowej
				this->GetMazeCell(endIndex)->isEnd = true; // ustawienie konca

				this->window->clear(); // wyswietlenie od razu, by nie zostaly niedorysowane resztki
				this->Draw();
				this->window->display();
			}
		}
	}
}

void Maze::Draw()
{
	for (int i = 0; i < cells.size(); i++)
	{
		cells[i]->Draw();
	}
	this->drawEnterAndExit();
}

void Maze::DrawItems()
{
	Item *curItem;
	for (int i = 0; i < cells.size(); i++)
	{
		curItem = cells[i]->getItem();
		if (curItem) this->window->draw(curItem->getImage());
	}
}

void Maze::DrawEnemies()
{
	for (auto &it : this->enemies)
	{
		it->Draw();
	}
}

void Maze::DeleteEnemies()
{
	for (auto &it : this->enemies)
	{
		it->Delete();
	}
}

int Maze::GetMazeCellIndexByPosition(int x, int y)
{
	if (x < 0 || y < 0 || x > collumns - 1 || y > rows - 1)
	{
		return -1;
	}
	else return x*collumns + y;
}

void Maze::RemoveWalls(MazeCell *cell1, MazeCell *cell2)
{
	if (cell1->GetCollumn() == cell2->GetCollumn() + 1)
	{
		cell1->leftWall = false;
		cell2->rightWall = false;
	}
	else if (cell1->GetCollumn() == cell2->GetCollumn() - 1)
	{
		cell1->rightWall = false;
		cell2->leftWall = false;
	}
	else if (cell1->GetRow() == cell2->GetRow() + 1)
	{
		cell1->topWall = false;
		cell2->bottomWall = false;
	}
	else if (cell1->GetRow() == cell2->GetRow() - 1)
	{
		cell1->bottomWall = false;
		cell2->topWall = false;
	}
}

MazeCell *Maze::GetRandomNeighbor(MazeCell *cell)
{
	std::vector<MazeCell *> availableNeighbors;

	int cellsSize = cells.size();

	// Right
	int index = GetMazeCellIndexByPosition(cell->GetCollumn() + 1, cell->GetRow());
	if (index < cellsSize && index != -1)
	{
		if (!cells[index]->isVisited)
		{
			availableNeighbors.push_back(cells[index]);
		}
	}
	// Left
	index = GetMazeCellIndexByPosition(cell->GetCollumn() - 1, cell->GetRow());
	if (index < cellsSize && index != -1)
	{
		if (!cells[index]->isVisited)
		{
			availableNeighbors.push_back(cells[index]);
		}
	}
	// Top
	index = GetMazeCellIndexByPosition(cell->GetCollumn(), cell->GetRow() - 1);
	if (index < cellsSize && index != -1)
	{
		if (!cells[index]->isVisited)
		{
			availableNeighbors.push_back(cells[index]);
		}
	}
	// Bottom
	index = GetMazeCellIndexByPosition(cell->GetCollumn(), cell->GetRow() + 1);
	if (index < cellsSize && index != -1)
	{
		if (!cells[index]->isVisited)
		{
			availableNeighbors.push_back(cells[index]);
		}
	}

	if (availableNeighbors.size() > 0)
	{
		return availableNeighbors[(int)(rand() % availableNeighbors.size())];
	}
	else
	{
		return nullptr;
	}
}

void Maze::PlaceItems()
{
	bool keyPlaced = false;
	srand(time(NULL));
	Item *przedmiot;
	int wallCounter = 0;
	int random;
	for (int i = this->getRows() - 1; i >= 0; i--)
	{
		for (int j = 0; j < this->getCollumns(); j++)
		{
			MazeCell *currcell = this->GetMazeCell(sf::Vector2i(j, i));
			if (!currcell->isStart && !currcell->isEnd)
			{
				if (currcell->isDeadEnd())
				{
					if (!keyPlaced)
					{
						przedmiot = new Key(this, this->getHeroPointer(), sf::Vector2i(j, i)); // if yes -> place item
						keyPlaced = true;
					}
					else
					{
						random = rand() % 100;
						if (random <= 30) przedmiot = new MixtureHP(this, this->getHeroPointer(), sf::Vector2i(j, i)); // if yes -> place item
						else if (random > 30 && random <= 45) przedmiot = new MixtureSpeed(this, this->getHeroPointer(), sf::Vector2i(j, i));
						else if (random > 45 && random <= 60) przedmiot = new Armor(this, this->getHeroPointer(), sf::Vector2i(j, i));
						else if (random > 60 && random <= 75) przedmiot = new Sword(this, this->getHeroPointer(), sf::Vector2i(j, i));
						else continue;
					}
					
					int cellSize = currcell->getSize();
					
					int textSizeX = przedmiot->getTexture().getSize().x;
					int textSizeY = przedmiot->getTexture().getSize().y;

					przedmiot->getImage().setPosition(sf::Vector2f(j*this->getMazeCellSize(), i*this->getMazeCellSize()));

					while (textSizeX >= cellSize || textSizeY >= cellSize)
					{
						przedmiot->getImage().scale(sf::Vector2f(0.8f, 0.8f));
						textSizeX = round(textSizeX * 0.8f);
						textSizeY = round(textSizeY * 0.8f);
					}

					this->GetMazeCell(przedmiot->getPosition())->sethasItem(true); // flaga dla komorki labiryntu
					this->GetMazeCell(przedmiot->getPosition())->setItem(przedmiot);
					this->window->draw(przedmiot->getImage());
					przedmiot = nullptr;
				}

			}

			wallCounter = 0;
		}
	}
}


sf::Vector2i Maze::searchEnd(sf::Vector2i startCell)
{
	for (int i = this->getCollumns() - 1; i >= 0; i--)
	{
		for (int j = 0; j < this->getRows(); j++)
		{
			if (this->GetMazeCell(sf::Vector2i(i, j))->isDeadEnd()) return sf::Vector2i(i, j);

		}
	}
}

void Maze::Delete()
{
	std::vector <MazeCell *>::iterator it;
	stack.clear();
	for (it = cells.begin(); it != cells.end(); it++)
	{
		(*it)->Delete();
	}
	std::list <Item *>::iterator it2;
	for (it2 = items.begin(); it2 != items.end(); it2++)
	{
		delete((*it2));
	}
	cells.clear();
	delete(this);
}

void Maze::drawEnterAndExit()
{
	if (this->generatingCompleted)
	{
		sf::RectangleShape doorOpened, doorClosed;
		int cellSize = this->getMazeCellSize();
		int wallWidth = this->GetMazeCell(sf::Vector2i(0, 0))->getWallWidth();
		doorOpened.setSize(sf::Vector2f(cellSize - wallWidth, cellSize - wallWidth));
		doorClosed.setSize(sf::Vector2f(cellSize - wallWidth, cellSize - wallWidth));
		doorOpened.setTexture(this->getGateOpenedTexture());
		doorClosed.setTexture(this->getGateClosedTexture());
		std::vector <MazeCell *>::iterator it;
		for (it = cells.begin(); it != cells.end(); it++)
		{
			if ((*it)->isStart)
			{
				doorOpened.setPosition(sf::Vector2f((*it)->GetCollumn()*cellSize + 1, (*it)->GetRow()*cellSize + 1));
				this->getWindow()->draw(doorOpened);
			}
			else if ((*it)->isEnd)
			{
				if (this->getExitOpened())
				{
					doorOpened.setPosition(sf::Vector2f((*it)->GetCollumn()*cellSize + 1 , (*it)->GetRow()*cellSize + 1));
					this->getWindow()->draw(doorOpened);
				}
				else
				{
					doorClosed.setPosition(sf::Vector2f((*it)->GetCollumn()*cellSize + 1, (*it)->GetRow()*cellSize + 1));
					this->getWindow()->draw(doorClosed);
				}
			}
		}
	}
}
