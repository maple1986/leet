#ifndef CONSTRUCTREL_H
#define CONSTRUCTREL_H
#include <string>
#include <algorithm>
using namespace std;
class constructRel
{
public:
    static void test();

    int magicalString(int n) {
        if(n <= 0) return 0;
        string S = "122";
        for(int i= 2; S.length() < n; ++i)
        {
            if(i&1)
            {
                S.append(S[i]-'0', '2');
            }
            else
            {
                S.append(S[i]-'0', '1');
            }
        }
        return std::count(S.begin(), S.begin()+n, '1');
    }
};

#endif // CONSTRUCTREL_H
