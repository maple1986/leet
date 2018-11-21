#include "hashrel.h"
#include <iostream>

hashRel::hashRel()
{

}

void hashRel::test()
{
    hashRel h;
    string s = h.frequencySort("abcdefgg");
    cout << s.c_str() << endl;
}
