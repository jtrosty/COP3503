#include <iostream>
#include "ABQ.h"
using namespace std;

int main()
{
cout << "Making integer ABQ...\n";
	ABQ<int> intABQ;
	cout << "Size: " << intABQ.getSize() << endl;
	cout << "Max Capacity: " << intABQ.getMaxCapacity() << endl;
	cout << "\nEnqueueing items...\n";
/*	
	for (int i = 1; i < 10; i++)
	{
		intABQ.enqueue(i);
		cout << "\nEnqueued " << i << endl;
		cout << "New Size: " << intABQ.getSize() << endl;
		cout << "New Max Capacity: " << intABQ.getMaxCapacity() << endl;
	}
	*/
	return 0;
}