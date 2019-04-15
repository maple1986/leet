#ifndef STRINGREL_H
#define STRINGREL_H
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <sstream>
#include <math.h>

using namespace std;

class StringRel
{
  public:
    StringRel()
    {
    }
    static void test();
    string multiply(string num1, string num2)
    {
        if (num1.empty() || num2.empty())
        {
            return "0";
        }
        int m = num1.size();
        int n = num2.size();
        string ret(m + n, '0');
        int c = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            int multi = num2[i] - '0';
            if (multi)
            {
                for (int j = m - 1; j >= 0; --j)
                {
                    int tmp = ret[i + j + 1] - '0' + multi * (num1[j] - '0') + c;
                    ret[i + j + 1] = tmp % 10 + '0';
                    c = tmp / 10;
                }
            }
            ret[i] += c;
            c = 0;
        }
        size_t pos = ret.find_first_not_of('0');
        if (pos == string::npos)
        {
            return "0";
        }
        return ret.substr(pos);
    }

    string longestCommonPrefix(vector<string> &strs)
    {
        if (strs.empty() || strs.size() == 1)
            return "";
        string prefix;
        for (int i = 0; i < strs[0].length(); ++i)
        {
            char c = strs[0][i];
            for (int j = 1; j < strs.size(); ++j)
            {
                if (i >= strs[j].size() || c != strs[j][i])
                    return prefix;
            }
            prefix += c;
        }
        return prefix;
    }

    string longestPalindrome(string s)
    {
        int n = s.length();
        if (n <= 1)
            return s;
        unordered_map<char, int> counter;
        for (char c : s)
        {
            counter[c]++;
        }
        auto it = counter.begin();
        string res;
        bool odd = false;
        for (; it != counter.end(); ++it)
        {
            if (it->second % 2 == 0)
            {
                string apd(it->first, it->second / 2);
                res = apd + res + apd;
            }
            else if (!odd)
            {
                //res.insert(res.length()/2, it->first);
            }
        }
        return res;
    }

    bool isPalindrome(string &s, int right)
    {
        int left = 0;
        while (left < right)
        {
            if (s[left] != s[right])
            {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

    int longsetPalidrome(string &s)
    {
        int right = s.length() - 1;
        while (right)
        {
            if (isPalindrome(s, right))
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
        string sub = s.substr(index + 1);

        reverse(sub.begin(), sub.end());
        return sub + s;
    }

    bool canPermutePalindrome(string s)
    {
        bitset<26> bs = {0};
        string::iterator it = s.begin();
        while (it != s.end())
        {
            bs.flip(*it - 'a');
            ++it;
        }
        return bs.count() < 2;
    }

    map<string, int> countOfAtoms(string &formula, int &pos)
    {
        map<string, int> res;
        while (pos < formula.length())
        {
            if (formula[pos] == '(')
            {
                map<string, int> tmp = countOfAtoms(formula, ++pos);
                int count = getCount(formula, pos);
                for (auto &atom : tmp)
                {
                    atom.second *= count;
                    res[atom.first] += atom.second;
                }
            }
            else if (formula[pos] == ')')
            {
                //int count = getCount(formula, ++pos);
                pos++;
                return res;
            }
            else
            {
                string name = getName(formula, pos);
                int count = getCount(formula, pos);
                res[name] += count;
            }
        }
        return res;
    }

    string countOfAtoms(string formula)
    {
        map<string, int> res;
        string ans;
        int pos = 0;
        res = countOfAtoms(formula, pos);
        for (auto v : res)
        {
            ans += v.first + to_string(v.second);
        }
        return ans;
    }

    string getName(string &formula, int &pos)
    {
        string name;
        if (isupper(formula[pos]))
        {
            name += formula[pos++];
            while (islower(formula[pos]))
            {
                name += formula[pos++];
            }
            return name;
        }
        else
        {
            return name;
        }
    }

    int getCount(string &formula, int &pos)
    {
        string count_str;
        while (isdigit(formula[pos]))
        {
            count_str = formula[pos++];
        }
        return count_str.empty() ? 1 : stoi(count_str);
    }

    bool isStrobogrammatic(string num)
    {
        if (num.empty())
            return false;
        unordered_map<char, char> dict;
        dict.insert(make_pair('0', '0'));
        dict.insert(make_pair('1', '1'));
        dict.insert(make_pair('8', '8'));
        dict.insert(make_pair('6', '9'));
        dict.insert(make_pair('9', '6'));

        if (num[0] == '0' && num.size() != 1)
        {
            return false;
        }
        int left = 0, right = num.size() - 1;
        while (left <= right)
        {
            if (dict[num[left++]] != num[right--])
            {
                return false;
            }
        }
        return true;
    }

    vector<string> findStrobogrammatic(int n)
    {
        vector<string> res;
        find(n, n, res);
        return res;
    }

    void find(int m, int n, vector<string> &res)
    {
        if (m == 0)
        {
            res = {""};
            return;
        }
        if (m == 1)
        {
            res = {"0", "1", "8"};
            return;
        }

        find(m - 2, n, res);
        vector<string> cur;
        for (auto &s : res)
        {
            if (m != n)
                cur.push_back("0" + s + "0");
            cur.push_back("1" + s + "1");
            cur.push_back("8" + s + "8");
            cur.push_back("6" + s + "9");
            cur.push_back("9" + s + "6");
        }
        res.swap(cur);
    }

    string reverseVowels(string s)
    {
        if (s.size() < 2)
            return s;
        int left = 0, right = s.size() - 1;
        while (left < right)
        {
            if (isVowel(s[left]) && isVowel(s[right]))
            {
                swap(s[left++], s[right--]);
            }
            else if (isVowel(s[left]))
            {
                --right;
            }
            else if (isVowel(s[right]))
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
        for (char vowel : vowels)
        {
            if (vowel == c)
            {
                return true;
            }
        }
        return false;
    }

    string reverseString(string s)
    {
        if (s.size() < 2)
            return s;
        int left = 0, right = s.size() - 1;
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
        for (char c : s)
        {
            dict[c - 'a']++;
        }
        for (char c : t)
        {
            dict[c - 'a']--;
        }
        for (int i = 0; i < dict.size(); ++i)
        {
            if (dict[i] == -1)
            {
                return 'a' + i;
            }
        }
        return 0;
    }

    bool detectCapitalUse(string word)
    {
        if (word.size() == 1)
            return true;
        bool initialCaptal = isupper(word[0]);
        bool secondaryCaptal = isupper(word[1]);
        for (int i = 1; i < word.size(); ++i)
        {
            if (initialCaptal)
            {
                if (secondaryCaptal && islower(word[i]))
                {
                    return false;
                }
                if (!secondaryCaptal && isupper(word[i]))
                {
                    return false;
                }
            }
            else
            {
                if (!islower(word[i]))
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
        int i = 0, j = 0;
        while (j < n && i < m)
        {
            if (word[i] == abbr[j])
            {
                ++i, ++j;
                continue;
            }
            int cnt = 0;
            if (isdigit(abbr[j]))
            {
                if (abbr[j] == '0')
                    return false;
                while (isdigit(abbr[j]))
                {
                    cnt = cnt * 10 + abbr[j] - '0';
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

    int findLUSlength(vector<string> &strs)
    {
        map<int, vector<int>> dict;
        int i = 0;
        for (const auto &str : strs)
        {
            dict[str.length()].push_back(i++);
        }
        int res = 0;
        for (const auto &item : dict)
        {
            //item
        }
    }

    string nextClosestTime(string &time)
    {
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

        if (_m2 != nextBiggerChar(_m2))
        {
            time[4] = nextBiggerChar(_m2);
            return time;
        }
        time[4] = minChar();
        if (_m1 != nextBiggerChar(_m1) && nextBiggerChar(_m1) < '6')
        {
            time[3] = nextBiggerChar(_m1);
            return time;
        }
        time[3] = minChar();
        if (_h2 != nextBiggerChar(_h2))
        {
            if (_h1 <= '1' || (_h1 > '1' && nextBiggerChar(_h2) < '4'))
            {
                time[1] = nextBiggerChar(_h2);
                return time;
            }
        }
        time[1] = minChar();
        if (_h1 != nextBiggerChar(_h1) && nextBiggerChar(_h1) <= '2')
        {
            time[0] = nextBiggerChar(_h1);
        }
        time[0] = minChar();
        return time;
    }

    char nextBiggerChar(char c)
    {
        char next = c;
        for (char s : _sorted)
        {
            if (s > next)
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

    string findContestMatch(int n)
    {
        vector<string> candidates;
        for (int i = 1; i <= n; ++i)
        {
            candidates.push_back(to_string(i));
        }
        while (n)
        {
            for (int i = 0; i < n / 2; ++i)
            {
                candidates[i] = "(" + candidates[i] + "," + candidates[2 * n - i - 1] + ")";
            }
            n /= 2;
        }

        return candidates[0];
    }

  public:
    char _h1;
    char _h2;
    char _m1;
    char _m2;
    string _sorted;

    vector<string> summaryRanges(vector<int> &nums)
    {
        vector<string> res;
        if (nums.empty())
            return res;
        int start = nums[0];
        int end = nums[0];
        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] - end == 1)
            {
                end++;
            }
            else
            {
                string cur;
                if (end == start)
                {
                    cur = to_string(start);
                }
                else
                {
                    cur = to_string(start) + "->" + to_string(end);
                }
                res.push_back(cur);
                end = nums[i];
                start = end;
            }
        }
        string cur;
        if (end == start)
        {
            cur = to_string(start);
        }
        else
        {
            cur = to_string(start) + "->" + to_string(end);
        }
        res.push_back(cur);
        return res;
    }

    vector<string> findMissingRanges(vector<int> &nums, int lower, int upper)
    {
        vector<string> res;
        if (nums.empty())
        {
            return res;
            //return res.push_back(to_string(lower)+"->"+to_string(upper));
        }
        if (nums[0] > lower + 1)
        {
            res.push_back(to_string(lower) + "->" + to_string(nums[0] - 1));
        }
        else if (nums[0] > lower)
        {
            res.push_back(to_string(lower));
        }
        for (int i = 1; i < nums.size(); ++i)
        {
        }

        if (1 + nums.back() < upper)
        {
            res.push_back(to_string(1 + nums.back()) + "->" + to_string(upper));
        }
        else if (nums.back() < upper)
        {
            res.push_back(to_string(upper));
        }
    }

    void ValidWordAbbr(vector<string> dictionary)
    {
        for (const auto &str : dictionary)
        {
            if (str.length() <= 2)
            {
                if (_m.count(str))
                {
                    _m[str]++;
                }
                else
                {
                    _m[str] = 1;
                }
            }
            else
            {
                string abbr = str[0] + to_string(str.length() - 2) + str[str.length() - 1];
                if (_m.count(abbr))
                {
                    _m[abbr]++;
                }
                else
                {
                    _m[abbr] = 1;
                }
            }
        }
    }

    /*
     * @param word: a string
     * @return: true if its abbreviation is unique or false
     */
    bool isUnique(string &word)
    {
        if (word.length() <= 2)
        {
            return _m.count(word) < 2;
        }
        else
        {
            string abbr = word[0] + to_string(word.length() - 2) + word[word.length() - 1];
            return _m.count(abbr) < 2;
        }
    }

    int countGroups(vector<string> &emails)
    {
        unordered_map<string, int> groups;
        int res = 0;
        for (string email : emails)
        {
            string formated_email;
            int offset_at = email.find('@');
            for (int i = 0; i < offset_at; ++i)
            {
                if ('.' == email[i])
                    continue;
                if ('+' == email[i])
                    break;
                formated_email += email[i];
            }
            formated_email.append(email.begin() + offset_at, email.end());
            if (groups[formated_email]++ == 1)
            {
                res++;
            }
        }
        return res;
    }

    int countGroups1(vector<string> &emails)
    {
        unordered_set<string> groups;
        for (string email : emails)
        {
            string formated_email;
            bool skiped = false;
            for (int i = 0; i < email.length(); ++i)
            {
                if (!skiped)
                {
                    if ('.' == email[i])
                        continue;
                    else if ('+' == email[i])
                    {
                        skiped = true;
                    }
                    else
                    {
                        formated_email += email[i];
                    }
                }
                else
                {
                    if (email[i] == '@')
                    {
                        formated_email += email.substr(i);
                        break;
                    }
                }
            }
            groups.insert(formated_email);
            /*
            if(groups[formated_email]++ == 1)
            {
                res++;
            }
            */
        }
        return groups.size();
    }

    int countGroups2(vector<string> &emails)
    {
        set<string> s;
        int ans = 0;
        for (auto &email : emails)
        {
            string temp = "";
            int size = email.size();
            bool flag = true;
            for (int i = 0; i < size; ++i)
            {
                if (flag)
                {
                    if (email[i] == '.')
                    {
                        continue;
                    }
                    else if (email[i] == '+')
                    {
                        flag = false;
                    }
                    else
                    {
                        temp += email[i];
                    }
                }
                else
                {
                    if (email[i] == '@')
                    {
                        temp += email.substr(i);
                    }
                }
            }

            if (s.count(temp) == 0)
            {
                s.insert(temp);
                ++ans;
            }
        }
        return ans;
    }
    unordered_map<string, int> _m;

    vector<int> findDisappearedNumbers(vector<int> &nums)
    {
        if (nums.size() < 1)
            return {};
        int n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            int pos = nums[i] - 1;
            if (nums[pos] > 0)
            {
                int value = nums[pos];
                nums[pos] = -value;
            }
        }

        vector<int> res;
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] > 0)
            {
                res.push_back(i + 1);
            }
        }
        return res;
    }

    string zigZag(string s, int numRows)
    {
        if (numRows == 1)
            return s;

        vector<string> rows(min(numRows, int(s.size())));
        int curRow = 0;
        bool goingDown = false;

        for (int i = 0; i < s.size(); ++i)
        {
            char c = s[i];
            rows[curRow] += c;
            if (curRow == 0 || curRow == numRows - 1)
                goingDown = !goingDown;
            curRow += goingDown ? 1 : -1;
        }

        string ret;
        for (int i = 0; i < rows.size(); ++i)
            ret += rows[i];
        return ret;
    }

    vector<int> findPermutation(string &s)
    {
        int n = s.length() + 1;
        if (n <= 1)
            return {};
        vector<int> res(n, 0);
        for (int i = 0; i < res.size(); ++i)
        {
            res[i] = i + 1;
        }
        int swapStart = 0, swapEnd = 0;
        while (swapEnd < s.length())
        {
            swapStart = swapEnd;
            if (s[swapEnd] == 'D')
            {
                while (swapEnd < s.length() && s[swapEnd] == 'D')
                {
                    ++swapEnd;
                }
                reverse(res.begin() + swapStart, res.begin() + swapEnd + 1);
            }
            else
            {
                ++swapEnd;
            }
        }
        return res;
    }

    vector<string> wordSegmentation(string &s, int k)
    {
        // Write your code here
        vector<string> temp;
        istringstream sb(s);
        string a;
        while (sb >> a)
        {
            temp.push_back(a);
        }
        a.clear();
        //a = temp[0];
        vector<string> result;
        if (temp.empty())
            return result;
        for (int i = 0; i < temp.size(); ++i)
        {
            if (a.size() + temp[i].size() < k)
            {
                a = a + " " + temp[i];
            }
            else
            {
                result.push_back(a);
                a = temp[i];
            }
        }
        result.push_back(a);
        return result;
    }

    int repeatedStringMatch(string A, string B)
    {
        int m = A.size(), n = B.size();
        int mn = m;
        string AB = A;
        while (mn < n)
        {
            AB.append(A);
            mn += m;
        }
        if (string::npos != AB.find(B))
            return mn / m;
        AB.append(A);
        if (string::npos != AB.find(B))
            return mn / m + 1;
        return -1;
    }

    vector<string> generatePossibleNextMoves(string &s)
    {
        if (s.length() < 2)
            return {};
        vector<string> res;
        for (int i = 1; i < s.length(); ++i)
        {
            if (s[i] == '+' && s[i - 1] == '+')
            {
                s[i] = '-', s[i - 1] = '-';
                res.push_back(s);
                s[i] = '+', s[i - 1] = '+';
            }
        }
        return res;
    }

    vector<vector<int>> twitchWords(string &str)
    {
        int n = str.length();
        if (n < 3)
            return {};
        vector<int> se(2, 0);
        vector<vector<int>> res;
        for (int i = 1; i < n; ++i)
        {
            if (str[i - 1] == str[i])
            {
                se[1] = i;
            }
            else
            {
                if (se[1] - se[0] >= 2)
                {
                    res.push_back(se);
                }
                se[0] = i;
            }
        }
        if (se[1] - se[0] >= 2)
        {
            res.push_back(se);
        }
        return res;
    }

    bool canGetString(string &s, string &t)
    {
        int m = s.length();
        int n = t.length();
        if (n == 0)
            return true;
        if (n > m)
            return false;
        int i = 0, j = 0;
        while (i < m && j < n)
        {
            if (s[i] == t[j])
            {
                j++;
            }
            i++;
        }
        return j == n;
    }

    void calc_next(const string &P, vector<int> &next)
    {
        next[0] = -1;
        int k = -1; //k初始化为-1
        for (int q = 1; q < P.length(); q++)
        {
            while (k > -1 && P[k + 1] != P[q]) //如果下一个不同，那么k就变成next[k]，注意next[k]是小于k的，无论k取任何值
            {
                k = next[k]; //往前回溯
            }
            if (P[k + 1] == P[q]) //如果相同，k++
            {
                k = k + 1;
            }
            next[q] = k; //这个是把算的k的值（就是相同的最大前缀和最大后缀长）赋给next[q]
        }
    }

    void calc_next1(const string &P, vector<int> &next)
    {

        for (int i = 1; i < P.size(); ++i)
        {
            int l = 0, r = l + 1;
            int match = 0;
            while (r < i)
            {
                if (P[l++] == P[r++])
                    match++;
                else
                {
                    break;
                }
            }
            next[i] = match;
        }
    }

    int KMP(const string &T, const string &P)
    {
        int m = T.size(), n = P.size();
        if (n == 0)
            return 0;
        if (m < n)
            return -1;
        vector<int> next(n, 0);
        calc_next(P, next);
        int s = 0;
        int j = 0;
        while (s < m)
        {
            j = 0;
            while (T[s + j] == P[j])
            {
                j++;
                if (j >= n)
                    return s;
            }
            j = next[j];
        }
        return -1;
    }

    void calcNext(const string &p, vector<int> &next)
    {
        next[0] = 0;
        for (int i = 1, k = 0; i < p.size(); ++i)
        {
            while (k > 0 && p[k] != p[i])
            {
                k = next[k - 1];
            }
            if (p[k] == p[i])
                k++;
            next[i] = k;
        }
    }

    int KMP2(const string &T, const string &P)
    {
        int m = T.size(), n = P.size();
        if (n == 0)
            return 0;
        if (m < n)
            return -1;
        vector<int> next(n, 0);
        calcNext(P, next);
        int i = 0;
        int j = 0;
        while (i < m)
        {
            if (j == -1 || P[i] == P[j])
            {
                ++i;
                ++j;
                next[i] = j;
            }
            else
                j = next[j];
        }
        return -1;
    }

    //const int maxNum = 1005;
    //int shift[maxNum];
    int Sunday(const string &T, const string &P)
    {
        int n = T.length();
        int m = P.length();
        vector<int> shift(26, 0);
        // 默认值，移动m+1位
        for (int i = 0; i < shift.size(); i++)
        {
            shift[i] = m + 1;
        }

        // 模式串P中每个字母出现的最后的下标
        // 所对应的主串参与匹配的最末位字符的下一位字符移动到该位，所需要的移动位数
        for (int i = 0; i < m; i++)
        {
            shift[P[i] - 'a'] = m - i;
        }

        // 模式串开始位置在主串的哪里
        int s = 0;
        // 模式串已经匹配到的位置
        int j;
        while (s <= n - m)
        {
            j = 0;
            while (T[s + j] == P[j])
            {
                j++;
                // 匹配成功
                if (j >= m)
                {
                    return s;
                }
            }
            // 找到主串中当前跟模式串匹配的最末字符的下一个字符
            // 在模式串中出现最后的位置
            // 所需要从(模式串末尾+1)移动到该位置的步数
            s += shift[T[s + m] - 'a'];
        }
        //return -1;
        return T.length();
    }

    int match(string &s, string &p, int &concat_idx)
    {
        if (p.size() == 0)
            return s.size();
        vector<int> next(p.size(), 0);
        next[0] = -1;
        int i = 0, j = -1;
        while (i < p.size())
        {
            if (j == -1 || p[i] == p[j])
            {
                next[++i] = ++j;
            }
            else
            {
                j = next[j];
            }
        }
        j = 0;
        i = 0;
        int ans = -1;
        while (i < s.size())
        {
            if (s[i] == p[j])
            {
                ++i;
                ++j;
                if (j == p.size())
                {
                    if (ans == -1)
                        ans = i - j;
                    if (i < s.size())
                        j = 0;
                }
            }
            else
            {
                j = next[j];
                if (j == -1)
                {
                    ++j;
                    ++i;
                }
            }
        }
        concat_idx = i - j;
        if (ans == -1)
            ans = concat_idx;
        return ans;
    }
    vector<int> wordsCompression2(const vector<string> &s)
    {
        // Write your code here
        vector<int> ans;
        string hatch;
        for (auto str : s)
        {
            int concat_idx = 0;
            int idx = match(hatch, str, concat_idx);
            ans.push_back(idx);
            if (hatch.size() < str.size() + concat_idx)
                hatch += str.substr(hatch.size() - concat_idx);
        }
        return ans;
    }

    int repeatedString(string &A, string &B)
    {
        // write your code here
        int N = A.size(), M = B.size();
        if (N == 0)
            return -1;
        //int res = M/N;
        string C(A);
        int L = N;
        while (L < M)
        {
            C += A;
            L += N;
        }
        if (C.find(B) != string::npos)
            return L / N;
        else
        {
            C += A;
            if (C.find(B) != string::npos)
                return L / N + 1;
            return -1;
        }
    }

    string inputStream(string &inputA, string &inputB)
    {
        // Write your code here
        int m = inputA.length() - 1, n = inputB.length() - 1;
        while (m >= 0 && n >= 0)
        {
            if (previous(inputA, m) != previous(inputB, n))
            {
                return "NO";
            }
        }
        if (m < 0 && n < 0)
            return "YES";
        if (m >= 0 && 0 == previous(inputA, m))
            return "YES";
        if (n >= 0 && 0 == previous(inputB, n))
            return "YES";
        return "NO";
    }

    char previous(string &input, int &index)
    {
        if (input[index] != '<')
        {
            index--;
            return input[index];
        }
        else
        {
            int cnt = 1;
            while (cnt || index >= 0)
            {
                if (input[index--] != '<')
                {
                    cnt--;
                }
                else
                {
                    cnt++;
                }
            }
            if (index >= 0)
                return input[index];
            return 0;
        }
    }

    int expressiveWords(string S, vector<string> &words)
    {
        int m = S.length();
        int n = words.size();
        if (n == 0)
            return 0;
        int res = 0;
        if (m == 0)
        {
            for (string &w : words)
            {
                if (w.empty())
                    res++;
            }
            return res;
        }
        vector<pair<char, int>> encodeS;
        encodeS.push_back({S[0], 1});
        for (int i = 1; i < n; ++i)
        {
            if (S[i] == S[i - 1])
                encodeS.back().second++;
            else
                encodeS.push_back({S[i], 1});
        }
        for (string &w : words)
        {
            if (w.size() > m || w.empty())
                continue;
            vector<pair<char, int>> encodeW;
            encodeW.push_back({w[0], 1});
            for (int i = 1; i < w.size(); ++i)
            {
                if (w[i] == w[i - 1])
                    encodeW.back().second++;
                else
                    encodeW.push_back({w[i], 1});
            }
            if (encodeW.size() != encodeS.size())
                continue;
            int matched = 0;
            for (int i = 0; i < encodeS.size(); ++i)
            {
                if (encodeW[i].first != encodeS[i].first)
                    break;
                if (encodeW[i].second == encodeS[i].second || (encodeS[i].second >= 3 && encodeW[i].second < encodeS[i].second))
                {
                    matched++;
                }
                else
                    break;
            }
            if (matched == encodeS.size())
                res++;
            //if(canExpand(encodeS, w)) res++;
        }
        return res;
    }

    string findReplaceString(string S, vector<int> &indexes, vector<string> &sources, vector<string> &targets)
    {
        if (S.empty() || indexes.empty())
            return S;
        /*
        map<int, int> mpIndex;
        for(int i=0; i<indexes.size(); ++i)
        {
            mpIndex[indexes[i]] = i;
        }
        */
        vector<pair<int, int>> mpIndex;
        for (int i = 0; i < indexes.size(); ++i)
        {
            mpIndex.push_back({indexes[i], i});
        }
        sort(mpIndex.rbegin(), mpIndex.rend());
        int n = S.length();
        auto it = mpIndex.begin();
        for (; it != mpIndex.end(); ++it)
        {
            //if(matched(S, it->first, sources[it->second]))
            //{
            //S.replace(S.begin()+it->first, S.begin()+it->first+sources[it->second].length(), targets[it->second]);
            int i = it->first, j = it->second;
            if (S.substr(i, sources[j].length()) == sources[j])
            {
                //S.replace(S.begin()+it->first, S.begin()+it->first+sources[it->second].length(), targets[it->second]);
                S = S.substr(0, i) + sources[j] + S.substr(i + sources[j].length());
            }
            //}
        }
        return S;
    }

    bool matched(string &S, int index, string &source)
    {
        int m = S.length(), n = source.length();
        if (index + n > m)
            return false;
        for (int i = 0; i < n; ++i)
        {
            if (S[i + index] != source[i])
                return false;
        }
        return true;
    }

    string getAns(string &s, string &word)
    {
        // Write a code here
        int m = s.length(), n = word.length();
        if (m == 0 && n == 0)
            return "yes";
        if (m < n)
            return "no";
        //if(s.find(word) != string::npos) return "yes";

        bool found = true;
        for (int st = 0; st < m - n + 1; ++st)
        {
            vector<int> from(26, -1);
            vector<int> to(26, -1);
            int i = st;
            for (int j = 0; j < n; ++j, ++i)
            {
                if (from[word[j] - 'a'] == s[i])
                    continue;
                if (from[word[j] - 'a'] == -1 && to[s[i] - 'a'] == -1)
                {
                    from[word[j] - 'a'] = s[i];
                    to[s[i] - 'a'] = word[j];
                }
                else
                {
                    found = false;
                    break;
                }
            }
            if (found)
                return "yes";
        }
        return "no";
    }

    string decodeString(string s)
    {
        if (s.empty())
            return s;
        int i = 0;
        return decode(s, i);
    }

    string decode(string &str, int &i)
    {
        string res;
        int cnt = 0;
        while (i < str.length())
        {
            char c = str[i];
            if (isdigit(c))
            {
                cnt = cnt * 10 + c - '0';
                i++;
            }
            else if (c == '[')
            {
                i++;
                string t = decode(str, i);
                while (cnt--)
                    res += t;
                cnt = 0;
            }
            else if (c == ']')
            {
                i++;
                return res;
            }
            else
            {
                res += c;
                i++;
            }
        }
        return res;
    }

    int scoreofParentheses(string s)
    {
        return getScore(s, 0, s.length() - 1);
    }

    int getScore(string &str, int s, int e)
    {
        //if(s >= e) return 1;
        //if(s+1 == e) return 1;
        int balance = 0, score = 0, begin = s;
        for (int i = s; i <= e; ++i)
        {
            char c = str[i];
            if (c == '(')
            {
                balance++;
            }
            else if (c == ')')
            {
                balance--;
            }
            if (balance == 0)
            {
                if (begin + 1 == i)
                    score += 1;
                else
                    score += 2 * getScore(str, begin + 1, i - 1);
                begin = i + 1;
            }
        }
        return score;
    }

    string countOfAtoms2(string formula)
    {
        if (formula.empty())
            return formula;
        map<string, int> dict;
        int i = 0;
        dict = countOfAtomsHelp(formula, i);
        string res;
        for (auto v : dict)
        {
            res += v.first;
            if (v.second > 1)
                res += to_string(v.second);
        }
        return res;
    }

    map<string, int> countOfAtomsHelp(string &formula, int &i)
    {
        map<string, int> dict;
        while (i < formula.length())
        {
            char c = formula[i];
            if (c == '(')
            {
                map<string, int> tmp = countOfAtomsHelp(formula, ++i);
                int cnt = getCount1(formula, i);
                for (auto &kv : tmp)
                {
                    dict[kv.first] += cnt * kv.second;
                }
            }
            else if (c == ')')
            {
                i++;
                return dict;
            }
            else
            {
                string name = getName1(formula, i);
                int count = getCount1(formula, i);
                dict[name] += count;
            }
        }
        return dict;
    }

    int getCount1(string &formula, int &i)
    {
        if (!isdigit(formula[i]))
            return 1;
        string cnt;
        while (isdigit(formula[i]))
            cnt += formula[i++];
        return stoi(cnt);
    }
    string getName1(string &formula, int &i)
    {
        string name;
        if (isupper(formula[i]))
        {
            name += formula[i++];
            while (islower(formula[i]))
            {
                name += formula[i++];
            }
        }
        return name;
    }
    //"abbbabbbcabbbabbbc"
    string encode(string &s)
    {
        // write your code here
    }

    vector<int> wordsCompression(vector<string> &s)
    {
        // Write your code here
        vector<int> rt;
        if (s.size() == 0)
            return rt;

        string cs = "";
        for (auto w : s)
        {
            if (cs.size() == 0)
            {
                cs += w;
                rt.push_back(0);
                continue;
            }

            vector<int> prefixArray(w.size(), 0);
            int i = 0;
            int j = 1;
            while (j < w.size())
            {
                if (w[i] == w[j])
                {
                    prefixArray[j] = i + 1;
                    i++;
                    j++;
                }
                else if (i)
                    i = prefixArray[i - 1];
                else
                    j++;
            }

            int si = 0;
            int ti = 0;
            int first_find = -1;
            while (si < cs.size())
            {
                if (cs[si] == w[ti])
                {
                    si++;
                    ti++;
                }
                else if (ti)
                    ti = prefixArray[ti - 1];
                else
                {
                    si++;
                }
                if (ti == w.size())
                {
                    if (first_find == -1)
                        first_find = si - ti;
                    /*if (si < cs.size())
                        ti = prefixArray[ti-1];
                        */
                }
            }

            if (first_find != -1)
                rt.push_back(first_find);
            else
                rt.push_back(cs.size() - ti);

            cs += w.substr(ti);
        }
        return rt;
    }

    vector<int> wordsCompression1(vector<string> &s)
    {
        // Write your code here
        vector<int> rt;
        if (s.size() == 0)
            return rt;

        string cs = "";
        for (auto w : s)
        {
            if (cs.size() == 0)
            {
                cs += w;
                rt.push_back(0);
                continue;
            }
            //vector<int> prefixArray(w.size(), 0);
            vector<int> next(w.size(), 0);
            next[0] = -1;
            int i = 0, j = -1;
            while (i < w.size())
            {
                if (j == -1 || w[i] == w[j])
                {
                    i++;
                    j++;
                    next[i] = j;
                }
                else
                {
                    j = next[j];
                }
            }

            i = 0, j = 0;
            int first_find = -1;
            while (i < cs.size())
            {
                if (j < 0 || cs[i] == w[j])
                {
                    i++;
                    j++;
                }
                else
                {
                    j = next[j];
                }
                if (j == w.size())
                {
                    if (first_find == -1)
                        first_find = i - j;
                }
            }

            if (first_find != -1)
                rt.push_back(first_find);
            else
                rt.push_back(cs.size() - j - 1);

            cs += w.substr(j + 1);
        }
        return rt;
    }
    int minimumCycleSection(vector<int> &array)
    {
        // Write your code here
        int *next = new int[array.size() + 1];
        int i = 0, j = -1;
        next[0] = -1;
        while (i < array.size())
        {
            if (j == -1 || array[i] == array[j])
            {
                i++;
                j++;
                next[i] = j;
            }
            else
            {
                j = next[j];
            }
        }
        return i - next[i];
    }

    int minimumCycleSection2(vector<int> &array)
    {
        // Write your code here
        int len = array.size();
        if (len == 0)
            return 0;
        vector<int> v(len, 0);
        int j = 0, ret = 1;
        for (int i = 1; i < len; i++)
        {
            if (array[i] == array[j])
            {
                v[i] = ++j;
            }
            else
            {
                while (j > 0 && array[i] != array[j])
                    j = v[j - 1];
                if (array[i] == array[j])
                    v[i] = ++j;
                else
                    v[i] = 0;
            }
            if (v[i] == 0)
                ret = max(ret, i + 1);
            else
                ret = max(ret, i + 1 - v[i]);
        }
        return ret;
    }

    int minimumCycleSection3(vector<int> &array)
    {
        int n = array.size();
        if (n <= 1)
            return n;
        vector<int> next(n + 1, 0);
        next[0] = -1;
        int i = 0, j = -1;
        while (i < n)
        {
            if (j == -1 || array[i] == array[j])
            {
                i++;
                j++;
                next[i] = j;
            }
            else
            {
                j = next[j];
            }
        }
        return n - next[n];
    }

    int calculate(string s)
    {
        int i = 0;
        return calcHelper(s, i);
    }

    int calcHelper(string &s, int &i)
    {
        int res = 0;
        int op = 1;
        while (i < s.length())
        {
            while (isspace(s[i]) && i < s.length())
                i++;
            char c = s[i];
            if (c == '(')
            {
                res += op * calcHelper(s, ++i);
            }
            else if (c == ')')
            {
                ++i;
                return res;
            }
            else if (c == '+')
            {
                ++i;
                op = 1;
            }
            else if (c == '-')
            {
                ++i;
                op = -1;
            }
            else
            {
                int tmp = 0;
                while (isdigit(s[i]))
                {
                    tmp = tmp * 10 + s[i] - '0';
                    i++;
                }
                res += op * tmp;
            }
        }
        return res;
    }

    int calculate2(string s)
    {
        int i = 0;
        return calcHelper2(s, i);
    }

    int calcHelper2(string &s, int &i)
    {
        if (s.empty())
            return 0;
        int pre = 0;
        int operand = 0;
        char op = '+';
        int res = 0;
        while(i < s.length())
        {
            char c = s[i];
            if (c == '+'||c == '-'||c =='*'||c=='/')
            {
                ++i;
                op = c;
            }
            else if(c == '(')
            {
                i++;
                int tmp = calcHelper2(s, i);
                switch(op)
                {
                    case '+': res = res+tmp; pre = tmp;break;
                    case '-': res = res-tmp; pre = -tmp;break;
                    case '*': res = res-pre+pre*tmp; pre=pre*tmp;break;
                    case '/': res = res-pre+pre/tmp; pre=pre/tmp;break;
                }
            }
            else if(c == ')')
            {
                i++;
                return res;
            }
            else if(isdigit(c))
            {
                int tmp = 0;
                while (isdigit(s[i]))
                {
                    tmp = tmp * 10 + s[i] - '0';
                    i++;
                }
                switch(op)
                {
                    case '+': res = res+tmp; pre = tmp;break;
                    case '-': res = res-tmp; pre = -tmp;break;
                    case '*': res = res-pre+pre*tmp; pre=pre*tmp;break;
                    case '/': res = res-pre+pre/tmp; pre=pre/tmp;break;
                }
            }

            else i++;
        }
        return res;
    }

    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        // write your code here
        string s;
        for(string& w: words) s+=w+" ";
        int len = s.length();
        vector<string> res;
        for(int i=0; i<len;)
        {
            int j = min(len, i+maxWidth);
            if(j==len || s[j] == ' ')
            {
                res.push_back(s.substr(i, j-i));
            }
            else
            {
                int blank = 0;
                int m=j;
                while(s[m-1] != ' ') m--;
                int delta = j-m;
                for(int k=i; k<m; ++k)
                {
                    if(s[k]==' ') blank++;
                }
                string tmp;
                for(int k=i; k<m; ++k)
                {
                    if(s[k]==' ')
                    {
                        int n = ceil(delta/(double)blank)+1;
                        delta-=n; blank--;
                        while(n--) tmp += ' ';
                    }
                    else tmp += s[k];
                }
                res.push_back(tmp);
                j=m+1;
            }
            i = j;
        }
        return res;
    }
};

#endif // STRINGREL_H
