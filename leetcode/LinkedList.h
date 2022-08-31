

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class SolutionReverseK {
    /*
        reverse a subset of the nodes at a time in a linked list
        if k = 2
        rever the frist two nodes, then the second 2 nodes, and so on and so forth.
        1. get the local head and the prev. (special case when workign with the actual head)
        2. Get the local tail and the pointer to next, determin if there are k nodes to flip.
        3. when walk though to tail, buitl arr[k] of poitners to the nodes.  walk though array to flip them.  
            1 >  2 >  3 >  4  > 5  k = 3
          p h         t    n

    */

public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode** tempArr = new ListNode*[k];
        ListNode* localPrev = nullptr;
        ListNode* current = head;
        ListNode* localTail =nullptr;
        ListNode* localTailNext =nullptr;
        bool notEnoughNodes = false;

        // Good to pass a function with the local head and prev

        while (current != nullptr) {
            for (int i = 0; i < k; i++) {
                if (current == nullptr) {
                    notEnoughNodes = true;
                    break;
                }
                tempArr[i] = current;
                current = current->next;
            }
            if (notEnoughNodes) break;
            else {
                localTail = tempArr[k -1];
                localTailNext = tempArr[k - 1]->next;

                if (localPrev == nullptr) {
                    head = localTail;
                }
                else {
                    localPrev->next = localTail;
                }

                for (int i = k - 1; i >= 0; i--) {
                    if (i == k - 1) {}
                    else {
                        localTail->next = tempArr[i];
                        localTail = localTail->next;
                    }
                }
                localTail->next = localTailNext;
                
                // Set up for the next round
                localPrev = localTail;
            }
        }
        delete[] tempArr;
        return head;
    }
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