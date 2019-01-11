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

    map<string, int> countOfAtoms(string& formula, int& pos)
    {
        map<string, int> res;
        while(pos < formula.length())
        {
            if(formula[pos] == '(')
            {
                map<string, int> tmp = countOfAtoms(formula, ++pos);
                int count = getCount(formula, pos);
                for(auto& atom : tmp)
                {
                    atom.second *= count;
                    res[atom.first] += atom.second;
                }
            }
            else if(formula[pos] == ')')
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
        for(auto v : res)
        {
            ans += v.first + to_string(v.second);
        }
        return ans;
    }

    string getName(string& formula, int& pos)
    {
        string name;
        if(isupper(formula[pos]))
        {
            name += formula[pos++];
            while(islower(formula[pos]))
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

    int getCount(string& formula, int& pos)
    {
        string count_str;
        while(isdigit(formula[pos]))
        {
            count_str = formula[pos++];
        }
        return count_str.empty()?1:stoi(count_str);
    }

    bool isStrobogrammatic(string num)
    {
        if(num.empty()) return false;
        unordered_map<char, char> dict;
        dict.insert(make_pair('0', '0'));
        dict.insert(make_pair('1', '1'));
        dict.insert(make_pair('8', '8'));
        dict.insert(make_pair('6', '9'));
        dict.insert(make_pair('9', '6'));

        if(num[0] == '0' && num.size() != 1)
        {
            return false;
        }
        int left = 0, right = num.size()-1;
        while(left <= right)
        {
            if(dict[num[left++]] != num[right--])
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

    void find(int m, int n, vector<string>& res)
    {
        if(m == 0)
        {
            res = {""};
            return;
        }
        if(m == 1)
        {
            res = {"0", "1", "8"};
            return;
        }

        find(m-2, n, res);
        vector<string> cur;
        for(auto& s : res)
        {
            if(m != n) cur.push_back("0" + s + "0");
            cur.push_back("1" + s + "1");
            cur.push_back("8" + s + "8");
            cur.push_back("6" + s + "9");
            cur.push_back("9" + s + "6");
        }
        res.swap(cur);
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

    string findContestMatch(int n)
    {
        vector<string> candidates;
        for(int i=1; i<=n; ++i)
        {
            candidates.push_back(to_string(i));
        }
        while(n)
        {
            for(int i=0; i < n/2; ++i)
            {
                candidates[i] = "(" + candidates[i] + "," + candidates[2*n-i-1] + ")";
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

    vector<string> summaryRanges(vector<int>& nums)
    {
        vector<string> res;
        if(nums.empty()) return res;
        int start = nums[0];
        int end = nums[0];
        for(int i=1; i<nums.size();++i)
        {
            if(nums[i] - end == 1)
            {
                end++;
            }
            else
            {
                string cur;
                if(end == start)
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
        if(end == start)
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
        if(nums.empty())
        {
            return res;
            //return res.push_back(to_string(lower)+"->"+to_string(upper));
        }
        if(nums[0] > lower+1)
        {
            res.push_back(to_string(lower)+"->"+to_string(nums[0]-1));
        }
        else if(nums[0] > lower)
        {
            res.push_back(to_string(lower));
        }
        for(int i=1; i<nums.size();++i)
        {

        }

        if(1 + nums.back() < upper)
        {
            res.push_back(to_string(1+nums.back())+"->"+to_string(upper));
        }
        else if(nums.back() < upper)
        {
            res.push_back(to_string(upper));
        }
    }

    void ValidWordAbbr(vector<string> dictionary) {
        for(const auto& str : dictionary)
        {
            if(str.length() <= 2)
            {
                if(_m.count(str))
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
                string abbr = str[0] + to_string(str.length()-2) + str[str.length()-1];
                if(_m.count(abbr))
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
    bool isUnique(string &word) {
        if(word.length() <= 2)
        {
            return _m.count(word) < 2;
        }
        else
        {
            string abbr = word[0] + to_string(word.length()-2) + word[word.length()-1];
            return _m.count(abbr) < 2;
        }
    }

    int countGroups(vector<string> &emails) {
        unordered_map<string, int> groups;
        int res = 0;
        for(string email : emails)
        {
            string formated_email;
            int offset_at = email.find('@');
            for(int i=0; i<offset_at; ++i)
            {
                if('.' == email[i]) continue;
                if('+' == email[i]) break;
                formated_email += email[i];
            }
            formated_email.append(email.begin()+offset_at, email.end());
            if(groups[formated_email]++ == 1)
            {
                res++;
            }
        }
        return res;
    }

    int countGroups1(vector<string> &emails) {
        unordered_set<string> groups;
        for(string email : emails)
        {
            string formated_email;
            bool skiped = false;
            for(int i=0; i<email.length(); ++i)
            {
                if(!skiped)
                {
                    if('.' == email[i]) continue;
                    else if('+' == email[i])
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
                    if(email[i] == '@')
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
        for (auto &email : emails) {
            string temp = "";
            int size = email.size();
            bool flag = true;
            for (int i = 0; i < size; ++i) {
                if (flag) {
                    if (email[i] == '.') {
                        continue;
                    } else if (email[i] == '+') {
                        flag = false;
                    } else {
                        temp += email[i];
                    }
                } else {
                    if (email[i] == '@') {
                        temp += email.substr(i);
                    }
                }
            }

            if (s.count(temp) == 0) {
                s.insert(temp);
                ++ans;
            }
        }
        return ans;
    }
    unordered_map<string, int> _m;

    vector<int> findDisappearedNumbers(vector<int>& nums) {
        if(nums.size() < 1 ) return {};
        int n = nums.size();
        for(int i=0; i<n; ++i)
        {
            int pos = nums[i]-1;
            if(nums[pos] > 0)
            {
                int value = nums[pos];
                nums[pos] = -value;
            }
        }

        vector<int> res;
        for(int i=0; i<n; ++i)
        {
            if(nums[i] > 0)
            {
                res.push_back(i+1);
            }
        }
        return res;
    }

    string zigZag(string s, int numRows)
    {
        if (numRows == 1) return s;

        vector<string> rows(min(numRows, int(s.size())));
        int curRow = 0;
        bool goingDown = false;

        for (int i =0; i<s.size(); ++i)
        {
            char c = s[i];
            rows[curRow] += c;
            if (curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;
            curRow += goingDown ? 1 : -1;
        }

        string ret;
        for (int i =0; i<rows.size(); ++i) ret += rows[i];
        return ret;
    }

    vector<int> findPermutation(string &s)
    {
        int n = s.length()+1;
        if(n <= 1) return {};
        vector<int> res(n, 0);
        for(int i=0; i<res.size(); ++i)
        {
            res[i] = i+1;
        }
        int swapStart = 0, swapEnd = 0;
        while(swapEnd < s.length())
        {
            swapStart = swapEnd;
            if(s[swapEnd] == 'D')
            {
                while(swapEnd<s.length() && s[swapEnd] == 'D')
                {
                    ++swapEnd;
                }
                reverse(res.begin()+swapStart, res.begin()+swapEnd+1);
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
        while (sb >> a) {
            temp.push_back(a);
        }
        a.clear();
        //a = temp[0];
        vector<string> result;
        if(temp.empty()) return result;
        for(int i=0; i<temp.size(); ++i)
        {
            if(a.size()+temp[i].size() < k)
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

    int repeatedStringMatch(string A, string B) {
        int m = A.size(), n = B.size();
        int mn = m;
        string AB = A;
        while(mn<n)
        {
            AB.append(A);
            mn += m;
        }
        if(string::npos != AB.find(B)) return mn/m;
        AB.append(A);
        if(string::npos != AB.find(B)) return mn/m+1;
        return -1;
    }

    vector<string> generatePossibleNextMoves(string &s) {
        if(s.length() < 2) return {};
        vector<string> res;
        for(int i=1; i<s.length(); ++i)
        {
            if(s[i] == '+' && s[i-1] == '+')
            {
                s[i] = '-', s[i-1] = '-';
                res.push_back(s);
                s[i] = '+', s[i-1] = '+';
            }
        }
        return res;
    }

    vector<int> wordsCompression(vector<string> &s) {
        // Write your code here
    }

    vector<vector<int>> twitchWords(string &str) {
        int n = str.length();
        if(n < 3) return {};
        vector<int> se(2, 0);
        vector<vector<int>> res;
        for(int i=1; i<n; ++i)
        {
            if(str[i-1] == str[i])
            {
                se[1] = i;
            }
            else
            {
                if(se[1]-se[0]>=2)
                {
                    res.push_back(se);
                }
                se[0] = i;
            }
        }
        if(se[1]-se[0]>=2)
        {
            res.push_back(se);
        }
        return res;
    }

    bool canGetString(string &s, string &t) {
        int m = s.length();
        int n = t.length();
        if(n == 0) return true;
        if(n > m) return false;
        int i=0, j = 0;
        while(i<m && j<n)
        {
            if(s[i] == t[j])
            {
                j++;
            }
            i++;
        }
        return j == n;
    }
    //const int maxNum = 1005;
    //int shift[maxNum];
    int Sunday(const string& T, const string& P) {
        int n = T.length();
        int m = P.length();
        vector<int> shift(26, 0);
        // 默认值，移动m+1位
        for(int i = 0; i < shift.size(); i++) {
            shift[i] = m + 1;
        }

        // 模式串P中每个字母出现的最后的下标
        // 所对应的主串参与匹配的最末位字符的下一位字符移动到该位，所需要的移动位数
        for(int i = 0; i < m; i++) {
            shift[P[i]-'a'] = m - i;
        }

        // 模式串开始位置在主串的哪里
        int s = 0;
        // 模式串已经匹配到的位置
        int j;
        while(s <= n - m) {
            j = 0;
            while(T[s + j] == P[j]) {
                j++;
                // 匹配成功
                if(j >= m) {
                    return s;
                }
            }
            // 找到主串中当前跟模式串匹配的最末字符的下一个字符
            // 在模式串中出现最后的位置
            // 所需要从(模式串末尾+1)移动到该位置的步数
            s += shift[T[s + m]-'a'];
        }
        //return -1;
        return T.length();
    }

    int match(string &s, string &p, int &concat_idx){
        if( p.size() == 0 ) return s.size();
        vector<int> next(p.size(), 0);
        next[0] = -1;
        int i = 0, j = -1;
        while( i < p.size()){
            if( j == -1 || p[i] == p[j]){
                next[++i] = ++j;
            }else{
                j = next[j];
            }
        }
        j = 0;
        i = 0;
        int ans = -1;
        while( i < s.size() ){
            if( s[i] == p[j]){
                ++i;
                ++j;
                if( j == p.size() ){
                    if( ans == -1 )
                        ans = i - j;
                    if( i < s.size() )
                        j = 0;
                }
            }else{
                j = next[j];
                if( j == -1 ){
                    ++j;
                    ++i;
                }
            }
        }
        concat_idx = i-j;
        if( ans == -1 )
            ans = concat_idx;
        return ans;
    }
    vector<int> wordsCompression2(const vector<string> &s) {
        // Write your code here
        vector<int> ans;
        string hatch;
        for( auto str: s){
            int concat_idx = 0;
            int idx = match(hatch, str, concat_idx);
            ans.push_back(idx);
            if( hatch.size() < str.size() + concat_idx )
                hatch += str.substr(hatch.size() - concat_idx);

        }
        return ans;
    }

    int repeatedString(string &A, string &B) {
        // write your code here
        int N = A.size(), M = B.size();
        if(N == 0) return -1;
        //int res = M/N;
        string C(A);
        int L = N;
        while(L < M)
        {
            C += A;
            L += N;
        }
        if(C.find(B) != string::npos)
            return L/N;
        else
        {
            C += A;
            if(C.find(B) != string::npos) return L/N+1;
            return -1;
        }
    }

    string inputStream(string &inputA, string &inputB) {
        // Write your code here
        int m = inputA.length()-1, n = inputB.length()-1;
        while(m>=0 && n>=0)
        {
            if(previous(inputA, m) != previous(inputB, n))
            {
                return "NO";
            }
        }
        if(m < 0 && n < 0) return "YES";
        if(m>=0 && 0 == previous(inputA, m)) return "YES";
        if(n>=0 && 0 == previous(inputB, n)) return "YES";
        return "NO";
    }

    char previous(string& input, int& index)
    {
        if(input[index] != '<')
        {
            index--;
            return input[index];
        }
        else
        {
            int cnt = 1;
            while(cnt || index >=0)
            {
                if(input[index--] != '<')
                {
                    cnt--;
                }
                else
                {
                    cnt++;
                }
            }
            if(index>=0) return input[index];
            return 0;
        }

    }
};

#endif // STRINGREL_H
