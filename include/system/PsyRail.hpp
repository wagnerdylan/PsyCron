
#ifndef PSYRAIL_HPP
#define PSYRAIL_HPP

#include "queue"

class Routine;
class TimedRoutine;
class PsyTrack;

class PsyRail{

public:

    PsyRail(PsyTrack* track, uint16_t cap) :
    hold_track(track),
    cap(cap){}

    void execute();

    void insert_routine(Routine routine, uint32_t value);

    void insert_routine(TimedRoutine routine, uint32_t value);

protected:

    // Overridable function designed to handle scheduling metrics 
    //
    // param: value
    //      The priority multiplyer set by the user
    // return
    //      A calculated priority value
    virtual uint32_t process_value(uint32_t value) = 0;

    // Fixes overflowed Routines within the rail
    //
    // param: rst_max
    //      The current max value to be reset
    virtual void priority_reset(uint32_t rst_max) = 0;

private:

    PsyTrack* hold_track;

    uint16_t cap;

    // The regular priority queue
    //priority_queue<Routine, Comparator> sch_queue;

};

class PriorityPsyRail : PsyRail{

public:

    PriorityPsyRail(PsyTrack* track, uint16_t cap)
    : PsyRail(track, cap){}
};

class TimedPsyRail : PsyRail{

public:

    TimedPsyRail(PsyTrack* track, uint16_t cap)
    : PsyRail(track, cap){}
};

#endif