
#ifndef PSYROUTINE_HPP
#define PSYROUTINE_HPP

#include <stdlib.h>

#include "PsyRail.hpp"

namespace psycron {


class PriorityRoutine{

    friend class PsyRail<PriorityRoutine>;

public:

    PriorityRoutine(){};

protected:

    // Adds this routine into the priority rail inside the encapsulating track
    //
    // param: priority_value
    //      The non-negative priority value. lowest(0)- greater ~ higher priority - lower priority
    void add_this_by_priority(uint16_t priority_value);

private:

    // virtual function called when routine is executed
    virtual void run(){};

    PsyRail<PriorityRoutine> *hold_rail;

    // The calculated priority value
    uint32_t sch_metric;

};


class TimedRoutine{

    friend class PsyRail<TimedRoutine>;

public:

	TimedRoutine(uint32_t time_delay)
	: time_delay(time_delay)
	{ // TODO check if time utils are enabled
	}

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
    virtual void run(){};

    PsyRail<TimedRoutine> *hold_rail;

    // The time at which this routine is to be executed in milliseconds
    uint32_t sch_metric;

    // The delay at which this routine is to be executed in milliseconds
    uint32_t time_delay;
};

}

#endif