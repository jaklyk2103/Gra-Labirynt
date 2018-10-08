#include <iostream>
#include <SFML/Graphics.hpp>

#include "GameEngine.h"

int main()
{
	int mazeSize = 1000;
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(mazeSize + 300, mazeSize), "MazeRPG", sf::Style::Close);
	window.setPosition(sf::Vector2i(300, 1));
	window.setFramerateLimit(60);
	bool manText = false;

	enum State {MENU, GAME, DEATH};
	State gameState = State::MENU;
	
	while (true)
	{
		switch (gameState)
		{
		case State::MENU:
		{
			if (!menu(window, manText)) return 1;
			else gameState = State::GAME;
			break;
		}
		case State::GAME:
		{
			game(window, mazeSize, manText);
			gameState = State::DEATH;
			break;
		}
		case State::DEATH:
		{
			gameState = State::MENU;
			break;
		}
		}
	}


	system("pause");
	return 0;
}