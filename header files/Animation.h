#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	Animation() = default;
	Animation(sf::Texture *texture, sf::Vector2u imageCnt, float switchTm);
	~Animation();

	bool getAnimationEnd() { return this->animationEnd;}
	void setAnimationEnd(bool value) { this->animationEnd = value; }

	void Update(int row, float deltaTime);

	sf::IntRect uvRect;
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	bool animationEnd = false;
	int animationCounter;
	float totalTime;
	float switchTime;
};