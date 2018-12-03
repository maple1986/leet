#include "trie.h"


void TrieQuestion::test()
{
    Trie* obj = new Trie();
    obj->insert("ab");
    bool param_2 = obj->search("a");
    bool param_3 = obj->startsWith("ab");
    delete obj;
}
