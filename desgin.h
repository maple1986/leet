#ifndef DESGIN_H
#define DESGIN_H
#include <list>
#include <unordered_map>
#include <vector>
#include <queue>

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

class ZigzagIterator2
{
public:
    static void test();
    ZigzagIterator2(vector<vector<int>>& vecs) {
        // do intialization if necessary
        x = 0;
        y = 0;
        _vecs = vecs;
    }

    /*
         * @return: An integer
         */
    int next() {
        // write your code here
        return _vecs[y++][x];
    }

    /*
         * @return: True if has next
         */
    bool hasNext() {
        // write your code here
        while(!_vecs.empty())
        {
            if(y >= _vecs.size())
            {
                y = 0;
                x++;
            }
            if(_vecs[y].size() <= x)
            {
                _vecs.erase(_vecs.begin()+y);
            }
            else
            {
                break;
            }
        }
        return !_vecs.empty();
    }

private:
    int x;
    int y;
    vector<vector<int>> _vecs;
};

class ZigzagIterator22 {
public:
    /*
    * @param vecs: a list of 1d vectors
    */ZigzagIterator22(vector<vector<int>>& vecs) {
        // do intialization if necessary
        _vecs = vecs;
        int i = 0;
        for(auto& vec : _vecs)
        {
            if(vec.begin() != vec.end())
            {
                _q.push(make_pair(i, vec.begin()));

            }
            ++i;
        }

    }

    /*
     * @return: An integer
     */
    int next() {
        // write your code here
        pair<int, vector<int>::iterator> element = _q.front();
        int res = *element.second;
        if(element.second+1 != _vecs[element.first].end())
        {
            _q.push(make_pair(element.first, element.second+1));
        }
        return res;
    }

    /*
     * @return: True if has next
     */
    bool hasNext() {
        return !_q.empty();
        // write your code here
    }
    std::queue<pair<int, vector<int>::iterator>> _q;
    vector<vector<int>> _vecs;
};

class ZigzagIterator23 {
    ZigzagIterator23(vector<vector<int>>& vecs) {
        _vecs = vecs;
        for(auto& vec : _vecs)
        {
            if(!vec.empty())
            {
                q.push(make_pair(vec.begin(), vec.end()));
            }
        }
    }

    int next() {
        auto it = q.front().first, end = q.front().second;
        q.pop();
        if (it + 1 != end) q.push(make_pair(it + 1, end));
        return *it;
    }
    bool hasNext() {
        return !q.empty();
    }
private:
    queue<pair<vector<int>::iterator, vector<int>::iterator>> q;
    vector<vector<int>> _vecs;
};


#endif // DESGIN_H
