#ifndef MYATOI_H
#define MYATOI_H

/***********************************
 * Implement atoi which converts a string to an integer.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found.
Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits
as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number,
which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number,
or if no such sequence exists because either str is empty or it contains only whitespace characters,
no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

Note:

    Only the space character ' ' is considered as whitespace character.
    Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range:
    [−231,  231 − 1].
 If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.

Example 1:

Input: "42"
Output: 42

Example 2:

Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.

Example 3:

Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.

Example 4:

Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical
             digit or a +/- sign. Therefore no valid conversion could be performed.

Example 5:

Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
             Thefore INT_MIN (−231) is returned.


 *
 *
 *
 *
 *
 ***********************************/

#include <string>
#include <vector>

using namespace std;
class MyAtoi
{
public:
    MyAtoi();
    static void test();

    int myAtoi(string str)
    {
        int ret = 0;
        //trim white space
        int i=0;
        bool negative = false;
        while(i<str.length())
        {
            if(str[i] == ' ')
                i++;
            else
                break;
        }

        //check the first non-white char
        if(str[i] == '-')
        {
            negative = true;
            ++i;
        }
        else if(str[i] == '+')
        {
            negative = false;
            ++i;
        }
        //to integer
        while(i<str.length() && str[i]>='0' && str[i]<='9')
        { 
             int add = str[i] - '0';
             if(ret > INT_MAX/10)
             {
                return negative?INT_MIN:INT_MAX;
             }
             else if(ret == INT_MAX/10)
             {
                if(negative && add >= 8)
                {
                    return INT_MIN;
                }
                else if(negative && add >= 7)
                {
                    return INT_MAX;
                }
             }
             ret = ret*10 + add;
             ++i;
        }
        if(negative)
        {
            ret = -ret;
        }
        return ret;
    }
    int reverse(int x) {
        //bool negative = x<0?true:false;
        int ret=0;
        while(x)
        {
            int add = x%10;
            if(ret > INT_MAX/10 || ret < INT_MIN / 10)
            {
               return 0;
            }
            else if(ret == INT_MAX/10 || ret == INT_MIN / 10)
            {
               if( ret < 0&& add >= 8 || (ret >0 && add >= 7))
               {
                   return 0;
               }
            }
            ret = ret*10;
            ret += add;
            x /= 10;
        }
        return ret;
    }
    unsigned int reverseBits(unsigned int n)
    {
        unsigned int x = 0;
        int i = 32;
        bool flag = n%2?false:true;
        if(flag)
            n += 1;
        while(n)
        {
           x <<= 1;
           x |= n%2;
           n /= 2;
           i--;
        }
        if(i)
        {
            x <<= i;
        }
        if(flag)
        {
            x &= 0x7FFFFFFF;
        }
        return x;
    }

    int hammingWeight(unsigned int n) {
        int i = 0;
        while(n)
        {
            if(n & 1)++i;
            n >>= 1;
        }
        return i;
    }

    std::vector<int> countBits(int num)
    {
        int i = 0;
        while(num)
        {
            ++i;
            num >>= 1;
        }
    }

    /****

     ****/

};


#endif // MYATOI_H
