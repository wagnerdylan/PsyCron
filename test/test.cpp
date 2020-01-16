//
// Created by Dylan Wagner on 8/1/18.
//

#include <iostream>
#include <chrono>

#include "PsyCron.hh"

uint32_t get_milli(){
    static std::chrono::milliseconds startup_time;
    static bool startup_set{false};
    auto now = std::chrono::system_clock::now();

    if(!startup_set){
        startup_time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        startup_set = true;
    }

    auto ms_now = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    //std::cout << "Time: " << (ms_now - startup_time).count() << std::endl;
    return (ms_now - startup_time).count();
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
        std::cout << "Routine " << this->_id << " some val: " << some_val
            << " Envrionment: " << ++this->_get_envrionment() << std::endl;

        if(some_val == 20) this->_deactivate_other(201);
        if(some_val == 40) this->_activate_other(201);

        if(some_val == 60){
            this->_deactivate_me();
            this->_deactivate_other(201);
        }
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
        std::cout << "Routine " << this->_id
            << " Envrionment: " << ++this->_get_envrionment() << std::endl;
    }
};

int main(){

    psycron::UIIL config{};
    config.sys_milli_second = get_milli;
    config.sys_send_msg = msg_printer;

    psycron::PsyCron psycron_ins(config, 1);

    int simple_env = 42;
    
    psycron_ins.add_application(
        0, // Identifer for the application 
        simple_env, // Application envrionment 
        psycron::PsyTrack<int>::PriorityRoutineArgs{new TestRoutine<int>{}, uint16_t{200}, 1},
        psycron::PsyTrack<int>::PriorityRoutineArgs{new TestRoutine<int>{}, uint16_t{201}, 2},
        psycron::PsyTrack<int>::TimedRoutineArgs{new TestTimedRoutine<int>{}, uint16_t{1}, 1000},
        psycron::PsyTrack<int>::TimedRoutineArgs{new TestTimedRoutine<int>{}, uint16_t{2}, 5000}
    );

    // Blocking call
    psycron_ins.start();
}
