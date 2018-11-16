#ifndef DESGIN_H
#define DESGIN_H
#include <list>
#include <unordered_map>

class desgin
{
public:
    desgin();
};

using namespace std;
class LRUCache {
public:
    LRUCache(int capacity) {
        _capacity = capacity;
    }

    int get(int key) {
        unordered_map<int, list<pair<int, int>>::iterator>::iterator it = _m.find(key);

        if(it != _m.end())
        {
            //
            _cache.splice(_cache.begin(), _cache, it->second);
            return it->second->second;
        }
        else
        {
            return -1;
        }
    }

    void put(int key, int value) {
        auto it = _m.find(key);
        if(it != _m.end())
        {
            it->second->second = value;
            _cache.splice(_cache.begin(), _cache, it->second);
        }

        if(_cache.size() == _capacity)
        {
            auto ref = _cache.back();
            _m.erase(ref.first);
            _cache.pop_back();
        }

        _cache.emplace_front(make_pair(key, value));
        _m[key] = _cache.begin();
    }


private:
    int _capacity;
    list<pair<int, int>> _cache;
    unordered_map<int, list<pair<int, int>>::iterator> _m;
};

#endif // DESGIN_H
