#ifndef DE1SOCHPS_H
#define DE1SOCHPS_H
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <cstdlib>

class DE1SoChps {
private:
    char *pBase;
    int fd;

public:
    DE1SoChps();
    ~DE1SoChps();
    

    // Function to write a value into a register given its offset
    void RegisterWrite(unsigned int reg_offset, int value);

    // Function to return the value read from a register given its offset
    int RegisterRead(unsigned int reg_offset);

    // Cyclone V HPS Devices
    static const unsigned int HPS_BRIDGE_BASE = 0xFF700000;
    static const unsigned int HPS_BRIDGE_SPAN = 0x006FFFFF;
    
    // I2C0 Peripheral Registers
    static const unsigned int I2C0_BASE = 0x00504000; // I2C0 Base Address
    static const unsigned int I2C0_CON = 0x00504000; // Control Register
    static const unsigned int I2C0_TAR = I2C0_BASE + 0x04; // Target Address Register
    static const unsigned int I2C0_DATA_CMD = I2C0_BASE + 0x10; // Tx Rx Data and Command Register
    static const unsigned int I2C0_FS_SCL_HCNT = I2C0_BASE + 0x1C; // Fast Spd Clock SCL HCNT Register
    static const unsigned int I2C0_FS_SCL_LCNT = I2C0_BASE + 0x20; // Fast Spd Clock SCL LCNT Register
    static const unsigned int I2C0_CLR_INTR = I2C0_BASE + 0x40; // Combined and Individual Interrupt Register
    static const unsigned int I2C0_ENABLE = I2C0_BASE + 0x6C; // Enable Register
    static const unsigned int I2C0_TXFLR = I2C0_BASE + 0x74; // Transmit FIFO Level Register
    static const unsigned int I2C0_RXFLR = I2C0_BASE + 0x78; // Receive FIFO Level Register
    static const unsigned int I2C0_ENABLE_STATUS = I2C0_BASE + 0x9C; // Enable Status Register
    
    // The Pin Multiplexer selection
    static const unsigned int PIN_MUX_GEN_IO7 = 0x0060849C; // GENERALIO7 reg offset
    static const unsigned int PIN_MUX_GEN_IO8 = 0x006084A0; // GENERALIO8 reg offset
    static const unsigned int PIN_MUX_GPLMUX55 = 0x006086B0; // GPLMUX55 reg offset
    static const unsigned int PIN_MUX_GPLMUX56 = 0x006086B4; // GPLMUX56 reg offset
    static const unsigned int PIN_MUX_I2C0USEFPGA = 0x00608704; // I2C0USEFPGA reg offset
    
    // I2C0 Peripheral Registers
    //static const unsigned int I2C0_BASE = 0x00504000; // I2C0 Base Address
    //static const unsigned int I2C0_CON = 0x00504000; // Control Register
    //static const unsigned int I2C0_TAR = 0x00504004; // Target Address Register
    //static const unsigned int I2C0_DATA_CMD = 0x00504010; // Tx Rx Data and Command Register
    //static const unsigned int I2C0_FS_SCL_HCNT = 0x0050401C; // Fast Spd Clock SCL HCNT Register
    //static const unsigned int I2C0_FS_SCL_LCNT = 0x00504020; // Fast Spd Clock SCL LCNT Register
    //static const unsigned int I2C0_CLR_INTR = 0x0050402C; // Combined and Individual Interrupt Register
    //static const unsigned int I2C0_ENABLE = 0x0050406C; // Enable Register
    //static const unsigned int I2C0_TXFLR = 0x00504078; // Transmit FIFO Level Register
    //static const unsigned int I2C0_RXFLR = 0x0050407C; // Receive FIFO Level Register
    //static const unsigned int I2C0_ENABLE_STATUS = 0x0050409C; // Enable Status Register
    
    // The Pin Multiplexer selection
    //static const unsigned int PIN_MUX_GEN_IO7 = 0x005050EC; // GENERALIO7 reg offset
    //static const unsigned int PIN_MUX_GEN_IO8 = 0x005050F0; // GENERALIO8 reg offset
    //static const unsigned int PIN_MUX_GPLMUX55 = 0x0050517C; // GPLMUX55 reg offset
    //static const unsigned int PIN_MUX_GPLMUX56 = 0x00505180; // GPLMUX56 reg offset
    //static const unsigned int PIN_MUX_I2C0USEFPGA = 0x005051B4; // I2C0USEFPGA reg offset
    
};

#endif // DE1SOCHPS_H
