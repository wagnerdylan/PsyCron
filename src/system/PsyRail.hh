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

    EnvType& get_envrionment(){
        return m_hold_track->get_environment();
    }

protected:

    PsyRail(PsyTrack<EnvType>* track, uint16_t cap) :
        m_hold_track{track},
        m_sch_queue{cap}
    {}

    inline bool deactivate_routine(uint16_t id){
        // @TODO call method in track which tries to deactivate in all rails
        return false;
    }

    /**
     * Used to deactivate a routine in the heap if it can be found there.
     * 
     * @param id Id of the routine to be deactivated.
     * @return True if requested routine to be deactivated can be found, false otherwise.
     */
    bool deactivate_rail_routine(uint16_t id){
        FindResult find_result = m_sch_queue.find_active(id);

        if(find_result.was_found){
            // @TODO Good call pop method in sch_queue then push non queue method in sch_queue
        }

        return find_result.was_found;
    }

    PsyTrack<EnvType>* m_hold_track;
    
    // Where all the routines are tracked
    PsyQueue<RoutineType> m_sch_queue;

};


template <typename EnvType>
class PriorityPsyRail final : public PsyRail<PriorityRoutine<EnvType>, EnvType>{

public:

    explicit PriorityPsyRail(PsyTrack<EnvType>* track, uint16_t cap) : 
        PsyRail<PriorityRoutine<EnvType>, EnvType>::PsyRail{track, cap}{};

    /**
     * Executes the top routine on the priority queue, setting and rescheduling 
     * the routine.
     */
    void execute(){
        PriorityRoutine<EnvType>* current_routine = this->m_sch_queue.m_split_queue.pop_queue();
        
        if(current_routine != nullptr){
            // Call run on routine, push back into PsyQueue
            current_routine->run();
            current_routine->m_sch_metric = process_priority(current_routine->m_priority_val);
            // A push in this context is guaranteed to never fail. 
            this->m_sch_queue.push(current_routine, current_routine->_is_active);

            m_priority_cnt += 1;
        }

    };
    
    /**
     * Inserts a PriorityRoutine into the PsyQueue, setting the appropiate inital fields.
     * 
     * @param routine The PriorityRoutine to be inserted.
     * @param priority_value The inital priority of the routine.
     */
    void insert_routine(PriorityRoutine<EnvType>* routine, uint16_t id, uint16_t priority_val, bool is_active){
        routine->m_hold_rail = this;
        routine->m_priority_val = priority_val;
        routine->_id = id;
        routine->_is_active = is_active;
        routine->m_sch_metric = process_priority(routine->m_priority_val);
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
    uint32_t process_priority(uint16_t priority_value){

        // Handle special condition
        if(priority_value == 0) return uint32_t{0};

        uint32_t calc_priority_value = m_priority_cnt + priority_value * 2;

        if(calc_priority_value >= UINT32_MAX){
            priority_reset();
            // This is the same calculation as above
            calc_priority_value = m_priority_cnt + priority_value * 2;
        }

        return calc_priority_value;
    };

    /**
     * Resets the priority for every routine in the queue if a calculated priority value approches
     * it's maximum value. This function will never fail.
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
