#include "MixtureHP.h"
#include "Character.h"

MixtureHP::MixtureHP(Maze *maze, Character *hero, sf::Vector2i pos) : Mixture(maze, hero, pos)
{
	ldTexture();
	getImage().setTexture(getTexture());
}

void MixtureHP::effect(Character *hero)
{
	cout << "Uzyto mikstury zycia!\n";
	if (hero->getCurrHealth() < hero->getMaxHealth()) hero->setCurrHealth(hero->getCurrHealth() + round(hero->getMaxHealth() * 0.1));
	if (hero->getCurrHealth() > hero->getMaxHealth()) hero->setCurrHealth(hero->getMaxHealth());
	this->destroy(hero->getMaze());
}

void MixtureHP::ldTexture()
{
	sf::Texture text;	
	if (!text.loadFromFile("../images/hppotion.png")) std::cout << "Could not load hp potion texture.\n";
	setTexture(text);
}