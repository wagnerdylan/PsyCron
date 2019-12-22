//
// PsyCron
// File: PsyTrack.hh
// Author: Dylan R. Wagner (drw6528@rit.edu)
// Description:
// 		PsyTrack header file.
//

#ifndef PSYTRACK_HH
#define PSYTRACK_HH

#include "PsyRail.hh"

namespace psycron {

class UIIL;

class PsyCron;

void* psyalloc_key_func(size_t size);

class PsyTrackBase{

friend class PsyCron;

public:

	PsyTrackBase(PsyCron* os, uint16_t id) :
		m_hold_os{os},
		m_id{id}
		{}

	UIIL* get_uiil();

	uint16_t m_id;

protected:

	PsyCron* m_hold_os;

private:

	virtual void execute() = 0;

};

template <typename EnvType>
class PsyTrack final: public PsyTrackBase{

public:

	PsyTrack(
		uint16_t id, 
		EnvType&& global_env, 
		PsyCron* os, 
		uint16_t priority_size, 
		uint16_t timed_size
	)
	  : PsyTrackBase{os, id}
	  ,	m_priority_rail{this, priority_size}
	  ,	m_timed_rail{this, timed_size}
	  ,	m_global_env{global_env}
	{}

	inline void *operator new(size_t size){
        return psyalloc_key_func(size);
    }

    inline void insert_routine(PriorityRoutine<EnvType>* routine, uint16_t id, uint16_t value, bool is_active=true){
		m_priority_rail.insert_routine(routine, id, value, is_active);
	};

    inline void insert_routine(TimedRoutine<EnvType>* routine, uint16_t id, uint32_t value, bool is_active=true){
		m_timed_rail.insert_routine(routine, id, value, is_active);
	};

	inline EnvType* get_environment(){
		return &m_global_env;
	};

private:

	void execute(){
		// Do priority, timed rail swapping
		m_priority_rail.execute();
	};

	EnvType m_global_env;

	// The priority rail which regular routines will be placed in.
	PriorityPsyRail<EnvType> m_priority_rail;

	// The timed rail which timed routines will be placed in.
	TimedPsyRail<EnvType> m_timed_rail;
};

}

#endif
