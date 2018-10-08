#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Character;
class Hero;
class Maze;

class Item
{
private:
	string name;
	sf::Vector2i position;
	sf::Texture text;
	sf::Sprite image;
	Character *hero;
	Maze *maze;

public:
	static int itemCounter;
	int id;
	Item(Maze *maze, Character *hero, sf::Vector2i pos);
	
	virtual void loadTexture() = 0;
	virtual void onPickUp() = 0;
	void destroy(Maze *maze);

	// GETTERS/SETTERS
	sf::Texture &getTexture() { return text; }
	sf::Vector2i getPosition() { return position; }
	sf::Sprite &getImage() { return image; }
	void setTexture(sf::Texture text_) { text = text_; }
	void setPosition(sf::Vector2i pos) { position = pos; }
	void setImage(sf::Sprite &spr) { image = spr; }

	Character *getHeroPointer() { return this->hero; }
	Maze *getMazePointer() { return this->maze; }
};