#include "Arduino.h"
#include "XcisMessage.h"
#include <stdio.h>
#include <string.h>


XcisMessage::XcisMessage()
{
  // Constructor
  
  Serial.println("XcisMessage::Constructor");
 

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
void XcisMessage::createMessage(uint8_t *data, uint8_t locationID, uint8_t sensorType, uint8_t command, uint8_t *paydata)
{
  Serial.println("XcisMessage::createMessage");
  this->message.setLocationID(locationID);
  this->message.setSensorType(sensorType);
  this->message.setCommand(command);
  // Copy payload into message payload
  //memcpy(this->payload, paydata, sizeof(payload));
  //this->message.setPayload(this->payload,sizeof(this->payload));
  // Can do direct copy provided size is set
  this->message.setPayload(paydata,28);
  this->message.setCrc(0x45);
  this->message.displayMessage();
  // Convert the message structure into a buffer
  this->message.getBuffer(this->buffer);
  // Copy the buffer into the incoming user buffer
  memcpy(data, this->buffer, sizeof(buffer));
}
void XcisMessage::processMessage(uint8_t *data)
{
  Serial.println("XcisMessage::processMessage");
  this->message.processBuffer(data);
  // check the payload
  this->message.getPayload(this->payload);
  // Payload is stored here - can now process.
  dumpHex(this->payload,28);
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