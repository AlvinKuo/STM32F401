/******************************************************************************
 * File: app_msc.h
 * 
 *                                             -- Felix Kuo 2018/05/24
 ******************************************************************************/
#ifndef _APP_MSC_H
#define _APP_MSC_H

/* Exported constants --------------------------------------------------------*/
/* This value can be equal to (512 * x) according to RAM size availability with x=[1, 128]
   In this project x is fixed to 64 => 512 * 64 = 32768bytes = 32 Kbytes */
#define BUFFER_SIZE        ((uint16_t)512*64)


extern FIL MyFile;


extern void Fail_Handler(void);
extern void FatFs_Fail_Handler(void);
extern void Erase_Fail_Handler(void);



extern void App_MSC_Process(void);
extern void App_MSC_FW_Update_Init(void);
extern void App_MSC_FW_Update_Process(void);




#endif  /* _APP_MSC_H */
