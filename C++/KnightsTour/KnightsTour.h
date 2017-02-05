class KnightsTour {
public:
	KnightsTour(int x, int y);
	void print();
	bool hasMoreMoves();
	bool isSolved();
	bool move(int x, int y);
	void lookAhead(int &r, int &c);
private:
	bool board[6][6];
	int posX, posY;
};