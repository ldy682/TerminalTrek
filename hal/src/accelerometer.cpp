#include "accelerometer.h"
#include "usefulFunc.h"
#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <cstdio>
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2C_DEVICE_ADDRESS 0x18 // Red Zencape BeagleBone


static int initI2cBus(const char* bus, int address);
static void writeI2cReg(int i2cFileDesc, unsigned char regAddr,
                        unsigned char value);

Accelerometer::Accelerometer(){
    // configures gpio pins for the accelerometer
    runCommand("config-pin p9.17 i2c");
    runCommand("config-pin p9.18 i2c");
    
    this->i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);
    this->regAddr = 0xa8; // register address of x,y,z + 0x80 for auto increment
    writeI2cReg(i2cFileDesc, 0x20, 0xc7); // turn on CTRL_REG1

   
}

Accelerometer::~Accelerometer(){
    // runCommand("config-pin p9.17 default");
    // runCommand("config-pin p9.18 default");
    std::cout<<"Accelerometer deconstructor called"<<std::endl;
}


static void writeI2cReg(int i2cFileDesc, unsigned char regAddr,
                        unsigned char value)
{
        unsigned char buff[2];
        buff[0] = regAddr;
        buff[1] = value;
        int res = write(i2cFileDesc, buff, 2);
        if (res != 2) {
        perror("I2C: Unable to write i2c register.");
        exit(1);
    }
}

void Accelerometer::updateAccValues(){
    unsigned int res = write(i2cFileDesc, &regAddr, sizeof(regAddr));
    if(res != sizeof(regAddr)){
        throw std::runtime_error("ERROR: Unable to write in i2c register");
    }
    std::vector<unsigned char> buff(6);
    res = read(i2cFileDesc, buff.data(), buff.size());
    if (res != buff.size()) {
        throw std::runtime_error("ERROR: Unable to read in i2c register");
    }
    // values received will be -17000 to 17000
    this->x = ((static_cast<int16_t>(buff[OUT_X_MSB]) << 8) | buff[OUT_X_LSB]);
    this->y = ((static_cast<int16_t>(buff[OUT_Y_MSB]) << 8) | buff[OUT_Y_LSB]);
    this->z = ((static_cast<int16_t>(buff[OUT_Z_MSB]) << 8) | buff[OUT_Z_LSB]);
    
    return;
} 

static int initI2cBus(const char* bus, int address)
{
    int i2cFileDesc = open(bus, O_RDWR);
    int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
    if (result < 0) {
        throw std::runtime_error("I2C: Unable to set I2C device to slave address.");
    }
    return i2cFileDesc;
}

int Accelerometer::getX(){
    return this->x;
}
int Accelerometer::getY(){
    return this->y;
}
int Accelerometer::getZ(){
    return this->z;
}
