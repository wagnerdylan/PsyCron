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
        return ++some_val_cnt;
    }

private:

    void run(){
        int16_t some_val = get_some_val();
        std::cout << "Routine " << this->m_id << " some val: " << some_val
            << " Envrionment: " << ++this->get_envrionment() << std::endl;
    }

    int16_t some_val_cnt{0};
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
        int i = get_some_val();
    }
};

int main(){

    psycron::UIIL config{};
    config.sys_milli_second = get_milli;
    config.sys_send_msg = msg_printer;

    psycron::PsyCron psycron_ins(config, 1);

    int simple_env = 42;
    
    psycron_ins.add_track(
        0, 
        simple_env,
        psycron::PsyTrack<int>::PriorityRoutineArgs{new TestRoutine<int>{}, uint16_t{200}, 1},
        psycron::PsyTrack<int>::PriorityRoutineArgs{new TestRoutine<int>{}, uint16_t{201}, 2},
        psycron::PsyTrack<int>::TimedRoutineArgs{new TestTimedRoutine<int>{}, uint16_t{1}, 100}
    );

    // Blocking call
    psycron_ins.execute();
}
