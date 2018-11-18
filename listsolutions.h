#ifndef LISTSOLUTIONS_H
#define LISTSOLUTIONS_H

#include <vector>
#include <set>
#include <stack>
#include <algorithm>
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


    ListNode* mergeTwoLists2(ListNode* l1, ListNode* l2) {
        if(!l1) return l2;
        if(!l2) return l1;
        ListNode Dummy(0);
        if(l1->val < l2->val)
        {
            Dummy.next = l1;
            l1 = l1->next;
        }
        else
        {
            Dummy.next = l2;
            l2 = l2->next;
        }
        ListNode* cur = Dummy.next;
        while(l1 && l2)
        {
            if(l1->val < l2->val)
            {
                cur->next = l1;
                l1 = l1->next;
            }
            else
            {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        if(l1)
        {
            cur->next = l1;
        }
        if(l2)
        {
            cur->next = l2;
        }
        return Dummy.next;
    }

    ListNode* mergeTwoLists3(ListNode* l1, ListNode* l2)
    {
        if(!l1) return l2;
        if(!l2) return l1;
        ListNode Dummy(0);
        ListNode* tail = &Dummy;
        while(l1 && l2)
        {
            if(l1->val > l2->val) swap(l1, l2);
            tail->next = l1;
            l1 = l1->next;
            tail = tail->next;
        }
        if(l1) tail->next = l1;
        if(l2) tail->next = l2;
        return Dummy.next;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        if(lists.empty()) return NULL;
        if(lists.size() == 1) return lists[0];
        ListNode* mergedList = mergeTwoLists(lists[0], lists[1]);
        for(int i=2; i<lists.size(); ++i)
        {
            mergedList = mergeTwoLists(mergedList, lists[i]);
        }
        return mergedList;
    }

    ListNode* mergeKLists2(vector<ListNode*>& lists)
    {
        if(lists.empty()) return NULL;
        if(lists.size() == 1) return lists[0];
        int interval = 1;
        while(interval < lists.size())
        {
            for(int i=0; i<lists.size(); i += interval+1)
            {
                if(i+interval < lists.size())
                {
                    lists[i] = mergeTwoLists(lists[i], lists[i+interval]);
                }
            }
            interval *= 2;
        }
        return lists[0];
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
        int m = 0;
        ListNode *pA = headA;
        while(pA)
        {
            pA = pA->next;
            m++;
        }

        int n = 0;
        ListNode *pB = headB;
        while(pB)
        {
            pB = pB->next;
            n++;
        }

        if(m > n)
        {
            ListNode *tmp = headA;
            headA = headB;
            headB = tmp;
        }
        int i = abs(m-n);
        pB = headB;
        while(i)
        {
            pB = pB->next;
            --i;
        }

        i = m;
        while(i)
        {
            if(headA == pB)
            {
                return pB;
            }
            headA = headA->next;
            pB = pB->next;
            --i;
        }
        return nullptr;
    }

    ListNode *getIntersectionNode_genius(ListNode *headA, ListNode *headB)
    {
        //List A + List B = List A + inserction + B + (will be meet there)intersection;
        //List B + List A = List B + inserction + A + (will be meet there)intersection;
        ListNode *p1 = headA;
        ListNode *p2 = headB;
        while(p1 != p2)
        {
            p1 = p1==nullptr?headB:p1->next;
            p2 = p2==nullptr?headA:p2->next;
        }
        return p1;
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

    ListNode* swapPairs(ListNode* head)
    {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* cur = &dummy;
        while(cur && cur->next && cur->next)
        {
            //do swap
            ListNode* p1 = cur;
            ListNode* p2 = cur->next;
            head = p2->next;
            p1->next = head;
            p2->next = p1;
        }
        return dummy.next;
    }
    /*
    ListNode* swapPairs(ListNode *head)
    {
        ListNode* dummy = new ListNode(0);
        dummy.next = head;
        ListNode* cur = dummy;
        while (cur != null && cur.next != null && cur.next.next != null)
        {
            cur.next = swap(cur.next, cur.next.next);
            cur = cur.next.next;
        }
        return dummy.next;
    }

    ListNode* swap(ListNode* next1, ListNode* next2)
    {
        next1.next = next2.next; next2.next = next1;
        return next2;
    }
    */
};

#endif // LISTSOLUTIONS_H
