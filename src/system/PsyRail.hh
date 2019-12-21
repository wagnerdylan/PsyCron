//
// PsyCron
// File: PsyRail.hh
// Author: Dylan R. Wagner (drw6528@rit.edu)
// Description:
//      PsyRail header File.
//

#ifndef PSYRAIL_HH
#define PSYRAIL_HH

#include <stdint.h>

#include "PsyQueue.hh"
#include "Codes.hh"
#include "Macros.hh"

namespace psycron {

// Forward declarations
template <typename EnvType>
class PsyTrack;

template <typename EnvType>
class PriorityRoutine;

template <typename EnvType>
class TimedRoutine;

/**
 * PsyRail interface.
 */
template <class RoutineType, typename EnvType>
class PsyRail{

public:

    virtual void execute() = 0;

protected:

    PsyRail(PsyTrack<EnvType>* track, uint16_t cap) :
        m_hold_track{track},
        m_sch_queue{cap}{}

    PsyTrack<EnvType>* m_hold_track;
    
    // Where all the routines are tracked
    PsyQueue<RoutineType> m_sch_queue;

};


template <typename EnvType>
class PriorityPsyRail final : public PsyRail<PriorityRoutine<EnvType>, EnvType>{

public:

    explicit PriorityPsyRail(PsyTrack<EnvType>* track, uint16_t cap) : 
        PsyRail<PriorityRoutine<EnvType>, EnvType>::PsyRail{track, cap}{};

    void execute(){};
    
    /**
     * Inserts a PriorityRoutine into the PsyQueue, setting the appropiate inital fields.
     * 
     * @param routine The PriorityRoutine to be inserted.
     * @param priority_value The inital priority of the routine.
     */
    void insert_routine(PriorityRoutine<EnvType>* routine, uint16_t id, uint16_t priority_value, bool is_active){
        routine->m_priority_val = priority_value;
        routine->m_id = id;
        routine->m_sch_metric = process_priority(priority_value);
        bool insert_success = this->m_sch_queue.push(routine, is_active);
        
        EASSERT_ABORT(!insert_success, errFAILED_TO_INSERT_ROUTINE);
    };

private:

    /**
     * Used to calculate the value to be used to schedule the PriorityRoutine on insertion and 
     * on every reschedule after execution.
     * 
     * @param priority_value Used to calculate scheduling metric.
     * @return The scheduling metric.
     */
    uint32_t process_priority(uint16_t priority_value){};

    /**
     * Resets the priority for every routine in the queue if a calculated priority value approches
     * it's maximum value.
     */
    void priority_reset(){};

    // Used to keep new routines from blocking other routines.
    uint32_t m_priority_cnt{0};

};


template <typename EnvType>
class TimedPsyRail final : public PsyRail<TimedRoutine<EnvType>, EnvType>{

public:

    explicit TimedPsyRail(PsyTrack<EnvType>* track, uint16_t cap) : 
        PsyRail<TimedRoutine<EnvType>, EnvType>::PsyRail{track, cap}{};

    void insert_routine(TimedRoutine<EnvType>* routine, uint16_t id, uint32_t time_delay, bool is_active){};

    /**
     * Timed rail will execute routines which are hold execution time equal to or behind the
     * actual system time. This is done so timed routines don't miss execution deadlines by
     * significant margins.
     */
    void execute(){};

private:

    uint32_t process_delay(uint32_t time_delay){};

    void time_reset(){};
};

}

#endif
