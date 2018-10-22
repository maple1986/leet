#include "greedy.h"
#include <stdio.h>
greedy::greedy()
{

}

void greedy::test()
{
    greedy gdy;
    vector<int> v = {1, 2, 3, 8, 1, 8};
    printf("greedy max rob= [%d]\n", gdy.rob(v));
}
