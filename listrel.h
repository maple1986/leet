#ifndef LISTREL_H
#define LISTREL_H

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class ListRel
{
public:
    ListRel();
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

#endif // LISTREL_H
