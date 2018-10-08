#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>

#include "Maze.h"
#include "MazeCell.h"
#include "Character.h"
#include "Hero.h"
#include "Enemy.h"
#include "MixtureHP.h"
#include "Item.h"

void printInterface(sf::Text &text, Maze *mz, float timeLeft, int gameLevel)
{
	std::string string;
	string += "Level: ";
	string += std::to_string(gameLevel);
	string += "\nTime left: ";
	string += std::to_string((int)timeLeft);
	string += "s";
	string += "\nHealth: ";
	string += std::to_string(mz->getHeroPointer()->getCurrHealth());
	string += "/";
	string += std::to_string(mz->getHeroPointer()->getMaxHealth());
	string += "\nDamage: ";
	string += std::to_string(mz->getHeroPointer()->getDamage());
	text.setString(string);
	mz->getWindow()->draw(text);
}

sf::Texture *chooseEnemyTexture(sf::Texture *warrior, sf::Texture *knight, sf::Texture *assassin)
{
	int random = rand() % 3 + 1;
	switch (random)
	{
	case 1:
	{
		return warrior;
	}
	case 2:
	{
		return knight;
	}
	case 3:
	{
		return assassin;
	}
	}
}

void game(sf::RenderWindow &window, int mazeSize, bool manText)
{
	int gameLevel = 1;
	const int startingCol = 7;
	const int startingRow = 7;
	int cellSize = (int)(mazeSize / (startingCol + gameLevel));
	const int wallwidth = 2;
	const float timeLimit = 60.0f;

	sf::Font font;
	sf::Text text;
	if (!font.loadFromFile("../fonts/OpenSans-Semibold.ttf")) std::cout << "Could not load font file.\n";
	text.setFont(font);
	text.setPosition(mazeSize + 10, 10);

	sf::Texture enemyWarrior, enemyKnight, enemyAssassin, heroManWalk1, heroManFight1, heroManWalk2, heroManFight2, gateOpened, gateClosed, chosenHeroTexture, chosenHeroFightTexture;
	if (!enemyWarrior.loadFromFile("../images/enemy_warrior.png")) cout << "Couldn't load enemy warrior texture.\n";
	if (!enemyKnight.loadFromFile("../images/enemy_knight.png")) cout << "Couldn't load enemy knight texture.\n";
	if (!enemyAssassin.loadFromFile("../images/enemy_assassin.png")) cout << "Couldn't load enemy assassin texture.\n";
	if (!heroManWalk1.loadFromFile("../images/char1Walk.png")) cout << "Couldn't load hero1 walking texture.\n";
	if (!heroManFight1.loadFromFile("../images/char1Fight.png")) cout << "Couldn't load hero1 fighting texture.\n";
	if (!heroManWalk2.loadFromFile("../images/char2Walk.png")) cout << "Couldn't load hero2 walking texture.\n";
	if (!heroManFight2.loadFromFile("../images/char2Fight.png")) cout << "Couldn't load hero2 fighting texture.\n";
	if (!gateOpened.loadFromFile("../images/gateOpened1.png")) std::cout << "Couldn't load opened gate texture.\n";
	if (!gateClosed.loadFromFile("../images/gateClosed1.png")) std::cout << "Couldn't load closed gate texture.\n";
	chosenHeroTexture = heroManWalk1;
	chosenHeroFightTexture = heroManFight1;
	if (!manText)
	{
		chosenHeroTexture = heroManWalk2;
		chosenHeroFightTexture = heroManFight2;
	}

	int charWidth = round(cellSize * 0.46);
	int charHeight = round(charWidth / 0.64);
	float currentSpeed = 300.0f;
	float currentSwitch = 0.1f;
	int playerMaxHealth = 20;
	int playerHealth = 20;
	int playerDamage = 2;
	int enemyDamage = 1;

	bool gameOver = false;
	bool noHealth = false;
	bool timePassed = false;
	bool gameWon = false;
	bool timeStarted = false;
	bool moving = false;
	bool attacking = false;

	bool mazeInitialized = true;
	bool charInitialized = true;
	bool enemiesInitialized = true;
	bool enemiesAlive = true;
	bool itemsGenerated = false;
	bool instantQuit = false;

	int enemyMoveLimit = 3;
	int randomEnemyMove = rand() % 100;
	int enemyRetainDirection = rand() % 100;

	Maze *maze = new Maze(mazeSize, mazeSize, startingCol + gameLevel, startingRow + gameLevel, &gateOpened, &gateClosed, &window);
	Hero *hero = new Hero(0, 0, charWidth, charHeight, playerHealth, playerMaxHealth, playerDamage, maze, &chosenHeroTexture, &chosenHeroFightTexture, sf::Vector2u(9, 4), currentSwitch, currentSpeed);
	maze->setHeroPointer(hero);
	for (int i = 0; i < gameLevel + 1; i++)
	{
		maze->getEnemiesList().push_back(new Enemy(rand() % (startingCol - 1 + gameLevel) + 1, rand() % (startingRow - 1 + gameLevel) + 1, charWidth, charHeight, (playerMaxHealth / 2) + gameLevel, enemyDamage + (gameLevel / 4), enemyMoveLimit, maze, chooseEnemyTexture(&enemyWarrior, &enemyKnight, &enemyAssassin), sf::Vector2u(4, 4), 0.06f, float((currentSpeed / gameLevel) * 2)));
	}

	float currentTime = timeLimit;
	sf::Clock gameTime;
	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		if (gameLevel % 2 == 0) currentSpeed *= 0.9;
		cellSize = (int)(mazeSize / (startingCol + gameLevel));
		charWidth = round(cellSize * 0.46);
		charHeight = round(charWidth / 0.64);
		if (!mazeInitialized)
		{
			maze = new Maze(mazeSize, mazeSize, startingCol + gameLevel, startingRow + gameLevel, &gateOpened, &gateClosed, &window);
			mazeInitialized = true;
		}
		if (!charInitialized)
		{
			hero = new Hero(0, 0, charWidth, charHeight, playerHealth, playerMaxHealth, playerDamage, maze, &chosenHeroTexture, &chosenHeroFightTexture, sf::Vector2u(9, 4), currentSwitch, currentSpeed);
			charInitialized = true;
			maze->setHeroPointer(hero);
		}
		if (!enemiesInitialized)
		{
			for (int i = 0; i < gameLevel + 1; i++)
			{
				maze->getEnemiesList().push_back(new Enemy(rand() % (startingCol - 1 + gameLevel) + 1, rand() % (startingRow - 1 + gameLevel) + 1, charWidth, charHeight, (playerMaxHealth / 2) + gameLevel, enemyDamage + (gameLevel / 4), enemyMoveLimit, maze, chooseEnemyTexture(&enemyWarrior, &enemyKnight, &enemyAssassin), sf::Vector2u(4, 4), 0.06f, float((currentSpeed / gameLevel) * 2)));
			}
			enemiesInitialized = true;
			enemiesAlive = true;
		}

		currentSpeed = hero->getSpeed();
		currentSwitch = hero->getSwitchTime();

		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();

		if (!maze->Generated()) maze->Generate();
		maze->Draw();

		if (maze->Generated() && !itemsGenerated)
		{
			maze->PlaceItems();
			itemsGenerated = true;
		}

		if (itemsGenerated) maze->DrawItems();

		if (maze->Generated() && itemsGenerated) 
		{	// EXPLORING OF MAZE
			if (!timeStarted)
			{
				gameTime.restart().asSeconds();
				timeStarted = true;
			}
			hero->Draw();
			maze->DrawEnemies();
			moving = false;

			// CALCULATING AND PRINTING TIME
			currentTime = timeLimit - gameTime.getElapsedTime().asSeconds();
			if (currentTime < 0)
			{
				gameOver = true;
				timePassed = true;
				currentTime = 0;
			}

			// PLAYER'S MOVEMENT / ATTACK

			if (!attacking) if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				moving = true;
				attacking = false;
				hero->moveHero(sf::Keyboard::Left, deltaTime);
			}
			if (!attacking) if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				moving = true;
				attacking = false;
				hero->moveHero(sf::Keyboard::Right, deltaTime);
			}
			if (!attacking) if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				moving = true;
				attacking = false;
				hero->moveHero(sf::Keyboard::Up, deltaTime);
			}
			if (!attacking) if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				moving = true;
				attacking = false;
				hero->moveHero(sf::Keyboard::Down, deltaTime);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || attacking)
			{
				moving = false;
				attacking = true;
				hero->attack(deltaTime);
				if (hero->getAnimationFight().getAnimationEnd() == true) attacking = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				gameOver = true;
				instantQuit = true;
			}

			// PICK UP ITEMS
			MazeCell *currentCell = maze->GetMazeCell(hero->getMazeIndex());
			if (currentCell->gethasItem())
			{
				currentCell->getItem()->onPickUp();
			}

			// ENEMIES' MOVEMENT & COLLISIONS
			std::list <Enemy *>::iterator itEn;

			if (maze->getEnemiesList().size() > 0)
			{
				for (itEn = maze->getEnemiesList().begin(); itEn != maze->getEnemiesList().end(); itEn++)
				{
					if ((*itEn)->getCurrHealth() <= 0)
					{
						(*itEn)->Delete();
						maze->getEnemiesList().erase(itEn);
						if (maze->getEnemiesList().size() == 0)
						{
							enemiesAlive = false;
						}
						break;

					}
					else
					{
						(*itEn)->randomizeMove(deltaTime);
						hero->check_collision(*itEn);
					}
				}
			}

			if (hero->getCurrHealth() <= 0)
			{
				noHealth = true;
				gameOver = true;
				hero->setCurrHealth(0);
			}

			printInterface(text, maze, currentTime, gameLevel);

			sf::Vector2f charPosition = hero->getShape().getPosition();
			if ((charPosition.x > maze->getEndIndex().x * cellSize) &&
				(charPosition.x + hero->getSize().x < (maze->getEndIndex().x + 1) * cellSize))
				if (charPosition.y > maze->getEndIndex().y * cellSize &&
					charPosition.y + hero->getSize().y < (maze->getEndIndex().y + 1) * cellSize)
				{ // LEVEL WON
					gameOver = true;
					gameWon = true;
					if (enemiesAlive) maze->DeleteEnemies();
					enemiesAlive = false;
					playerMaxHealth = hero->getMaxHealth();
					playerHealth = hero->getCurrHealth();
					playerDamage = hero->getDamage();
					currentSpeed = hero->getSpeed();
					hero->Delete();
					maze->Delete();
					mazeInitialized = false;
					charInitialized = false;
					enemiesInitialized = false;
					itemsGenerated = false;
					timeStarted = false;
				}
		}

		window.display();

		if (gameOver)
		{
			if (gameWon)
			{
				std::cout << "Gratulacje! Przechodzisz dalej.\n";
				gameOver = false;
				gameWon = false;
				gameLevel++;
			}
			else
			{
				if (!instantQuit)
				{
					if (timePassed) std::cout << "Zabraklo czasu.\n";
					else if (noHealth) std::cout << "Zostales pokonany.\n";
					std::cout << "Przegrales! Koniec gry :(\n";
					sf::Text text;
					sf::Font font;
					if (!font.loadFromFile("../fonts/OpenSans-ExtraBold.ttf")) std::cout << "Could not load font file.\n";
					text.setFont(font);
					text.setString("DEATH");
					text.setFillColor(sf::Color::Red);
					text.setScale(sf::Vector2f(3.0f, 3.0f));
					text.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 - 100);
					window.draw(text);
					window.display();
					Sleep(2000);
				}
				return;
			}
		}
	}
}

