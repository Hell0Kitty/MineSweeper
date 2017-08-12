#include"Mines.h"
#include<iostream>
#include<utility>
#include<set>
#include<ctime>
#include<map>

constexpr extern  int sizex = 9, sizey = 9; //0=<size<=26
extern unsigned mine_number = 10;           //ONLY NEED CHANGE 5 NUMBERS

void Board::ini(void)
{
	std::pair<int, int> luck[10] = {};
	std::default_random_engine engine/*(time(0))*/;

	std::uniform_int_distribution<unsigned> dis(0, 8);

	for (int j = 1; j < sizey+1; j++)
	{
		std::vector<Mines> row;

		for (int i = 1; i < sizex+1; i++)
		{

			row.push_back(Mines('-', false, 0));

		}
		column.push_back(row);

	}

	while (all.size() < mine_number)
	{
		all.insert({ dis(engine),dis(engine) });
	}
	for (auto b = all.begin(); b != all.end(); b++)
	{
		column[b->first][b->second].boomb = true;
	}
	//
	calc();
}

void Board::calc(void)
{
	for (int j = 0; j < sizey; ++j)
	{
		for (int i = 0; i < sizex; ++i)
		{
			switch (j)
			{
			case 0: {
				switch (i)
				{
				case 0:           column[j][i].around = column[j][i + 1].boomb + column[j + 1][i].boomb + column[j + 1][i + 1].boomb;         break;
				case sizex-1:     column[j][i].around = column[j][i - 1].boomb + column[j + 1][i].boomb + column[j + 1][i - 1].boomb;     break;
				default:          column[j][i].around = column[j][i - 1].boomb + column[j][i + 1].boomb + column[j + 1][i].boomb + column[j + 1][i - 1].boomb + column[j + 1][i + 1].boomb;      break;

				}
			}
					break;
			case sizey-1:
				switch (i)
				{
				case 0:           column[j][i].around = column[j - 1][i].boomb + column[j - 1][i + 1].boomb + column[j][i + 1].boomb;         break;
				case sizex-1:     column[j][i].around = column[j][i - 1].boomb + column[j - 1][i].boomb + column[j - 1][i - 1].boomb;     break;
				default:          column[j][i].around = column[j][i - 1].boomb + column[j][i + 1].boomb + column[j - 1][i - 1].boomb + column[j - 1][i].boomb + column[j - 1][i + 1].boomb;      break;

				}
				break;
			default:
				switch (i)
				{
				case 0:           column[j][i].around = column[j][i + 1].boomb + column[j + 1][i].boomb + column[j + 1][i + 1].boomb + column[j - 1][i].boomb + column[j - 1][i + 1].boomb;         break;
				case sizex-1:     column[j][i].around = column[j][i - 1].boomb + column[j + 1][i].boomb + column[j + 1][i - 1].boomb + column[j - 1][i].boomb + column[j - 1][i - 1].boomb;     break;
				default:          column[j][i].around = column[j - 1][i - 1].boomb + column[j - 1][i].boomb + column[j - 1][i + 1].boomb + column[j][i - 1].boomb + column[j][i + 1].boomb + column[j + 1][i - 1].boomb + column[j + 1][i].boomb + column[j + 1][i + 1].boomb;      break;

				}
				break;
			}

		}


	}

}

