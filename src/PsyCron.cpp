
#include "PsyCron.hh"

namespace psycron{
    bool PsyCron::running = false;
    UIIL PsyCron::user_parameters{};
    unsigned char PsyCron::psycron_arena[PSYCRON_BUFFER_SIZE] = {0};

    void* psyalloc_key_func(size_t size){
        return PsyCron::psyalloc(size);
    }

    void assert_fail_key_func(const char* error_name, const char* error_string){
        PsyCron::assert_fail(error_name, error_string);
    }

    // OS level exceptions which do not exist in embedded applications
    extern "C" void __cxa_pure_virtual() { while (1); }
}
