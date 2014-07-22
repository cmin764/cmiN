#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;


class Ball {

	private:
	typedef pair<int, int> pii_t;
	typedef pair<int, pii_t> pip_t;
	typedef set<pip_t> sp_t;
	int bounceTime; // total moving time
	sp_t path; // check for loops
	int lin, col; // position of the ball
	int addL, addC; // modifiers
	bool loop; // loop switch
	int destroyed; // destroyed bricks
	vector<vector<int> > mat; // the map
	
	void bounce()
	{
		/// Change direction of the ball.
		// Ox hit
		if (!(col % 2)) {
			if (addC == 1) addC = -1;
			else addC = 1;
		}
		// Oy hit
		if (!(lin % 2)) {
			if (addL == 1) addL = -1;
			else addL = 1;
		}
	}
	
	void update_path()
	{
		/// Update path in order to find loops.
		int dir = addL * 10 + addC; // direction
		pip_t item;
		item.first = dir;
		item.second.first = lin;
		item.second.second = col;
		pair<sp_t::iterator, bool> ret = path.insert(item);
		if (!ret.second) {
			// already there
			loop = true;
		}
	}
	
	pii_t get_crd()
	{
		pii_t ret;
		ret.first = lin / 2;
		ret.second = col / 2;
		if (addL == -1 && lin % 2 == 0) --ret.first;
		if (addC == -1 && col % 2 == 0) --ret.second;
		return ret;
	}
	
	public:
	Ball(vector<vector<int> >& mat)
	{
		this->mat = mat;
		lin = 2;
		col = 3;
		addL = addC = 1;
		bounceTime = 0;
		loop = false;
		destroyed = 0;
	}
	
	void advance()
	{
		// next position
		lin += addL;
		col += addC;
		//cerr << lin << " " << col << endl;
		pii_t ret = get_crd();
		int tmpL = ret.first, tmpC = ret.second;
		if (mat[tmpL][tmpC] == 2) { // brick
			// destroy it
			mat[tmpL][tmpC] = 1;
			++destroyed;
			path.clear();
			bounce();
		} else if (mat[tmpL][tmpC] == 0) { // block
			bounce();
		} // nothing if empty space
		++bounceTime;
		update_path();
	}
	
	bool in_loop() const
	{
		return loop;
	}
	
	int get_destroyed() const
	{
		return destroyed;
	}
	
	int get_time() const
	{
		return bounceTime;
	}
	
	void show_map()
	{
		/// Debugging purposes.
		for (int i = 0; i < mat.size(); ++i) {
			for (int j = 0; j < mat.size(); ++j) {
				cout << mat[i][j];
			}
			cout << endl;
		}
	}
};


struct BrickByBrick {
	
	int bricks;
	vector<vector<int> > mat;
	
	inline int decode(char arg)
	{
		switch (arg) {
			case '#': return 0; // block
			case '.': return 1; // space
			case 'B': return 2; // brick
		}
		return -1;
	}
	
	int timeToClear(vector<string> mat)
	{
		bricks = 0;
		this->mat.resize(mat.size() + 2);
		this->mat[0].resize(mat[0].size() + 2);
		this->mat[mat.size() + 1].resize(mat[0].size() + 2);
		for (int i = 1; i <= mat.size(); ++i) {
			this->mat[i].resize(mat[0].size() + 2);
			for (int j = 1; j <= mat[0].size(); ++j) {
				int obj = decode(mat[i - 1][j - 1]);
				this->mat[i][j] = obj;
				if (obj == 2) ++bricks;
			}
		}
		Ball ball(this->mat);
		//ball.show_map();
		while (!(ball.in_loop() || ball.get_destroyed() == bricks)) ball.advance();
		if (ball.in_loop()) return -1;
		return ball.get_time();
	}
};
