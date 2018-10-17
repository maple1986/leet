#include "myatoi.h"

MyAtoi::MyAtoi()
{

}

void MyAtoi::test()
{
    MyAtoi myatoi;
    printf("myatoi=[%d]\n", myatoi.myAtoi("-91283472332"));
    printf("myatoi=[%d]\n", myatoi.reverse(1534236469));
    printf("myatoi=[%d]\n", myatoi.reverseBits(43261596));
}
