//
// PsyCron
// File: PsyCron.hpp
// Author: Dylan R. Wagner (drw6528@rit.edu)
// Description:
//      PsyCron is a simplistic soft Run to Completion (RTC) priority and time based scheduler designed for embedded applications. 
//      ...
//

#ifndef PROJECT_PSYCRON_HPP
#define PROJECT_PSYCRON_HPP

#include <stdint.h>

#include "PsyRoutine.hpp"
#include "UIIL.hpp"
#include "PsyTrack.hpp"

namespace psycron {

class PsyCron {

    friend class PsyTrack;

public:

    // Allows user implemented functions to be included into the PsyCron system
    PsyCron(UIIL user_parameters, uint8_t num_track);

    explicit PsyCron(uint8_t num_track);

    // Executes one routine within the current track
    void execute();

    PsyTrack* create_add_track(uint16_t cap);

    // Swaps operating execution environments
    //
    // param: index
    //      The index of the track to be swapped in
    void swap_track(uint8_t index);

private:

    PsyTrack *current_track;
    PsyTrack **rail_track;

    UIIL sys_utilities;

    // Used to block any misuse of the PsyCron system in regards to initialization
    bool running;
};

}

// OS level exceptions which do not exist in embedded applications
extern "C" void __cxa_pure_virtual() { while (1); }

#endif //PROJECT_PSYCRON.H
