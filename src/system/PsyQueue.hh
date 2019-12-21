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

template<typename T, class Comparator>
class PsyQueue final{

public:

    PsyQueue(size_t cap):
        split_queue{cap}{};

    PrioritySplitQueue<T*, Comparator, PsyCronAllocator > split_queue;
};

}