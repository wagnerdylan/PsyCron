//
// PsyCron
// File: PsyCron.hpp
// Author: Dylan R. Wagner (drw6528@rit.edu)
// Description:
//      PsyCron is a real time operating system designed in compliance with JSF C++
//      ...
//

#ifndef PROJECT_PSYCRON_HPP
#define PROJECT_PSYCRON_HPP

#include <stdint.h>

#include "PsyRoutine.hpp"
#include "UIIL.hpp"
#include "PsyRail.hpp"
#include "PsyUtils.hpp"


class PsyCron {

    friend class PsyRail;

public:

    // Allows user implemented functions to be included into the PsyCron system
    PsyCron(UIIL user_parameters, uint8_t num_rail);

    explicit PsyCron(uint8_t num_rail);

    // Executes one routine within the current track
    void execute();

    void add_rail(PsyRail *rail);

    // Swaps operating execution environments
    //
    // param: index
    //      The index of the track to be swapped in
    void swap_rail(uint8_t index);

private:

    PsyRail *current_rail;
    PsyRail **rail_array;

    UIIL sys_utilities;

    // Used to block any misuse of the PsyCron system in regards to initialization
    bool running;
};

// OS level exceptions which do not exist in embedded applications
extern "C" void __cxa_pure_virtual() { while (1); }

#endif //PROJECT_PSYCRON.H
