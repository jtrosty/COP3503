#include <stdio.h>
#include "addTwoNum.h"


int main(void) {
    SolutionAddTwoNumbers solAddTwoNum;
    SolutionAddTwoNumbers::ListNode* list1 = new SolutionAddTwoNumbers::ListNode(9);
    SolutionAddTwoNumbers::ListNode* list2 = new SolutionAddTwoNumbers::ListNode(9);
    SolutionAddTwoNumbers::ListNode* result;

    result = solAddTwoNum.addTwoNumbers(list1, list2);

    while (result != nullptr) {
        printf("%i ", result->val);
        result = result->next;
    }
    printf("\n");
    printf("iok\n");

    return 0;
}