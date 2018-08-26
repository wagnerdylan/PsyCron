//
// Created by Dylan Wagner on 8/1/18.
//

#include <stdint.h>
#include "../include/PsyCron.hpp"
#include "../include/usr/PsyUtils.hpp"

uint32_t get_milli(){
    return 10;
}

int main(){

    UIIL config;

    //uint32_t millis = PsyUtils::conv_micros_to_millis(1000);

    config.sys_mili_second = get_milli;
}