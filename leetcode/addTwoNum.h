#include <stddef.h>

class SolutionAddTwoNumbers {
public:

    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* current1 = l1;
        ListNode* current2 = l2;
        ListNode* resultList = l1;
        ListNode* resultListCurrent = l1;
        int resultVal = 0;
        char active1 = 0;
        char active2 = 0;
        if (l1 != nullptr) active1 = 1;
        if (l2 != nullptr) active2 = 1;
        char isGreaterThanTen = 0;
        

        while (active1 || active2) {
            // are both lists still going are is is one down
            if (active1 && active2) {
                resultVal = current1->val + current2->val;
            }
            else if (active1 && !active2) {
                resultVal = current1->val;
            }
            else {
                resultVal = current2->val;
            }
            
            // If the digits add to ten, carry that to next digit
            if (isGreaterThanTen) resultVal++;
            
            if (resultVal > 9) {
                isGreaterThanTen = 1;
                resultVal = resultVal % 10;
            }
            else {
                isGreaterThanTen = 0;
            }

            // handle making the result
            resultListCurrent->val = resultVal;
            if (isGreaterThanTen && resultListCurrent->next == nullptr && current2->next == nullptr)  {
                resultListCurrent->next = new ListNode(1);
                active1 = 0;
            }
            resultListCurrent = resultListCurrent->next;

            // Code to handle if the linked list is still active
            if (active1) current1 = current1->next;
            //else if (current1->next == nullptr) current1->next = new ListNode(1);
            if (active2) current2 = current2->next;

            if (current1 == nullptr) {
                active1 = 0;
                current1 = current2;
                resultListCurrent = current2;
            }
            if (current2 == nullptr) active2 = 0;

        }
        return resultList;
    }
};