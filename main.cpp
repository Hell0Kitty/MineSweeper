#include<iostream>
#include<ctime>
#include<utility>
#include"Mines.h"
int pause;
extern unsigned mine_number;
int sizex=9, sizey=9;
bool check(char ctr, char row, char col)
{

	return (row > 96 && row < 'a'+sizey) && (col < 'A'+sizex && col>64) && (ctr == 'C' || ctr == '?' || ctr == '!' || ctr == 'R');  
}


int main()
{
	Board board(mine_number);
	char ctr = 0;
	char row = 0;
	char col = 0;
	board.ini();
	board.print();

	do {
		std::cin >> ctr >> row >> col;
		if (ctr == 'E') return 0;
		if (!check(ctr, row, col))
		{
			std::cout << "Invalid Inputs,Try Again: " << std::endl;
			continue;
		}
		board.set(ctr, row,col);
		board.print();
		std::cout << "Hiya!" <<std::endl;
	} while (board.remains!=0 && board.game==0);
	if (board.game == 1)
		std::cout << "Yahi! Game Over!";
	else
		std::cout << "Hiya! You Win!";
	std::cin >> pause;

}