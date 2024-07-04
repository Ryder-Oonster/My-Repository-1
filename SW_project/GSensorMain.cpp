#include <iostream>
#include <unistd.h> // For usleep
#include "GSensor.h"
#include "DE1SoChps.h"
#include "PIOControl.h"

int main() {
    std::cout << "Starting GSensorMain main function!" << std::endl;

    // Instantiate GSensor object using dynamic memory allocation
    std::cout << "Instantiating GSensor object using dynamic memory allocation!" << std::endl;
    GSensor *gsensor = new GSensor();
    PIOControl *piocontrol = new PIOControl();

    // Read the ADXL345 Device ID (Reg 0x00) and verify correct ID
    std::cout << "Reading the ADXL345 Device ID (Reg 0x00) and verify correct ID!" << std::endl;
    uint8_t deviceId;
    gsensor->ADXL345_RegRead(ADXL345_REG_DEVID, &deviceId);
    if (deviceId != 0xE5) {
        std::cerr << "Error: Incorrect device ID!" << std::endl;
        delete gsensor; // Clean up allocated memory
        return 1;
    } else {
        std::cerr << "Device ID valid!" << std::endl;
    }

    // Initialize the ADXL345 module
    std::cout << "Initializing the ADXL345 module!" << std::endl;
    gsensor->ADXL345_Init();

    // Set the resolution factor (mg_per_lsb)
    float mg_per_lsb = 4; // Approximate multiplier

    // Infinite loop to read and print X, Y, Z data
    std::cout << "Starting the infinite loop to read and print X, Y, Z data: " << std::endl;
    std::cout << "Move the board around to obtain valid data within the range of about -1000 mg to 1000 mg on each axis." << std::endl;
    while (true) {
        int16_t data[3];
        gsensor->ADXL345_XYZ_Read(data, mg_per_lsb);
        int16_t x_mg = data[0] * mg_per_lsb;
        int16_t y_mg = data[1] * mg_per_lsb;
        int16_t z_mg = data[2] * mg_per_lsb;

        // Ensure X value is within desired range
        if (x_mg > 1000) {
            x_mg = 1000;
        } else if (x_mg < -1000) {
            x_mg = -1000;
        }

        // Ensure Y value is within desired range
        if (y_mg > 1000) {
            y_mg = 1000;
        } else if (y_mg < -1000) {
            y_mg = -1000;
        }

        // Ensure Z value is within desired range
        if (z_mg > 1000) {
            z_mg = 1000;
        } else if (z_mg < -1000) {
            z_mg = -1000;
        }

        std::cout << "X: " << x_mg << " mg, Y: " << y_mg << " mg, Z: " << z_mg << " mg" << std::endl;

        // Store X coordinate in PIO output register
        piocontrol->WritePIOout(x_mg);

        // Read angle value from PIO input register
        int angle = piocontrol->ReadPIOin();
        
        // Print angle
        std::cout << "angle: " << angle << std::endl;
        
        // Wait for a short duration before polling again
        usleep(100000); // Sleep for 100 milliseconds (adjust as needed)
    }

    delete gsensor; // Clean up allocated memory
    return 0;
}
