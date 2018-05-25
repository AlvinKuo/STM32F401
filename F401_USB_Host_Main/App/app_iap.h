/******************************************************************************
 * File: app_iap.h
 * 
 *                                             -- Felix Kuo 2018/05/23
 ******************************************************************************/
#ifndef _APP_IAP_H
#define _APP_IAP_H

#include "flash_if.h"

#define UPLOAD_FILENAME            "0:UPLOAD.BIN"
#define DOWNLOAD_FILENAME          "0:image.BIN"









extern void COMMAND_Jump(void);


extern void COMMAND_Download(void);

#endif  /* _APP_IAP_H */
