#include <iostream>
#include <string.h>
#include "NumofOnes.h"
#include "backtrack.h"
#include "listrel.h"
#include "stringrel.h"
#include "powerofn.h"
using namespace std;

int main()
{
    /*
    char* test[]= {"100", "1", "10", "11", "111",
                   "10000", "1111", "10110", "110011", "110011001"};
    int test_num = 10;
    int len = 0, i = 0, total=0;
    NumofOnes num;
    for (i = 0; i < test_num; i++)
    {
        len = strlen(test[i]);
        total = num.calc1(test[i], len);

        cout << test[i] << ":  result=" << total << endl;
        cout << "\n\n =========================\n" << endl;
    }

    cin >> len;
    */
    backtrack bt;
    //cout << bt.addBinary1("11", "1") << endl;

    string num1("99");
    string num2("9");
    StringRel str;
    str.multiply(num1, num2);

    PowerofN::test();
    return 0;
}

