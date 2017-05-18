#include <iostream>
#include <cstdlib>
using namespace std;

// 클래스 선언

class LifeGame
{
public:
	LifeGame();
	~LifeGame();

	void initialize(int w, int h);

	int getWidth() const;
	int getHeight() const;

	void setState(int i, int j, bool s);
	bool getState(int i, int j) const;

	void clear();
	void update();

	friend ostream &operator <<(ostream &os, const LifeGame &game);

private:
	typedef bool * boolptr;
	int width;
	int height;
	boolptr *current_cells;
	boolptr *next_cells;
};

// 멤버 함수 정의

LifeGame::LifeGame()
{
	width = 0;
	height = 0;
	current_cells = nullptr;
	next_cells = nullptr;
}

LifeGame::~LifeGame()
{
	delete[] current_cells;
	delete[] next_cells;
}

void LifeGame::initialize(int w, int h)
{

	if (current_cells != nullptr)
	{
		delete[] current_cells;
		current_cells = nullptr;
	}
	if (next_cells != nullptr)
	{
		delete[] next_cells;
		next_cells = nullptr;
	}

	current_cells = new bool *[h];
	next_cells = new bool *[h];

	for (int j = 0; j < h; j++)
	{
		current_cells[j] = new bool[w];
		next_cells[j] = new bool[w];
	}

	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			current_cells[j][i] = false;
			next_cells[j][i] = false;
		}
	}

	width = w;
	height = h;
}

int LifeGame::getWidth() const
{
	return width;
}

int LifeGame::getHeight() const
{
	return height;
}

void LifeGame::setState(int i, int j, bool s)
{
	current_cells[j][i] = s;
}

bool LifeGame::getState(int i, int j) const
{
	return current_cells[j][i];
}

void LifeGame::clear()
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			current_cells[j][i] = false;
			next_cells[j][i] = false;
		}
	}
}

