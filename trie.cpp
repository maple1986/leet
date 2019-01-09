#include "trie.h"


void TrieQuestion::test()
{
    Trie* obj = new Trie();
    obj->insert("ab");
    bool param_2 = obj->search("a");
    bool param_3 = obj->startsWith("ab");
    delete obj;
    vector<string> v1 = {"01","10","0","1","1001010"};
    vector<string> v2 = {"01","0","0101010"};
    vector<string> v3 = {"01","00"};
    TrieQuestion tq;
    int i = tq.getAns(v2);
    i = 0;
}
