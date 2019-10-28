//
// PsyCron
// File: PsyCron.hh
// Author: Dylan R. Wagner (drw6528@rit.edu)
// Description:
//      PsyCron is a simplistic soft Run to Completion (RTC) priority and time based scheduler designed for embedded applications. 
//      ...
//

#ifndef PROJECT_PSYCRON_HH
#define PROJECT_PSYCRON_HH

#include <stdint.h>
#include <stdlib.h>
#include <iostream>

#include "PsyRoutine.hh"
#include "UIIL.hh"
#include "PsyTrack.hh"

namespace psycron {

class PsyCron {

    friend class PsyTrackBase;

public:
 
    explicit PsyCron(uint16_t track_cap):
	    m_current_track{nullptr},
	    m_user_parameters{},
	    m_track_cap{track_cap},
	    m_num_track_cnt{0}{
            running = false;
            m_rail_track = (PsyTrackBase**) psyalloc(track_cap * sizeof(PsyTrackBase*));
        };
    
    // Allows user implemented functions to be included into the PsyCron system
    PsyCron(UIIL user_parameters, uint16_t track_cap):
        PsyCron(track_cap){
            m_user_parameters = user_parameters;
    };

    // Executes one routine within the current track
    void execute();

    template<typename EnvType>
    PsyTrack<EnvType>* add_track(size_t id, EnvType& global_env){
        PsyTrack<EnvType>* track = 
            new PsyTrack<EnvType>(id, (EnvType&&) global_env, this);
        m_rail_track[m_num_track_cnt++] = track;

        return track;
    }

    /**
     * Swaps operating execution environments
     *
     * @param[in] index The index of the track to be swapped in.
     */
    void swap_track(uint8_t index);

    static void* psyalloc(size_t size){
        static size_t bytes_used = 0;

        if(running || (bytes_used + size) > PSYCRON_BUFFER_SIZE){
            abort();
        }

        void* ptr_to_start = (void*) &psyalloc_buffer[bytes_used];
        bytes_used += size;

        std::cout << "Allocated total: " << bytes_used << " bytes" << std::endl;

        return ptr_to_start;
    }

private:

    PsyTrackBase* m_current_track;
    PsyTrackBase** m_rail_track;

    UIIL m_user_parameters;

    // Used to block any misuse of the PsyCron system in regards to initialization
    static bool running;

    uint16_t m_track_cap;
    uint16_t m_num_track_cnt;
        
    static unsigned char psyalloc_buffer[];
};

void* psyalloc_key_func(size_t size);

}

#endif //PROJECT_PSYCRON.H
