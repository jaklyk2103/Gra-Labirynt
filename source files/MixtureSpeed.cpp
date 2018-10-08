#include "MixtureSpeed.h"
#include "Character.h"

MixtureSpeed::MixtureSpeed(Maze *maze, Character *hero, sf::Vector2i pos) : Mixture(maze, hero, pos)
{
	ldTexture();
	getImage().setTexture(getTexture());
}

void MixtureSpeed::effect(Character *hero)
{
	cout << "Uzyto mikstury szybkosci!\n";
	hero->setSpeed(hero->getSpeed() + 20.0f);
	if (hero->getSwitchTime() - 0.015 >= 0.1) hero->setSwitchTime(hero->getSwitchTime() - 0.015);
	this->destroy(hero->getMaze());
}

void MixtureSpeed::ldTexture()
{
	sf::Texture text;
	if (!text.loadFromFile("../images/speedpotion.png")) std::cout << "Could not load hp potion texture.\n";
	setTexture(text);
}