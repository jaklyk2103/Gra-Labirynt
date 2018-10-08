#pragma once
#include "Mixture.h"

class Character;

class MixtureSpeed : public Mixture
{
public:
	MixtureSpeed(Maze *maze, Character *hero, sf::Vector2i pos);

	void ldTexture();
	void effect(Character *hero);
};

