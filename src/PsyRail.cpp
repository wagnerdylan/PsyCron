//
// PsyCron
// File: PsyRail.cpp
// Author: Dylan R. Wagner (drw6528@rit.edu)
// Description:
//     PsyRail implementation
//     ...

#include "PsyRail.hpp"

namespace psycron {

void PriorityPsyRail::execute(){}

uint32_t PriorityPsyRail::process_value(uint32_t value){}

void PriorityPsyRail::priority_reset(uint32_t rst_max){}

void TimedPsyRail::execute(){}

uint32_t TimedPsyRail::process_value(uint32_t value){}

void TimedPsyRail::priority_reset(uint32_t rst_max){}

}