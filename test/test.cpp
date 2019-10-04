//
// Created by Dylan Wagner on 8/1/18.
//

#include <iostream>

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

        std::cout << get_some_val();
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

        std::cout << get_some_val();
    }
};

int main(){

    psycron::UIIL config;
    config.sys_milli_second = get_milli;

    int simple_env = 42;

    psycron::PsyTrack<int> *track_one = new psycron::PsyTrack<int>(10, nullptr, 0, std::move(simple_env));

    psycron::PriorityRoutine<int> *test = new TestRoutine<int>();
    psycron::TimedRoutine<int> *test_timed = new TestTimedRoutine<int>(100);

    std::cout << *track_one->get_environment();
}