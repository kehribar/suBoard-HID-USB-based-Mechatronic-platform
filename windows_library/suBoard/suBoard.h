#ifdef SUBOARD
#define EXTERN
#define ASSIGN (x) =x
#else
#define EXTERN extern
#define ASSIGN(x)
#endif

#define ACTIVE 1
#define DISABLE 0

#ifdef _WIN32
#define API_EXPORT __declspec(dllexport)
#define API_CALL  _stdcall
#else
#define API_EXPORT
#define API_CALL
#endif

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
$FE, 1 Clear display
$FE, 2 Return home
$FE, $0C Cursor off
$FE, $0E Underline cursor on
$FE, $0F Blinking cursor on
$FE, $10 Move cursor left one position
$FE, $14 Move cursor right one position
$FE, $80 Move cursor to beginning of first line
$FE, $C0 Move cursor to beginning of second line
$FE, $94 Move cursor to beginning of third line
$FE, $D4 Move cursor to beginning of fourth line
*/

EXTERN API_EXPORT API_CALL hid_device* suBoardOpen(void);
EXTERN API_EXPORT API_CALL unsigned char sendLcd(hid_device* mySuBoard_handle, const char sendBuffer[],unsigned char cmd1,unsigned char cmd2,unsigned char cmd3); //modified
EXTERN API_EXPORT API_CALL unsigned int readAdc(hid_device* mySuBoard_handle, unsigned char channel); // modified
EXTERN API_EXPORT API_CALL unsigned char configurePort(hid_device* mySuBoard_handle, unsigned char portName,unsigned char value); // modified
EXTERN API_EXPORT API_CALL unsigned char readPortConfiguration(hid_device* mySuBoard_handle, unsigned char portName); //modified
EXTERN API_EXPORT API_CALL unsigned char configureAnalogPort(hid_device* mySuBoard_handle, unsigned char value); // Direct write to ADCON1  modified
EXTERN API_EXPORT API_CALL unsigned char readAnalogPortConfiguration(hid_device* mySuBoard_handle);  //modified
EXTERN API_EXPORT API_CALL unsigned char readPort(hid_device* mySuBoard_handle, unsigned char portName); // modified
EXTERN API_EXPORT API_CALL unsigned char writePort(hid_device* mySuBoard_handle, unsigned char portName, unsigned char value); // modified
EXTERN API_EXPORT API_CALL unsigned char initMotor(void);
EXTERN API_EXPORT API_CALL unsigned char stopMotor(void);
EXTERN API_EXPORT API_CALL unsigned char attachServo(unsigned char servoNumber, unsigned char portName, unsigned char pinNumber);
EXTERN API_EXPORT API_CALL unsigned char writeServo(unsigned char servoNumber,unsigned char isActive,unsigned int value);
EXTERN API_EXPORT API_CALL unsigned int writeMotorValue(unsigned char motor1Direction, unsigned int motor1Speed, unsigned char motor2Direction, unsigned int motor2Speed);
EXTERN API_EXPORT API_CALL unsigned int writeMotorValue_A(unsigned char motor1Direction, unsigned int motor1Speed);
EXTERN API_EXPORT API_CALL unsigned int writeMotorValue_B(unsigned char motor2Direction, unsigned int motor2Speed);

#ifdef __cplusplus
}
#endif

