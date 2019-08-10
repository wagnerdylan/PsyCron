//
// Created by Dylan Wagner on 8/1/18.
//

#include "PsyCron.hpp"

uint32_t get_milli(){
    return 10;
}

class TestRoutine : public Routine 
{
public:
    void run(){
        int i = 10;

        get_some_val();
    }

    int16_t get_some_val(){
        return(221);
    }
};

class TestTimedRoutine : public TimedRoutine
{
public:
    TestTimedRoutine(uint32_t time_delay) : TimedRoutine(time_delay){};
};

int main(){

    UIIL config;
    config.sys_milli_second = get_milli;

    Routine* test = new TestRoutine();
    TimedRoutine* test_timed = new TestTimedRoutine(100);
}