#define SUBOARD
#include <string.h>
#ifdef WIN32
    #include <malloc.h>
#else
    #include <stdlib.h>
#endif
#include "../hidLibrary/hidapi.h"
#include "suBoard.h"

const unsigned short _usVID=0x04D8;
const unsigned short _usPID=0x003F;

EXTERN API_EXPORT API_CALL hid_device *suBoardOpen(void)
{
    struct hid_device_info *phdi=NULL;
    hid_device *phd=NULL;
    char *pszPath=NULL;

    phdi=hid_enumerate(_usVID,_usPID);
    if (phdi==NULL)
    {
        return NULL; // No suBoard device found
    }
    pszPath=strdup(phdi->path);
    if (pszPath==NULL)
    {
        return NULL;
    }
    hid_free_enumeration(phdi);
    phdi=NULL;

    if ((phd=hid_open_path(pszPath))==NULL)
    {
        free(pszPath);
        pszPath=NULL;
        return NULL;
    }
    free(pszPath);
    pszPath=NULL;
    hid_set_nonblocking(phd, 0);
    return phd;
}

static void suBoardClose(hid_device *mySuBoard)
{
    hid_close(mySuBoard);
}

EXTERN API_EXPORT API_CALL unsigned char sendLcd(hid_device* mySuBoard_handle, const char sendBuffer[],unsigned char cmd1,unsigned char cmd2,unsigned char cmd3)
{      
       unsigned char usbIn[65];
       unsigned char usbOut[65];
       memset(usbOut,0xFF,65);
       usbOut[0]=0x0;
       usbOut[1]=0x4A;

       usbOut[3]=cmd1;
       usbOut[4]=cmd2;
       usbOut[5]=cmd3;

       unsigned char index=0;

       while(sendBuffer[index])
       {
            usbOut[6+index]=sendBuffer[index];
            index++;
       }

       usbOut[2]=index;

       hid_write(mySuBoard_handle,usbOut,65);

       memset(usbIn,0xFF,65);
       hid_read(mySuBoard_handle,usbIn,65);
       return 1;

   /* hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    usbOut[0]=0x0;
    usbOut[1]=0x4A;

    usbOut[3]=cmd1;
    usbOut[4]=cmd2;
    usbOut[5]=cmd3;

    unsigned char index=0;

    while(sendBuffer[index])
    {
        usbOut[6+index]=sendBuffer[index];
        index++;
    }

    usbOut[2]=index;

    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;
    return 1;
    */
}

EXTERN API_EXPORT API_CALL unsigned int readAdc(hid_device* mySuBoard_handle, unsigned char channel)
{      
       unsigned char usbIn[65];
       unsigned char usbOut[65];
       memset(usbOut,0xFF,65);

       usbOut[0]=0x0;
       usbOut[1]=0x38;
       usbOut[2]=channel;
       
       hid_write(mySuBoard_handle,usbOut,65);

       memset(usbIn,0xFF,65);
       hid_read(mySuBoard_handle,usbIn,65);
       if(usbIn[0]==0x38)
       {
             unsigned int result = usbIn[1]+(usbIn[2]<<8) ;
             return result;
       }
       else
       {
             return 0;
       }

/*
    hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    usbOut[0]=0x0;
    usbOut[1]=0x38;
    usbOut[2]=channel;

    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;

    if(usbIn[0]==0x38)
    {
        unsigned int result = usbIn[1]+(usbIn[2]<<8) ;
        return result;
    }
    else
    {
        return 0;
    }
    */
}

EXTERN API_EXPORT API_CALL unsigned char configurePort(hid_device* mySuBoard_handle, unsigned char portName,unsigned char value)
{
    unsigned char usbIn[65];
    unsigned char usbOut[65];
    memset(usbOut,0xFF,65);
    
    usbOut[0]=0;
    usbOut[1]=0x39;
    usbOut[2]=portName; // capital letter
    usbOut[3]=value;
    usbOut[4]=1; //writeEnable
    
    hid_write(mySuBoard_handle,usbOut,65);
    
    memset(usbIn,0xFF,65);
    hid_read(mySuBoard_handle,usbIn,65);
    
    if(usbIn[0]==0x39)
    {
        return usbIn[1];
    }
    else
    {
        return 0;
    }
     /*
    hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    usbOut[0]=0;
    usbOut[1]=0x39;
    usbOut[2]=portName; // capital letter
    usbOut[3]=value;
    usbOut[4]=1; //writeEnable

    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;

    if(usbIn[0]==0x39)
    {
        return usbIn[1];
    }
    else
    {
        return 0;
    }
*/
}

