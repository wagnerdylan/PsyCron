//
// User Implemented Interface Layer (UIIL)
// File: UIIL.hpp
// Author: Dylan R. Wagner (drw6528@rit.edu)
// Description:
//      The User Implemented Interface Layer provides additional functionality to the
//      PsyCron system without platform dependence.
//

#ifndef PROJECT_UIIL_H
#define PROJECT_UIIL_H

typedef uint32_t (*micro_second)();
typedef uint32_t (*milli_second)();

typedef void (*drop_clock)();
typedef void (*raise_clock)();

typedef void (*print_msg)(char* msg);

typedef struct UIIL{
    micro_second    sys_micro_sec;
    milli_second    sys_mili_second;

    drop_clock      sys_drop_core_clock;
    raise_clock     sys_raise_core_clock;

    print_msg       sys_print_msg();

    UIIL()
        : sys_micro_sec(0)
        , sys_mili_second(0)
        , sys_drop_core_clock(0)
        , sys_raise_core_clock(0)
    {
    }
} UIIL;

#endif //PROJECT_UIIL_H
