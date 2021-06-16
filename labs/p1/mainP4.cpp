#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
using namespace std;
//#include "leaker.h"

void TestRemove();
void TestRemoveHeadTail();
void TestOtherRemoval();
void TestRecursion();
void TestRemove2();

int main()
{
   int testNum;
	cin >> testNum;
	if (testNum == 1)
		TestRemove();
   else if (testNum == 2)
      TestRemoveHeadTail();
   else if (testNum == 3)
      TestOtherRemoval();
   else if (testNum == 4)
      TestRecursion();
   else if (testNum == 5)
      TestRemove2(); 
      
	return 0;
}

void TestRemove()
{
	cout << "=====Testing Remove() functionality=====" << endl;
	LinkedList<string> data;
	string test = "Test RemoveMe to RemoveMe find RemoveMe all RemoveMe matching ";
	test.append("RemoveMe nodes RemoveMe completed RemoveMe with RemoveMe no ");
	test.append("RemoveMe \"RemoveMe\" RemoveMe nodes RemoveMe remaining.");
	stringstream x(test);
	string tmp;
	while (getline(x, tmp, ' '))
		data.AddTail(tmp);

	cout << "Initial list: " << endl;
	data.PrintForward();
	string val = "RemoveMe";
	int count = data.Remove(val);
	cout << "\nRemoving " << val << " from the list." << endl;
	cout << "Removed " << count << " nodes from the list.\n" << endl;
	data.PrintForward();
	cout << "\nNodes removed: " << count << endl;

	count = data.Remove(val);
	cout << "Removing " << val << " from the list again." << endl;
	cout << "Nodes removed: " << count << endl;

}

void TestRemove2() {
	LinkedList<int> data;
	data.AddHead(3);
	data.AddHead(1);
	data.AddHead(3);
	data.AddHead(1);
	data.AddHead(1);
	data.AddHead(3);
	data.AddHead(3);
	cout << " node count " << data.NodeCount() << endl;

	//first printout
	data.PrintForward();
	cout << "test remove of 3 " << endl;
	cout << "Nodes removed: " << data.Remove(3) << endl;
	data.PrintForward();
}

void TestRemoveHeadTail()
{
	cout << "=====Testing RemoveHead()/RemoveTail() functionality=====" << endl;
	LinkedList<int> data;
	for (unsigned int i = 0; i < 70; i += 5)
		data.AddTail(i);

	cout << "Initial list: " << endl;
	data.PrintForward();

	cout << "Removing 2 Tail and 2 Head Nodes..." << endl;
	data.RemoveHead();
	data.RemoveTail();
	data.RemoveHead();
	data.RemoveTail();
	data.PrintForward();
}

void TestOtherRemoval()
{
	cout << "=====Testing RemoveAt() and clearing with RemoveHead()/RemoveTail() functionality=====" << endl;
	LinkedList<string> data;
	data.AddTail("Batman");
	data.AddTail("RemoveMe");
	data.AddTail("Superman");
	data.AddTail("RemoveMe");
	data.AddTail("Wonder Woman");
	data.AddTail("RemoveMe");
	data.AddTail("The Flash");

	cout << "Initial list: " << endl;
	data.PrintForward();
	cout << "\nRemoving using RemoveAt()..." << endl;
	data.RemoveAt(1);
	data.RemoveAt(2);
	data.RemoveAt(3);

	data.PrintForward();
	
	cout << "\nAttempting to remove out of range using RemoveAt()..." << endl;
	if (!data.RemoveAt(100))
		cout << "Attempt to RemoveAt(100) failed." << endl;
	else
		cout << "Successfully removed node 100? Weird, there are only 4 nodes..." << endl;

	cout << "\nClearing list using RemoveHead()..." << endl;
	while (data.RemoveHead()){}

	if (data.NodeCount() == 0)
		cout << "List is empty!" << endl;
	else
		cout << "List not empty!" << endl;

	cout << "Adding additional nodes..." << endl;
	data.AddTail("Robin");
	data.AddTail("Batgirl");
	data.AddTail("Nightwing");
	data.AddTail("Red Hood");
	data.AddTail("Bluebird");

	data.PrintForward();

	cout << "Clearing list using RemoveTail()..." << endl;
	while (data.RemoveTail()) {}

	if (data.NodeCount() == 0)
		cout << "List is empty!" << endl;
	else
		cout << "List not empty!" << endl;
}

void TestRecursion()
{
	LinkedList<int> power2;
	int val = 2;
	for (int i = 0; i < 10; i++)
	{
		power2.AddTail(val);
		val *= 2;
	}
	cout << "Initial list: " << endl;
	power2.PrintForward();
	cout << "Printing recursively forward from 64: " << endl;
	LinkedList<int>::Node *node = power2.Find(64);
	power2.PrintForwardRecursive(node);

	cout << "Printing recursively in reverse from 512: " << endl;
	node = power2.Find(512);
	power2.PrintReverseRecursive(node);
}