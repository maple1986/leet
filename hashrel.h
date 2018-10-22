#ifndef HASHREL_H
#define HASHREL_H

#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;
class hashRel
{
public:
    hashRel();

    vector<vector<string>> groupAnagrams(vector<string>& strs)
    {
        vector<vector<string>> res;
        if(strs.empty()) return res;

        std::unordered_map<string, vector<string>> um;
        //std::unordered_map<vector<int>, string> un;
        auto it = strs.begin();
        while(it != strs.end())
        {
            string tmp = *it;
            sort(tmp.begin(), tmp.end());
            um[tmp].push_back(*it);
        }
        auto it2 = um.begin();
        while(it2 != um.end())
        {
            vector<string> tmp(it2->second.begin(), it2->second.end());
            res.push_back(tmp);
        }
        return res;
    }

    string count_letters ( string s ) {
        vector<int> vi(26, 0);
        for ( char c : s ) {
            vi[c-'a'] += 1;
        }
        string rval;
        for ( int i :  vi ) {
            rval += to_string(i);
        }
        return rval;
    }

    string sort_letters ( string s ) {
        vector<char> vc(s.begin(), s.end());
        sort(vc.begin(), vc.end());
        string rval(vc.begin(), vc.end());
        return rval;
    }

    vector<vector<string>> groupAnagrams1(vector<string>& strs) {
        map<string, vector<string>> msvs;

        for ( string s : strs ) {
            string sorted = sort_letters(s);
            msvs[sorted].push_back(s);
        }

        vector<vector<string>> vvs;
        for ( auto vs : msvs ) {
            vvs.push_back(move(vs.second));
        }

        return vvs;
    }
};


int findSubstring(string s){
        /*
        vector<int> map(128,0);
        int counter; // check whether the substring is valid
        int begin=0, end=0; //two pointers, one point to tail and one  head
        int d; //the length of substring

        for() { /* initialize the hash map here * / }

        while(end<s.size()){

            if(map[s[end++]]-- ?){  /* modify counter here * / }

            while(/* counter condition * /){

                 /* update d here if finding minimum* /

                //increase begin to make it invalid/valid again

                if(map[s[begin++]]++ ?){ /*modify counter here* / }
            }

            /* update d here if finding maximum* /
        }
        return d;
        */
    return 0;
  }


#endif // HASHREL_H
