#include "MCP23017_16_IO.h"

void MCP23017_16_IO::setAddress(int a0, int a1, int a2){
	address1 = a0;
	address2 = a1;
	address3 = a2;
    if(a0 == 1){
        address = address | 1;
    }
    if(a1 == 1){
        address = address | 2;
    }
    if(a2 == 1){
        address = address | 4;
    }
    //Start I2C port
    Wire.begin();
    //Open connection to specified address
    Wire.beginTransmission(address);
    //Set all channels to inputs
    Wire.write(0);
    Wire.write(255);
    Wire.write(255);
    //Determine if device is present at that address
    byte status = Wire.endTransmission();
    if(status != 0){
        initialized = false;
    }else{
        // Serial.println("Command Successful");
        initialized = true;
    }
    Wire.beginTransmission(address);
    //Pull all inputs up.
    Wire.write(0x0C);
    Wire.write(255);
    Wire.write(255);
    status = Wire.endTransmission();
    if(status != 0){
        initialized = false;
    }else{
        // Serial.println("Command Successful");
        initialized = true;
    }
}

void MCP23017_16_IO::readAllInputs(int* buffer){

	if(!initialized){
		//ReInitialize i2c chip.
		setAddress(address1, address2, address3);
	}

    Wire.beginTransmission(address);
    Wire.write(18);
    byte status = Wire.endTransmission();
    if(status != 0){
    	//Chip did not respond to write.
        initialized = false;
        buffer[0] = 256;
        buffer[1] = 256;
        Wire.end();
        delay(50);
        Wire.begin();
        return;
    }else{
        initialized = true;
    }
    Wire.requestFrom(address, 2);
    unsigned long startTime = millis();
    while(Wire.available() != 2 && millis()<startTime+timeout);
    if(Wire.available() != 2){
    	buffer[0] = 256;
    	buffer[1] = 256;
    	initialized = false;
    	Wire.end();
    	delay(50);
    	Wire.begin();
    	return;
    }
    //All clear
    buffer[0] = Wire.read();
    buffer[1] = Wire.read();

    return;
}
