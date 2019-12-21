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

template<typename RoutineType>
class PsyQueue final{

public:

    PsyQueue(size_t cap):
        m_split_queue{cap}{};

    bool push(RoutineType* routine, bool is_active){
        if(is_active){
            return m_split_queue.push_queue(routine);
        } else {
            return m_split_queue.push_non_queue(routine);
        }
    }

    // Force RoutineType to implement a nested class Comparator
    PrioritySplitQueue<RoutineType*, typename RoutineType::Comparator, PsyCronAllocator> m_split_queue;
};

}