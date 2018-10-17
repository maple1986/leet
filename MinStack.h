#ifndef MINSTACK_H
#define MINSTACK_H
#include <vector>
#include <stack>
#include <list>
using namespace std;

class MinStack
{
public:
    /** initialize your data structure here. */
    MinStack() {
        //_min = INT_MAX;
    }

    void push(int x) {
        _v.push_back(x);
        if(x<_min)
        {
            _min = x;
        }
    }

    void pop() {
        int tmp = top();
        _v.pop_back();
        if(_min == tmp)
        {
            //_min = INT_MAX;
            for(int i=0; i<_v.size(); ++i)
            {
                _min = min(_v[i], _min);
            }
        }
    }

    int top() {
        return _v.back();
    }

    int getMin() {
        return _min;
    }

private:
    vector<int> _v;
    int _min;
};

class MinStack1
{
public:
    stack<int> s1;
    stack<int> s2;
    MinStack1() {

    }

    void push(int x) {
        s1.push(x);
        if (s2.empty() || s1.top() <= getMin()) s2.push(x);
    }

    void pop() {
        if (s2.top() == s1.top()) s2.pop();
        s1.pop();
    }

    int top() {
        return s1.top();
    }

    int getMin() {
        return s2.top();
    }
};

class MinStack2
{
public:
    struct node
    {
        int val;
        int min;
        node* next;
        node(int x, int m, node* p)
        {
            val = x;
            min = m;
            next = p;
        }
    };
    MinStack2()
    {
        head = nullptr;
    }

    void push(int x) {
        if(!head)
        {
            head = new node(x, x, nullptr);
        }
        else
        {
            head = new node(x, min(x, head->min), head);
        }

    }

    void pop() {
        node* tmp = head;
        head = head->next;
        delete tmp;
    }

    int top() {
        return head->val;
    }

    int getMin() {
        return head->min;
    }

private:
    node* head;
};

#endif // MINSTACK_H
