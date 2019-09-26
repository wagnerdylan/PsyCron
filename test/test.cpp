//
// Created by Dylan Wagner on 8/1/18.
//

#include "PsyCron.hpp"

uint32_t get_milli(){
    return 10;
}

class TestRoutine : public psycron::PriorityRoutine 
{
public:

    int16_t get_some_val(){
        return(221);
    }

private:

    void run(){
        int i = 10;

        get_some_val();
    }
};

class TestTimedRoutine : public psycron::TimedRoutine
{
public:

    TestTimedRoutine(uint32_t time_delay) : 
        psycron::TimedRoutine(time_delay){};

    int16_t get_some_val(){
        return(221);
    }

private:

    void run(){
        int i = 10;

        get_some_val();
    }
};

int main(){

    psycron::UIIL config;
    config.sys_milli_second = get_milli;

    psycron::PriorityRoutine test = TestRoutine();
    psycron::TimedRoutine test_timed = TestTimedRoutine(100);

}