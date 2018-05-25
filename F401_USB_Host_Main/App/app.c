/******************************************************************************
 * File: app.c
 *
 *                                             -- Felix Kuo 2018/03/26
 ******************************************************************************/

#include "driver.h"


//Test
pFunction JumpToApplication;
uint32_t JumpAddress;



void APP_HW_Ctrl(void)
{
	
}


void App_Init(void)
{
	uint8_t i = 20;	
	
	
    while(i--)
    {
        if (i & 1) APP_Led_Off(LED_ALL);
        else	APP_Led_On(Orange);
        HAL_Delay(50);
    }
	
	APP_Led_Flash_Init();

}

void App_Process(void)
{
    System_Reboot_Handle();
    APP_Led_Flash_Handle();    
}



void APP_Run_Application(void)
{
    /* Test if user code is programmed starting from address "APPLICATION_ADDRESS" */
    if (((*(__IO uint32_t*)APPLICATION_ADDRESS) & 0x2FFE0000 ) == 0x20000000)
    {
        /* Jump to user application */
        JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
        JumpToApplication = (pFunction) JumpAddress;
        /* Initialize user application's Stack Pointer */
        __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
        JumpToApplication();
    }
}









