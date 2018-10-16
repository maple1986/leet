#ifndef POWEROFN_H
#define POWEROFN_H


class PowerofN
{
public:
    PowerofN();
    static void test();
    bool isPowerOfFour(int num)
    {
        if(num<=0)
        {
            return false;
        }
        while(num)
        {
            if(num & 0x03)
            {
                if(num == 1)
                {
                    return true;
                }
                return false;
            }
            else
            {
                num = num >> 2;
            }

        }
        return false;
    }
    bool isPowerOfTwo(int n) {
        if(n <= 0)
            return false;
        if(n&n-1) return false;
        return n & 0xFFFFFFFF;
    }
};

#endif // POWEROFN_H
