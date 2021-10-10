#ifndef XcisMessage_h
#define XcisMessage_h

#include "Arduino.h"
#include "Message.h"



// Device TYPES
#define TANK                0x01
#define TROUGH              0x02
#define PULSE_COUNTER       0x03
#define LEVEL_MEASURE       0x04
#define BORE_CONTROLLER     0x05
#define WEATHER_SENSOR      0x06
#define RAIN_GAUGE          0x07
#define FENCE               0x08
#define FLOW_METER          0x09
#define NEW                 0x10
#define UNDEFINED           0x11
#define GATEWAY             0x12

// COMMAND TYPES
#define SENSOR_DATA_REQUEST     0x01
#define SENSOR_DATA_RESPONSE    0x02
#define SET_LOCATION_ID         0x03
#define SET_SENSOR_LORAID       0x04
#define CONTROL_ON              0x05
#define CONTROL_OFF             0x06
#define COMMAND_OK              0x07
#define COMMAND_FAIL            0x08
#define RESEND                  0x09
#define DIGITAL_OUTPUT          0x10
#define ANALOG_OUTPUT           0x11
#define DEFAULT_SENSOR          0x12
#define SET_GPS_LOCATION        0x13
#define GET_GPS_DATA            0x14

class XcisMessage
{
    public:
    XcisMessage();
    void sayHello();
    void resetPayload();

    void createCommandPayload( uint8_t command, uint8_t nodeId);
    void createPulseCounterPayload( uint8_t command, uint16_t battery, uint8_t value, uint32_t timestamp);
    void processPulseCounterPayload(pulse_counter &pcm);
    void createMessage(uint8_t *data, uint8_t locationID, uint8_t deviceType, uint8_t command, uint8_t *paydata);
    void createMessage(uint8_t *data, uint8_t locationID, uint8_t deviceType, uint8_t command);

    void processMessage(uint8_t *data);
    void dumpHex(void *p, size_t size);

    inline uint8_t getLocationID(){return message.getLocationID();}
    inline uint8_t getDeviceType(){return message.getDeviceType();}
    inline uint8_t getCommand(){return message.getCommand();}
    inline void getPayload(uint8_t *data){ memcpy(data, this->payload, 28);}

    uint8_t payload[28];
    uint8_t buffer[32];
    Message message;
    size_t used;
    private:
   
};


#endif