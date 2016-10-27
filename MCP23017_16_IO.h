#include "spark_wiring_i2c.h"
#include "spark_wiring_usbserial.h"
#include "spark_wiring_constants.h"
#include "spark_wiring.h"

class MCP23017_16_IO{
public:
    void setAddress(int a1, int a2, int a3);
    void readAllInputs(int* buffer);

    bool initialized;

private:
    int address = 0x20;
    unsigned long timeout = 100;
    bool inFailureMode = false;
    int address1;
    int address2;
    int address3;

};
