/**
 * File: PsyQueue.hh
 * Organization: RIT Space Exploration
 * Author: Dylan Wagner (drw6528@rit.edu)
 * Description:
 *	    Wrapper around a split priority queue used for psycron specific 
 *      functionality. 
 */

#include "PrioritySplitQueue.hh"

namespace psycron
{

template<typename T>
class PsyCronAllocator;

struct FindResult{
    bool was_found{false};
    uint16_t index{0};
};

template<typename RoutineType>
class PsyQueue final{

public:

    PsyQueue(uint16_t cap):
        m_split_queue{cap}{};

    /**
     * Pushes a routine into the appropiate section of the split queue.
     * Active routines are placed into the heap area of the split queue and non active
     * routines are placed into the non-queue section of the split queue.
     * 
     * @param routine The routine to be inserted.
     * @param is_active Used to determine where the routine is placed.
     * @return True is push was successfull, false otherwise.
     */
    bool push(RoutineType* routine, const bool is_active){
        if(is_active){
            return m_split_queue.push_queue(routine);
        } else {
            return m_split_queue.push_non_queue(routine);
        }
    }

    // Force RoutineType to implement a nested class Comparator
    PrioritySplitQueue<RoutineType*, typename RoutineType::Comparator, PsyCronAllocator> m_split_queue;

    /**
     * Finds a routine in the queue with the provided id.
     * 
     * @param id The id of the routine to be found.
     * @return A struct contiaing the results of the search.
     */ 
    FindResult find_active(const uint16_t id){
        FindResult result{};

        for(uint16_t i = 0; i < m_split_queue.queue_size; i++){
            if(m_split_queue.peek_heap()[i]->id_ == id){
                result.was_found = true;
                result.index = i;
                break;
            }
        }

        return result;
    }

    /**
     * Finds a routine in the non queue with the provided id.
     * 
     * @param id The id of the routine to be found.
     * @return A struct contiaing the results of the search.
     */ 
    FindResult find_non_active(const uint16_t id){
        FindResult result{};

        for(uint16_t i = m_split_queue.get_capacity() - 1; 
            i >= m_split_queue.get_capacity() - m_split_queue.get_non_queue_size(); 
            i--
        ){
            if(m_split_queue.peek_heap()[i]->id_ == id){
                result.was_found = true;
                result.index = i;
                break;
            }
        }

        return result;
    }

};

}