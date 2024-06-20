#define OUT_X_LSB 0
#define OUT_X_MSB 1
#define OUT_Y_LSB 2
#define OUT_Y_MSB 3
#define OUT_Z_LSB 4
#define OUT_Z_MSB 5
#include <cstdint>

class Accelerometer{
    public:
        Accelerometer();
        ~Accelerometer();
        int getX();
        int getY();
        int getZ();
        void updateAccValues();
    private:
        float x;
        float y;
        float z;
        int i2cFileDesc;
        unsigned char regAddr;
}; 