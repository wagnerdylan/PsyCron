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

class PsyCron;
class UIIL;

void* psyalloc_key_func(size_t size);

class PsyTrackBase{

public:

	PsyTrackBase(PsyCron* os, uint16_t id) :
		m_hold_os{os},
		m_id{id}
		{}

	UIIL* get_uiil();

	uint16_t m_id;

private:

	virtual void execute() = 0;

	PsyCron* m_hold_os;

};

template <typename EnvType>
class PsyTrack final: public PsyTrackBase{

public:

	PsyTrack(
		uint16_t id, 
		EnvType&& global_env, 
		PsyCron* os, 
		size_t priority_size, 
		size_t timed_size
	) :
		PsyTrackBase{os, id},
		m_priority_rail{this, priority_size},
		m_timed_rail{this, timed_size},
		m_global_env{global_env}
		{}

	inline void *operator new(size_t size){
        return psyalloc_key_func(size);
    }

    inline void insert_routine(PriorityRoutine<EnvType>* routine, uint16_t value, bool is_active=true){
		m_priority_rail.insert_routine(routine, value, is_active);
	};

    inline void insert_routine(TimedRoutine<EnvType>* routine, uint32_t value, bool is_active=true){
		m_timed_rail.insert_routine(routine, value, is_active);
	};

	inline EnvType* get_environment(){
		return &m_global_env;
	};

private:

	void execute(){};

	EnvType m_global_env;

	// The priority rail which regular routines will be placed in.
	PriorityPsyRail<EnvType> m_priority_rail;

	// The timed rail which timed routines will be placed in.
	TimedPsyRail<EnvType> m_timed_rail;
};

}

#endif
