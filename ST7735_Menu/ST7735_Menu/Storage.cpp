#include "Storage.h"

Storage::Storage(){EEPROM.begin(STORAGE_SIZE);};

// save the passed buffer into memory
void Storage::save(byte* buffer){
    write(0, buffer, STORAGE_SIZE);
}

// read eeprom into passed buffer
void Storage::load(byte* buffer){
    read(0, buffer, STORAGE_SIZE);
}

// indicate cleared by removing magic bytes
void Storage::reset(){
    byte magic_killer[2] = {0};
    write(0, magic_killer, 2);
}

// write data of length at specified index
void Storage::write(int startAddress, const byte* data, size_t length) {
  for (size_t i = 0; i < length; ++i) {
    EEPROM.write(startAddress + i, data[i]);
  }
  EEPROM.commit();  // Commit the changes to flash
}

// read data into buffer of length at specified index
void Storage::read(int startAddress, byte* data, size_t length) {
  for (size_t i = 0; i < length; ++i) {
    data[i] = EEPROM.read(startAddress + i);
  }
}