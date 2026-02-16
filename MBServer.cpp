#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <winsock.h>
#include "MBServer.h"

typedef enum
{
    TRANSACTION_ID_SHIFT = 0,
    PROTOCOL_ID_SHIFT = 2,
    LENGHT_SHIFT = 4,
    UNIT_ID_SHIFT = 6,
} MBAP_Offsets;

typedef enum
{
    FUNCTION_CODE_SHIFT = 7,
    START_ADDR_SHIFT = 8,
    QUANTITY_SHIFT = 10,
    BYTE_COUNT_SHIFT = 12,
    DATA_SHIFT
} PDU_Offsets;

typedef enum
{
    RD_COILS = 1,
    RD_CONTCTS = 2,
    RD_H_REGS = 3,
    RD_IN_REGS = 4,
    WR_SINGLE_COIL = 5,
    WR_SINGLE_REG = 6,
    RD_EXEPTION_STATUS = 7,
    DIAGNOSTIC = 8,
    WR_MULT_COILS = 15,
    WR_MULT_REGS = 16,
    REPORT_SERVER_ID = 17
} MB_Cmd;

typedef enum
{
    ILLEGAL_FUNCTION = 0x01,
    ILLEGAL_DATA_ADDRESS = 0x02,
    ILLEGAL_DATA_VALUE = 0x03,
    SLAVE_DEVICE_FAILURE = 0x04,
    SLAVE_DEVICE_BUSY  = 0x06
} MBExceptionCode;


//extern uint16_t regsRO[256];
using namespace std;
mutex mtx;

uint8_t MBServer::GetCmd(char* buf)
{
    return RD_IN_REGS;
}
uint16_t MBServer::GetStartOffset(char* buf)
{
    uint16_t temp;
    memcpy(&temp, buf + START_ADDR_SHIFT, 2);
    return ntohs(temp);
}
uint16_t MBServer::GetDataQuantity(char* buf)
{
    uint16_t temp;
    memcpy(&temp, buf + QUANTITY_SHIFT, 2);
    return ntohs(temp);
}
uint8_t MBServer::GetByteCount(char* buf)
{
   return buf[BYTE_COUNT_SHIFT];
}
char* MBServer::GetDataPtr(char* buf)
{
   return buf + DATA_SHIFT;
}


// in regs, a pointer to the first register for writing/reading
// in sz, the number of two-byte registers for writing/reading
// The buf array contains a Modbus (MBAP+PDU) packet received from the network
// in the form in which they came in a ModBus packet from the network.
void MBServer::RegsWrite(uint16_t* regs, char* buf,  unsigned char sz)
{

}
//  After reading, the buf array contains a buffer ready to be sent to the network.
void MBServer::RegsRead(uint16_t* regs, char* buf,  unsigned char sz)
{
   uint16_t temp;
   char* dataPtr;// = GetDataPtr(buf);
   lock_guard<mutex>lock(mtx);
   {
       memcpy(buf, (char*) rgsInp, 4);
       dataPtr = buf + 4;
       int rgsShift = 2;
       for (int dataNum = 0; dataNum < sz - 2; ++dataNum)
           memcpy(dataPtr + dataNum * 2, (char*) &rgsInp[rgsShift + dataNum], 2);
   }
//   for(int regCnt = 0; regCnt < regsNum; ++regCnt)
//   {
//       memcpy(buf, (char*) &rgsInp[regCnt], 2);
////       temp = htons(regs[regCnt]);
////       memcpy(dataPtr + 2 * regCnt, &temp, 2);
//   }
}

MBServer::MBServer(uint16_t* holdRegs, uint16_t* inpRegs, unsigned int holdRgSz, unsigned int inpRgSz) :
    rgsHold (holdRegs), rgsInp(inpRegs), szRgHold(holdRgSz), szRgInp(inpRgSz)
{

}
// The buf array contains a Modbus (MBAP+PDU) packet received from the network
// len is the length of the data (MBAP+PDU) in buf in bytes
// Server performs all the necessary actions and writes the data
//   that needs to be sent to the network to the buf
// The server returns the length of the output data (MBAP+PDU) in bytes
//   written to the buf
// !! The function calling the Server must ensure that
// !! the size of the buf is at least 260 bytes
int MBServer::Server(char* buf, int len, int* errCode)
{
    RegsRead(rgsInp, buf, len);
}
 MBServer::~MBServer()
{

}


 ////////////////////////////////////////////////


 //static uint16_t GetTransactionID(char* buf)
 //{
 //    uint16_t temp;
 //    memcpy(&temp, buf, 2);
 //    return ntohs(temp);
 //}

 //static uint16_t GetProtocolID(char* buf)
 //{
 //    uint16_t temp;
 //    memcpy(&temp, buf +PROTOCOL_ID_SHIFT, 2);
 //    return ntohs(temp);
 //}

 //static uint16_t GetPDUplusUILen(char* buf)
 //{
 //    uint16_t temp;
 //    memcpy(&temp, buf + LENGHT_SHIFT, 2);
 //    return ntohs(temp);
 //}

 //static uint16_t GetStartOffset(char* buf)
 //{
 //    uint16_t temp;
 //    memcpy(&temp, buf + START_ADDR_SHIFT, 2);
 //    return ntohs(temp);
 //}

 //static uint16_t GetDataSize(char* buf)
 //{
 //    uint16_t temp;
 //    memcpy(&temp, buf + QUANTITY_SHIFT, 2);
 //    return ntohs(temp);
 //}

 ////uint16_t* rgsHold;
 //uint16_t* rgsInp;
