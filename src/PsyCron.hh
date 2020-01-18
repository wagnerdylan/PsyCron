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
#include <string.h>

#include "system/PsyRoutine.hh"
#include "UIIL.hh"
#include "system/PsyTrack.hh"
#include "Codes.hh"
#include "Macros.hh"

namespace psycron {

class PsyCron {

public:
 
    explicit PsyCron(uint16_t track_cap):
	    m_current_track{nullptr},
	    m_track_cap{track_cap}{

            m_rail_track = (PsyTrackBase**) psyalloc(track_cap * sizeof(PsyTrackBase*));

    };
    
    // Allows user implemented functions to be included into the PsyCron system
    PsyCron(UIIL user_parameters_arg, uint16_t track_cap):
        PsyCron{track_cap}{
            user_parameters = user_parameters_arg;
    };

    /**
     * Starts execution of routines within the psycron system. This call will block forever.
     */
    void start(){
        validate_state();
        init_system();
        running = true;

        if(m_current_track == nullptr){
            m_current_track = m_rail_track[0];
        }

        while(true){
            m_current_track->execute();
        }
    }

    /**
     * Adds an application into the PsyCron system atomically.
     * 
     * @param id The id of the routine.
     * @param global_env The application envrionment.
     * @param args Varadict function parameter containing the routines to be added into the application.
     */
    template<typename EnvType, typename ... Args>
    void add_application(
        uint16_t id, 
        EnvType& global_env, 
        Args ... args
    ){

        PsyTrack<EnvType>* track = 
            new PsyTrack<EnvType>(
                id,
                (EnvType&&) global_env, 
                this, 
                args...
            );
        m_rail_track[m_num_track_cnt] = track;
        m_num_track_cnt += 1;
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
            EASSERT(running, errCANNOT_ALLOCATE_MEMORY_AFTER_INIT);
            EASSERT((bytes_used + size) > PSYCRON_BUFFER_SIZE, errOUT_OF_ARENA_MEMORY);
            abort();
        }

        void* ptr_to_start = (void*) &psycron_arena[bytes_used];
        bytes_used += size;

        return ptr_to_start;
    }

    static void assert_fail(const char* error_name, const char* error_string){

        if(user_parameters.sys_send_msg){
            // Codes will always be < 253 chars in length
            char buffer[256];
            strcpy(buffer, error_name);
            strcat(buffer, ": ");
            strcat(buffer, error_string);

            user_parameters.sys_send_msg(buffer);
        }
    }

    UIIL& get_user_parameters(){
        return user_parameters;
    };

private:

    void validate_state(){
        //@TODO check state just before first execution, fail on any violators.
    }

    /**
     * Used to initialize routines across the entire system at startup.
     */
    void init_system(){
        for(uint16_t i{0}; i < m_num_track_cnt; ++i){
            m_rail_track[i]->init_rails();
        }
    }

    PsyTrackBase* m_current_track;
    PsyTrackBase** m_rail_track;

    // Used to block any misuse of the PsyCron system in regards to initialization
    static bool running;

    uint16_t m_track_cap;
    uint16_t m_num_track_cnt{0};
        
    static unsigned char psycron_arena[];
    
    static UIIL user_parameters;
};

void* psyalloc_key_func(size_t size);

void assert_fail_key_func(const char* error_name, const char* error_string);

template<typename T>
class PsyCronAllocator {
    public:
        T* operator()(size_t size){
            return (T*) psyalloc_key_func(size);
        }
};


}

#endif //PROJECT_PSYCRON.H
