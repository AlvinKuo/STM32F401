/*
 * APP_Global.c
 *
 *  Created on: 2017¦~5¤ë8¤é
 *      Author: felixkuo
 */

#include "driver.h"




void APP_Led_On(led_t led)
{
    switch (led)
    {
#ifdef Device_Anchor

        case Led_R:
            HAL_GPIO_WritePin(GPIO_Port_C, LED_Red, GPIO_PIN_SET);
            break;
        case Led_G:
            HAL_GPIO_WritePin(GPIO_Port_C, LED_Green, GPIO_PIN_SET);
            break;
        case Led_R_1:
            HAL_GPIO_WritePin(GPIO_Port_C, LED_Red_2, GPIO_PIN_SET);
            break;
        case Led_G_1:
            HAL_GPIO_WritePin(GPIO_Port_C, LED_Green_2, GPIO_PIN_SET);
            break;
        case LED_ALL:
            HAL_GPIO_WritePin(GPIO_Port_C, LED_Red | LED_Green | LED_Red_2 | LED_Green_2, GPIO_PIN_SET);
            break;

#endif

#ifdef Device_Tag
        case Red:
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
            break;

        case Green:
            HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
            break;

        case Blue:
            HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
            break;

        case Orange:
            HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_SET);
            break;

        case Led_G:
            HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
            break;

        case Led_R:
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
            break;

        case Led_G_1:
            HAL_GPIO_WritePin(LED_G_1_GPIO_Port, LED_G_1_Pin, GPIO_PIN_SET);
            break;

        case Led_R_1:
            HAL_GPIO_WritePin(LED_R_1_GPIO_Port, LED_R_1_Pin, GPIO_PIN_SET);
            break;

        case LED_ALL:

            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin | LED_GREEN_Pin | LED_BLUE_Pin | LED_ORANGE_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_R_1_GPIO_Port, LED_G_Pin | LED_R_Pin | LED_G_1_Pin | LED_R_1_Pin, GPIO_PIN_SET);

            break;
#endif

        default:
            break;
    }
}

void APP_Led_Off(led_t led)
{
    switch (led)
    {
#ifdef Device_Anchor

        case Led_R:
            HAL_GPIO_WritePin(GPIO_Port_C, LED_Red, GPIO_PIN_RESET);
            break;
        case Led_G:
            HAL_GPIO_WritePin(GPIO_Port_C, LED_Green, GPIO_PIN_RESET);
            break;
        case Led_R_1:
            HAL_GPIO_WritePin(GPIO_Port_C, LED_Red_2, GPIO_PIN_RESET);
            break;
        case Led_G_1:
            HAL_GPIO_WritePin(GPIO_Port_C, LED_Green_2, GPIO_PIN_RESET);
            break;
        case LED_ALL:
            HAL_GPIO_WritePin(GPIO_Port_C, LED_Red | LED_Green | LED_Red_2 | LED_Green_2, GPIO_PIN_RESET);
            break;

#endif

#ifdef Device_Tag
        case Red:
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
            break;

        case Green:
            HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
            break;

        case Blue:
            HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
            break;

        case Orange:
            HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_RESET);
            break;

        case Led_G:
            HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
            break;

        case Led_R:
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
            break;

        case Led_G_1:
            HAL_GPIO_WritePin(LED_G_1_GPIO_Port, LED_G_1_Pin, GPIO_PIN_RESET);
            break;

        case Led_R_1:
            HAL_GPIO_WritePin(LED_R_1_GPIO_Port, LED_R_1_Pin, GPIO_PIN_RESET);
            break;

        case LED_ALL:

            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin | LED_GREEN_Pin | LED_BLUE_Pin | LED_ORANGE_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_R_1_GPIO_Port, LED_G_Pin | LED_R_Pin | LED_G_1_Pin | LED_R_1_Pin, GPIO_PIN_RESET);

            break;
        default:
            break;
#endif
    }
}




#define LED_FLASH_TIME 10
#define LED_FLASH_HANDLE_TICK 10

struct _led_flash_para
{
    volatile unsigned char activate;
    volatile unsigned long tick;

} led_flash_para[Led_Num] = {0};
volatile unsigned long led_flash_handle_tick;

