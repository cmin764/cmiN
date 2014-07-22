#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


struct King {

	string name, num;
	int nr;
	
	King()
	{
		name = num = string();
		nr = 0;
	}
};


struct Comp {

	bool operator()(const King& a, const King& b) const
	{
		int ret = a.name.compare(b.name);
		if (!ret) return a.nr < b.nr;
		if (ret < 0) return true;
		return false;
	}
} comp;


class KingSort {

	typedef vector<string> vs_t;
	typedef vector<King> vK_t;
	map<string, int> numbers;
	vs_t final;
	vK_t kings;
	
	King process(const string& id)
	{
		King tmp; // temporar object
		int ind = id.find(' ');
		tmp.name = id.substr(0, ind);
		tmp.num = id.substr(ind + 1);
		tmp.nr = numbers.find(tmp.num)->second;
		return tmp;
	}

	public:
	KingSort()
	{
		string nrs[9] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
		for (int i = 0; i < 5; ++i) {
			string pref = "";
			if (i == 4) {
				pref = "XL";
			} else {
				pref.insert(0, i, 'X');
			}
			for (int j = 0; j < 9; ++j) {
				numbers.insert(make_pair(pref + nrs[j], i * 10 + j + 1));
			}
		}
		numbers.insert(make_pair("L", 50));
		numbers.insert(make_pair("XL", 40));
		numbers.insert(make_pair("XXX", 30));
		numbers.insert(make_pair("XX", 20));
		numbers.insert(make_pair("X", 10));
		//for (map<string, int>::iterator it = numbers.begin(); it != numbers.end(); ++it) cerr << it->first << ":" << it->second << endl;
	}
	
	vs_t getSortedList(vs_t param)
	{
		int size = param.size();
		kings.reserve(size);
		final.reserve(size);
		for (int i = 0; i < size; ++i) {
			kings.push_back(process(param[i]));
		}
		sort(kings.begin(), kings.end(), comp);
		for (int i = 0; i < size; ++i) {
			King tmp = kings[i];
			final.push_back(tmp.name + " " + tmp.num);
		}
		return final;
	}
};
