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

    inline bool deactivate_routine(uint16_t id){
        return m_hold_track->deactivate_routine(id);
    }

    inline bool activate_routine(uint16_t id){
        return m_hold_track->activate_routine(id);
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
            RoutineType* routine = m_sch_queue.m_split_queue.remove_queue(find_result.index);
            if(routine == nullptr) return false;
            
            routine->_is_active = false;
            schedule_routine(routine);
        }

        return find_result.was_found;
    }

    /**
     * Used to activate a routine in the non_heap if it can be found there.
     * 
     * @param id ID of the routine to be deactivated.
     * @return True if requested routine to be activated can be found, false otherwise.
     */
    bool activate_rail_routine(uint16_t id){
        FindResult find_result = m_sch_queue.find_non_active(id);

        if(find_result.was_found){
            RoutineType* routine = m_sch_queue.m_split_queue.remove_non_queue(find_result.index);
            if(routine == nullptr) return false;

            routine->_is_active = true;
            schedule_routine(routine);
        }

        return find_result.was_found;
    }

protected:

    PsyRail(PsyTrack<EnvType>* track, uint16_t cap) :
        m_hold_track{track},
        m_sch_queue{cap}
    {}

    PsyTrack<EnvType>* m_hold_track;
    
    // Where all the routines are tracked
    PsyQueue<RoutineType> m_sch_queue;

private:

    virtual void schedule_routine(RoutineType* routine) = 0;

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
            schedule_routine(current_routine);

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
     * Schedules a routine, inserting into the queue.
     * 
     * @param routine The routine to be scheduled.
     */
    void schedule_routine(PriorityRoutine<EnvType>* routine){
        routine->m_sch_metric = process_priority(routine->m_priority_val);
        // A push in this context is guaranteed to never fail. 
        this->m_sch_queue.push(routine, routine->_is_active);
    }

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
     * it's maximum value.
     */
    void priority_reset(){
        
        if(this->m_sch_queue.m_split_queue.get_queue_size() == 0){
            m_priority_cnt = 0;
            return;
        }

        PriorityRoutine<EnvType>* top_routine = this->m_sch_queue.m_split_queue.top();
        // Wait till we get a routine which isn't a special case.
        if(top_routine->m_sch_metric == 0) return;

        for(uint16_t i{0}; i < this->m_sch_queue.m_split_queue.get_queue_size(); i++){
            this->m_sch_queue.m_split_queue.peek_heap()[i]->m_sch_metric -= top_routine->m_sch_metric;
        }

        m_priority_cnt = 0;
    };

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

    /**
     * Schedules a routine, inserting into the queue.
     * 
     * @param routine The routine to be scheduled.
     */
    void schedule_routine(TimedRoutine<EnvType>* routine){
        process_time();
        routine->m_sch_metric = m_last_time_pulled;
        routine->m_at_reset = m_reset_cnt;
        // A push in this context is guaranteed to never fail. 
        this->m_sch_queue.push(routine, routine->_is_active);
    };

    void process_time(){
        uint32_t current_time = this->m_hold_track->get_user_parameters().sys_milli_second();

        // User defined millisecond function was reset
        if(current_time < m_last_time_pulled){
            reset_cnt += 1;
        }

        m_last_time_pulled = current_time;
    }

    uint16_t m_reset_cnt{0};

    uint32_t m_last_time_pulled{0};
};

}

#endif