bool chooseHeroMenu(sf::RenderWindow &window)
{
	sf::Font font;
	sf::Text textMan;
	sf::Text textWoman;
	if (!font.loadFromFile("../fonts/OpenSans-Semibold.ttf")) std::cout << "Could not load font file.\n";
	textMan.setFont(font);
	textWoman.setFont(font);
	textMan.setPosition(sf::Vector2f(window.getSize().x / 2 - 50, window.getSize().y / 3));
	textWoman.setPosition(sf::Vector2f(window.getSize().x / 2 - 50, window.getSize().y / 3 + 200));
	textMan.setString("MAN");
	textWoman.setString("WOMAN");
	sf::RectangleShape man, woman;
	man.setSize(sf::Vector2f(60, 100));
	woman.setSize(sf::Vector2f(60, 100));
	sf::Texture manText, womanText;
	if (!manText.loadFromFile("../images/char1Icon.png")) std::cout << "Could not load man hero icon.\n";
	if (!womanText.loadFromFile("../images/char2Icon.png")) std::cout << "Could not load woman hero icon.\n";
	man.setTexture(&manText);
	woman.setTexture(&womanText);
	man.setPosition(sf::Vector2f(window.getSize().x / 2 + 100, window.getSize().y / 3 - 60));
	woman.setPosition(sf::Vector2f(window.getSize().x / 2 + 100, window.getSize().y / 3 + 140));
	bool keyPressed = true;

	enum Hero { MAN, WOMAN };
	Hero selectedHero = Hero::MAN;

	while (true)
	{
		window.clear();
		textMan.setFillColor(sf::Color::White);
		textWoman.setFillColor(sf::Color::White);
		switch (selectedHero)
		{
		case Hero::MAN:
		{
			textMan.setFillColor(sf::Color::Red);
			break;
		}
		case Hero::WOMAN:
		{
			textWoman.setFillColor(sf::Color::Red);
			break;
		}
		}

		window.draw(textMan);
		window.draw(textWoman);
		window.draw(man);
		window.draw(woman);

		if (!keyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			{
				if (selectedHero == Hero::MAN) selectedHero = Hero::WOMAN;
				else if (selectedHero == Hero::WOMAN) selectedHero = Hero::MAN;
				keyPressed = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
			{
				if (selectedHero == Hero::MAN) return true;
				else return false;
				keyPressed = true;
			}
		}
		else if ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)))
			keyPressed = false;

		window.display();
	}
}

