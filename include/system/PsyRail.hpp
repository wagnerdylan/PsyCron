
#ifndef PSYRAIL
#define PSYRAIL

#include "../PsyCron.hpp"
#include "../queue"

class PsyRail{

public:

    explicit PsyRail(uint8_t cap);

    void execute();

    void insert_routine(Routine* Routine, uint32_t value);

protected:

    // Overridable function designed to handle scheduling metrics 
    //
    // param: value
    //      The priority multiplyer set by the user
    // return
    //      A calculated priority value
    uint32_t process_value(uint32_t value);

    // Fixes overflowed Routines within the rail
    //
    // param: rst_max
    //      The current max value to be reset
    void priority_reset(uint32_t rst_max);

private:

    priority_queue<Routine, Comparator> sch_queue;

};

#endif