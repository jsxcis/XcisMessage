#ifndef Message_h
#define Message_h

#include "Arduino.h"

struct Message
{
    public:
    Message();
    void sayHello();
    void displayMessage();
    void dumpHex(void *p, size_t size);
    
    // Message contents
    struct{
        uint8_t locationID;
        uint8_t deviceType;
        uint8_t command;
        uint8_t payload[28];
        uint8_t crc;
    } mess;

    size_t used;
    
      inline void setLocationID(uint8_t nNewValue) {
          this -> mess.locationID = nNewValue;}

      inline uint8_t getLocationID(){return this->mess.locationID;}

      inline void setDeviceType(uint8_t nNewValue) {
          this -> mess.deviceType = nNewValue;}

      inline uint8_t getDeviceType(){return this->mess.deviceType;}

      inline void setCommand(uint8_t nNewValue) {
          this -> mess.command = nNewValue;}

      inline uint8_t getCommand(){return this->mess.command;}

      inline void setCrc(uint8_t nNewValue) {
          this -> mess.crc = nNewValue;}

      void setPayload(uint8_t *data,  size_t size );

      void getPayload(uint8_t *data);

      void getBuffer(uint8_t *buffer);
      void processBuffer(uint8_t *buffer);

};
#endif