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

    vector<string> wordsAbbreviation(vector<string> &dict)
    {
        // write your code here
        unordered_map<string, vector<pair<int, string>>> abbrs;
        for(int i=0; i<dict.size(); ++i)
        {
            string cur = dict[i];
            if(cur.length() > 3)
            {
                cur = cur.front() + to_string(cur.length()-2) + cur.back();
            }
            abbrs[cur].emplace_back(i, dict[i]);
        }
        resolveConflict(abbrs);
        vector<string> res;
        for(int i=0; i<dict.size(); ++i)
        {
            string cur = dict[i];
            if(cur.length() > 3)
            {
                cur = cur.front() + to_string(cur.length()-2) + cur.back();
            }
            if(abbrs[cur].size() == 1)
            {
                res.emplace_back(cur);
            }
            else
            {
                //vector<pair<int, string>>& conflicts = abbrs[cur];
            }
        }
    }

    void resolveConflict(unordered_map<string, vector<pair<int, string>>>& abbrs)
    {
        for(auto abbr : abbrs)
        {
            if(abbr.second.size() == 1)
            {
                continue;
            }
            else
            {
                vector<int> pre;
            }
        }
    }

    vector<string> wordsAbbreviation1(vector<string> &dict)
    {

    }

    int longestConsecutive(vector<int>& nums) {
        if(nums.empty()) return 0;
        unordered_map<int, int> counter;
        for(int num : nums)
        {
            if(counter.count(num)) continue;
            if(!counter.count(num-1) && !counter.count(num+1))
            {
                counter[num] = 1;
            }
            else if(counter.count(num-1) && counter.count(num+1))
            {
                int l = counter[num-1];
                int r = counter[num+1];
                int n = l + r + 1;
                counter[num-l] = n;
                counter[num+r] = n;
                counter[num]   = max(l, r) + 1;
            }
            else
            {
                if(counter.count(num-1))
                {
                    int l = counter[num-1];
                    int n = l + 1;
                    counter[num-l] = n;
                    counter[num] = n;
                }
                else
                {
                    int r = counter[num+1];
                    int n = r + 1;
                    counter[num+r] = n;
                    counter[num] = n;
                }
            }
        }
        int res = 1;
        for(auto& c : counter)
        {
            res = max(res, c.second);
        }
        return res;
    }

    string sameNumber(vector<int> &nums, int k) {
        // Write your code here
        if(nums.empty()) return "NO";
        unordered_map<int, vector<int>> hmap;
        for(int i=0; i<nums.size(); ++i)
        {
            hmap[nums[i]].push_back(i);
        }
        auto it = hmap.begin();
        while(it != hmap.end())
        {
            if(it->second.size() < 2)
                continue;
            for(int i=1; i<it->second.size(); ++i)
            {
                if((it->second[i] - it->second[i-1]) < k)
                   return "YES";
            }
        }
        return "NO";
    }

    vector<vector<string>> wordSquares(vector<string>& words) {
        vector<vector<string>> res;
        unordered_map<string, set<string>> m;
        int n = words[0].size();
        for (string word : words) {
            for (int i = 0; i < n; ++i) {
                string key = word.substr(0, i);
                m[key].insert(word);
            }
        }
        vector<vector<char>> mat(n, vector<char>(n));
        helper(0, n, mat, m, res);
        return res;
    }
    
    void helper(int i, int n, vector<vector<char>>& mat, unordered_map<string, set<string>>& m, vector<vector<string>>& res) {
            if (i == n) {
                vector<string> out;
                for (int j = 0; j < n; ++j) out.push_back(string(mat[j].begin(), mat[j].end()));
                res.push_back(out);
                return;
            }
            string key = string(mat[i].begin(), mat[i].begin() + i);
        for (string str : m[key]) {
            mat[i][i] = str[i];
            int j = i + 1;
            for (; j < n; ++j) {
                mat[i][j] = str[j];
                mat[j][i] = str[j];
                if (!m.count(string(mat[j].begin(), mat[j].begin() + i + 1))) break;
            }
            if (j == n) helper(i + 1, n, mat, m, res);
        }
    }
};

#endif // HASHREL_H
