#include <iostream>
#include <string>
#include <iterator>
#include "../ModernCpp/knuth_morris_pratt.h"

using namespace std;
using r00tk1t::algorithm::knuth_morris_pratt_search;

int main()
{
    string pattern = "abab";
    string corpus = "abacdababad";
    pair<string::iterator, string::iterator> res = knuth_morris_pratt_search(corpus.begin(), corpus.end(), pattern.begin(), pattern.end());
    cout << res.first - corpus.begin() << "\t" << res.second - corpus.begin() << endl;
    cout << corpus.substr(res.first - corpus.begin(), res.second - res.first);
    return 0;
}