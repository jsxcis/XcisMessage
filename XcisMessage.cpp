#include "Arduino.h"
#include "XcisMessage.h"
#include <stdio.h>
#include <string.h>


XcisMessage::XcisMessage()
{
  // Constructor
  
  //Serial.println("XcisMessage::Constructor");
   for (int i = 0; i < sizeof(this->payload); i++ )
    {
        this->payload[i] = 0;
    }

}
void XcisMessage::resetPayload()
{
   for (int i = 0; i < sizeof(this->payload); i++ )
    {
        this->payload[i] = 0;
    }
}
void XcisMessage::sayHello()
{
  Serial.println("Hello from XcisMessage");
  this->message.sayHello();
  this->message.displayMessage();
  /*
  message.setLocationID(0x01); // 8 bit value corresponding to a farm ID. 
  message.setSensorType(TANK); // 8 bit value correspinding to a sensor type
  message.setCommand(SENSOR_DATA_REQUEST); // 8 bit value corresponding to a command
  //JONATHAN EDGAR SHARP 030367A
  // 4a 4f 4e 41 54 48 41 4e 20 45 44 47 41 52 20 53 48 41 52 50 20 30 33 30 33 36 37 41
  uint8_t payload[28] = {0x4a, 0x4f, 0x4e, 0x41, 0x54, 0x48, 0x41, 0x4e, 0x20, 0x45, 0x44, 0x47, 0x41, 0x52, 0x20, 0x53, 0x48, 0x41, 0x52, 0x50, 0x20, 0x30, 0x33, 0x30, 0x33, 0x36, 0x37, 0x41};
  message.setPayload(payload,sizeof(payload));
  message.setCrc(0x45);
  message.displayMessage();
  */
  return;
}
void XcisMessage::createStatusPayload(uint8_t command,uint32_t uid, uint8_t deviceType)
{
  Serial.print("XcisMessage::createStatusPayload");
  sensor_status sts;
  if (command == STATUS_RESPONSE)
  {
    sts.uid = __builtin_bswap32(uid); // Make sure we use byte order swap for 16 and 32 bit values
    sts.deviceType = deviceType;
    // now convert to an array
    this->resetPayload();
    used = 0;
    memmove(&payload[used], &sts.uid, sizeof(sts.uid));
    used += sizeof(sts.uid);
    memmove(&payload[used], &sts.deviceType, sizeof(sts.deviceType));
    used += sizeof(sts.deviceType);
    Serial.print("Payload used:");
    Serial.println(used);
  }
  else
  {
    Serial.println("Command not found - sending ZEROs");
  }
}
void XcisMessage::createPulseCounterPayload(uint8_t command,uint16_t battery, uint16_t value, uint32_t timestamp )
{
  Serial.print("XcisMessage::createPulseCounterPayload");
  pulse_counter pcm;
  if (command == SENSOR_DATA_RESPONSE)
  {
    pcm.battery = __builtin_bswap16(battery); // Make sure we use byte order swap for 16 and 32 bit values
    pcm.value = __builtin_bswap16(value);
    pcm.timestamp =  __builtin_bswap32(timestamp);
    // now convert to an array
    this->resetPayload();
    used = 0;
    memmove(&payload[used], &pcm.battery, sizeof(pcm.battery));
    used += sizeof(pcm.battery);
    memmove(&payload[used], &pcm.value, sizeof(pcm.value));
    used += sizeof(pcm.value);
    memmove(&payload[used], &pcm.timestamp, sizeof(pcm.timestamp));
    used += sizeof(pcm.timestamp);
    Serial.print("Payload used:");
    Serial.println(used);
  }
  else
  {
    Serial.println("Command not found - sending ZEROs");
  }
}
void XcisMessage::createDistancePayload(uint8_t command,uint16_t battery, uint16_t value)
{
  Serial.print("XcisMessage::createDistancePayload");
  distance dist;
  if (command == SENSOR_DATA_RESPONSE)
  {
    dist.battery = __builtin_bswap16(battery); // Make sure we use byte order swap for 16 and 32 bit values
    dist.value = __builtin_bswap16(value);
    // now convert to an array
    this->resetPayload();
    used = 0;
    memmove(&payload[used], &dist.battery, sizeof(dist.battery));
    used += sizeof(dist.battery);
    memmove(&payload[used], &dist.value, sizeof(dist.value));
    used += sizeof(dist.value);
    Serial.print("Payload used:");
    Serial.println(used);
  }
  else
  {
    Serial.println("Command not found - sending ZEROs");
  }
}
void XcisMessage::createVoltagePayload(uint8_t command,uint16_t battery, uint16_t value)
{
  Serial.print("XcisMessage::createVoltagePayload");
  voltage volts;
  if (command == SENSOR_DATA_RESPONSE)
  {
    volts.battery = __builtin_bswap16(battery); // Make sure we use byte order swap for 16 and 32 bit values
    volts.value = __builtin_bswap16(value);
    // now convert to an array
    this->resetPayload();
    used = 0;
    memmove(&payload[used], &volts.battery, sizeof(volts.battery));
    used += sizeof(volts.battery);
    memmove(&payload[used], &volts.value, sizeof(volts.value));
    used += sizeof(volts.value);
    Serial.print("Payload used:");
    Serial.println(used);
  }
  else
  {
    Serial.println("Command not found - sending ZEROs");
  }
}
void XcisMessage::processPulseCounterPayload(pulse_counter &pcm)
 {
       memmove(&pcm,this->payload,sizeof(pulse_counter));
       pcm.battery =  __builtin_bswap16(pcm.battery);
       pcm.value = __builtin_bswap16(pcm.value);
       pcm.timestamp = __builtin_bswap32(pcm.timestamp);
 }
 void XcisMessage::processDistancePayload(distance &dist)
 {
       memmove(&dist,this->payload,sizeof(distance));
       dist.battery =  __builtin_bswap16(dist.battery);
       dist.value = __builtin_bswap16(dist.value);
 }
 void XcisMessage::processVoltagePayload(voltage &volts)
 {
       memmove(&volts,this->payload,sizeof(voltage));
       volts.battery =  __builtin_bswap16(volts.battery);
       volts.value = __builtin_bswap16(volts.value);
 }
