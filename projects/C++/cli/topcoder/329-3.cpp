#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;


struct ProbabilisticTranslator {

    typedef vector<pair<string, int> > vp_t;
	typedef vector<string> vs_t;
	typedef map<string, vector<string> > msv_t;
	typedef map<pair<string, string>, int> mpi_t;

    int maxValue;
	vs_t text; // contiguous
	msv_t dict;
	mpi_t freq;
	vp_t vec; // vector used to calculate `maxValue`

	void dp()
	{
	    maxValue = 0;
	    msv_t::iterator it = dict.find(text[0]);
        for (int i = 0; i < it->second.size(); ++i) vec.push_back(make_pair(it->second[i], 0));
        for (int i = 1; i < text.size(); ++i) {
            vp_t tmpVec;
            it = dict.find(text[i]); // find possible translation
            for (int j = 0; j < it->second.size(); ++j) { // for each of them
                int localMax = 0;
                for (int k = 0; k < vec.size(); ++k) {
                    mpi_t::iterator freqIt = freq.find(make_pair(vec[k].first, it->second[j]));
                    int newValue = freqIt == freq.end() ? 0 : freqIt->second;
                    newValue += vec[k].second;
                    localMax = max(localMax, newValue);
                }
                maxValue = max(maxValue, localMax);
                tmpVec.push_back(make_pair(it->second[j], localMax));
            }
            vec = tmpVec;
        }
	}

	int maximumFidelity(vs_t text, vs_t dict, vs_t freq)
	{
		// parse data
		for (int i = 0; i < text.size(); ++i) {
			stringstream sio;
			string word;
			sio << text[i];
			while (sio >> word) this->text.push_back(word);
		}
		for (int i = 0; i < dict.size(); ++i) {
		    stringstream sio;
		    string word, value;
		    sio << dict[i];
		    sio >> word >> value;
		    while (sio >> value) this->dict[word].push_back(value);
		}
		for (int i = 0; i < freq.size(); ++i) {
            stringstream sio;
            string first, second;
            int coef;
            sio << freq[i];
            sio >> first >> second >> coef;
            this->freq[make_pair(first, second)] = coef;
		}
		// solve
		dp();
		return maxValue;
	}
};
