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

protected:

    /**
     * Used to move 'this' routine to the active state. If already
     * active, do nothing.
     */
    void activate_me(){
        // @TODO
    };

    /**
     * Used to activate another routine in the same track.
     * 
     * @param other_id The id of the other routine to be activated.
     * @return true if other routine was found, false otherwise.
     */
    bool activate_other(uint16_t other_id){
        // @TODO
        return false;
    };

    /**
     * Used to deactive 'this' routine. This routine is not possible to call
     * if already not active.
     */
    void deactivate_me(){
        // @TODO
    };

    /**
     * Used to deactive another routine in the same track.
     * 
     * @param other_id The id of the other routine to be deactivated.
     * @return true if other routine was found, false otherwise.
     */
    bool deactivate_other(uint16_t other_id){
        // @TODO
        return false;
    };

private:

    // virtual function called when routine is executed
    virtual void run() = 0;

    PsyRail<RailType, EnvType>* m_hold_rail;

    // The calculated priority value
    uint32_t m_sch_metric{0};

};


template <typename EnvType>
class PriorityRoutine : public PsyRoutine<PriorityPsyRail<EnvType>, EnvType>{

public:

    PriorityRoutine(){};

private:

    virtual void run() = 0;

    uint16_t m_priority_val{1};

};


template <typename EnvType>
class TimedRoutine : public PsyRoutine<TimedPsyRail<EnvType>, EnvType>{

public:

	TimedRoutine(uint32_t time_delay)
	: m_time_delay(time_delay)
	{ // TODO check if time utils are enabled
	}

private:

    virtual void run() = 0;

    // The delay at which this routine is to be executed in milliseconds
    uint32_t m_time_delay{0};

    // Metric which provides a loose execution time of the routine. This is used to prevent
    // edge hogging.
    uint16_t m_metric_execution_time{0};
};

}

#endif