void Board::print()
{
	std::cout << "Total Boomb Number: " << mine_number << std::endl;
	std::cout << "Mines Sweeped:      " << mine_number - remains << std::endl;
	std::map<int, char> match = 
	{ { 1,'a' },{ 2,'b' },{ 3,'c' },{ 4,'d' },{ 5,'e' },{ 6,'f' },{ 7,'g' },{ 8,'h' },{ 9,'i' },{10,'j'},{11,'k'},{12,'l'},{13,'m'},
	  {14,'n'},{15,'o'},{16,'p'},{17,'q'},{18,'r'},{19,'s'},{20,'t'},{21,'u'},{22,'v'},{23,'w'},{24,'x'},{25,'y'},{26,'z'}
	};
	std::map<int, char> Match = 
	{ { 1,'A' },{ 2,'B' },{ 3,'C' },{ 4,'D' },{ 5,'E' },{ 6,'F' },{ 7,'G' },{ 8,'H' },{ 9,'I' },{ 10,'J' },{ 11,'K' },{ 12,'L' },{ 13,'M' },
	  { 14,'N' },{ 15,'O' },{ 16,'P' },{ 17,'Q' },{ 18,'R' },{ 19,'S' },{ 20,'T' },{ 21,'U' },{ 22,'V' },{ 23,'W' },{ 24,'X' },{ 25,'Y' },{ 26,'Z' }
	};
	std::cout << "    ";
	for (int i = 1; i < sizex+1; i++)
		std::cout << Match[i]<<"   ";
	std::cout << std::endl;
	std::cout << "  |";
	for (int i = 0; i < sizey; i++)
		std::cout << "===|";
	std::cout << std::endl;
	
	for (int j = 0; j < sizey; j++)

	{
		std::cout << match[j + 1] << "-| ";
		for (int i = 0; i < sizex; i++)

		{
			std::cout << column[j][i].display << " | ";
		}
		std::cout << std::endl;
		std::cout << "  |";
			for (int i = 0; i < sizey; i++)
				std::cout << "---|";
		std::cout << std::endl; 
	}
	std::cout << "Sweep! " << std::endl
		<< "    C to click;" << std::endl
		<< "    ! to locate mines;" << std::endl
		<< "    ? to label concertain;" << std::endl
		<< "    R to reset;" << std::endl
		<< "Sample: C a A" << std::endl;
}

void Board::set(char ctr, char row, char col)
{

	switch (ctr) {
	case'C': click(row, col);
		break;
	case'R': reset(row, col);
		break;
	case'!':choose(row, col);
		break;
	case'?':label(row, col);
		break;

	}
}

void Board::click(char row, char col)
{
	if (column[row - 97][col - 65].boomb == true)
	{
		game = true;
		for (auto p = all.begin(); p != all.end(); p++)
			column[p->first][p->second].display = 'X';

		print();
	}
	else {
		if (column[row - 97][col - 65].around != 0)
		{
			std::map<int, char> match = { { 1,'1' },{ 2,'2' },{ 3,'3' },{ 4,'4' },{ 5,'5' },{ 6,'6' },{ 7,'7' },{ 8,'8' },{ 9,'9' } };
			column[row - 97][col - 65].display = match[column[row - 97][col - 65].around];
		}
		else { white(row - 97, col - 65); }
	}


}

void Board::white(int j, int i)
{
	if (!column[j][i].around)
	{
		if (!column[j][i].visit)
		{
			column[j][i].visit = 1;
			column[j][i].display = ' ';
			switch (j)
			{
			case 0:
				switch (i)
				{
				case 0: white(j, i + 1); white(j + 1, i); break;
				case 8: white(j, i - 1); white(j + 1, i); break;
				default:white(j, i + 1); white(j, i - 1); white(j + 1, i); break;
				}      break;
			case 8:
				switch (i)
				{
				case 0: white(j, i + 1); white(j - 1, i); break;
				case 8: white(j, i - 1); white(j - 1, i); break;
				default:white(j, i + 1); white(j, i - 1); white(j - 1, i); break;
				}      break;
			default:
				switch (i)
				{
				case 0: white(j, i + 1); white(j - 1, i); white(j + 1, i); break;
				case 8: white(j, i - 1); white(j - 1, i); white(j + 1, i); break;
				default:white(j, i + 1); white(j, i - 1); white(j - 1, i); white(j + 1, i); break;
				}      break;
			}
		}
	}
	else {
		std::map<int, char> match = { { 1,'1' },{ 2,'2' },{ 3,'3' },{ 4,'4' },{ 5,'5' },{ 6,'6' },{ 7,'7' },{ 8,'8' },{ 9,'9' } };
		column[j][i].display = match[column[j][i].around];
	}
	return;
}

void Board::reset(char row, char col)
{
	if (column[row - 97][col - 65].display == '!'&& column[row - 97][col - 65].boomb == true)
		++remains;
	column[row - 97][col - 65].display = '-';

}

void Board::choose(char row, char col)
{
	column[row - 97][col - 65].display = '!';
	if (column[row - 97][col - 65].boomb == true)
		--remains;
}

void Board::label(char row, char col)
{

	column[row - 97][col - 65].display = '?';
}

