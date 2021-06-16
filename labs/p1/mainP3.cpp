#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
using namespace std;
#include "leaker.h"

void TestInsertBeforeAfter();
void TestInsertAt();

int main()
{
	int testNum;
	cin >> testNum;
	if (testNum == 1)
		TestInsertBeforeAfter();
	else if (testNum == 2)
	   TestInsertAt();
	return 0;
}

void TestInsertBeforeAfter()
{
   	LinkedList<int> data;
	data.AddTail(10);
	data.AddHead(9);
	data.AddTail(11);
	data.AddHead(8);
	data.AddTail(12);
	
	cout << "Initial list: " << endl;
	data.PrintForward();

	LinkedList<int>::Node * node = data.Find(10);
	cout << "\nSearching for node with value of 10..." << endl;

	if (node != nullptr)
	{
		cout << "Node found! Value: " << node->data << endl;
		cout << "Prev value: " << node->prev->data << endl;
		cout << "Next value: " << node->next->data << endl;
	}
	else
		cout << "Error! Returned node was a nullptr.";

	cout << "\nInserting 2048 before node and 4096 after node." << endl;
	data.InsertBefore(node, 2048);
	data.InsertAfter(node, 4096);
	data.PrintForward();
}

void TestInsertAt()
{
	cout << "=====Testing InsertAt() functionality=====" << endl;
	LinkedList<string> data;
	string test = "great benefit linked is the ability to easily into the";
	stringstream x(test);
	string tmp;
	while (getline(x, tmp, ' '))
		data.AddTail(tmp);

	cout << "Initial list: " << endl;
	data.PrintForward();
	cout << "Node count: " <<  data.NodeCount() << endl;

	cout << "\nInserting words into the list with InsertAt()..." << endl;

	data.InsertAt("One", 0);
	cout << "Node count: " <<  data.NodeCount() << endl;
	data.InsertAt("of", 3);
	cout << "Node count: " <<  data.NodeCount() << endl;
	data.InsertAt("lists", 5);
	cout << "Node count: " <<  data.NodeCount() << endl;
	data.InsertAt("insert", 10);
	cout << "Node count: " <<  data.NodeCount() << endl;
	data.InsertAt("nodes", 11);
	cout << "Node count: " <<  data.NodeCount() << endl;
	data.InsertAt("list.", 15);
	cout << "Node count last: " <<  data.NodeCount() << endl;

	data.PrintForward();
	cout << "Node count: " << data.NodeCount() << endl;
	cout << "Recursive: " << endl;
	data.PrintForwardRecursive(data.GetNode(7));
	cout << "Recursive reverse: " << endl;
	data.PrintReverseRecursive(data.GetNode(7));
}