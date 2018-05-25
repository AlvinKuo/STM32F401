/*
 * APP_Global.h
 *
 *  Created on: 2017¦~5¤ë8¤é
 *      Author: felixkuo
 */

#ifndef APP_GLOBAL_H_
#define APP_GLOBAL_H_



extern uint8_t debug_MSG[128];
extern int sys;


#define Consle_Debug	0
#define TCP_Debug 		0
#define DW1000_Debug	0





#define HiByte(value)             ((unsigned char)((value) >>8))
#define LoByte(value)             ((unsigned char)(value))
#define HIWORD(value)             ((unsigned int)((value) >>16))
#define LOWORD(value)             ((unsigned int)(value))
#define MAKEUINT(value1, value2)  ((((unsigned int)value1) << 8) + value2)
#define MAKEBYTE(value1, value2)  ((value1 <<4) + value2)


#define Set 	1
#define Clear 	0

#define Success 	(0)
#define Fail		(-1)
#define CRC_Fail	(-2)



#define HI_LO_BYTE_NOT_REVERSE		0
#define HI_LO_BYTE_REVERSE			1

/*******************************************************************
HI_LO_BYTE_NOT_REVERSE
unsinged int value is 0x00003039	=> buffer data is 0x00 0x00 0x30 0x39
unsigned short value is 0x3039		=> buffer data is 0x30 0x39
unsigned char value is 0x12			=> buffer data is 0x0C
HI_LO_BYTE_REVERSE
unsinged int value is 0x00003039	=> buffer data is 0x39 0x30 0x00 0x00
unsigned short value is 0x3039		=> buffer data is 0x39 0x30
unsigned char value is 0x12			=> buffer data is 0x0C

*******************************************************************/


#pragma pack(1)

/**
 * @union _var8
 * @brief union type for 16bit varable
 */
typedef union _var8
{
    unsigned char u8;		///< 8bit variable
    char s8;
    struct
    {
        unsigned char b0: 1; ///< 1bit low byte variable
        unsigned char b1: 1;
        unsigned char b2: 1;
        unsigned char b3: 1;
        unsigned char b4: 1;
        unsigned char b5: 1;
        unsigned char b6: 1;
        unsigned char b7: 1; ///< 1bit high byte variable
    } u1;
} var8;

/**
 * @union _var16
 * @brief union type for 16bit varable
 */
typedef union _var16
{
    unsigned short u16; 	///< 16bit variable
    short s16;
    struct
    {
        unsigned char lo;	///< 8bit low byte variable
        unsigned char hi;	///< 8bit high byte variable
    } u8;
} var16;

/**
 * @union _var32
 * @brief union type for 32bit variable
 */
typedef union _var32
{
    unsigned long u32;		///< 32bit variable
    long s32;
    struct
    {
        unsigned short lo;	///< 16bit lower variable
        unsigned short hi;	///< 16bit higher variable
    } u16;
    struct
    {
        unsigned char b0;	///< 8bit byte 0 variable
        unsigned char b1;	///< 8bit byte 1 variable
        unsigned char b2;	///< 8bit byte 2 variable
        unsigned char b3;	///< 8bit byte 3 variable
    } u8;
} var32;

typedef union _var64
{
    unsigned long long u64;
    long long s64;
    struct
    {
        unsigned long lo;
        unsigned long hi;
    } u32;
    struct
    {
        unsigned short b0;
        unsigned short b1;
        unsigned short b2;
        unsigned short b3;
    } u16;
    struct
    {
        unsigned char b0;	///< 8bit byte 0 variable
        unsigned char b1;	///< 8bit byte 1 variable
        unsigned char b2;	///< 8bit byte 2 variable
        unsigned char b3;	///< 8bit byte 3 variable
        unsigned char b4;	///< 8bit byte 0 variable
        unsigned char b5;	///< 8bit byte 1 variable
        unsigned char b6;	///< 8bit byte 2 variable
        unsigned char b7;	///< 8bit byte 3 variable
    } u8;
} var64;
#pragma pack()


typedef enum
{
#ifdef Device_Tag
    Red,
    Green,
    Blue,
    Orange,
#endif
    Led_G,
    Led_R,
    Led_G_1,
    Led_R_1,
    Led_Num,

    LED_ALL,
} led_t;


/*
#define U8_MAX                          ((u8)255)
#define S8_MAX                          ((s8)127)
#define S8_MIN                          ((s8)-128)
#define U16_MAX                         ((u16)65535u)
#define S16_MAX                         ((s16)32767)
#define S16_MIN                         ((s16)-32768)
#define U32_MAX                         ((u32)4294967295uL)
#define S32_MAX                         ((s32)2147483647)
#define S32_MIN                         ((s32)-2147483648uL)
#define U64_MAX                         ((u64)18446744073709551615uL)
#define S64_MAX                         ((s64)9223372036854775807)
#define S64_MIN                         ((s64)-9223372036854775808uL)
#define DBL_MAX                         (1.7976931348623158e+308)
#define DBL_MIN                         (2.2250738585072014e-308)
#define FLT_MAX                         (3.402823466e+38F)
#define FLT_MIN                         (1.175494351e-38F)
*/

#define U32_MAX                         ((uint32_t)4294967295uL)


extern void APP_Led_On(led_t led);
extern void APP_Led_Off(led_t led);
extern void APP_Led_Flash(led_t LEDx);
extern void APP_Led_Flash_Init(void);
extern void APP_Led_Flash_Handle(void);
extern int Check_TimeUp(unsigned long current_time, unsigned long chk_time);
extern void defMemoryCopy(void* dst, void* src, unsigned char size, unsigned char reverse);
extern uint8_t APP_Cmd_CheckSum(unsigned int Length, uint8_t *buf);
extern unsigned long MAKEULONG(char Buffer_0, char Buffer_1,char Buffer_2,char Buffer_3);
extern unsigned int APP_Buffer_Compare(unsigned char * BufferA, unsigned char * BufferB, unsigned int BufferLngth);

void SystemClock_Config(void);
void System_Reboot_Activate(unsigned long acting_time);
void System_Reboot_Handle(void);

#endif /* APP_GLOBAL_H_ */
