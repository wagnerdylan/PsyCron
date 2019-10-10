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

    	friend class PsyTrackBase;

public:
 
    explicit PsyCron(size_t track_cap):
	    m_current_track{nullptr},
	    m_user_parameters{},
	    m_running{false},
	    m_track_cap{track_cap},
	    m_num_track_cnt{0}{};
    
    // Allows user implemented functions to be included into the PsyCron system
    explicit PsyCron(UIIL user_parameters, size_t track_cap):
	    m_current_track{nullptr},
	    m_user_parameters{user_parameters},
	    m_running{false},
	    m_track_cap{track_cap},
	    m_num_track_cnt{0}{};

    // Executes one routine within the current track
    void execute();

    template<typename EnvType>
    PsyTrack<EnvType>* add_track(size_t id, EnvType& global_env){
	PsyTrack<EnvType>* track = 
		new PsyTrack<EnvType>(id, (EnvType&&) global_env, this);
	
	m_rail_track[++m_num_track_cnt] = track;
	
	return track;
    }

    /**
     * Swaps operating execution environments
     *
     * @param[in] index The index of the track to be swapped in.
     */
    void swap_track(uint8_t index);

private:

    PsyTrackBase* m_current_track;
    PsyTrackBase** m_rail_track;

    UIIL m_user_parameters;

    // Used to block any misuse of the PsyCron system in regards to initialization
    bool m_running;

    size_t m_track_cap;
    size_t m_num_track_cnt;
};

}

// OS level exceptions which do not exist in embedded applications
extern "C" void __cxa_pure_virtual() { while (1); }

#endif //PROJECT_PSYCRON.H
