#include "msra.h"
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;
MSRA::MSRA()
{

}

void MSRA::test()
{
    MSRA msra;
    cout << "#" << msra.Count1s_main(21231231) << endl;
    cout << "#" << msra.Count1s3(21231231) << endl;
    //cout << bt.isBalanced(root) << endl;
    //cout << bt.SumPathIII(root, 8) << endl;
}

int MSRA::Count1s(int num)
{
    int num1s = 0;
    while(num)
    {
        if(num % 10 == 1) num1s++;
        num /= 10;
    }
    return num1s;
}
/*
 *
*/
int MSRA::Count1s3(int N)
{
    int nCnt = 0;
    int nH=0, nC=0, nL=0;
    int nStep = 10;

    cout << "N=" << N << endl << endl;
    while(nStep/10 <= N)
    {
        nC = (N % nStep)/(nStep/10);
        nH = N / nStep;
        nL = (N % nStep) - nC * (nStep/10);

        cout << "C=" << nC << "   H=" << nH << "   L=" << nL << "   Step=" << nStep/10 << endl;
        switch(nC)
        {
        case 0:
            nCnt += nH*(nStep/10);
            break;
        case 1:
            nCnt += nH*(nStep/10) + nL+1;
            break;
        default:
            nCnt += (nH+1)*(nStep/10);
            break;
        }

        nStep *= 10;
    }

    cout << "count=" << nCnt << endl;
    cout << "=====================================\n" <<endl;
    return nCnt;
}
/*
int main()
{
    int nRet = 0, i = 0;
    int test[] = {19,0,1,10,23,123,223,1023};
    int len = sizeof(test)/sizeof(test[0]);

    for (i = 0; i < len; i++)
    {
        nRet = calc(test[i]);
    }
    cin >> nRet;
    return 0;
}
*/


int MSRA::Count1s2(int num1)
{
    std::vector<int> v;
    int num = num1;
    while(num)
    {
        v.push_back(num % 10);
        num /= 10;
    }
    int ret = 0;
    for(int i = v.size()-1; i >= 0; --i)
    {
        if(i == v.size()-1)
        {
            if(v[i] == 1)
            {
                int div = pow(double(10), i);
                ret += num1 % div + 1;
            }
            else if(v[i] > 1)
            {
                ret += pow(double(10), i);
            }
        }
        else if(i == 0)
        {
            ret += num1 / 10;
            if(v[i] >= 1)
            {
                ret++;
            }
        }
        else
        {
            if(v[i] == 0)
            {
                ret += num1/pow(double(10), i) * pow(double(10), i-1);
            }
            else if(v[i] > 1)
            {
                int j = (num1/pow(double(10), i+1)+1);
                ret +=  j * pow(double(10), i);
            }
            else if(v[i] == 1)
            {
                //ret += num1/pow(double(10), i) * pow(double(10), i-1) + num1%int(pow(double(10), i));
                int j = num1/pow(double(10), i+1);
                j *= pow(double(10), i);
                ret += j + num1%int(pow(double(10), i))+1;
            }
        }
    }

    return ret;
}

int MSRA::Count1s_main(int num)
{
    int ret = 0;
    for(int i = 1; i <= num; i++)
    {
        ret += Count1s(i);
    }
    return ret;
}
