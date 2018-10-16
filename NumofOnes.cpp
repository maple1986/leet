#include "NumofOnes.h"
#include <iostream>
using namespace std;
NumofOnes::NumofOnes()
{

}

/*
    first calculate the count of 1 in a full 1 number
    eg: 1 => cnt = 1;   11 => (01 10 11) cnt = 4;   111 => (001 010 011 100 101 110 111) cnt = 12
    so we got cnt = k * 2^(k-1)
*/

int NumofOnes::calc1(char* binary, int len)
{
    int nCnt = 1, num = 0;
    int k = len, total = 0;
    char* p = binary+1;

    if (len <= 0)
        return 0;

    while (k > 1)
    {
        if (binary[k-1]=='1')
            num += nCnt;

        nCnt *= 2;
        k--;
    }

    if (num == (nCnt-1))      // full of 1
        return total = len*nCnt;
    else
        total = (len-1)*(nCnt/2);

    total += num+1;

    k = 1;
    while ((*p != '1') && (k<len))
    {
        *p++; k++;
    }

    total += calc1(p, len-k);
    return total;
}
