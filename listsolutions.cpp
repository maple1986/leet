#include "listsolutions.h"

ListSolutions::ListSolutions()
{

}

void ListSolutions::test()
{
    ListSolutions lists;
    ListNode* head = new ListNode(1);
    //ListNode* p1 = new ListNode(2);
    //head->next = p1;
    ListNode* head1 = nullptr;
    lists.getIntersectionNode(head, head1);
    int i = 0;
    //p1 = new ListNode(3);
    //head->next = p1;
    //lists.reverseList(head1);
}
