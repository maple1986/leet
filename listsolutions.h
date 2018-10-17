#ifndef LISTSOLUTIONS_H
#define LISTSOLUTIONS_H

#include <vector>
#include <set>
#include <stack>
using namespace std;
//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(nullptr), random(nullptr) {}
};

class Node {
public:
    int val = 0;
    Node* prev = nullptr;
    Node* next = nullptr;
    Node* child = nullptr;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};

class ListSolutions
{
public:
    ListSolutions();
    static void test();
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        return nullptr;
    }
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        ListNode* res = nullptr;
        ListNode* l3 = nullptr;
        while(l1 && l2)
        {
            int minNum = 0;
            if(l1->val < l2->val)
            {
                minNum = l1->val;
                l1 = l1->next;
            }
            else
            {
                minNum = l2->val;
                l2 = l2->next;
            }
            if(!res)
            {
                res = l3 = new ListNode(minNum);
            }
            else
            {
                l3->next = new ListNode(minNum);
                l3 = l3->next;
            }

        }
        if(l1)
        {
            l3->next = l1;
        }
        if(l2)
        {
            l3->next = l2;
        }
        return res;
    }

    RandomListNode *copyRandomList(RandomListNode *head)
    {

    }

    Node* flatten(Node* head) {
        if(!head) return head;
        Node* res = nullptr;
        if(head)
        {
            res = new Node(head->val, nullptr, nullptr, nullptr);
        }
        if(head->child)
        {
            flatten(head->child);
        }
        if(head->next)
        {
            flatten(head->next);
        }
        return res;
    }
    ListNode* middleNode(ListNode* head)
    {
        if(!head)
        {
            return head;
        }
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast->next)
        {
            fast = fast->next;
            slow = slow->next;
            if(fast->next)
            {
                fast = fast->next;
            }
            else
            {
                break;
            }
        }
        return slow;
    }

    bool hasCycle(ListNode *head) {
        if(!head)
        {
            return false;
        }
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow)
            {
                return true;
            }
        }
        return false;
    }

    bool hasCycle1(ListNode *head)
    {
        if (head == nullptr) return false;
        ListNode *p1 = head;
        ListNode *p2 = head;
        while (true)
        {
            // p1 += 2
            // p2 += 1
            if (p1->next == nullptr || p1->next->next == nullptr)
                return false;
            p1 = p1->next->next;
            p2 = p2->next;
            if (p1->val == p2->val)
                return true;
        }
    }

    ListNode *reverseList(ListNode *head)
    {
        if(!head) return nullptr;
        ListNode * p = head;
        ListNode * q = head->next;
        while (q)
        {
            ListNode* tmp = q->next;
            q->next = p;
            p = q;
            q = tmp;
        }
        return p;
    }

    ListNode *reverseList1(ListNode *head)
    {
        if(!head) return nullptr;
        ListNode * p = nullptr;
        ListNode * q = head;
        while (true)
        {
            if(p->next)
            {
                ListNode * r = q->next;
                q->next = p;
                p = q;
                q = r;
                r = r->next;
            }
            else
            {
                break;
            }

        }
        return p;
    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        ListNode *rA = reverseList(headA);
        ListNode *rB = reverseList(headB);
        ListNode *res = nullptr;
        ListNode *rAHead = rA;
        ListNode *rBHead = rB;
        while(rA && rB)
        {
            if(rA == rB)
            {
                res = rA;
            }
            else
            {
                return rA;
            }
            rA = rA->next;
            rB = rB->next;
        }
        reverseList(rAHead);
        reverseList(rBHead);
        return nullptr;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int c = 0;
        int s = 0;
        ListNode *root = nullptr, *tmp = nullptr;
        while(l1 || l2){
            int i = 0, j = 0;
            if(l1){
                i = l1->val;
                l1 = l1->next;
            }
            if(l2){
                j = l2->val;
                l2 = l2->next;
            }
            s = i + j + c;
            c = s / 10;
            s %= 10;
            ListNode *ln = new ListNode(s);
            if(!root){
                tmp = root = ln;
                continue;
            }
            tmp->next = ln;
            tmp = ln;
        }
        if(c){
            tmp->next = new ListNode(c);
        }
        return root;
    }

};

#endif // LISTSOLUTIONS_H
