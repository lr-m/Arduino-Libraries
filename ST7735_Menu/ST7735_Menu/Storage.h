#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define STORAGE_SIZE 512

#ifndef Storage_h
#define Storage_h

class Storage {
    public:
        Storage();
        void save(byte*);
        void load(byte*);
        void reset();
        void write(int startAddress, const byte* data, size_t length);
        void read(int startAddress, byte* data, size_t length);
};

#endif