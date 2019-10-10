//
// Created by Dylan Wagner on 8/1/18.
//

//#include <iostream>

#include "PsyCron.hpp"

uint32_t get_milli(){
    return 10;
}

template <typename EnvType>
class TestRoutine : public psycron::PriorityRoutine<EnvType>
{
public:

    int16_t get_some_val(){
        return(221);
    }

private:

    void run(){
        int i = 10;
    }
};

template <typename EnvType>
class TestTimedRoutine : public psycron::TimedRoutine<EnvType>
{
public:

    TestTimedRoutine(uint32_t time_delay) : 
        psycron::TimedRoutine<EnvType>(time_delay){};

    int16_t get_some_val(){
        return(290);
    }

private:

    void run(){
        int i = 10;
    }
};

int main(){

    psycron::UIIL config;
    config.sys_milli_second = get_milli;

    psycron::PsyCron psycron_ins(config);

    int simple_env = 42;

    psycron::PsyTrack<int> *track_one = 
        psycron_ins.add_track<int>(0, simple_env);

    track_one->insert_routine(new TestRoutine<int>(), 0);
    track_one->insert_routine(new TestTimedRoutine<int>(100), 0);
}
