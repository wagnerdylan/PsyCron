
#ifndef PSYRAIL
#define PSYRAIL

#include "../PsyCron.hpp"
#include "../queue"

class PsyRail{

public:

    explicit PsyRail(uint8_t cap);

    void execute();

    void add_routine(Routine* Routine, uint32_t value);

protected:

    uint32_t process_value(uint32_t value);

private:

};

#endif