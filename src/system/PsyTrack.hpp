//
// PsyCron
// File: PsyTrack.hpp
// Author: Dylan R. Wagner (drw6528@rit.edu)
// Description:
// 		PsyTrack header file.
//

#ifndef PSYTRACK_HPP
#define PSYTRACK_HPP

#include "PsyRail.hpp"

namespace psycron {

class PsyCron;
class UIIL;

class PsyTrackBase{

public:

	PsyTrackBase(PsyCron* os, size_t id) :
		m_hold_os{os},
		m_id{id}
		{}

	UIIL* get_uiil();

	size_t m_id;

private:

	virtual void execute() = 0;

	PsyCron* m_hold_os;

};

template <typename EnvType>
class PsyTrack final: public PsyTrackBase{

public:

	PsyTrack(size_t id, EnvType&& global_env, PsyCron* os) :
		PsyTrackBase{os, id},
		m_priority_rail{this},
		m_timed_rail{this},
		m_global_env{global_env}
		{}

	inline void *operator new(size_t size){
        	// TODO Use custom allocator for this
    	}

    	void insert_routine(PriorityRoutine<EnvType>* routine, uint32_t value){
		m_priority_rail.insert_routine(routine, value);
	};

    	void insert_routine(TimedRoutine<EnvType>* routine, uint32_t value){
		m_timed_rail.insert_routine(routine, value);
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