void LifeGame::update()
{
	int count = 0;
	int countD = 0;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			count = 0;
			countD = 0;

			if (getState(i, j) == true)
			{
				//top_left
				if (j - 1 >= 0 && j - 1 < height && i - 1 >= 0 && i - 1 < width)
				{
					if (getState(i-1, j-1) == true)
					{
						count++;
					}
				}
				else
				{
					//j-1은 범위에 있는 경우
					if (j - 1 >= 0 && j - 1 < height)
					{
						//top까지는 갈 수 있는데 left가 범위를 벗어나는 경우
						if (getState(width -1, j -1) == true)
						{
							count++;
						}
					}
					//j-1은 범위에 없는 경우
					else
					{
						//i-1은 범위에 있는 경우
						if (i - 1 >= 0 && i - 1 < width)
						{
							if (getState(i -1, height -1) == true)
							{
								count++;
							}
						}
						//i-1은 범위에 없는 경우
						else
						{
							if (getState(width -1, height -1) == true)
							{
								count++;
							}
						}
					}
				}
				//top
				if (j - 1 >= 0 && j - 1 < height && i >= 0 && i < width)
				{
					if (getState(i, j-1) == true)
					{
						count++;
					}
				}
				else
				{
					if (getState(i, height -1) == true)
					{
						count++;
					}
				}
				//top_right
				if (j - 1 >= 0 && j - 1 < height && i + 1 >= 0 && i + 1 < width)
				{
					if (getState(i+1, j-1) == true)
					{
						count++;
					}
				}
				else
				{
					//j -1 있는 경우 (= top은 가능하지만, right가 불가능한 상태)
					if (j - 1 >= 0 && j - 1 < height)
					{
						if (getState(0, j-1) == true)
						{
							count++;
						}
					}
					//j -1 없는 경우
					else
					{
						//i+1 은 가능한 경우
						if (i + 1 >= 0 && i + 1 < width)
						{
							if (getState(i +1, height -1) == true)
							{
								count++;
							}
						}
						//i+1 도 불가능한 경우
						else
						{
							if (getState(0, height -1) == true)
							{
								count++;
							}
						}
					}
				}
				//left
				if (j >= 0 && j < height && i - 1 >= 0 && i - 1 < width)
				{
					if (getState(i-1, j) == true)
					{
						count++;
					}
				}
				else
				{
					if (getState(width-1, j) == true)
					{
						count++;
					}
				}
				//right
				if (j >= 0 && j < height && i + 1 >= 0 && i + 1 < width)
				{
					if (getState(i+1, j) == true)
					{
						count++;
					}
				}
				else
				{
					if (getState(0, j) == true)
					{
						count++;
					}
				}
				//down_left
				if (j + 1 >= 0 && j + 1 < height && i - 1 >= 0 && i - 1 < width)
				{
					if (getState(i-1, j+1) == true)
					{
						count++;
					}
				}
				else
				{
					// j+1 은 되는 경우
					if (j + 1 >= 0 && j + 1 < height)
					{
						if (getState(width -1, j+1) == true)
						{
							count++;
						}
					}
					// j+1 은 안되는 경우
					else
					{
						//i-1 은 되는 경우
						if (i - 1 >= 0 && i - 1 < width)
						{
							if (getState(i-1, 0) == true)
							{
								count++;
							}
						}
						//i-1 도 안되는 경우
						else
						{
							if (getState(width -1, 0) == true)
							{
								count++;
							}
						}
					}
				}
				//down
				if (j + 1 >= 0 && j + 1 < height && i >= 0 && i < width)
				{
					if (getState(i, j+1) == true)
					{
						count++;
					}
				}
				else
				{
					if (getState(i, 0) == true)
					{
						count++;
					}
				}
				//down_right
				if (j + 1 >= 0 && j + 1 < height && i + 1 >= 0 && i + 1 < width)
				{
					if (getState(i+1, j+1) == true)
					{
						count++;
					}
				}
				else
				{
					//j+1 은 되는 경우
					if (j + 1 >= 0 && j + 1 < height)
					{
						if (getState(0, j+1) == true)
						{
							count++;
						}
					}
					//j+1 은 안되는 경우
					else
					{
						//i+1은 되는 경우
						if (i + 1 >= 0 && i + 1 < width)
						{
							if (getState(i+1, 0) == true)
							{
								count++;
							}
						}
						//i+1도 안되는 경우
						else
						{
							if (getState(0,0) == true)
							{
								count++;
							}
						}
					}
				}
				//check
				if (count <= 1)
				{
					next_cells[j][i] = false;
				}
				if (count >= 4)
				{
					next_cells[j][i] = false;
				}
				if (count >= 2 && count <= 3)
				{
					next_cells[j][i] = true;
				}
			}
			//=================================================================================================
			//current_cells[i][j] is dead
			if (getState(i, j) == false)
			{
				//top_left
				if (j - 1 >= 0 && j - 1 < height && i - 1 >= 0 && i - 1 < width)
				{
					if (getState(i - 1, j - 1) == true)
					{
						countD++;
					}
				}
				else
				{
					//j-1은 범위에 있는 경우
					if (j - 1 >= 0 && j - 1 < height)
					{
						//top까지는 갈 수 있는데 left가 범위를 벗어나는 경우
						if (getState(width - 1, j - 1) == true)
						{
							countD++;
						}
					}
					//j-1은 범위에 없는 경우
					else
					{
						//i-1은 범위에 있는 경우
						if (i - 1 >= 0 && i - 1 < width)
						{
							if (getState(i - 1, height - 1) == true)
							{
								countD++;
							}
						}
						//i-1은 범위에 없는 경우
						else
						{
							if (getState(width - 1, height - 1) == true)
							{
								countD++;
							}
						}
					}
				}
				//top
				if (j - 1 >= 0 && j - 1 < height && i >= 0 && i < width)
				{
					if (getState(i, j - 1) == true)
					{
						countD++;
					}
				}
				else
				{
					if (getState(i, height - 1) == true)
					{
						countD++;
					}
				}
				//top_right
				if (j - 1 >= 0 && j - 1 < height && i + 1 >= 0 && i + 1 < width)
				{
					if (getState(i + 1, j - 1) == true)
					{
						countD++;
					}
				}
				else
				{
					//j -1 있는 경우 (= top은 가능하지만, right가 불가능한 상태)
					if (j - 1 >= 0 && j - 1 < height)
					{
						if (getState(0, j - 1) == true)
						{
							countD++;
						}
					}
					//j -1 없는 경우
					else
					{
						//i+1 은 가능한 경우
						if (i + 1 >= 0 && i + 1 < width)
						{
							if (getState(i + 1, height - 1) == true)
							{
								countD++;
							}
						}
						//i+1 도 불가능한 경우
						else
						{
							if (getState(0, height - 1) == true)
							{
								countD++;
							}
						}
					}
				}
				//left
				if (j >= 0 && j < height && i - 1 >= 0 && i - 1 < width)
				{
					if (getState(i - 1, j) == true)
					{
						countD++;
					}
				}
				else
				{
					if (getState(width - 1, j) == true)
					{
						countD++;
					}
				}
				//right
				if (j >= 0 && j < height && i + 1 >= 0 && i + 1 < width)
				{
					if (getState(i + 1, j) == true)
					{
						countD++;
					}
				}
				else
				{
					if (getState(0, j) == true)
					{
						countD++;
					}
				}
				//down_left
				if (j + 1 >= 0 && j + 1 < height && i - 1 >= 0 && i - 1 < width)
				{
					if (getState(i - 1, j + 1) == true)
					{
						countD++;
					}
				}
				else
				{
					// j+1 은 되는 경우
					if (j + 1 >= 0 && j + 1 < height)
					{
						if (getState(width - 1, j + 1) == true)
						{
							countD++;
						}
					}
					// j+1 은 안되는 경우
					else
					{
						//i-1 은 되는 경우
						if (i - 1 >= 0 && i - 1 < width)
						{
							if (getState(i - 1, 0) == true)
							{
								countD++;
							}
						}
						//i-1 도 안되는 경우
						else
						{
							if (getState(width - 1, 0) == true)
							{
								countD++;
							}
						}
					}
				}
				//down
				if (j + 1 >= 0 && j + 1 < height && i >= 0 && i < width)
				{
					if (getState(i, j + 1) == true)
					{
						countD++;
					}
				}
				else
				{
					if (getState(i, 0) == true)
					{
						countD++;
					}
				}
				//down_right
				if (j + 1 >= 0 && j + 1 < height && i + 1 >= 0 && i + 1 < width)
				{
					if (getState(i + 1, j + 1) == true)
					{
						countD++;
					}
				}
				else
				{
					//j+1 은 되는 경우
					if (j + 1 >= 0 && j + 1 < height)
					{
						if (getState(0, j + 1) == true)
						{
							countD++;
						}
					}
					//j+1 은 안되는 경우
					else
					{
						//i+1은 되는 경우
						if (i + 1 >= 0 && i + 1 < width)
						{
							if (getState(i + 1, 0) == true)
							{
								countD++;
							}
						}
						//i+1도 안되는 경우
						else
						{
							if (getState(0, 0) == true)
							{
								countD++;
							}
						}
					}
				}
				//check
				if (countD == 3)
				{
					next_cells[j][i] = true;
				}
			}
		}
	}

	//다음 상태로 변경
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			current_cells[j][i] = next_cells[j][i];
		}
	}
	//next_cells 초기화
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			next_cells[j][i] = false;
		}
	}
}
// friend 함수 정의