void APP_Led_Flash(led_t LEDx)
{
    APP_Led_On(LEDx);
    led_flash_para[LEDx].activate = 1;
    led_flash_para[LEDx].tick = HAL_GetTick() + LED_FLASH_TIME;
}

void APP_Led_Flash_Init(void)
{
    int i;
    for(i = 0; i < Led_Num; i++)
    {
        led_flash_para[i].activate = 0;
    }

    led_flash_handle_tick = 0;
}


void APP_Led_Flash_Handle(void)
{
    if(!Check_TimeUp(HAL_GetTick(), led_flash_handle_tick))
    {
        return;
    }

    led_flash_handle_tick = HAL_GetTick() + LED_FLASH_HANDLE_TICK;

    int i;
    for(i = 0; i < Led_Num; i++)
    {
        if(led_flash_para[i].activate)
        {
            if(Check_TimeUp(HAL_GetTick(), led_flash_para[i].tick))
            {
                led_flash_para[i].activate=0;
                APP_Led_Off((led_t)i);
            }
        }
    }
}


int Check_TimeUp(unsigned long current_time, unsigned long chk_time)
{
    if(current_time < chk_time)
    {
        return 0;
    }
    else
    {
        unsigned long diff_time = 0;

        diff_time = (current_time - chk_time);

        if((diff_time) > ((U32_MAX - 1) / 2)) //reversion
        {
            return 0;
        }
        return 1;
    }
}


void defMemoryCopy(void* dst, void* src, unsigned char size, unsigned char reverse)
{
    unsigned char uc[8];
    unsigned char ucr[8];
    unsigned char i;

    if (reverse == HI_LO_BYTE_NOT_REVERSE)
    {
        memset(uc, 0, sizeof(uc));
        memset(ucr, 0, sizeof(ucr));
        memcpy(uc, src, size);

        for ( i = 0; i < size; i++)
        {
            ucr[i] = uc[size - i - 1];
        }

        memcpy(dst, ucr, size);
    }
    else if (reverse == HI_LO_BYTE_REVERSE)
    {
        memcpy(dst, src, size);
    }
}

uint8_t APP_Cmd_CheckSum(unsigned int Length, uint8_t *buf)
{
    uint8_t ChkSUM = 0;
    uint8_t i = 0;
    for(i = 0; i < (Length - 1); i++)
    {
        ChkSUM = ChkSUM + (uint8_t)buf[i];
    }
    ChkSUM = (0xFF - ChkSUM) + 1;

    return ChkSUM;
}


unsigned long MAKEULONG(char Buffer_0, char Buffer_1,char Buffer_2,char Buffer_3)
{
    unsigned long LongData;
    unsigned int TempData[2];

    TempData[0]=MAKEUINT(Buffer_0,Buffer_1);
    TempData[1]=MAKEUINT(Buffer_2,Buffer_3);

    LongData=0;
    LongData += TempData[0];
    LongData = LongData << 16;
    LongData += TempData[1];

    return LongData;
}


unsigned int APP_Buffer_Compare(unsigned char * BufferA, unsigned char * BufferB, unsigned int BufferLngth)
{
    unsigned char loop;
    unsigned int idx, NumOfDiff;

    NumOfDiff=0;
    loop=1;
    idx=0;

    while(loop)
    {
        if (BufferA[idx] != BufferB[idx])
        {
            NumOfDiff++;
        }

        idx++;

        if(BufferLngth <= idx)
        {
            loop=0; //compare at the end of buffer
        }
    }

    return NumOfDiff;
}




struct _sys_reboot_para
{
    unsigned short activate;
    unsigned long acting_time;
    unsigned long timer;
} sys_reboot_para = {0};

void System_Reboot_Activate(unsigned long acting_time)
{
    sys_reboot_para.acting_time = acting_time;
    sys_reboot_para.timer = HAL_GetTick();
    sys_reboot_para.activate = 0xF5A0;
}


void System_Reboot_Handle(void)
{
    if((sys_reboot_para.activate == 0xF5A0) && ((HAL_GetTick() - sys_reboot_para.timer) >= sys_reboot_para.acting_time))
    {
        HAL_NVIC_SystemReset();
    }
}


