#ifndef HASHREL_H
#define HASHREL_H

#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;
class hashRel
{
public:
    hashRel();

    static void test();

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


    class charFrequency
    {
    public:
        charFrequency(char c, int freq): _c(c), _freq(freq){}
        char _c;
        int  _freq;
        bool operator <(const charFrequency& other) const
        {
            if(this == &other)
            {
                return false;
            }
            if(_freq < other._freq)
            {
                return true;
            }
            else if(_freq == other._freq)
            {
                return _c < other._c;
            }
            return false;
        }
    };

    string frequencySort(string s)
    {
        unordered_map<char, int> dict;
        priority_queue<charFrequency> pq;
        for(char c : s)
        {
            dict[c]++;
        }
        for(const auto& it : dict)
        {
            pq.push(charFrequency(it.first, it.second));
        }
        string res;
        while(!pq.empty())
        {
            string tmp(pq.top()._freq, pq.top()._c);
            res += tmp;
            pq.pop();
        }
        return res;
    }

    string frequencySort1(string s)
    {
        vector<int> freq(256, 0);
        for(char c : s) ++freq[c];
        priority_queue<pair<int, char>> pq;
        for(int i=0; i<256; ++i)
        {
            if(freq[i])
            {
                pq.push(make_pair(freq[i], i));
            }
        }
        string res;
        while(!pq.empty())
        {
            res.append(pq.top().first, pq.top().second);
            pq.pop();
        }
        return res;
    }


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

};





#endif // HASHREL_H
