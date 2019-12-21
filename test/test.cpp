//
// Created by Dylan Wagner on 8/1/18.
//

#include <iostream>

#include "PsyCron.hh"

uint32_t get_milli(){
    return 10;
}

void msg_printer(char* msg){
    std::cout << msg << std::endl;
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
    config.sys_send_msg = msg_printer;

    psycron::PsyCron psycron_ins(config, 1);

    int simple_env = 42;
    
    {
        psycron::PsyTrack<int> *track_one = 
            psycron_ins.add_track<int>(0, simple_env, 1, 1);

        track_one->insert_routine(new TestRoutine<int>(), uint16_t{0}, 10);
        track_one->insert_routine(new TestTimedRoutine<int>(), uint16_t{1}, 100);
    }
}
