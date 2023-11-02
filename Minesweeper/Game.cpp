#include "Game.h"

Game::Game(int winSizeX, int winSizeY, gameDiff difficultyLevel)
{
	winSize = sf::Vector2f(winSizeX, winSizeY);
	this->difficultyLevel = difficultyLevel;
	window.create(sf::VideoMode(winSizeX, winSizeY), "Minesweeper!");
}

bool Game::init()
{
}

GameState Game::run()
{
	return GameState();
}

void Game::reset()
{
}

void Game::over()
{
}

Game::~Game()
{
}
