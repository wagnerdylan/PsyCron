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

template <uint8_t num_tracks>
class PsyCron {
public:

    // Allows user implemented functions to be included into the PsyCron system
    explicit PsyCron(UIIL user_parameters);

    PsyCron();

    // Executes one routine within the current track
    void execute();

    // Creates a track to be included into the PsyCron system.
    //
    // param: cap
    //      The capacity of the track
    // return:
    //      A new Track object
    //
    Track build_track(uint16_t cap);

private:

    Track* current_track;
    Track* track_arry[tracks] = {0};

    UIIL sys_utilities = {0};

    // Used to block any misuse of the PsyCron system in regards to initialization
    bool running = false;

    // Swaps operating execution environments
    //
    // param: index_id
    //      The index of the track to be swapped in
    void swap_track(uint8_t index_id);

    friend class Track;
};


template <uint16_t cap>
class Track {
public:

private:

    PsyCron* hold_os;
};


class Routine{
public:

    // Pure virtual function called when routine is executed
    virtual void run() = 0;

protected:

    // Adds this routine into the priority rail inside the encapsulating track
    //
    // param: priority_value
    //      The non-negative priority value. lowest(0)- greater ~ higher priority - lower priority
    void add_this_by_priority(uint16_t priority_value);

    // Adds a specified routine into the priority rail inside the encapsulating track
    //
    // param: rid
    //      Unique id to the routine to be added into the priority rail
    // param: priority_value
    //      The non-negative priority value. lowest(0)- greater ~ higher priority - lower priority
    void add_by_priority(int16_t rid, priority_value);

    // Adds this routine into the micro second rail inside the encapsulating track
    //
    // param: micro_seconds
    //      Time to next execution in micro seconds
    // return:
    //      true: if routine was successfully submitted
    //      false: otherwise
    bool add_this_by_micros(uint32_t micros_seconds);

    // Adds routine into the micro second rail inside the encapsulating track
    //
    // param: rid
    //      Unique id to the routine to be added into the priority rail
    // param: priority_value
    //      The non-negative priority value. lowest(0)- greater ~ higher priority - lower priority
    // return:
    //      true: if routine was successfully submitted
    //      false: otherwise
    bool add_by_micros(int16_t rid, uint32_t micro_seconds);

private:

    Track* hold_track;
};

#endif //PROJECT_PSYCRON.H
