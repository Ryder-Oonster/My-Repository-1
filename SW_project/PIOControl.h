#ifndef PIOCONTROL_H
#define PIOCONTROL_H

#include "DE1SoCfpga.h"

class PIOControl : public DE1SoCfpga {
private:
    unsigned int out_regValue;
    unsigned int in_regValue;

public:
    PIOControl();
    ~PIOControl();
    void WritePIOout(int value);
    int ReadPIOin();
};

#endif // PIOCONTROL_H
