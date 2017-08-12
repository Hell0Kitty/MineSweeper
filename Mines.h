#ifndef MINES
#define MINES
#endif 
#include<vector>
#include<set>
#include<random>
bool check(char, char, char);


class Mines 
{
	friend struct Board;
	char display;
	bool boomb;
	int around;
	bool visit;

public:
	Mines() :display('_'), boomb(false), around(0), visit(0) {};
	Mines(char c, bool b, int i) :display(c), boomb(b), around(i), visit(0) {};
};

struct Board
{
	Board(unsigned m) :game(0), remains(m), column({}), all({}) {}
	friend class Mines;
	void ini(void);
	void set(char, char, char);    
	void print(void);    
	bool game;         
	unsigned remains;                 

private:
	std::vector<std::vector<Mines> > column;
	std::set<std::pair<int, int>> all;
	void click(char, char);
	void reset(char, char);
	void choose(char, char);
	void label(char, char);
	void calc(void);
	void white(int, int);

};
