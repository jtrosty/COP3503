
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class SolutionMergeKLists {
    public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
            /*
                merging k amount of linked lits.
                need k pointers for the number of liked lits. 
                make an array of the pointers. iterate thorugh them.  
                need pointer for the final linked list. 
            */
        int k = lists.size();
        ListNode* kList = new ListNode[k];
        ListNode* resultHead = nullptr;
        ListNode* currentResult;
        bool moreNodes = true;

        for (int i = 0; i < k; i++) {
                kList[i] = *lists.at(i);
        }

        while (moreNodes) {
            bool checkIfEnd = false;
            int currentValue;   
            int indexCurrentValue = -1;
            int i = 0;
            for (i = 0; i < k; i++) {
                if (&kList[i] != nullptr) {
                    if (indexCurrentValue == -1) {
                        indexCurrentValue = i;
                        currentValue = (kList[i]).val;
                    }
                    else {
                        if (currentValue > (kList[i]).val) {
                            currentValue = (kList[i]).val;
                            indexCurrentValue = i;
                        }
                    }
                }
            }
            ListNode* tmp = kList[indexCurrentValue].next;
            if (tmp == nullptr) kList[indexCurrentValue] = nullptr;
            else                kList[indexCurrentValue] = *tmp;
            if (&kList[i] == nullptr) checkIfEnd = true;
            if (resultHead == nullptr) {
                resultHead = new ListNode(currentValue);
                currentResult = resultHead;
            }
            else {
                currentResult->next = new ListNode(currentValue);
                currentResult = currentResult->next;
            }
            if (checkIfEnd) {
                for (int i = 0; i < k; i++) {
                    if (&kList[i] != nullptr) checkIfEnd = true;
                }
                if (checkIfEnd == false) moreNodes = false;
            }
        }
        return resultHead;
    }
};

class SolutionCopyRandomList {
    /*
        Copying a linked list, 
        But i can walk through 1 at a time and just copy becauseof th random pointer.  
        The easiest solution could be to go thorugh the list twice, the first time, make all the nodes and set the values
        the second time, assign the random pointers.
        1. use a map for help.
        2. So walk thorugh the list, assign all nodes to a map with the key being hte pointer to the node and the value being the index that they are at.
        3. Then go through the list again and build the index node each random ponter is pointing to.  
        4. Copy all nodes, keep random null initially
        5. As all nodes are copied, keep pointers to all nodes in another data structure, an array.
        6. Go through a last time assigning all the random pointers.
    */
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, int> originalList; 
        Node* current = head;
        Node* result;

        if (head == NULL) {
            return (result = NULL);
        }
        else {
            result = new Node(head->val);
        }
        Node* resultCurrent= result;

        int i = 0;
        // map of pointer and nindex
        while (current != NULL) {
            originalList.emplace(current, i++);
            current = current->next;
        }
        // Now assign indexes
        int* randomIndexes = new int[i];
        Node** newNodes = new Node*[i];

        current = head;
        i = 0;
        while (current != NULL) {
            if (current->random == NULL) {
                randomIndexes[i] = -1;
            }
            else {
                randomIndexes[i] = originalList.at(current->random);
            }
            i++;
            current = current->next;
        }

        // So I can now build the new list
        current = head;
        int test = 0;
        // Copy all the nodes, ignrore random for now
        // Copy all the pointers into an array of Nodes* for the new to help with assigning the rando pointer
        i = 0;
        while (current != NULL) {
            newNodes[i] = resultCurrent;
            Node* nextNode;
            if (current->next == NULL) {
                nextNode = NULL;
            }
            else {
                nextNode = new Node(current->next->val);
            }
            resultCurrent->next = nextNode;
            resultCurrent = resultCurrent->next;
            current = current->next;
            i++;
        }
        // Now assing the random pointers
        resultCurrent = result;
        i = 0;
        while (resultCurrent != NULL) {
            int theRandomIndex = randomIndexes[i];
            if (theRandomIndex == -1) {
                resultCurrent->random = NULL;
            }
            else {
                resultCurrent->random = newNodes[randomIndexes[i]];
            }
            resultCurrent = resultCurrent->next;
            i++;
        }
        return result;
    }
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