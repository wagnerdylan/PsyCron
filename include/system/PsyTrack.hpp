#ifndef PSYTRACK_HPP
#define PSYTRACK_HPP

#include "PsyRail.hpp"

namespace psycron {

class PsyCron;
class UIIL;

class PsyTrack{

public:

	PsyTrack(uint16_t cap, PsyCron* os, size_t id) :
		priority_rail(this, cap),
		timed_rail(this, cap),
		hold_os(os),
		id(id){}

    void insert_routine(PriorityRoutine routine, uint32_t value);

    void insert_routine(TimedRoutine routine, uint32_t value);

	UIIL* get_uiil(); 

	size_t id;

private:

	void execute();

	PsyCron* hold_os;

	// The priority rail which regular routines will be placed in.
	PriorityPsyRail priority_rail;

	// The timed rail which timed routines will be placed in.
	TimedPsyRail timed_rail;
};

}

#endif