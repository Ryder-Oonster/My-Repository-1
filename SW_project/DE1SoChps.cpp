#include "DE1SoChps.h"

DE1SoChps::DE1SoChps() {
    // Open /dev/mem to give access to physical addresses
    fd = open("/dev/mem", (O_RDWR | O_SYNC));
    if (fd == -1) {
        std::cerr << "ERROR: could not open /dev/mem..." << std::endl;
        exit(1);
    }

    // Get a mapping from physical addresses to virtual addresses
    pBase = (char *)mmap(NULL, HPS_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, HPS_BRIDGE_BASE);
    if (pBase == MAP_FAILED) {
        std::cerr << "ERROR: mmap() failed..." << std::endl;
        close(fd); // close memory before exiting
        exit(1);   // Returns 1 to the operating system;
    }
}

DE1SoChps::~DE1SoChps() {
    if (munmap(pBase, HPS_BRIDGE_SPAN) != 0) {
        std::cerr << "ERROR: munmap() failed..." << std::endl;
        exit(1);
    }
    close(fd); // close memory
}

void DE1SoChps::RegisterWrite(unsigned int reg_offset, int value) {
    *(volatile unsigned int *)(pBase + reg_offset) = value;
}

int DE1SoChps::RegisterRead(unsigned int reg_offset) {
    return *(volatile unsigned int *)(pBase + reg_offset);
}
