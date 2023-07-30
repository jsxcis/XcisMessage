#ifndef Message_h
#define Message_h

#include "Arduino.h"
    // Gateway payload
    struct{
        uint8_t gatewayID;
    } sensor_data_request;

    // Sensor status payload 
    typedef struct{
        uint32_t uid;
        uint8_t  deviceType;
    } sensor_status;

    // Pulse counter payload for flow meter or rain gauge
    typedef struct{
        uint16_t battery;
        uint16_t value;
        uint32_t accumulatedDataToken;
    } pulse_counter;

    // Distance Payload for tank or trough
    typedef struct{
        uint16_t battery;
        uint16_t value;
    } distance;

    // Voltage Payload for electric fence
    typedef struct{
        uint16_t battery;
        uint16_t pos_fenceVoltage;
        uint16_t neg_fenceVoltage;
    } voltage;
    //  Payload for bore controller
    typedef struct{
        uint16_t battery;
        uint16_t currentValue;
        uint16_t accumulatedPulses;
        uint32_t accumulatedDataToken;
        uint8_t boreState;
    } boreStatus;
    // Payload for bore controller relays
    struct{
        uint8_t gatewayID;
        uint16_t value;
    } sensor_control_request;
    
    typedef struct{
        uint8_t gatewayID;
        uint16_t value;
    } sensor_control_data;

struct Message
{
    public:
    Message();
    void sayHello();
    void displayMessage();
    void dumpHex(void *p, size_t size);
    
    // Base Message contents
    struct{
        uint8_t locationID;
        uint8_t deviceType;
        uint8_t command;
        uint8_t payload[26];
        uint16_t crc;
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

      inline void setCrc(uint16_t nNewValue) {
          this -> mess.crc = nNewValue;}

      inline uint16_t getCRC(){return this->mess.crc;}

      void setPayload(uint8_t *data,  size_t size );

      void getPayload(uint8_t *data);

      void getBuffer(uint8_t *buffer);
      void processBuffer(uint8_t *buffer);

      uint16_t ip_checksum(void* vdata,size_t length);

};
#endif