#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

class TrieNode
{
public:
    TrieNode():_children(26, NULL),_is_word(false)
    {

    }

    ~TrieNode()
    {
        for(TrieNode* child : _children)
        {
            if(child) delete child;
        }
    }

    bool _is_word;
    //char _value;
    vector<TrieNode*> _children;
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie():_root(new TrieNode){

    }
    ~Trie()
    {
        if(_root) delete _root;
    }
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* p = _root;
        for(char c : word)
        {
            if(!p->_children[c-'a'])
            {
                p->_children[c-'a'] = new TrieNode;
            }
            p = p->_children[c-'a'];
        }
        p->_is_word = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* p = find(word);
        return p && p->_is_word;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        if(find(prefix))
            return true;
        return false;
    }

private:
    TrieNode* _root;
    TrieNode* find(string word)
    {
        TrieNode* p = _root;
        for(char c : word)
        {
            if(p->_children[c-'a'])
                p = p->_children[c-'a'];
            else
            {
                p = NULL;
                break;
            }
        }
        return p;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */

class TrieQuestion
{
public:
    static void test();
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end(), [](const string& s1, const string& s2){
            if(s1.length() != s2.length())
            {
                return s1.length() > s2.length();
            }
            else return s1<s2;
        });
        string best;
        unordered_set<string> dict(words.begin(), words.end());
        for(string word : words)
        {
            string prefix;
            bool valid = true;
            for(int i=0; i<word.size(); ++i)
            {
                prefix += word[i];
                if(!dict.count(prefix))
                {
                    valid = false;
                    break;
                }
            }
            if(valid)
            {
                best = word;
                break;
            }
        }
        return best;
    }
};

class WordFilter {
public:
    class WordFilterTrieNode
    {
    public:
        WordFilterTrieNode():_children(26, NULL),max_weight(0)
        {

        }

        ~WordFilterTrieNode()
        {
            for(WordFilterTrieNode* child : _children)
            {
                if(child) delete child;
            }
        }

        int max_weight;
        vector<WordFilterTrieNode*> _children;
    };

    WordFilter(vector<string> words) {
        for(int i=0; i<words.size(); ++i)
        {
            _prefixTrie.insert(words[i], i);
            reverse(words[i].begin(), words[i].end());
            _suffixTrie.insert(words[i], i);
        }
        _max = words.size()-1;
    }

    int f(string prefix, string suffix) {
        if(prefix.empty() && suffix.empty())
            return _max;
        if(prefix.empty())
            return _suffixTrie.search(suffix);
        if(suffix.empty())
            return _prefixTrie.search(prefix);
        return min(_suffixTrie.search(suffix), _prefixTrie.search(prefix));
    }



    class WordFilterTrie {
    public:
        /** Initialize your data structure here. */
        WordFilterTrie():_root(new WordFilterTrieNode){

        }
        ~WordFilterTrie()
        {
            if(_root) delete _root;
        }
        /** Inserts a word into the trie. */
        void insert(string word, int weight) {
            WordFilterTrieNode* p = _root;
            for(char c : word)
            {
                if(!p->_children[c-'a'])
                {
                    p->_children[c-'a'] = new WordFilterTrieNode;
                }
                p = p->_children[c-'a'];
                p->max_weight = weight;
            }
            //p->_is_word = true;
        }

        /** Returns if the word is in the trie. */
        int search(string word) {
            WordFilterTrieNode* p = find(word);
            return p?p->max_weight:-1;
        }

    private:
        WordFilterTrieNode* _root;
        WordFilterTrieNode* find(string word)
        {
            WordFilterTrieNode* p = _root;
            for(char c : word)
            {
                if(p->_children[c-'a'])
                    p = p->_children[c-'a'];
                else
                {
                    p = NULL;
                    break;
                }
            }
            return p;
        }
    };
private:
    WordFilterTrie _prefixTrie;
    WordFilterTrie _suffixTrie;
    int _max;
};

#endif // TRIE_H
