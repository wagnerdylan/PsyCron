//
// PsyCron
// File: PsyRail.hpp
// Author: Dylan R. Wagner (drw6528@rit.edu)
// Description:
//      PsyRail header File.
//

#ifndef PSYRAIL_HPP
#define PSYRAIL_HPP

#include <stdint.h>

#include "queue"

namespace psycron {

class PriorityRoutine;
class TimedRoutine;
class PsyTrack;

template <class RailType>
class PsyRail{

public:

    virtual void execute() = 0;

    // TODO make this move routine
    void insert_routine(RailType routine, uint32_t value);

protected:

    PsyRail(PsyTrack* track, uint16_t cap) :
        hold_track(track),
        cap(cap){}

    PsyTrack* hold_track;

    uint16_t cap;
    
    //priority_queue<RailType, Comparator> sch_queue;
    
private:

    /** 
     * Overridable function designed to handle scheduling metrics
     *
     * @param value The priority multiplier set by the user
     * @return A calculated priority value
     */
    virtual uint32_t process_value(uint32_t value) = 0;

    /**
     * Fixes overflowed Routines within the rail
     *
     * @param rst_max The current max value to be reset
     */
    virtual void priority_reset(uint32_t rst_max) = 0;

};

class PriorityPsyRail : public PsyRail<PriorityRoutine>{

public:

    PriorityPsyRail(PsyTrack* track, uint16_t cap) : 
        PsyRail(track, cap){};

    void execute();

private:

    uint32_t process_value(uint32_t value);

    void priority_reset(uint32_t rst_max);

};

class TimedPsyRail : public PsyRail<TimedRoutine>{

public:

    TimedPsyRail(PsyTrack* track, uint16_t cap) : 
        PsyRail(track, cap){};

    /**
     * Timed rail will execute routines which are hold execution time equal to or behind the
     * actual system time. This is done so timed routines don't miss execution deadlines by
     * significant margins.
     */
    void execute();

private:

    uint32_t process_value(uint32_t value);

    void priority_reset(uint32_t rst_max);

};

}

#endif