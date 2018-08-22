//
// PsyCron
// File: PsyUtils.hpp
// Author: Dylan R. Wagner (drw6528@rit.edu)
// Description:
//      Set of utility functions for users
//

#ifndef PSYCRON_PSYUTILS_HPP
#define PSYCRON_PSYUTILS_HPP

#include <stdint.h>

class PsyUtils {

public:

    static uint32_t conv_micros_to_millis(uint32_t micros_sec);

    static uint32_t conv_millis_to_seconds(uint32_t milli_sec);

    static uint32_t conv_millis_to_minutes(uint32_t milli_sec);

    static uint32_t conv_millis_to_hours(uint32_t milli_sec);

    static uint32_t conv_millis_to_days(uint32_t milli_sec);

    static uint32_t conv_millis_to_micros(uint32_t milli_sec);

    static uint32_t conv_seconds_to_millis(uint32_t seconds);

    static uint32_t conv_minutes_to_millis(uint32_t minutes);

    static uint32_t conv_hours_to_millis(uint32_t hours);

    static uint32_t conv_days_to_millis(uint32_t days);

    static uint32_t conv_delta_to_millis(uint32_t days, uint32_t hours,
                                         uint32_t minutes, uint32_t seconds, uint32_t millis);
};

#endif //PSYCRON_PSYUTILS_HPP
