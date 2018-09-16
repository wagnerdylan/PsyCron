//
// Created by Dylan Wagner on 8/1/18.
//

#include <stdint.h>
#include "../include/PsyCron.hpp"
#include "../include/usr/PsyUtils.hpp"

uint32_t get_milli(){
    return 10;
}

class TestRoutine : public Routine 
{
public:
    void run(){
        int i = 10;
    }

    int16_t get_some_val(){
        return(221);
    }
};

int main(){

    UIIL config;

    TestRoutine *test = new TestRoutine();
    test->run();
}