bool menu(sf::RenderWindow &window, bool &manText)
{
	enum Button { START, CHOOSE, QUIT };
	Button selectedButton = Button::START;
	sf::Font font;
	sf::Text textStart;
	sf::Text textChooseHero;
	sf::Text textQuit;
	if (!font.loadFromFile("../fonts/OpenSans-Semibold.ttf")) std::cout << "Could not load font file.\n";
	textStart.setFont(font);
	textStart.setPosition(sf::Vector2f(window.getSize().x / 2 - 50, window.getSize().y / 3));
	textStart.setString("START GAME");
	textChooseHero.setFont(font);
	textChooseHero.setPosition(sf::Vector2f(window.getSize().x / 2 - 50, window.getSize().y / 3 + 100));
	textChooseHero.setString("CHOOSE HERO");
	textQuit.setFont(font);
	textQuit.setPosition(sf::Vector2f(window.getSize().x / 2 - 50, window.getSize().y / 3 + 200));
	textQuit.setString("QUIT");
	bool keyPressed = false;
	while (true)
	{
		window.clear();
		textStart.setFillColor(sf::Color::White);
		textChooseHero.setFillColor(sf::Color::White);
		textQuit.setFillColor(sf::Color::White);
		switch (selectedButton)
		{
		case Button::START:
		{
			textStart.setFillColor(sf::Color::Red);
			break;
		}
		case Button::CHOOSE:
		{
			textChooseHero.setFillColor(sf::Color::Red);
			break;
		}
		case Button::QUIT:
		{
			textQuit.setFillColor(sf::Color::Red);
			break;
		}
		}

		window.draw(textStart);
		window.draw(textChooseHero);
		window.draw(textQuit);

		if (!keyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			{
				if (selectedButton == Button::START) selectedButton = Button::CHOOSE;
				else if (selectedButton == Button::CHOOSE) selectedButton = Button::QUIT;
				else if (selectedButton == Button::QUIT) selectedButton = Button::START;
				keyPressed = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			{
				if (selectedButton == Button::START) selectedButton = Button::QUIT;
				else if (selectedButton == Button::CHOOSE) selectedButton = Button::START;
				else if (selectedButton == Button::QUIT) selectedButton = Button::CHOOSE;
				keyPressed = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
			{
				keyPressed = true;
				if (selectedButton == Button::START) return true;
				else if (selectedButton == Button::CHOOSE)
				{
					if (chooseHeroMenu(window)) manText = true;
					else manText = false;
				}
				else if (selectedButton == Button::QUIT) return false;
			}
		}
		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)))
			keyPressed = false;

		window.display();
	}
}