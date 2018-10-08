#include "Animation.h"

Animation::Animation(sf::Texture *texture, sf::Vector2u imageCnt, float switchTm)
{
	this->animationCounter = 0;
	this->imageCount = imageCnt;
	this->switchTime = switchTm;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime)
{
	if (animationEnd) animationEnd = false;
	this->currentImage.y = row;
	this->totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		this->animationCounter++;
		this->totalTime -= switchTime;
		this->currentImage.x++;

		if (this->currentImage.x >= this->imageCount.x)
		{
			this->currentImage.x = 0;
			this->animationEnd = true;
			this->animationCounter = 0;
		}
	}

	this->uvRect.left = this->currentImage.x * this->uvRect.width;
	this->uvRect.top = this->currentImage.y * this->uvRect.height;
}
