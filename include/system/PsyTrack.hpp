#ifndef PSYTRACK_HPP
#define PSYTRACK_HPP

class PriorityPsyRail;
class TimedPsyRail;
class PsyCron;
class UIIL;

class PsyTrack{

public:

	explicit PsyTrack(uint16_t cap, PsyCron& os);

    void insert_routine(Routine routine, uint32_t value);

    void insert_routine(TimedRoutine routine, uint32_t value);

	UIIL* get_uiil(); 

private:

	void execute();

	PsyCron* hold_os;

	// The priority rail which regular routines will be placed in.
	//PriorityPsyRail priority_rail;

	// The timed rail which timed routimes will be placed in.
	//TimedPsyRail timed_rail;
};

#endif