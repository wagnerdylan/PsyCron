/**
 * File: PrioritySplitQueue.hh
 * Organization: RIT Space Exploration
 * Author: Dylan Wagner (drw6528@rit.edu)
 * Description:
 *	    Priority Split Queue implementation using a heap.
 */

#include <stdlib.h>

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (uint16_t) (x - 1) / 2
#define START 0

template <typename T, class Compare, template<typename> class Allocator>
class PrioritySplitQueue {
public:

    explicit PrioritySplitQueue(uint16_t cap) : 
        capacity{cap},
        queue_size{0},
        non_queue_size{0}
    {   
	    Allocator<T> allocator;
        heap_array = allocator(capacity * sizeof(T));
    }

    /**
     * Remove first element from the priority queue
     *
     * @return the fisrt element from the priority queue
     */
    T pop_queue(){
        if(!queue_size) return NULL; // If array is empty return default

        T root = heap_array[START];
        heap_array[START] = heap_array[queue_size - 1];
        queue_size -= 1;

        sift_down(START);

        return root;
    }

    /**
     * Grab the first element in the priority queue and return it
     * @return
     *      First element in the priority queue if queue_size > 0
     *      Default element id queue size is 0
     */
    T top(){
        if(queue_size > 0) return heap_array[START];
	    return NULL;
    }

    /**
     * Push a element onto the priority queue.
     *
     * @param element The element to be inserted.
     * @return true on success, false on failue
     */
    bool push_queue(T element){

        if (hit_capacity()) return false;

        heap_array[queue_size] = element;

        sift_up(queue_size);

        queue_size += 1;

	    return true;
    }

    /**
     * Push a element onto the non queue segment
     *
     * @param element The element to be inserted.
     * @return true on success, false on failure
     */
    bool push_non_queue(T element){
	
        if (hit_capacity()) return false;

        non_queue_size += 1;
        heap_array[capacity - non_queue_size] = element;

	    return true;
    }

    /**
     * Return the size of the split priority queue
     * @return
     *      Size of priority queue.
     */
    uint16_t size(){
        return queue_size + non_queue_size;
    }

    /**
     * Return the size of the heap segment
     * @return size of heap segment
     */
    uint16_t get_queue_size(){
        return queue_size;
    }

    /**
     * Return the size of the non heap segment
     * @return size of non heap segment
     */
    uint16_t get_non_queue_size(){
        return non_queue_size;
    }

    uint16_t get_capacity(){
        return capacity;
    }

    /**
     * Return the heap
     * @return
     *      The heap
     */
    T* peek_heap(){
        return heap_array;
    }

private:

    /**
     * Checks if heap has hit max size.
     * @return
     *      TRUE: if size is greater than capacity
     *      FALSE: if size is less than capacity
     */
    bool hit_capacity(){
        return queue_size + non_queue_size >= capacity;
    }

    /**
     * Swap two elements in the array
     * @param s1
     *      first element index
     * @param s2
     *      second element index
     */
    void swap(const uint16_t s1, const uint16_t s2){
        T temp = heap_array[s1];
        heap_array[s1] = heap_array[s2];
        heap_array[s2] = temp;
    }
    
    /**
     * Sift up heap operation
     *
     * @param dec_cnt index to start the sift up operation
     */
    void sift_up(uint16_t dec_cnt){
        
	while (dec_cnt > 0 && compare(heap_array[dec_cnt], heap_array[PARENT(dec_cnt)])){
            swap(dec_cnt, PARENT(dec_cnt));
            dec_cnt = PARENT(dec_cnt);
        }
    }
    
    /**
     * Sift down heap operation
     *
     * @param cnt starting index for sift down heap operation
     */
    void sift_down(uint16_t cnt){
        
        while (cnt < queue_size){

            uint16_t lchild = cnt, rchild = cnt;

            if(LCHILD(cnt) < queue_size) lchild = LCHILD(cnt);
            if(RCHILD(cnt) < queue_size) rchild = RCHILD(cnt);

            if(lchild == rchild) break;

            if(compare(heap_array[lchild], heap_array[rchild])){
                swap(cnt, lchild);
                cnt = lchild;
            } else {
                if(rchild == cnt) break;
                swap(cnt, rchild);
                cnt = rchild;
            }
        }

    }

    // Number of current elements in the queue.
    uint16_t queue_size;
    uint16_t non_queue_size;
    uint16_t capacity;

    // Min-Heap array
    T* heap_array;

    // Compare object for two objects
    Compare compare;
};
