#ifndef XcisMessage_h
#define XcisMessage_h

#include "Arduino.h"
#include "Message.h"

#define XCIS_RH_MESH_MAX_MESSAGE_LEN  32

// Device TYPES
#define TANK                0x00
#define TROUGH              0x01
#define BORE_CONTROLLER     0x02
#define WEATHER_SENSOR      0x03
#define RAIN_GAUGE          0x04
#define FENCE               0x05
#define FLOW_METER          0x06
#define GATEWAY             0x07
#define TEST_MODE           0x07


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
#define STATUS_REQUEST          0x15
#define STATUS_RESPONSE         0x16

class XcisMessage
{
    public:
    XcisMessage();
    void sayHello();
    void resetPayload();

    void createCommandPayload(uint8_t command, uint8_t nodeId);
    void createCommandPayload(uint8_t command, uint16_t value, uint8_t nodeId);

    void createPulseCounterPayload( uint8_t command, uint16_t battery, uint16_t value, uint32_t accumulatedDataToken);
    void createDistancePayload( uint8_t command, uint16_t battery, uint16_t value);
    void createVoltagePayload( uint8_t command, uint16_t battery, uint16_t value);
    void createVoltagePayload( uint8_t command, uint16_t battery, uint16_t pos_fenceVoltage, uint16_t neg_fenceVoltage);
    void createBorePayload( uint8_t command, uint16_t battery, uint16_t currentValue, uint16_t accumulatedPulses, uint32_t accumulatedDataToken, uint8_t boreState);
    void createStatusPayload(uint8_t command, uint32_t uid, uint8_t deviceType);

    void processPulseCounterPayload(pulse_counter &pcm);
    void processDistancePayload(distance &dist);
    void processVoltagePayload(voltage &volts);
    void processBorePayload(boreStatus &status);
    void processStatusPayload(sensor_status &status);
    void processControlPayload(sensor_control_data &control);


    void createMessage(uint8_t *data, uint8_t locationID, uint8_t deviceType, uint8_t command, uint8_t *paydata);
    void createMessage(uint8_t *data, uint8_t locationID, uint8_t deviceType, uint8_t command);

    bool processMessage(uint8_t *data);
    void dumpHex(void *p, size_t size);

    inline uint8_t getLocationID(){return message.getLocationID();}
    inline uint8_t getDeviceType(){return message.getDeviceType();}
    inline uint8_t getCommand(){return message.getCommand();}
    inline uint16_t getCRC(){return message.getCRC();}

    inline void getPayload(uint8_t *data){ memcpy(data, this->payload, 28);}

    String convertDeviceTypeToString(uint8_t deviceType);

    uint8_t payload[26]; // Was 28
    uint8_t buffer[32];
    Message message;
    size_t used;
    inline void setOrigin(uint8_t nNewValue ){
          this->origin = nNewValue;}
    inline uint8_t getOrigin() {
          return this->origin;}

    private:
    uint8_t origin;
   
};


#endif