#include <iostream>
#include <cstdlib>
using namespace std;

// Ŭ���� ����

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

// ��� �Լ� ����

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

	current_cells = new bool *[w];
	next_cells = new bool *[w];

	for (int i = 0; i < w; i++)
	{
		current_cells[i] = new bool[h];
		next_cells[i] = new bool[h];
	}

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			current_cells[i][j] = false;
			next_cells[i][j] = false;
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
	current_cells[i][j] = s;
}

bool LifeGame::getState(int i, int j) const
{
	return current_cells[i][j];
}

void LifeGame::clear()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			current_cells[i][j] = false;
		}
	}
}

void LifeGame::update()
{
	int count = 0;
	int countD = 0;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			count = 0;
			countD = 0;

			if (getState(i, j) == true)
			{
				//top_left
				if (i - 1 >= 0 && i - 1 < width && j - 1 >= 0 && j - 1 < height)
				{
					if (getState(i - 1, j - 1) == true)
					{
						count++;
					}
				}
				else 
				{
					//i-1�� ������ �ִ� ���
					if (i -1 >= 0 && i - 1 < width) 
					{
						//top������ �� �� �ִµ� left�� ������ ����� ���
						if (getState(i -1, height -1) == true) 
						{
							count++;
						}
					}
					//i-1�� ������ ���� ���
					else 
					{
						//j-1�� ������ �ִ� ���
						if (j -1 >= 0 && j -1 < height) 
						{
							if (getState(width - 1, j - 1) == true)
							{
								count++;
							}
						}
						//j-1�� ������ ���� ���
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
				if (i - 1 >= 0 && i - 1 < width && j >= 0 && j < height)
				{
					if (getState(i - 1, j) == true)
					{
						count++;
					}
				}
				else 
				{
					if (getState(width -1, j) == true) 
					{
						count++;
					}
				}
				//top_right
				if (i - 1 >= 0 && i - 1 < width && j + 1 >= 0 && j + 1 < height)
				{
					if (getState(i - 1, j + 1) == true)
					{
						count++;
					}
				}
				else 
				{
					//i -1 �ִ� ��� (= top�� ����������, right�� �Ұ����� ����)
					if (i - 1 >= 0 && i - 1 < width) 
					{
						if (getState(i -1, 0) == true) 
						{
							count++;
						}
					}
					//i -1 ���� ���
					else 
					{
						//j+1 �� ������ ���
						if (j + 1 >= 0 && j + 1 < height) 
						{
							if (getState(width -1, j+1) == true) 
							{
								count++;
							}
						}
						//j+1 �� �Ұ����� ���
						else 
						{
							if (getState(width -1, 0) == true) 
							{
								count++;
							}
						}
					}
				}
				//left
				if (i >= 0 && i < width && j - 1 >= 0 && j - 1 < height)
				{
					if (getState(i, j - 1) == true)
					{
						count++;
					}
				}
				else 
				{
					if (getState(i, height - 1) == true) 
					{
						count++;
					}
				}
				//right
				if (i >= 0 && i < width && j + 1 >= 0 && j + 1 < height)
				{
					if (getState(i, j + 1) == true)
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
				//down_left
				if (i + 1 >= 0 && i + 1 < width && j - 1 >= 0 && j - 1 < height)
				{
					if (getState(i + 1, j - 1) == true)
					{
						count++;
					}
				}
				else 
				{
					// i+1 �� �Ǵ� ���
					if (i + 1 >= 0 && i + 1 < width) 
					{
						if (getState(i +1, height -1) == true) 
						{
							count++;
						}
					}
					// i+1 �� �ȵǴ� ���
					else 
					{
						//j-1 �� �Ǵ� ���
						if (j - 1 >= 0 && j - 1 < height) 
						{
							if (getState(0, j-1) == true) 
							{
								count++;
							}
						}
						//j-1 �� �ȵǴ� ���
						else 
						{
							if (getState(0, height -1) == true) 
							{
								count++;
							}
						}
					}
				}
				//down
				if (i + 1 >= 0 && i + 1 < width && j >= 0 && j < height)
				{
					if (getState(i + 1, j) == true)
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
				//down_right
				if (i + 1 >= 0 && i + 1 < width && j + 1 >= 0 && j + 1 < height)
				{
					if (getState(i + 1, j + 1) == true)
					{
						count++;
					}
				}
				else 
				{
					//i+1 �� �Ǵ� ���
					if (i + 1 >= 0 && i + 1 < width) 
					{
						if (getState(i+1, 0) == true) 
						{
							count++;
						}
					}
					//i+1 �� �ȵǴ� ���
					else 
					{
						//j+1�� �Ǵ� ���
						if (j + 1 >= 0 && j + 1 < height) 
						{
							if (getState(0, j+1) == true) 
							{
								count++;
							}
						}
						//j+1�� �ȵǴ� ���
						else 
						{
							if (getState(0, 0) == true) 
							{
								count++;
							}
						}
					}
				}
				//check
				if (count <= 1)
				{
					next_cells[i][j] = false;
				}
				if (count >= 4)
				{
					next_cells[i][j] = false;
				}
				if (count >= 2 && count <= 3)
				{
					next_cells[i][j] = true;
				}
			}
//=================================================================================================
			//current_cells[i][j] is dead
			if (getState(i, j) == false) 
			{
				//top_left
				if (i - 1 >= 0 && i - 1 < width && j - 1 >= 0 && j - 1 < height)
				{
					if (getState(i - 1, j - 1) == true)
					{
						countD++;
					}
				}
				else
				{
					//i-1�� ������ �ִ� ���
					if (i - 1 >= 0 && i - 1 < width)
					{
						//top������ �� �� �ִµ� left�� ������ ����� ���
						if (getState(i - 1, height - 1) == true)
						{
							countD++;
						}
					}
					//i-1�� ������ ���� ���
					else
					{
						//j-1�� ������ �ִ� ���
						if (j - 1 >= 0 && j - 1 < height)
						{
							if (getState(width - 1, j - 1) == true)
							{
								countD++;
							}
						}
						//j-1�� ������ ���� ���
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
				if (i - 1 >= 0 && i - 1 < width && j >= 0 && j < height)
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
				//top_right
				if (i - 1 >= 0 && i - 1 < width && j + 1 >= 0 && j + 1 < height)
				{
					if (getState(i - 1, j + 1) == true)
					{
						countD++;
					}
				}
				else
				{
					//i -1 �ִ� ��� (= top�� ����������, right�� �Ұ����� ����)
					if (i - 1 >= 0 && i - 1 < width)
					{
						if (getState(i - 1, 0) == true)
						{
							countD++;
						}
					}
					//i -1 ���� ���
					else
					{
						//j+1 �� ������ ���
						if (j + 1 >= 0 && j + 1 < height)
						{
							if (getState(width - 1, j + 1) == true)
							{
								countD++;
							}
						}
						//j+1 �� �Ұ����� ���
						else
						{
							if (getState(width - 1, 0) == true)
							{
								countD++;
							}
						}
					}
				}
				//left
				if (i >= 0 && i < width && j - 1 >= 0 && j - 1 < height)
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
				//right
				if (i >= 0 && i < width && j + 1 >= 0 && j + 1 < height)
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
				//down_left
				if (i + 1 >= 0 && i + 1 < width && j - 1 >= 0 && j - 1 < height)
				{
					if (getState(i + 1, j - 1) == true)
					{
						countD++;
					}
				}
				else
				{
					// i+1 �� �Ǵ� ���
					if (i + 1 >= 0 && i + 1 < width)
					{
						if (getState(i + 1, height - 1) == true)
						{
							countD++;
						}
					}
					// i+1 �� �ȵǴ� ���
					else
					{
						//j-1 �� �Ǵ� ���
						if (j - 1 >= 0 && j - 1 < height)
						{
							if (getState(0, j - 1) == true)
							{
								countD++;
							}
						}
						//j-1 �� �ȵǴ� ���
						else
						{
							if (getState(0, height - 1) == true)
							{
								countD++;
							}
						}
					}
				}
				//down
				if (i + 1 >= 0 && i + 1 < width && j >= 0 && j < height)
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
				//down_right
				if (i + 1 >= 0 && i + 1 < width && j + 1 >= 0 && j + 1 < height)
				{
					if (getState(i + 1, j + 1) == true)
					{
						countD++;
					}
				}
				else
				{
					//i+1 �� �Ǵ� ���
					if (i + 1 >= 0 && i + 1 < width)
					{
						if (getState(i + 1, 0) == true)
						{
							countD++;
						}
					}
					//i+1 �� �ȵǴ� ���
					else
					{
						//j+1�� �Ǵ� ���
						if (j + 1 >= 0 && j + 1 < height)
						{
							if (getState(0, j + 1) == true)
							{
								countD++;
							}
						}
						//j+1�� �ȵǴ� ���
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
					next_cells[i][j] = true;
				}
			}
			//���� ���·� ����
			for (int i = 0; i < width; i++) 
			{
				for (int j = 0; j < height; j++) 
				{
					current_cells[i][j] = next_cells[i][j];
				}
			}
			//next_cells �ʱ�ȭ
			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					next_cells[i][j] = false;
				}
			}
		}
	}
}
// friend �Լ� ����

ostream &operator <<(ostream &os, const LifeGame &game)
{
	cout << "The current game state is : " << endl << endl;
	for (int i = 0; i < game.width; i++)
	{
		for (int j = 0; j < game.height; j++)
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




// �Ʒ� ������ �������� �� ��

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
