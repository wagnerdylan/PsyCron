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

template <typename EnvType>
class PriorityPsyRail;

template <typename EnvType>
class TimedPsyRail;

void* psyalloc_key_func(size_t size);


template<typename RailType, typename EnvType>
class PsyRoutine{

public:
    
    inline void *operator new(size_t size){
        return psyalloc_key_func(size);
    };

    uint16_t _id;

    bool _is_active;

// Protected methods are exposed as part of the PsyCron API
protected:

    /**
     * Used to activate another routine in the same track.
     * 
     * @param other_id The id of the other routine to be activated.
     * @return true if other routine was found, false otherwise.
     */
    bool _activate_other(uint16_t other_id){
        return m_hold_rail->activate_routine(other_id);
    };

    /**
     * Used to deactivate 'this' routine. This routine is not possible to call
     * if already not active. When this routine is rescheduled, setting the is_active
     * flag to false will cause this routine to be placed into non heap.
     */
    void _deactivate_me(){
        _is_active = false;
    };

    /**
     * Used to deactivate another routine in the same track.
     * 
     * @param other_id The id of the other routine to be deactivated.
     * @return true if other routine was found, false otherwise.
     */
    bool _deactivate_other(uint16_t other_id){
        return m_hold_rail->deactivate_routine(other_id);
    };

    EnvType& _get_envrionment(){
        return m_hold_rail->get_envrionment();
    }

    // Redefined as private in derived class
    RailType* m_hold_rail;

    // Metric used by the derived routine classes for scheduling
    // Redefined as private in derived class
    uint32_t m_sch_metric{0};
    
private:

    // virtual function called when routine is executed
    virtual void run() = 0;

};


template <typename EnvType>
class PriorityRoutine : public PsyRoutine<PriorityPsyRail<EnvType>, EnvType>{

friend class PriorityPsyRail<EnvType>;

public:

    class Comparator {
    public:
        bool operator()(PriorityRoutine<EnvType>* lhs, PriorityRoutine<EnvType>* rhs){
            return lhs->m_sch_metric < rhs->m_sch_metric;
        }
    };

private:

    using PsyRoutine<PriorityPsyRail<EnvType>, EnvType>::m_sch_metric;
    using PsyRoutine<PriorityPsyRail<EnvType>, EnvType>::m_hold_rail;

    virtual void run() = 0;

    uint16_t m_priority_val{1};

};


template <typename EnvType>
class TimedRoutine : public PsyRoutine<TimedPsyRail<EnvType>, EnvType>{

friend class TimedPsyRail<EnvType>;

public:

    class Comparator {
    public:
        bool operator()(TimedRoutine<EnvType>* lhs, TimedRoutine<EnvType>* rhs){
            // @TODO change this
            return lhs->m_sch_metric < rhs->m_sch_metric;
        }
    };

private:

    using PsyRoutine<TimedPsyRail<EnvType>, EnvType>::m_sch_metric;
    using PsyRoutine<TimedPsyRail<EnvType>, EnvType>::m_hold_rail;

    virtual void run() = 0;

    // The delay at which this routine is to be executed in milliseconds
    uint32_t m_time_delay{0};
    // Used for scheduling, handles issues with user defined time function resetting. 
    uint16_t m_at_reset{0};

    // Metric which provides a loose execution time of the routine. This is used to prevent
    // edge hogging.
    uint8_t m_metric_execution_time{0};
};

}

#endif
