

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class SolutionMergeTwoLists {
    /*
        Merge two sorted linked lits. Use no additional nodes.
        Need to walk down both and compare nodes.  
        1. pointer to each head.
        1.1 determien starting node. then the starting node will be the new head. Advance pointer from starting node
        2. Compare
        3. The smaller one points to the larger node. Advance the smaller nodes pointer. 
        
         
    */

public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* currOne = list1;
        ListNode* currTwo = list2;
        ListNode* prevResult = nullptr;
        ListNode* resultHead = nullptr;
        
        if  ( list1 == nullptr && list2 == nullptr) {
            return resultHead;
        }
        else if (list1 == nullptr && list2 != nullptr) {
            return list2;
        }
        else if (list1 != nullptr && list2 == nullptr) {
            return list1;
        }


        // Determine head, advance pointer from head.
        if (currOne->val < currTwo->val) {
            resultHead = currOne;
            currOne = currOne->next;
        }
        else {
            resultHead = currTwo;
            currTwo = currTwo->next;
        }
        prevResult = resultHead;
        //Common case 
        while (currOne != nullptr && currTwo != nullptr) {
            if (currOne->val < currTwo->val) {
                prevResult->next = currOne;
                prevResult = currOne;
                currOne = currOne->next;
            }
            else {
                prevResult->next = currTwo;
                prevResult = currTwo;
                currTwo = currTwo->next;
            }
        }
        if (currOne == nullptr) {
            prevResult->next = currTwo;
        }
        else {
            prevResult->next = currOne;
        }
        return resultHead;
    }
};