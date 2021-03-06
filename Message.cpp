#include "Arduino.h"
#include "Message.h"
Message::Message()
{
    //Serial.println("Message::Constructor");
    mess.locationID = 0x00;
    mess.deviceType = 0x00;
    mess.command = 0x00;
    for (int i = 0; i < sizeof(mess.payload); i++ )
    {
        mess.payload[i] = 0;
    }
    mess.crc = 0x0000;
    //Serial.print("Message size:");
    //Serial.println(sizeof(mess));
}
void Message::sayHello()
{
  Serial.println("Hello from Message");
  return;
}
void Message::setPayload(uint8_t *data,  size_t size)
{
    memcpy(mess.payload, data, size);
}
void Message::getPayload(uint8_t *data)
{
    memcpy(data, mess.payload, 28);
}
void Message::getBuffer(uint8_t *buffer)
{
    used = 0;
    memmove(&buffer[used], &mess.locationID, sizeof(mess.locationID));
    used += sizeof(mess.locationID);

    memmove(&buffer[used], &mess.deviceType, sizeof(mess.deviceType));
    used += sizeof(mess.deviceType);

    memmove(&buffer[used], &mess.command, sizeof(mess.command));
    used += sizeof(mess.command);

    memmove(&buffer[used], &mess.payload, sizeof(mess.payload));
    used += sizeof(mess.payload);

    memmove(&buffer[used], &mess.crc, sizeof(mess.crc));
    used += sizeof(mess.crc);
    //Serial.print("Used:");
    //Serial.println(used);
    //Serial.print("Sizeof mess:");
    //Serial.println(sizeof(mess));

}
void Message::processBuffer(uint8_t *buffer)
{
    //Serial.println("Message::processBuffer");
    memcpy(&mess, buffer,sizeof(mess));
}
void Message::displayMessage()
{
    Serial.print("Message:");
    Serial.print(mess.locationID,HEX);
    Serial.print(mess.deviceType,HEX);
    Serial.print(mess.command,HEX);
    for (int i = 0; i < sizeof(mess.payload); i++ )
    {
        Serial.print(mess.payload[i],HEX);
    }
    Serial.println(mess.crc,HEX);
}
void Message::dumpHex(void *p, size_t size )
{
  unsigned char *bytes = (unsigned char *)p;
  for ( size_t i = 0 ; i < size ; i++ ) {
    unsigned int b = bytes[i];
    Serial.print(b,HEX);
  }
  Serial.println();
}
uint16_t Message::ip_checksum(void* vdata,size_t length)
{
    // Cast the data pointer to one that can be indexed.
    char* data=(char*)vdata;

    // Initialise the accumulator.
    uint32_t acc=0xffff;

    // Handle complete 16-bit blocks.
    for (size_t i=0;i+1<length;i+=2)
    {
        uint16_t word;
        memcpy(&word,data+i,2);
        //acc+=__builtin_bswap16(word);
        acc+=word;
        if (acc>0xffff)
        {
            acc-=0xffff;
        }
    }

    // Handle any partial block at the end of the data.
    if (length&1)
    {
        uint16_t word=0;
        memcpy(&word,data+length-1,1);
        //acc+=__builtin_bswap16(word);
        acc+=word;
        if (acc>0xffff)
        {
            acc-=0xffff;
        }
    }

    // Return the checksum in network byte order.
    //return __builtin_bswap16(~acc);
    return (~acc);
}