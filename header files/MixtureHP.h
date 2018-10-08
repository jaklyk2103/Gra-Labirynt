#pragma once
#include "Mixture.h"

class Character;

class MixtureHP : public Mixture
{
public:
	MixtureHP(Maze *maze, Character *hero, sf::Vector2i pos);

	void ldTexture();
	void effect(Character *hero);
};