EXTERN API_EXPORT API_CALL unsigned char readPortConfiguration(hid_device* mySuBoard_handle, unsigned char portName)
{
    unsigned char usbIn[65];
    unsigned char usbOut[65];
    memset(usbOut,0xFF,65);

    usbOut[0]=0;
    usbOut[1]=0x39;
    usbOut[2]=portName; // capital letter
    usbOut[3]=0xFF;
    usbOut[4]=0; //writeEnable

    hid_write(mySuBoard_handle,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard_handle,usbIn,65);
    
    if(usbIn[0]==0x39)
    {
        return usbIn[1];
    }
    else
    {
        return 0;
    }

    /*hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    usbOut[0]=0;
    usbOut[1]=0x39;
    usbOut[2]=portName; // capital letter
    usbOut[3]=0xFF;
    usbOut[4]=0; //writeEnable

    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;

    if(usbIn[0]==0x39)
    {
        return usbIn[1];
    }
    else
    {
        return 0;
    }
    */

}

EXTERN API_EXPORT API_CALL unsigned char configureAnalogPort(hid_device* mySuBoard_handle, unsigned char value)
{
    unsigned char usbIn[65];
    unsigned char usbOut[65];
    memset(usbOut,0xFF,65);

    usbOut[0]=0;
    usbOut[1]=0x3D;
    usbOut[2]=value;
    usbOut[3]=1; //writeEnable

    hid_write(mySuBoard_handle,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard_handle,usbIn,65);
    if(usbIn[0]==0x3D)
    {
        return usbIn[1];
    }
    else
    {
        return 0;
    }

    /*
    hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    usbOut[0]=0;
    usbOut[1]=0x3D;
    usbOut[2]=value;
    usbOut[3]=1; //writeEnable

    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;

    if(usbIn[0]==0x3D)
    {
        return usbIn[1];
    }
    else
    {
        return 0;
    }

*/
}

EXTERN API_EXPORT API_CALL unsigned char writePort(hid_device* mySuBoard_handle, unsigned char portName, unsigned char value)
{
    unsigned char usbIn[65];
    unsigned char usbOut[65];
    memset(usbOut,0xFF,65);
    usbOut[0]=0;
    usbOut[1]=0x3A;
    usbOut[2]=portName; // Capital Char
    usbOut[3]=value;
    usbOut[4]=1; //writeEnable
    
    hid_write(mySuBoard_handle,usbOut,65);  /* this is a comment */
    memset(usbIn,0xFF,65);
    hid_read(mySuBoard_handle,usbIn,65);
    if(usbIn[0]==0x3A)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    /*   
    hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    usbOut[0]=0;
    usbOut[1]=0x3A;
    usbOut[2]=portName; // Capital Char
    usbOut[3]=value;
    usbOut[4]=1; //writeEnable

    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;

    if(usbIn[0]==0x3A)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    */

}

EXTERN API_EXPORT API_CALL unsigned char readPort(hid_device* mySuBoard_handle, unsigned char portName)
{
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    memset(usbOut,0xFF,65);

    usbOut[0]=0;
    usbOut[1]=0x3A;
    usbOut[2]=portName; // Capital Char
    usbOut[3]=0xFF;
    usbOut[4]=0; //writeDisable

    hid_write(mySuBoard_handle,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard_handle,usbIn,65);

    if(usbIn[0]==0x3A)
    {
        return usbIn[1];
    }
    else
    {
        return 0;
    }
}

EXTERN API_EXPORT API_CALL unsigned char readAnalogPortConfiguration(hid_device* mySuBoard_handle)
{
    unsigned char usbIn[65];
    unsigned char usbOut[65];
    memset(usbOut,0xFF,65);

    usbOut[0]=0;
    usbOut[1]=0x3D;
    usbOut[2]=0xFF;
    usbOut[3]=0; //writeEnable

    hid_write(mySuBoard_handle,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard_handle,usbIn,65);
    if(usbIn[0]==0x3D)
    {
        return usbIn[1];
    }
    else
    {
        return 0;
    }

       /*
    hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    usbOut[0]=0;
    usbOut[1]=0x3D;
    usbOut[2]=0xFF;
    usbOut[3]=0; //writeEnable

    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;

    if(usbIn[0]==0x3D)
    {
        return usbIn[1];
    }
    else
    {
        return 0;
    }
*/
}

