#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <cstdio>
#include <cmath>
using namespace std;


struct Buy {
	/**
	 * Class used for data encapsulation from purchases.
	 */

	int shelf, column, time;
	
	Buy()
	{
		/* Error flag constructor. */
		shelf = column = time = -1;
	}
	
	Buy(int shelf, int column, int time)
	{
		this->shelf = shelf;
		this->column = column;
		this->time = time;
	}
};


class Comp {
	/**
	 * Comparison class with total price priority.
	 */
	 
	public:
	bool operator()(const pair<int, int>& var1, const pair<int, int>& var2)
	{
		if (var1.second == var2.second) {
			return var1.first < var1.first;
		} else {
			return var1.second > var2.second;
		}
	}
};


class VendingMachine {
	
	vector<vector<int> > tambur; // Here we store the prices.
	queue<Buy> query; // And here the orders.
	multiset<pair<int, int>, Comp> best; // Dinamic update for best column.
	int curCol; // Current column.
	int lastTime;
	
	void set_best()
	{
		for (int j = 0; j < tambur[0].size(); ++j) {
			int sum = 0;
			for (int i = 0; i < tambur.size(); ++i) {
				sum += tambur[i][j];
			}
			best.insert(make_pair(j, sum));
		}
	}
	
	int get_path(int from, int to)
	{
		int nPath, aPath;
		nPath = abs(to - from); // ClockWise
		aPath = tambur[0].size() - nPath; // Counter
		return min(nPath, aPath);
	}
	
	int rotate()
	{
		pair<int, int> tmp = *best.begin();
		int dist = get_path(curCol, tmp.first);
		curCol = tmp.first;
		return dist;
	}
	
	int rotate(int to)
	{
		int dist = get_path(curCol, to);
		curCol = to;
		return dist;
	}
	
	int process()
	{
		int elapsed = 0, newSum = -1;
		Buy tmp;
		while (!query.empty()) {
			tmp = query.front();
			query.pop();
			if (!tambur[tmp.shelf][tmp.column]) {
				return -1;
			}
			if (tmp.time - lastTime >= 5) {
				elapsed += rotate();
			}
			lastTime = tmp.time;
			elapsed += rotate(tmp.column);
			int price = tambur[tmp.shelf][tmp.column];
			tambur[tmp.shelf][tmp.column] = 0;
			multiset<pair<int, int>, Comp>::iterator it;
			for (it = best.begin(); it != best.end(); ++it) {
				if (it->first == tmp.column) {
					newSum = it->second - price;
					break;
				}
			}
			best.erase(it);
			best.insert(make_pair(tmp.column, newSum));
		}
		return elapsed;
	}
	
	void test()
	{
		int i, j;
		for (i = 0; i < tambur.size(); ++i) {
			for (j = 0; j < tambur[i].size(); ++j) {
				cout << tambur[i][j] << " ";
			}
			cout << endl;
		}
		cout << "..........." << endl;
		multiset<pair<int, int>, Comp>::iterator it;
		for (it = best.begin(); it != best.end(); ++it) {
			cout << it->first << ":" << it->second << endl;
		}
	}

	public:
	VendingMachine()
	{
		curCol = lastTime = 0;
	}
	
	int motorUse(vector<string> prices, vector<string> purchases)
	{
		int result = 0, ret;
		tambur.resize(prices.size());
		for (int i = 0; i < prices.size(); ++i) {
			tambur[i].reserve(25); // Maximum number of integers in each element.
			stringstream sout(prices[i]);
			while (sout.good()) {
				int price = -1;
				sout >> price;
				tambur[i].push_back(price);
			}
		}
		for (int i = 0; i < purchases.size(); ++i) {
			int shelf, column, time;
			sscanf(purchases[i].c_str(), "%d,%d:%d", &shelf, &column, &time);
			query.push(Buy(shelf, column, time));
		}
		set_best();
		//test();
		result += rotate();
		if ((ret = process()) == -1) {
			return -1;
		}
		result += ret;
		result += rotate();
		return result;
	}
};
