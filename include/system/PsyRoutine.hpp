
#ifndef PSYROUTINE_HPP
#define PSYROUTINE_HPP

#include <stdlib.h>

class PsyRail;

class Routine{

    friend class PsyRail;

public:

    inline void *operator new(size_t size){
        return malloc(size);
    };

protected:

    // Adds this routine into the priority rail inside the encapsulating track
    //
    // param: priority_value
    //      The non-negative priority value. lowest(0)- greater ~ higher priority - lower priority
    void add_this_by_priority(uint16_t priority_value);

private:

    // Pure virtual function called when routine is executed
    virtual void run() = 0;

    PsyRail *hold_rail;

    // The calculated priority value
    uint32_t sch_metric;

};


class TimedRoutine{

    friend class PsyRail;

public:

    inline void *operator new(size_t size){
        return malloc(size);
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

    // Pure virtual function called when routine is executed
    virtual void run() = 0;

    PsyRail *hold_rail;

    // The time at which this routime is to be executed in milliseconds
    uint32_t sch_metric;

    // The delay at which this routime is to be executed in milliseconds
    uint32_t time_delay;
};

#endif