void XcisMessage::createCommandPayload(uint8_t command,uint8_t nodeId)
{
  Serial.print("XcisMessage::createCommandPayload");
  this->resetPayload();
  
  if (command == SENSOR_DATA_REQUEST)
  {
    sensor_data_request.gatewayID = nodeId;
    // now convert to an array
    used = 0;
    memmove(&payload[used], &sensor_data_request.gatewayID, sizeof(sensor_data_request.gatewayID));
    used += sizeof(sensor_data_request.gatewayID);
    Serial.print("Payload used:");
    Serial.println(used);
  }
  if (command == STATUS_REQUEST)
  {
    sensor_data_request.gatewayID = nodeId;
    // now convert to an array
    used = 0;
    memmove(&payload[used], &sensor_data_request.gatewayID, sizeof(sensor_data_request.gatewayID));
    used += sizeof(sensor_data_request.gatewayID);
    Serial.print("Payload used:");
    Serial.println(used);
  }
  else
  {
    Serial.println("Command not found - sending ZEROs");
  }
}
void XcisMessage::createMessage(uint8_t *data, uint8_t locationID, uint8_t deviceType, uint8_t command, uint8_t *paydata)
{
  Serial.println("XcisMessage::createMessage");
  this->message.setLocationID(locationID);
  this->message.setDeviceType(deviceType);
  this->message.setCommand(command);
  // Copy payload into message payload
  //memcpy(this->payload, paydata, sizeof(payload));
  //this->message.setPayload(this->payload,sizeof(this->payload));
  // Can do direct copy provided size is set - ignore internal payload
  this->message.setPayload(paydata,sizeof(paydata));
  this->message.setCrc(0x45);
  // Convert the message structure into a buffer
  this->message.getBuffer(this->buffer);
  // Copy the buffer into the incoming user buffer
  memcpy(data, this->buffer, sizeof(buffer));
}
void XcisMessage::createMessage(uint8_t *data, uint8_t locationID, uint8_t deviceType, uint8_t command)
{
  Serial.println("XcisMessage::createMessage");
  this->message.setLocationID(locationID);
  this->message.setDeviceType(deviceType);
  this->message.setCommand(command);
  // Copy payload into message payload
  //memcpy(this->payload, paydata, sizeof(payload));
  //this->message.setPayload(this->payload,sizeof(this->payload));
  // Can do direct copy provided size is set - use internal payload set by createPayload by device
  this->message.setPayload(this->payload,sizeof(this->payload));
  this->message.setCrc(0x45);
  // Convert the message structure into a buffer
  this->message.getBuffer(this->buffer);
  // Copy the buffer into the incoming user buffer
  memcpy(data, this->buffer, sizeof(buffer));
}

void XcisMessage::processMessage(uint8_t *data)
{
  //Serial.println("XcisMessage::processMessage");
  this->message.processBuffer(data);
  // check the payload
  this->message.getPayload(this->payload);
  // Payload is stored here - can now process.
  //dumpHex(this->payload,28);
}

void XcisMessage::dumpHex(void *p, size_t size )
{
  unsigned char *bytes = (unsigned char *)p;
  for ( size_t i = 0 ; i < size ; i++ ) {
    unsigned int b = bytes[i];
    Serial.print(b,HEX);
  }
  Serial.println();
}