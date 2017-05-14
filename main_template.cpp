#include <iostream>
#include <cstdlib>
using namespace std;

// 클래스 선언

class LifeGame
{
public:

private:
};



// 멤버 함수 정의






// friend 함수 정의






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

		switch( n ) {
			case 0:							break;
			case 1:	setBoat( life );		break;
			case 2:	setToad( life );		break;
			case 3:	setGlider( life );		break;
			case 4: setCross( life );		break;
			case 5:	setRandom( life );		break;
			default:						break;
		}

		for( i=0; i < 10; i++ )
		{
			cout << "[" << i << "] generation: " << endl;
			cout << life;
			cout << endl;
			life.update();
		}

		cout << "Continue (Y/N)? ";
		cin >> answer;
	}
	while( answer == 'Y' || answer == 'y' );
}

void setBoat( LifeGame& life )
{
	int w = life.getWidth();
	int h = life.getHeight();

	if( w < 3 || h < 3 )
	{
		return;
	}

	int ci = w / 2;
	int cj = h / 2;

	life.clear();
	life.setState( ci-1, cj, true );
	life.setState( ci+1, cj, true );
	life.setState( ci, cj-1, true );
	life.setState( ci, cj+1, true );
	life.setState( ci-1, cj-1, true );
}

void setToad( LifeGame& life )
{
	int w = life.getWidth();
	int h = life.getHeight();

	if( w < 5 || h < 3 )
	{
		return;
	}

	int ci = w / 2;
	int cj = h / 2;

	life.clear();
	life.setState( ci, cj, true );
	life.setState( ci-1, cj, true );
	life.setState( ci-2, cj, true );
	life.setState( ci, cj-1, true );
	life.setState( ci-1, cj-1, true );
	life.setState( ci+1, cj-1, true );
}

void setGlider( LifeGame& life )
{
	int w = life.getWidth();
	int h = life.getHeight();

	if( w < 3 || h < 3 )
	{
		return;
	}

	int ci = w / 2;
	int cj = h / 2;

	life.clear();
	life.setState( ci-1, cj, true );
	life.setState( ci, cj-1, true );
	life.setState( ci, cj+1, true );
	life.setState( ci-1, cj-1, true );
	life.setState( ci+1, cj-1, true );
}

void setCross( LifeGame& life )
{
	int w = life.getWidth();
	int h = life.getHeight();

	if( w < 3 || h < 3 )
	{
		return;
	}

	int ci = w / 2;
	int cj = h / 2;

	life.clear();
	life.setState( ci, cj, true );
	life.setState( ci-1, cj, true );
	life.setState( ci+1, cj, true );
	life.setState( ci, cj-1, true );
	life.setState( ci, cj+1, true );
}

void setRandom( LifeGame& life )
{
	int w = life.getWidth();
	int h = life.getHeight();
	int num_cells = w * h;
	int num_live_cells = (int)( (float)num_cells * 0.1f );

	life.clear();
	for( int c=0; c < num_live_cells; c++ )
	{
		int i = rand() % w;
		int j = rand() % h;

		life.setState( i, j, true );
	}
}
