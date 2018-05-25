/******************************************************************************
 * File: app_iap.c
 *
 *                                             -- Felix Kuo 2018/05/23
 ******************************************************************************/

#include "driver.h"

static uint32_t TmpReadSize = 0x00;
static uint32_t RamAddress = 0x00;
static uint8_t RAM_Buf[BUFFER_SIZE] = {0x00};
static __IO uint32_t LastPGAddress = APPLICATION_ADDRESS;


/**
  * @brief  Programs the internal Flash memory.
  * @param  None
  * @retval None
  */
static void COMMAND_ProgramFlashMemory(void)
{
    uint32_t programcounter = 0x00;
    uint8_t readflag = TRUE;
    uint16_t bytesread;

    /* RAM Address Initialization */
    RamAddress = (uint32_t) &RAM_Buf;

    /* Erase address init */
    LastPGAddress = APPLICATION_ADDRESS;

    /* While file still contain data */
    while ((readflag == TRUE))
    {
        /* Read maximum 512 Kbyte from the selected file */
        f_read (&MyFile, RAM_Buf, BUFFER_SIZE, (void *)&bytesread);

        /* Temp variable */
        TmpReadSize = bytesread;

        /* The read data < "BUFFER_SIZE" Kbyte */
        if(TmpReadSize < BUFFER_SIZE)
        {
            readflag = FALSE;
        }

        /* Program flash memory */
        for (programcounter = 0; programcounter < TmpReadSize; programcounter += 4)
        {
            /* Write word into flash memory */
            if (FLASH_If_Write((LastPGAddress + programcounter),
                               *(uint32_t *) (RamAddress + programcounter)) != 0x00)
            {
                /* Flash programming error: Turn LED2 On and Toggle LED3 in infinite
                 * loop */
                APP_Led_On(Orange);
                APP_Led_Off(Blue);
                Fail_Handler();
            }
        }
        /* Update last programmed address value */
        LastPGAddress += TmpReadSize;
    }
}

/**
  * @brief  IAP Write Flash memory.
  * @param  None
  * @retval None
  */
void COMMAND_Download(void)
{

    /* Open the binary file to be downloaded */
    if(f_open(&MyFile, DOWNLOAD_FILENAME, FA_READ) == FR_OK)
    {
        if(f_size(&MyFile) > USER_FLASH_SIZE)
        {
            /* No available Flash memory size for the binary file: Turn Blue On and
               Toggle Led_R in infinite loop */
            APP_Led_On(Blue);
            Fail_Handler();
        }
        else
        {
            /* Download On Going: Turn Blue On */
            APP_Led_On(Blue);

            /* Erase FLASH sectors to download image */
            if(FLASH_If_EraseSectors(APPLICATION_ADDRESS) != 0x00)
            {
                /* Flash erase error: Turn Orange On and Toggle Led_R infinite loop */
                APP_Led_On(Orange);
                Erase_Fail_Handler();
            }

            /* Program flash memory */
            COMMAND_ProgramFlashMemory();

            /* Download Done: Turn Blue Off and Led_G On */
            APP_Led_Off(Blue);
            APP_Led_On(Led_G);

            /* Close file */
            f_close(&MyFile);
        }
    }
    else
    {
        /* The binary file is not available: Turn LED1, LED2 and LED4 On and Toggle
           LED3 in infinite loop */
        APP_Led_On(Orange);
        APP_Led_On(Blue);
        APP_Led_On(Led_G);
        Fail_Handler();
    }
}

void COMMAND_Jump(void)
{
    /* Software reset */
    NVIC_SystemReset();
}



