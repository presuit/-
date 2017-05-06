#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector <vector<char>> game_board;
vector <char> _game_board;


void build_stage1() 
{
	for (int i = 0; i < 4; i++) 
	{
		game_board.push_back(_game_board);
	}
	
	game_board[0].push_back('T');
	game_board[0].push_back('R');
	game_board[0].push_back('T');
	game_board[0].push_back('Y');

	game_board[1].push_back('T');
	game_board[1].push_back('R');
	game_board[1].push_back('U');
	game_board[1].push_back('R');

	game_board[2].push_back('E');
	game_board[2].push_back('U');
	game_board[2].push_back('E');
	game_board[2].push_back('Y');

	game_board[3].push_back('Y');
	game_board[3].push_back('R');
	game_board[3].push_back('Y');
	game_board[3].push_back('R');

	for (int i = 0; i < game_board.size(); i++) 
	{
		for (int j = 0; j < game_board[i].size(); j++) 
		{
			cout << setw(2) << game_board[i][j];
		}
		cout << endl;
	}
}

int main() 
{
	build_stage1();

	return 0;
}