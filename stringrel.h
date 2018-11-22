#ifndef STRINGREL_H
#define STRINGREL_H
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

class StringRel
{
public:
    StringRel()
    {

    }
    static void test();
    string multiply(string num1, string num2) {
        if(num1.empty() || num2.empty())
        {
            return "0";
        }
        int m = num1.size();
        int n = num2.size();
        string ret(m+n, '0');
        int c = 0;
        for(int i=n-1; i>=0; --i)
        {
            int multi = num2[i] - '0';
            if(multi)
            {
                for(int j=m-1; j>=0; --j)
                {
                    int tmp = ret[i+j+1]-'0'+ multi*(num1[j]-'0')+c;
                    ret[i+j+1] = tmp%10 + '0';
                    c = tmp/10;
                }
            }
            ret[i] += c;
            c=0;
        }
        size_t pos = ret.find_first_not_of('0');
        if(pos == string::npos)
        {
            return "0";
        }
        return ret.substr(pos);
    }

    string longestCommonPrefix(vector<string>& strs)
    {
        return "";
    }

    string longestPalindrome(string s)
    {
        return "";
    }

    bool isPalindrome(string& s, int right)
    {
        int left = 0;
        while(left < right)
        {
            if(s[left] != s[right])
            {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

    int longsetPalidrome(string& s)
    {
        int right = s.length()-1;
        while(right)
        {
            if(isPalindrome(s, right))
            {
                return right;
            }
            --right;
        }
        return 0;
    }

    string shortestPalindrome(string s)
    {
        int index = longsetPalidrome(s);
        string sub = s.substr(index+1);

        reverse(sub.begin(), sub.end());
        return sub + s;
    }

    bool canPermutePalindrome(string s)
    {
        bitset<26> bs = {0};
        string::iterator it = s.begin();
        while(it != s.end())
        {
            bs.flip(*it-'a');
            ++it;
        }
        return bs.count() < 2;
    }

    void countOfAtoms(map<string, int>& res, string& formula, int& i)
    {

        while(i < formula.size())
        {
            if(formula[i] == '(')
            {
                countOfAtoms(res, formula, ++i);
            }
            else if(formula[i] == ')')
            {

            }
        }
    }

    string countOfAtoms(string formula)
    {
        map<string, int> res;
        string ans;
        /*
        countOfAtoms(res, formula, 0);
        for(auto v : res)
        {
            ans += v->first + ":" + to_string(v->second);
        }
        */
        return ans;
    }

    bool isStrobogrammatic(string num)
    {
        return true;
    }

    string reverseVowels(string s)
    {
        if(s.size() < 2) return s;
        int left = 0, right = s.size()-1;
        while (left < right)
        {
            if(isVowel(s[left]) && isVowel(s[right]))
            {
                swap(s[left++], s[right--]);
            }
            else if(isVowel(s[left]))
            {
                --right;
            }
            else if(isVowel(s[right]))
            {
                ++left;
            }
            else
            {
                ++left;
                --right;
            }
        }
        return s;
    }

    vector<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

    bool isVowel(char c)
    {
        for(char vowel : vowels)
        {
            if(vowel == c)
            {
                return true;
            }
        }
        return false;
    }

    string reverseString(string s)
    {
        if(s.size() < 2) return s;
        int left = 0, right = s.size()-1;
        while (left < right)
        {
            char c = s[left];
            s[left] = s[right];
            s[right] = s[left];
            ++left;
            --right;
        }
        return s;
    }

    /*
   Sunday(T, P)
01 n <- the length of T
02 m <- the length of P
03 // computer the shift table for P
04 for c <- 0 to the length of OffsetTable - 1
05 shift[c] = m + 1
06 for k <- 0 to m - 1
07 shift[P[k]] = m - k
08 // search
09 s <- 0
10 while s ≤ n - m do
11 j <- 0  // start from the begin
12 // check if T[s..s+m-1] = P[0..m-1]
13 while T[s + j] = P[j] do
14 j <- j + 1
15 if j ≥ m then return s
16 s <- s + shift[T[s + m]]
17 return -1
     */
/*
    int Sunday(string T, string P)
    {
        int n = T.size();
        int m = P.size();

        int s = 0;
        while(s <= n-m)
        {
            for(int j=0; j<m; ++j)
            {
                while T[s + j] = P[j] do
                        j <- j + 1
                        if j ≥ m then return s
            }
            s <- s + shift[T[s + m]];
        }
    }
*/
    char findDifference(string s, string t)
    {
        vector<int> dict(26, 0);
        for(char c : s)
        {
            dict[c-'a']++;
        }
        for(char c : t)
        {
            dict[c-'a']--;
        }
        for(int i=0; i < dict.size(); ++i)
        {
            if(dict[i] == -1)
            {
                return 'a'+i;
            }
        }
        return 0;
    }

    bool detectCapitalUse(string word)
    {
        if(word.size() == 1) return true;
        bool initialCaptal = isupper(word[0]);
        bool secondaryCaptal = isupper(word[1]);
        for(int i=1; i<word.size(); ++i)
        {
            if(initialCaptal)
            {
                if(secondaryCaptal && islower(word[i]))
                {
                    return false;
                }
                if(!secondaryCaptal && isupper(word[i]))
                {
                    return false;
                }
            }
            else
            {
                if(!islower(word[i]))
                {
                    return false;
                }
            }
        }
        return true;
    }

    vector<string> generatePalindromes(string s)
    {
        /*
        unordered_map<char> dict;
        for(char c : s)
        {
            dict[c]++;
        }
        int odd = 0;
        char mid = 0;
        for(const auto& c: dict)
        {
            if(c.second%2)
            {
                mid = c.first;
                odd++;
            }
        }
        vector<string> res;
        if(odd > 1) return res;
        string init;
        if(odd) init += mid;
        dfs(init, dict, res);
        */
    }
/*
    void dfs(mid, dict, res)
    {

    }
*/
    bool validWordAbbreviation(string word, string abbr)
    {
        int m = word.size();
        int n = abbr.size();
        int i = 0, j =0;
        while(j < n && i < m)
        {
            if(word[i] == abbr[j])
            {
                ++i, ++j;
                continue;
            }
            int cnt = 0;
            if(isdigit(abbr[j]))
            {
                if(abbr[j] == '0') return false;
                while(isdigit(abbr[j]))
                {
                    cnt = cnt*10+abbr[j]-'0';
                    ++j;
                }
                i += cnt;
            }
            else
            {
                return false;
            }
        }
        return j == n && i == m;
    }

    int findLUSlength(vector<string>& strs)
    {
        map<int, vector<int>> dict;
        int i = 0;
        for(const auto& str : strs)
        {
            dict[str.length()].push_back(i++);
        }
        int res = 0;
        for(const auto& item : dict)
        {
            //item
        }
    }

    string nextClosestTime(string &time) {
        // write your code here
        _h1 = time[0];
        _h2 = time[1];
        _m1 = time[3];
        _m2 = time[4];
        _sorted.append(1, _h1);
        _sorted.append(1, _h2);
        _sorted.append(1, _m1);
        _sorted.append(1, _m2);
        sort(_sorted.begin(), _sorted.end());
        //get max and min

        if(_m2 != nextBiggerChar(_m2))
        {
             time[4] = nextBiggerChar(_m2);
             return time;
        }
        time[4] = minChar();
        if(_m1 != nextBiggerChar(_m1) && nextBiggerChar(_m1) < '6')
        {
            time[3] = nextBiggerChar(_m1);
            return time;
        }
        time[3] = minChar();
        if(_h2 != nextBiggerChar(_h2))
        {
            if(_h1 <= '1' || (_h1 > '1' && nextBiggerChar(_h2)< '4'))
            {
                time[1] = nextBiggerChar(_h2);
                return time;
            }
        }
        time[1] = minChar();
        if(_h1 != nextBiggerChar(_h1) && nextBiggerChar(_h1) <= '2')
        {
            time[0] = nextBiggerChar(_h1);
        }
        time[0] = minChar();
        return time;
    }

    char nextBiggerChar(char c)
    {
        char next = c;
        for(char s : _sorted)
        {
            if(s > next)
            {
                next = s;
                break;
            }
        }
        return next;
    }

    char minChar()
    {
        return _sorted[0];
    }
private:
    char _h1;
    char _h2;
    char _m1;
    char _m2;
    string _sorted;
};

#endif // STRINGREL_H
