/******************************************************************************
 * File: app.h
 *
 *                                             -- Felix Kuo 2018/03/26
 ******************************************************************************/
#ifndef _APP_H
#define _APP_H

extern void App_Init(void);
extern void APP_HW_Ctrl(void);
extern void App_Process(void);
extern void APP_FW_Update_Check(void);
extern void APP_Run_Application(void);

#endif  /* _APP_H */
