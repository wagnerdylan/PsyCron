//
// PsyCron
// File: PsyCron.h
// Author: Dylan R. Wagner (drw6528@rit.edu)
// Description:
//      PsyCron is a real time operating system designed in compliance with JSF C++
//      ...
//

#ifndef PROJECT_PSYCRON_H
#define PROJECT_PSYCRON_H

#include <stdint.h>
#include "../lib/queue"
#include "usr/UIIL.hpp"

class PsyCron;
class Routine;

class PsyTrack {
public:

    void *operator new(size_t size);

    void add_routine(Routine *routine);

    int execute();

private:

    PsyCron *hold_os;
};


class PsyCron {

    friend class Track;

public:

    // Allows user implemented functions to be included into the PsyCron system
    PsyCron(UIIL user_parameters, uint8_t num_tracks);

    explicit PsyCron(uint8_t num_tracks);

    // Executes one routine within the current track
    void execute();

    void add_track(PsyTrack *track);

    // Swaps operating execution environments
    //
    // param: index_id
    //      The index of the track to be swapped in
    void swap_track(char *name);

private:

    PsyTrack *current_track;
    PsyTrack **track_arry;

    UIIL sys_utilities;

    // Used to block any misuse of the PsyCron system in regards to initialization
    bool running;
};


class Routine{

    friend class PsyTrack;

public:

    // Pure virtual function called when routine is executed
    virtual void run() = 0;

    inline void *operator new(size_t size){
        return malloc(size);
    }

protected:

    // Adds this routine into the priority rail inside the encapsulating track
    //
    // param: priority_value
    //      The non-negative priority value. lowest(0)- greater ~ higher priority - lower priority
    void add_this_by_priority(uint16_t priority_value);


    // Adds this routine into the micro second rail inside the encapsulating track
    //
    // param: micro_seconds
    //      Time to next execution in micro seconds
    // return:
    //      true: if routine was successfully submitted
    //      false: otherwise
    bool add_this_by_micros(uint32_t micros_seconds);


    // Adds this routine into the milli second rail inside the encapsulating track
    //
    // param: milli_seconds
    //      Time to next execution in milli seconds
    // return:
    //      true: if routine was successfully submitted
    //      false: otherwise
    bool add_this_by_milli(uint32_t milli_seconds);

private:

    PsyTrack *hold_track;

    uint32_t priority_value;

};

// OS level exceptions which do not exist in embedded applications
extern "C" void __cxa_pure_virtual() { while (1); }

#endif //PROJECT_PSYCRON.H
