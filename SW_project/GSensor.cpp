#include "GSensor.h"

GSensor::GSensor() {
    std::cout << "GSensor constructor called!" << std::endl;
    PinmuxConfig();
    I2C0_Init();
}

GSensor::~GSensor() {
    std::cout << "Finalizing G-Sensor module..." << std::endl;
    // Any necessary cleanup code here
}

void GSensor::PinmuxConfig() {
    // Configure Pin Mux to connect the ADXL345's I2C wires to I2C0
    // Access the necessary registers using RegisterRead and RegisterWrite

    // Set I2C0USEFPGA register to 0
    RegisterWrite(PIN_MUX_I2C0USEFPGA, 0);

    // Set GENERALIO7 and GENERALIO8 registers to 1
    RegisterWrite(PIN_MUX_GEN_IO7, 1);
    RegisterWrite(PIN_MUX_GEN_IO8, 1);
}

void GSensor::I2C0_Init() {
    // Configure I2C0 for communication with ADXL345
    // Write the necessary settings to the corresponding I2C0 registers

    // Abort any ongoing transmits and disable I2C0
    RegisterWrite(I2C0_ENABLE, 2);

    // Wait until I2C0 is disabled
    while (RegisterRead(I2C0_ENABLE_STATUS) & 0x1) {}

    // Configure the config reg with the desired setting
    RegisterWrite(I2C0_CON, 0x65); // (act as a master, use 7bit addressing, fast mode (400kb/s))

    // Set target address (disable special commands, use 7bit addressing)
    RegisterWrite(I2C0_TAR, 0x53);

    // Set SCL high/low counts
    RegisterWrite(I2C0_FS_SCL_HCNT, 60 + 30); // 0.6us + 0.3us
    RegisterWrite(I2C0_FS_SCL_LCNT, 130 + 30); // 1.3us + 0.3us

    // Enable the controller
    RegisterWrite(I2C0_ENABLE, 1);

    // Wait until controller is powered on
    while (!(RegisterRead(I2C0_ENABLE_STATUS) & 0x1)) {}
}

void GSensor::ADXL345_Init() {
    // Initialize the ADXL345 chip
    // Write the settings to the corresponding I2C0 registers

    ADXL345_RegWrite(ADXL345_REG_DATA_FORMAT, XL345_RANGE_16G | XL345_FULL_RESOLUTION); // +- 16g range, full resolution
    ADXL345_RegWrite(ADXL345_REG_BW_RATE, XL345_RATE_200); // Output Data Rate: 200Hz

    // Configure thresholds and interrupts
    ADXL345_RegWrite(ADXL345_REG_THRESH_ACT, 0x04); // Activity threshold
    ADXL345_RegWrite(ADXL345_REG_THRESH_INACT, 0x02); // Inactivity threshold
    ADXL345_RegWrite(ADXL345_REG_TIME_INACT, 0x02); // Time for inactivity
    ADXL345_RegWrite(ADXL345_REG_ACT_INACT_CTL, 0xFF); // Enables AC coupling for thresholds
    ADXL345_RegWrite(ADXL345_REG_INT_ENABLE, XL345_ACTIVITY | XL345_INACTIVITY); // Enable interrupts

    // Stop measure
    ADXL345_RegWrite(ADXL345_REG_POWER_CTL, XL345_STANDBY);

    // Start measure
    ADXL345_RegWrite(ADXL345_REG_POWER_CTL, XL345_MEASURE);
}

void GSensor::ADXL345_RegRead(uint8_t address, uint8_t *value) {
    // Read value from internal register at address
    // Write the register address to initiate the read operation
    RegisterWrite(I2C0_DATA_CMD, address + 0x400); // Send reg address (+0x400 to send START signal)

    // Write the read signal to receive the data
    RegisterWrite(I2C0_DATA_CMD, 0x100); // Send read signal

    // Wait for the response (data) to be available in the RX buffer
    while (RegisterRead(I2C0_RXFLR) == 0) {}

    // Read the response (data) from the RX buffer
    *value = RegisterRead(I2C0_DATA_CMD);
}

void GSensor::ADXL345_RegWrite(uint8_t address, uint8_t value) {
    // Write value to internal register at address
    RegisterWrite(I2C0_DATA_CMD, address + 0x400); // Send reg address (+0x400 to send START signal)
    RegisterWrite(I2C0_DATA_CMD, value); // Send value
}

void GSensor::ADXL345_RegMultiRead(uint8_t address, uint8_t values[], uint8_t len) {
    // Reads values from multiple internal registers
    RegisterWrite(I2C0_DATA_CMD, address + 0x400); // Send reg address (+0x400 to send START signal)

    // Send read signal len times
    for (int i = 0; i < len; i++)
        RegisterWrite(I2C0_DATA_CMD, 0x100);

    // Read the bytes
    int nth_byte = 0;
    while (len) {
        if ((RegisterRead(I2C0_RXFLR)) > 0) {
            values[nth_byte] = RegisterRead(I2C0_DATA_CMD);
            nth_byte++;
            len--;
        }
    }
}

void GSensor::ADXL345_XYZ_Read(int16_t szData16[3], int16_t mg_per_lsb) {
    // Read acceleration data of all three axes
    uint8_t szData8[6];
    ADXL345_RegMultiRead(0x32, (uint8_t *)&szData8, sizeof(szData8));

    szData16[0] = (szData8[1] << 8) | szData8[0];
    szData16[1] = (szData8[3] << 8) | szData8[2];
    szData16[2] = (szData8[5] << 8) | szData8[4];
}

bool GSensor::ADXL345_IsDataReady() {
    // Return true if there is new data
    bool bReady = false;
    uint8_t data8;

    ADXL345_RegRead(ADXL345_REG_INT_SOURCE, &data8);
    if (data8 & XL345_ACTIVITY)
        bReady = true;

    return bReady;
}
