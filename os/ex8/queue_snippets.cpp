#include <iostream>
#include <list>
#include <vector>

/*
Two examples of using the C++ STL to make a queue you can easily iterate over.

Do the exercise however you want (other solutions exist, like circular arrays or
using an actual std::queue) - these are just a couple of suggestions.
*/

int main() {
	// Using a std::vector as a queue
	std::vector<int> vector_queue;
	// Add elements to the back (queue = [1, 2, 3])
	vector_queue.push_back(1);
	vector_queue.push_back(2);
	vector_queue.push_back(3);
	// Remove the first element (1)
	vector_queue.erase(vector_queue.begin());
	// Print the elements sequentially
	for (int message : vector_queue) {
		std::cout << message << ' ';
	}
	std::cout << std::endl;

	// Using a std::list as a queue
	std::list<int> list_queue;
	// Add elements to the back (queue = [4, 5, 6])
	list_queue.push_back(4);
	list_queue.push_back(5);
	list_queue.push_back(6);
	// Remove the first element (4)
	list_queue.pop_front();
	// Print the elements sequentially
	for (int message : list_queue) {
		std::cout << message << ' ';
	}
	std::cout << std::endl;
}
