//
// PsyCron
// File: PsyRoutine.hh
// Author: Dylan R. Wagner (drw6528@rit.edu)
// Description:
//      PsyRoutine header file. Defines the routine classes inherited by users.
//

#ifndef PSYROUTINE_HH
#define PSYROUTINE_HH

#include <stddef.h>

namespace psycron {

// Forward declaration 
template <class RailType, typename EnvType>
class PsyRail;

void* psyalloc_key_func(size_t size);

template <typename EnvType>
class PriorityRoutine{

    friend class PsyRail<PriorityRoutine, EnvType>;

public:

    PriorityRoutine(){};

    inline void *operator new(size_t size){
        return psyalloc_key_func(size);
    };

protected:

    // Adds this routine into the priority rail inside the encapsulating track
    //
    // param: priority_value
    //      The non-negative priority value. lowest(0)- greater ~ higher priority - lower priority
    void add_this_by_priority(uint16_t priority_value);

private:

    // virtual function called when routine is executed
    virtual void run() = 0;

    PsyRail<PriorityRoutine, EnvType>* m_hold_rail;

    // The calculated priority value
    uint32_t m_sch_metric;

};

template <typename EnvType>
class TimedRoutine{

    friend class PsyRail<TimedRoutine, EnvType>;

public:

	TimedRoutine(uint32_t time_delay)
	: m_time_delay(time_delay)
	{ // TODO check if time utils are enabled
	}

    inline void *operator new(size_t size){
        return psyalloc_key_func(size);
    };

protected:

    // Adds this routine into the timed second rail inside the encapsulating track
    //
    // param: milli_seconds
    //      Time to next execution in milli seconds
    // return:
    //      true: if routine was successfully submitted
    //      false: otherwise
    bool add_this_by_milli(uint32_t milli_seconds);

private:

    // virtual function called when routine is executed
    virtual void run() = 0;

    PsyRail<TimedRoutine, EnvType>* m_hold_rail;

    // The time at which this routine is to be executed in milliseconds
    uint32_t m_sch_metric;

    // The delay at which this routine is to be executed in milliseconds
    uint32_t m_time_delay;
};

}

#endif
