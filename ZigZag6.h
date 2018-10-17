#ifndef ZIGZAG6_H
#define ZIGZAG6_H

#include <string>
#include <vector>
using namespace std;

class ZigZag6 {
public:
    static string convert(string s, int numRows) {

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
};


#endif // ZIGZAG6_H