ostream &operator <<(ostream &os, const LifeGame &game)
{
	cout << "The current game state is : " << endl << endl;
	for (int j = 0; j < game.height; j++)
	{
		for (int i = 0; i < game.width; i++)
		{
			if (game.getState(i, j) == true)
			{
				cout << "O" << " ";
			}
			if (game.getState(i, j) == false)
			{
				cout << "." << " ";
			}
		}
		cout << endl;
	}
	return os;
}




// 아래 내용은 수정하지 말 것

void setBoat(LifeGame& life);
void setToad(LifeGame& life);
void setGlider(LifeGame& life);
void setCross(LifeGame& life);
void setRandom(LifeGame& life);

void main()
{
	int width = 0, height = 0;
	char answer = ' ';

	cout << "Input grid width: ";
	cin >> width;

	cout << "Input grid height: ";
	cin >> height;

	LifeGame life;
	life.initialize(width, height);
	do
	{
		int n, i;

		cout << endl << "[Menu]" << endl;
		cout << "(0) No change\n";
		cout << "(1) Boat\n";
		cout << "(2) Toad\n";
		cout << "(3) Glider\n";
		cout << "(4) Cross\n";
		cout << "(5) Random\n";
		cout << "Select a command (0-5) : ";
		cin >> n;

		switch (n) {
		case 0:							break;
		case 1:	setBoat(life);		break;
		case 2:	setToad(life);		break;
		case 3:	setGlider(life);		break;
		case 4: setCross(life);		break;
		case 5:	setRandom(life);		break;
		default:						break;
		}

		for (i = 0; i < 10; i++)
		{
			cout << "[" << i << "] generation: " << endl;
			cout << life;
			cout << endl;
			life.update();
		}

		cout << "Continue (Y/N)? ";
		cin >> answer;
	} while (answer == 'Y' || answer == 'y');
}

