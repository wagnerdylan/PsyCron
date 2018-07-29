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

template <uint8_t tracks>
class PsyCron {
public:

    /**
     * Executes one routine within the current track
     */
    void execute();

    /**
     * Creates a track to be included into the PsyCron system.
     *
     * @param cap
     *      The capacity of the track
     * @return
     *      A new Track object
     */
    Track build_track(uint16_t cap);

private:

    Track* current_track;

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

    /**
     * Virtual function called when routine is executed
     */
    void run() = 0;
private:

    Track* hold_track;
};

#endif //PROJECT_PSYCRON.H
