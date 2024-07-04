#ifndef DE1SOCFPGA_H
#define DE1SOCFPGA_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <cstdlib>

class DE1SoCfpga {
private:
    char *pBase;
    int fd;

public:
    DE1SoCfpga();
    ~DE1SoCfpga();
    void RegisterWrite(unsigned int reg_offset, int value);
    int RegisterRead(unsigned int reg_offset);

    // Constants for DE1-SoC FPGA devices
    static const unsigned int OUT_BASE = 0x00000020;
    static const unsigned int IN_BASE = 0x00000040;
    static const unsigned int LW_BRIDGE_BASE = 0xFF200000;
    static const unsigned int LW_BRIDGE_SPAN = 0x00005000;
    //const unsigned int LEDR_BASE;
    //const unsigned int SW_BASE;
    //const unsigned int KEY_BASE;
    //const unsigned int HEX3_HEX0_BASE;
    //const unsigned int HEX5_HEX4_BASE;
    //const unsigned int JP2_BASE;
    //const unsigned int JP2_DDR;
};

#endif // DE1SOCFPGA_H
