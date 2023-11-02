#include "Grid.h"

// [COLORS] constants

// sf::Color bg_color = sf::Color();


// [CELLS] class

Cells::Cells(int posX, int posY)
{
	pos = sf::Vector2f(posX, posY);
	initialised = false;
	cellTile.setFillColor(sf::Color());
}

sf::Vector2f Cells::getPos()
{
	return this->pos;
}

void Cells::initCell(vals val, flags flag)
{
	if (!initialised)
	{
		this->val = val;
		this->flag = flag;
		initialised = true;
	}
}

bool Cells::isInitialised()
{
	return initialised;
}

// [CELLS] end

// [GRID] class

Grid::Grid(int gridSizeX, int gridSizeY)
{
	isInitialised = false;
	gridSize = sf::Vector2f(gridSizeX, gridSizeY);

	for (int i = 0; i < gridSizeX; i++)
	{
		vector1c tmp;
		for (int j = 0; j < gridSizeY; j++)
		{
			tmp.push_back(new Cells(i, j));
		}
		grid.push_back(tmp);
	}
}

Grid::~Grid()
{
	for (int i = 0; i < gridSize.x; i++)
	{
		for (int j = 0; j < gridSize.y; j++)
		{
			delete grid[i][j];
		}
	}
}

void Grid::randomGen(Cells* startingCell, gameDiff difficulty)
{
	if (!isInitialised)
	{
		// [MISC.] for random position generation
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 rng(seed);
		std::uniform_int_distribution<int> genX(0, gridSize.x - 1); // uniform, unbiased
		std::uniform_int_distribution<int> genY(0, gridSize.y - 1); // uniform, unbiased
		// [MISC.] end

		for (int i = 0; i < difficulty; i++)
		{
			sf::Vector2f minePos;
			do {
				minePos = sf::Vector2f(genX(rng), genY(rng));	// be in the neighbouring vicinity of the start theoretically
			} while (minePos == startingCell->getPos());		// should check for mine to NOT be there in the vicinity

			Cells* pos = *((this->getGrid()->begin() + minePos.x)->begin() + minePos.y);
			pos->initCell(mine, closed);
		}
	}
}

void Grid::getValidNeighbours()
{
	for (int i = 0; i < gridSize.x; i++)
	{
		for (int j = 0; j < gridSize.y; j++)
		{
			int up = i - 1;
			int down = i + 1;
			int right = j + 1;
			int left = j - 1;

			// adgacent neighbours
			if (up >= 0)
				grid[i][j]->neighbours.push_back(grid[up][j]);
			if (down < gridSize.x)
				grid[i][j]->neighbours.push_back(grid[down][j]);
			if (right < gridSize.y)
				grid[i][j]->neighbours.push_back(grid[i][right]);
			if (left >= 0)
				grid[i][j]->neighbours.push_back(grid[i][left]);

			// diagonal neighbours
			if (up >= 0 && right < gridSize.y)
				grid[i][j]->neighbours.push_back(grid[up][right]);
			if (up >= 0 && left >= 0)
				grid[i][j]->neighbours.push_back(grid[up][left]);
			if (down < gridSize.x && right < gridSize.y)
				grid[i][j]->neighbours.push_back(grid[down][right]);
			if (down < gridSize.x && left >= 0)
				grid[i][j]->neighbours.push_back(grid[down][left]);
		}
	}
}

//	[TRIAL CODE]

vals& operator++(vals& v) {
	v = static_cast<vals>(v + 1);
	return v;
}

//	[TRIAL CODE]

void Grid::initAllRemainingCells()
{
	for (int i = 0; i < gridSize.x; i++)
	{
		for (int j = 0; j < gridSize.y; j++)
		{
			Cells* cell = grid[i][j];
			if (!cell->isInitialised())
			{
				vals val = none;
				vector1c::iterator it;
				for (it = cell->neighbours.begin(); it != cell->neighbours.end(); ++it)
					if ((*it)->val == mine)
						++val;

				cell->initCell(val, closed);
			}
		}
	}
}

void Grid::openCellsByFlag(Cells* cell)
{
	std::queue<Cells*> q;
	q.push(cell);

	while (!q.empty())
	{
		q.front()->flag = opened;
		vector1c neighbours = q.front()->neighbours;

		if (q.front()->val == none)
		{
			vector1c::iterator it;
			for (it = neighbours.begin(); it != neighbours.end(); ++it)
				q.push(*it);
		}

		if (q.front()->val == mine)
		{
			// [TODO] what happens if the cell is mine -> create event and trigger it such that the game ends.
			// To implement this, first implement the visual part and check the current game status works!
		}

		q.pop();
	}
}

void Grid::initGrid(Cells* startingCell, gameDiff difficulty)
{
	if (!isInitialised)
	{
		randomGen(startingCell, difficulty);
		getValidNeighbours();
		initAllRemainingCells();
		openCellsByFlag(startingCell);
		isInitialised = true;
	}
}

vector2c* Grid::getGrid()
{
	return &(this->grid);
}

// [GRID] end