EXTERN API_EXPORT API_CALL unsigned char initMotor(void)
{
    hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    usbOut[0]=0;
    usbOut[1]=0x4C;
    usbOut[2]=1;

    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;

    if(usbIn[0]==0x4C)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

EXTERN API_EXPORT API_CALL unsigned char stopMotor(void)
{
    hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    usbOut[0]=0;
    usbOut[1]=0x4C;
    usbOut[2]=0;

    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;

    if(usbIn[0]==0x4C)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

EXTERN API_EXPORT API_CALL unsigned char attachServo(unsigned char servoNumber, unsigned char portName, unsigned char pinNumber)
{
    hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    usbOut[0]=0;
    usbOut[1]=0x3B;
    usbOut[2]=servoNumber;
    usbOut[3]=portName-65; // Convert 'A' -> 0 , 'B' -> 1 , ...
    usbOut[4]=pinNumber;

    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;

    if(usbIn[0]==0x3B)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

EXTERN API_EXPORT API_CALL unsigned char writeServo(unsigned char servoNumber,unsigned char isActive,unsigned int value)
{

    hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    unsigned char valueLow,valueHigh;

    valueLow=value-((value>>8)<<8);
    valueHigh=value>>8;

    usbOut[0]=0;
    usbOut[1]=0x3C;
    usbOut[2]=servoNumber;
    usbOut[3]=isActive;
    if(isActive==1)
    {
        usbOut[4]=valueLow;
        usbOut[5]=valueHigh;
    }
    else
    {
        usbOut[4]=0;
        usbOut[5]=0;
    }
    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;

    if(usbIn[0]==0x3C)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

EXTERN API_EXPORT API_CALL unsigned int writeMotorValue(unsigned char motor1Direction, unsigned int motor1Speed, unsigned char motor2Direction, unsigned int motor2Speed)
{
    hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    unsigned char mot1Low,mot1High,mot2Low,mot2High;

    mot1Low=motor1Speed-((motor1Speed>>8)<<8);
    mot1High=motor1Speed>>8;

    mot2Low=motor2Speed-((motor2Speed>>8)<<8);
    mot2High=motor2Speed>>8;

    usbOut[0]=0;
    usbOut[1]=0x4B;
    usbOut[2]=motor1Direction;
    usbOut[3]=mot1Low;
    usbOut[4]=mot1High;
    usbOut[5]=motor2Direction;
    usbOut[6]=mot2Low;
    usbOut[7]=mot2High;

    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;

    if(usbIn[0]==0x4B)
    {
        static unsigned int result[2];
        result[0]=(usbIn[1]<<8)+usbIn[2];
        result[1]=(usbIn[3]<<8)+usbIn[4];
        return (unsigned int)result;
    }
    else
    {
        return 0;
    }
}

EXTERN API_EXPORT API_CALL unsigned int writeMotorValue_A(unsigned char motor1Direction, unsigned int motor1Speed)
{
    hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    unsigned char mot1Low,mot1High;

    mot1Low=motor1Speed-((motor1Speed>>8)<<8);
    mot1High=motor1Speed>>8;

    usbOut[0]=0;
    usbOut[1]=0x4D;
    usbOut[2]=motor1Direction;
    usbOut[3]=mot1Low;
    usbOut[4]=mot1High;

    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;

    if(usbIn[0]==0x4D)
    {
        static unsigned int result[2];
        result[0]=(usbIn[1]<<8)+usbIn[2];
        result[1]=(usbIn[3]<<8)+usbIn[4];
        return (unsigned int)result;
    }
    else
    {
        return 0;
    }
}

EXTERN API_EXPORT API_CALL unsigned int writeMotorValue_B(unsigned char motor2Direction, unsigned int motor2Speed)
{
    hid_device *mySuBoard=NULL;
    unsigned char usbIn[65];
    unsigned char usbOut[65];

    mySuBoard=suBoardOpen();

    if (mySuBoard==NULL)
    {
        return 0;
    }

    memset(usbOut,0xFF,65);

    unsigned char mot2Low,mot2High;

    mot2Low=motor2Speed-((motor2Speed>>8)<<8);
    mot2High=motor2Speed>>8;

    usbOut[0]=0;
    usbOut[1]=0x4E;
    usbOut[2]=motor2Direction;
    usbOut[3]=mot2Low;
    usbOut[4]=mot2High;

    hid_write(mySuBoard,usbOut,65);

    memset(usbIn,0xFF,65);
    hid_read(mySuBoard,usbIn,65);

    suBoardClose(mySuBoard);
    mySuBoard=NULL;

    if(usbIn[0]==0x4E)
    {
        static unsigned int result[2];
        result[0]=(usbIn[1]<<8)+usbIn[2];
        result[1]=(usbIn[3]<<8)+usbIn[4];
        return (unsigned int)result;
    }
    else
    {
        return 0;
    }
}
