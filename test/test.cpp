//
// Created by Dylan Wagner on 8/1/18.
//

#include <iostream>
#include <unitypes.h>
#include "../include/PsyCron.hpp"
#include "../include/usr/PsyUtils.hpp"

uint32_t get_milli(){
    return 10;
}

int main(){
    std::cout << "Hello!";

    UIIL config;

    config.sys_mili_second = get_milli;

    std::cout << config.sys_mili_second();
    if(config.sys_mili_second == 0) std::cout << "NULL";
}