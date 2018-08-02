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

class PsyTrack {
public:

    // Used to display debug error messages
    //
    // param: error
    //      The error message to be displayed
    void sys_display_error(char* error);

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

    // Creates a track to be included into the PsyCron system.
    //
    // param: cap
    //      The capacity of the track
    // return:
    //      A new Track object
    //
    PsyTrack *build_track(uint16_t cap);

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

    friend class Track;

public:

    // Pure virtual function called when routine is executed
    virtual void run() = 0;

    void *operator new(size_t size);

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


    // Calls the system error function
    //
    // param: error
    //      The error message to be displayed
    void sys_display_error(char* error);

private:

    PsyTrack *hold_track;

};

#endif //PROJECT_PSYCRON.H
