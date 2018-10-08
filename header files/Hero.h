#pragma once
#include "Character.h"

class Animation;

class Hero : public Character
{	
public:
	enum Type { MAN, WOMAN };
private: 
	Type type;
	sf::Texture *textureFight;
	Animation animationFight;
public:
	Hero() = default;
	Hero(int indexX, int indexY, int sizex, int sizey, int health, int maxHealth, int damage, Maze *maze, sf::Texture *texture, sf::Texture *textureFight, sf::Vector2u imageCount, float switchTime, float speed);
	

	sf::Texture *getTextureFight() { return textureFight; }
	sf::IntRect getFightUVRect() { return this->animationFight.uvRect; }
	Animation &getAnimationFight() { return this->animationFight; }

	void setTextureFight(sf::Texture *text) { this->textureFight = text; }
	void setAnimationFight(Animation anim) { this->animationFight = anim; }
	void setAnimationFightUVRectTop(int value) { this->animationFight.uvRect.top = value; }

	bool IsMovePossible(sf::Keyboard::Key, float deltaTime);
	void moveHero(sf::Keyboard::Key pressedKey, float deltaTime);
	void attack(float deltaTime);
	void use_item(Item *it);
	void Hero::Update(float deltaTime, sf::Keyboard::Key pressedKey);
	void Hero::check_collision(Enemy *enemy);
};

