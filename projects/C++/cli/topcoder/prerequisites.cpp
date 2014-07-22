#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
using namespace std;


struct Course {
	/**
	 * Used like a pair.
	 */

	string name;
	int number;

	bool operator==(const Course& param) const
	{
	    if (this->name != param.name) return false;
	    if (this->number != param.number) return false;
	    return true;
	}
};


struct Compare {
	/**
	 * Comparison class.
	 * First by number then lexicographyc.
	 */

    bool operator()(const Course& first, const Course& second) const
	{
		if (first.number == second.number) {
			int res = first.name.compare(second.name);
			if (res < 0) return true;
			else return false;
		} else {
			return first.number < second.number;
		}
	}
};


class Prerequisites {

	typedef vector<string> vs_t;
	typedef set<Course, Compare> sc_t;
	typedef map<Course, sc_t, Compare> mc_t;
	typedef list<Course> lc_t;
	mc_t dict; // the input
	lc_t total; // total courses/classes

	void test()
	{
		for (mc_t::iterator it = dict.begin(); it != dict.end(); ++it) {
			cout << it->first.name << it->first.number << ":";
			for (sc_t::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
				cout << " " << it2->name << it2->number;
			}
			cout << endl;
		}
	}

	Course split(string param)
	{
	    /** Split a string into course name and number. */
	    Course tmp;
	    int pos;
	    stringstream sio;
	    for (pos = 0; pos < param.size() && isalpha(param[pos]); ++pos);
	    tmp.name = param.substr(0, pos);
	    sio << param.substr(pos);
	    sio >> tmp.number;
	    return tmp;
	}

	bool verify()
	{
		/** Verify if a prerequisite requires itself and return false. */
		for (mc_t::iterator mit = dict.begin(); mit != dict.end(); ++mit) {
			sc_t apear(mit->second.begin(), mit->second.end());
			while (!apear.empty()) {
				if (apear.count(mit->first)) return false;
				Course tmp = *apear.begin();
				apear.erase(apear.begin());
				mc_t::iterator ret = dict.find(tmp);
				if (ret == dict.end()) cerr << "Error, key not found: " << tmp.name << tmp.number << endl;
				else apear.insert(ret->second.begin(), ret->second.end());
			}
		}
		return true; // everything's fine
	}

	inline bool in_front(lc_t::iterator first, lc_t::iterator second, lc_t::iterator end)
	{
	    while (++first != end) if (*first == *second) return true;
	    return false;
	}

	void process()
	{
	    bool status = true;
	    lc_t::iterator cur, tmp;
	    while (status) {
            status = false;
            for (mc_t::iterator mit = dict.begin(); mit != dict.end(); ++mit) {
                cur = find(total.begin(), total.end(), mit->first);
                if (cur == total.end()) {
                    cerr << "Error, key not found: " << mit->first.name << mit->first.number << endl;
                    return;
                }
                for (sc_t::iterator sit = mit->second.begin(); sit != mit->second.end(); ++sit) {
                    tmp = find(total.begin(), total.end(), *sit);
                    if (tmp == total.end()) {
                        cerr << "Error, key not found: " << sit->name << sit->number << endl;
                        return;
                    }
                    if (!in_front(tmp, cur, total.end())) {
                        status = true;
                        total.erase(tmp);
                        total.insert(cur, *sit);
                    }
                }
            }
	    }
	}

	public:
	vs_t orderClasses(vs_t param)
	{
		/* some tests...
		Course a, b, c;
		sc_t obj;
		a.name = "CSE"; a.number = 123;
		b.name = "MATH"; b.number = 100;
		c.name = "CSE"; c.number = 101;
		obj.insert(b); obj.insert(c);
		dict[a] = obj;
		test();*/
		for (vs_t::iterator vit = param.begin(); vit != param.end(); ++vit) {
			int ind = vit->find(':'); // index of ':'
			string sub = vit->substr(0, ind); // string before ':'
			Course tmp = split(sub);
			total.push_back(tmp);
			sc_t& val = dict[tmp]; // course with empty prerequisites list
			if (ind != vit->size() - 1) { // if it has prerequisites
				istringstream sin(vit->substr(ind + 1));
				while (sin >> sub) {
					tmp = split(sub);
					val.insert(tmp);
					//total.push_back(tmp);
				}
			}
		}
		total.sort(Compare());
		//total.erase(unique(total.begin(), total.end()), total.end()); // remove duplicates
		vs_t final; // returned vector
		if (verify()) {
			process();
			for (lc_t::iterator lit = total.begin(); lit != total.end(); ++lit) {
				ostringstream sout;
				sout << lit->number;
				final.push_back(lit->name + sout.str());
			}
			//cerr << "OK!";
		}
		//test();
		return final;
	}
};


int main()
{
    char* vec[] = {"CSE258: CSE244 CSE243 INTR100",
                   "CSE221: CSE254 INTR100",
                   "CSE254: CSE111 MATH210 INTR100",
                   "CSE244: CSE243 MATH210 INTR100",
                   "MATH210: INTR100",
                   "CSE101: INTR100",
                   "CSE111: INTR100",
                   "ECE201: CSE111 INTR100",
                   "ECE111: INTR100",
                   "CSE243: CSE254",
                   "INTR100:"};
    vector<string> con(vec, vec + 11);
    con.clear(); // comment from here
    string str; //
    while (getline(cin, str)) con.push_back(str); // to here if you want to disable input fron console
    Prerequisites obj;
    vector<string> lol = obj.orderClasses(con);
    for (int i = 0; i < lol.size(); ++i) cout << lol[i] << " ";
    return 0;
}
