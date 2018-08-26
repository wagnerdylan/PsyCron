
#include "../../include/usr/PsyUtils.hpp"
#include <stdint.h>

uint32_t PsyUtils::conv_micros_to_millis(uint32_t micros){
    return((uint32_t) micros/1000);
}