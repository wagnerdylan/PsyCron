
#include "PsyCron.hh"

namespace psycron{
    bool PsyCron::m_running = false;
    unsigned char PsyCron::psyalloc_buffer[PSYCRON_BUFFER_SIZE] = {0};

    void* psyalloc_key_func(size_t size){
        return PsyCron::psyalloc(size);
    }

    // OS level exceptions which do not exist in embedded applications
    extern "C" void __cxa_pure_virtual() { while (1); }
}
