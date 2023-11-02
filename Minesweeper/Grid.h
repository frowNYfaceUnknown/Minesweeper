#pragma once
#include <vector>
#include <queue>
#include <random>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#define vector1c std::vector<Cells*>
#define vector2c std::vector<vector1c>

enum vals { none, one, two, three, four, five, six, seven, eight, mine };
enum flags { closed, opened, flagged };

enum gameDiff
{
	easy = 7,
	med = 10,
	hard = 20
};

class Cells
{
public:
	Cells(int posX, int posY);
	sf::Vector2f getPos();
	void initCell(vals val, flags flag);
	bool isInitialised();

	// [GRAPHICS] variables for visuals
	sf::CircleShape cellTile;
	sf::Text minesNum;
	// [GRAPHICS] end
private:
	bool initialised;
	sf::Vector2f pos;
	vals val;
	flags flag;
	vector1c neighbours;
public:
	friend class Grid;
};

class Grid
{
public:
	Grid(int gridSizeX, int gridSizeY);
	~Grid();
	void initGrid(Cells* startingCell, gameDiff difficulty);
	vector2c* getGrid();
private:
	void randomGen(Cells* startingCell, gameDiff difficulty);
	void getValidNeighbours();
	void initAllRemainingCells();
	void openCellsByFlag(Cells* cell);
private:
	bool isInitialised;
	sf::Vector2f gridSize;
	vector2c grid;
};