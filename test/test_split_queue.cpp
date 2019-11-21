/* 
 * File: test_split_queue.cpp
 * Desc:
 * 	Used to test split queue
 * 
 */


#include "PrioritySplitQueue.hh"
#include <iostream>
#include <cassert>


class TestComparator {
public:
	bool operator()(int lhs, int rhs){
		return lhs < rhs;
	}
};

template<typename T>
class TestAllocator {
public:
	T* operator()(size_t size){
		return (T*) malloc(size);
	}
};

int main(){
	PrioritySplitQueue<int, TestComparator, TestAllocator > split_queue(10);
	
	split_queue.push_queue(1);
	split_queue.push_queue(2);
	split_queue.push_queue(3);
        
	assert(split_queue.get_queue_size() == 3);

	assert(split_queue.pop_queue() == 1);
	assert(split_queue.pop_queue() == 2);

	assert(split_queue.get_queue_size() == 1);

	assert(split_queue.push_non_queue(100));
	
	for(int i = 0; i < 8; i++)
		assert(split_queue.push_queue(i));

	for(int i = 0; i < 9; i++)
		std::cout << "pop: " << i << " value: " << split_queue.pop_queue() << std::endl;

	assert(split_queue.get_queue_size() == 0);
	assert(split_queue.get_non_queue_size() == 1);
}
