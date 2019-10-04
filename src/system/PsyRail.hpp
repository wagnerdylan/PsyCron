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

// Forward declarations
template <typename EnvType>
class PsyTrack;

template <typename EnvType>
class PriorityRoutine;

template <typename EnvType>
class TimedRoutine;

template <class RailType, typename EnvType>
class PsyRail{

public:

    virtual void execute() = 0;

    // TODO make this move routine
    void insert_routine(RailType* routine, uint32_t value);

protected:

    PsyRail(PsyTrack<EnvType>* track, uint16_t cap) :
        m_hold_track(track),
        m_cap(cap){}

    PsyTrack<EnvType>* m_hold_track;

    uint16_t m_cap;
    
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

template <typename EnvType>
class PriorityPsyRail final : public PsyRail<PriorityRoutine<EnvType>, EnvType>{

public:

    PriorityPsyRail(PsyTrack<EnvType>* track, uint16_t cap) : 
        PsyRail<PriorityRoutine<EnvType>, EnvType>::PsyRail{track, cap}{};

    void execute(){};

private:

    uint32_t process_value(uint32_t value){};

    void priority_reset(uint32_t rst_max){};

};

template <typename EnvType>
class TimedPsyRail final : public PsyRail<TimedRoutine<EnvType>, EnvType>{

public:

    TimedPsyRail(PsyTrack<EnvType>* track, uint16_t cap) : 
        PsyRail<TimedRoutine<EnvType>, EnvType>::PsyRail{track, cap}{};

    /**
     * Timed rail will execute routines which are hold execution time equal to or behind the
     * actual system time. This is done so timed routines don't miss execution deadlines by
     * significant margins.
     */
    void execute(){};

private:

    uint32_t process_value(uint32_t value){};

    void priority_reset(uint32_t rst_max){};

};

}

#endif