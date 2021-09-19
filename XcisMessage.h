#ifndef XcisMessage_h
#define XcisMessage_h

#include "Arduino.h"
#include "Message.h"

// SENSOR TYPES
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

// COMMAND TYPES
#define SENSOR_DATA_REQUEST     0x01
#define SENSOR_DATA_RESPONSE    0x02
#define SET_FARM_ID             0x03
#define SET_SENSOR_LORAID       0x04
#define CONTROL_ON              0x05
#define CONTROL_OFF             0x06
#define COMMAND_OK              0x07
#define COMMAND_FAIL            0x08
#define RESEND                  0x09
#define DIGITAL_OUTPUT          0x10
#define ANALOG_OUTPUT           0x11
#define DEFAULT_SENSOR          0x12

class XcisMessage
{
    public:
    XcisMessage();
    void sayHello();
    void createMessage(uint8_t *data, uint8_t locationID, uint8_t sensorType, uint8_t command, uint8_t *paydata);
    void processMessage(uint8_t *data);
    void dumpHex(void *p, size_t size);

    uint8_t payload[28];
    uint8_t buffer[32];
    Message message;
    private:
   
};


#endif