#pragma once

#include "Grid.h"

enum GameState {
	play,
	reset,
	over
};

class Game
{
public:
	sf::RenderWindow window;
	sf::Vector2f winSize;
public:
	Game(int winSizeX, int winSizeY, gameDiff difficultyLevel);
	bool init();
	GameState run();
	void reset();
	void over();
	~Game();
private:
	gameDiff difficultyLevel;
};