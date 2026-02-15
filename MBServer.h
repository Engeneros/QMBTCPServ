#ifndef MBSERVER_H
#define MBSERVER_H

#define uint16_t unsigned short
#define uint8_t unsigned char



class MBServer
{
private:
    uint16_t* rgsHold;
    uint16_t* rgsInp;
    uint16_t szRgHold;
    uint16_t szRgInp;
    uint16_t regsNum;
    uint8_t GetCmd(char* buf);
    uint16_t GetStartOffset(char* buf);
    uint16_t GetDataQuantity(char* buf);
    uint8_t GetByteCount(char* buf);
    char* GetDataPtr(char* buf);
    // in regs, a pointer to the first register for writing/reading
    // in sz, the number of two-byte registers for writing/reading
    // The buf array contains a Modbus (MBAP+PDU) packet received from the network
    // in the form in which they came in a ModBus packet from the network.
    void RegsWrite(uint16_t* regs, char* buf,  unsigned char sz);
    //  After reading, the buf array contains a buffer ready to be sent to the network.
    void RegsRead(uint16_t* regs, char* buf,  unsigned char sz);
public:
    MBServer(uint16_t* holdRegs, uint16_t* inpRegs, unsigned int holdRgSz, unsigned int inpRgSz);
    // The buf array contains a Modbus (MBAP+PDU) packet received from the network
    // len is the length of the data (MBAP+PDU) in buf in bytes
    // Server performs all the necessary actions and writes the data
    //   that needs to be sent to the network to the buf
    // The server returns the length of the output data (MBAP+PDU) in bytes
    //   written to the buf
    // !! The function calling the Server must ensure that
    // !! the size of the buf is at least 260 bytes
    int Server(char* buf, int len, int* errCode);
    ~MBServer();
};




#endif // MBSERVER_H