void setBoat(LifeGame& life)
{
	int w = life.getWidth();
	int h = life.getHeight();

	if (w < 3 || h < 3)
	{
		return;
	}

	int ci = w / 2;
	int cj = h / 2;

	life.clear();
	life.setState(ci - 1, cj, true);
	life.setState(ci + 1, cj, true);
	life.setState(ci, cj - 1, true);
	life.setState(ci, cj + 1, true);
	life.setState(ci - 1, cj - 1, true);
}

void setToad(LifeGame& life)
{
	int w = life.getWidth();
	int h = life.getHeight();

	if (w < 5 || h < 3)
	{
		return;
	}

	int ci = w / 2;
	int cj = h / 2;

	life.clear();
	life.setState(ci, cj, true);
	life.setState(ci - 1, cj, true);
	life.setState(ci - 2, cj, true);
	life.setState(ci, cj - 1, true);
	life.setState(ci - 1, cj - 1, true);
	life.setState(ci + 1, cj - 1, true);
}

void setGlider(LifeGame& life)
{
	int w = life.getWidth();
	int h = life.getHeight();

	if (w < 3 || h < 3)
	{
		return;
	}

	int ci = w / 2;
	int cj = h / 2;

	life.clear();
	life.setState(ci - 1, cj, true);
	life.setState(ci, cj - 1, true);
	life.setState(ci, cj + 1, true);
	life.setState(ci - 1, cj - 1, true);
	life.setState(ci + 1, cj - 1, true);
}

void setCross(LifeGame& life)
{
	int w = life.getWidth();
	int h = life.getHeight();

	if (w < 3 || h < 3)
	{
		return;
	}

	int ci = w / 2;
	int cj = h / 2;

	life.clear();
	life.setState(ci, cj, true);
	life.setState(ci - 1, cj, true);
	life.setState(ci + 1, cj, true);
	life.setState(ci, cj - 1, true);
	life.setState(ci, cj + 1, true);
}

void setRandom(LifeGame& life)
{
	int w = life.getWidth();
	int h = life.getHeight();
	int num_cells = w * h;
	int num_live_cells = (int)((float)num_cells * 0.1f);

	life.clear();
	for (int c = 0; c < num_live_cells; c++)
	{
		int i = rand() % w;
		int j = rand() % h;

		life.setState(i, j, true);
	}
}
