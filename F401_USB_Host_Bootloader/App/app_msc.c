/******************************************************************************
 * File: app_msc.c
 *
 *                                             -- Felix Kuo 2018/05/24
 ******************************************************************************/

#include "driver.h"


extern ApplicationTypeDef Appli_state;
extern USBH_HandleTypeDef hUsbHostFS;

FIL MyFile;
FRESULT file_res;

uint8_t wtext[] = "USB Host Library : Mass Storage Example";
uint8_t rtext[200];

uint32_t bytesWritten;
__IO uint32_t UploadCondition = 0x00;



void Fail_Handler(void)
{
  while(1)
  {
    /* Toggle LED3 */
    HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin); 
    HAL_Delay(100);
  }
}

void Erase_Fail_Handler(void)
{
  while(1)
  {
    /* Toggle Led_R */    
    HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin); 
    HAL_Delay(100);
  }
}


void FatFs_Fail_Handler(void)
{
  while(1)
  {
    /* Toggle LED_R */
	HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin); 
	HAL_Delay(100);
  }
}


static void USBH_USR_BufferSizeControl(void)
{
  /* Control BUFFER_SIZE and limit this value to 32Kbyte maximum */
  if((BUFFER_SIZE % 4 != 0x00) || (BUFFER_SIZE / 4 > 8192))
  {
    while(1)
    {
      /* Toggle Led_R */      
      HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);      
      HAL_Delay(100);
    }
  }
}





void App_MSC_FW_Update_Init(void)
{			
	if(f_mount(&USBHFatFS, (TCHAR const*) USBHPath, 0) != FR_OK)
	{		
		APP_Led_Off(Blue);
		FatFs_Fail_Handler();
	}
	else
	{
		FLASH_If_FlashUnlock();		
	}

}

void App_MSC_FW_Update_Process(void)
{	
	while(USBH_MSC_IsReady(&hUsbHostFS))
	{
		/* Control BUFFER_SIZE value */
		USBH_USR_BufferSizeControl();
		
		APP_Led_Off(Blue);
		
		/* Writes Flash memory */
		COMMAND_Download();
		
		/* Jump to user application code located in the internal Flash memory */
        COMMAND_Jump();
	
	}
}




void App_MSC_Process(void)
{
    switch(Appli_state)
    {
        case APPLICATION_IDLE:

            break;

        case APPLICATION_START:

            App_MSC_FW_Update_Init();
		
			//APP_Led_On(Led_R_1);

            break;

        case APPLICATION_READY:
			
			//APP_Led_On(Led_G_1);

            App_MSC_FW_Update_Process();

            Appli_state = APPLICATION_IDLE;

            break;

        case APPLICATION_DISCONNECT:

			/*
            if(f_close(&MyFile) == FR_OK)
            {
                APP_Led_Off(LED_ALL);
                APP_Led_On(Led_G_1);
            }
			*/
            break;

    }

}


