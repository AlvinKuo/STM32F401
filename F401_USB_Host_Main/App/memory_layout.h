/******************************************************************************
 * File: memory_layout.h
 *
 *                                             -- Joseph Hsu 2018/01/12
 ******************************************************************************/
#ifndef _MEMORY_LAYOUT_H
#define _MEMORY_LAYOUT_H


//ROM/Flash/Code
#define ROM_ADDRESS                      (0x08000000) //flash address

#define BOOT_CODE_SIZE                   (32 * 1024) //32 KBytes
#define BOOT_CODE_START_ADDR             (ROM_ADDRESS)
#define BOOT_CODE_END_ADDR               (BOOT_CODE_START_ADDR + BOOT_CODE_SIZE)

#define MAIN_CODE_OFFSET                 (BOOT_CODE_SIZE)
#define MAIN_CODE_SIZE                   (224 * 1024) //224 KBytes
#define MAIN_CODE_START_ADDR             (ROM_ADDRESS + MAIN_CODE_OFFSET)
#define MAIN_CODE_END_ADDR               (MAIN_CODE_START_ADDR + MAIN_CODE_SIZE)

//RAM
#define RAM_ADDRESS                      (0x20000000)
#define RAM_SIZE                         (0x00010000)




#if 0

/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbyte */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbyte */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbyte */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbyte */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbyte */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbyte */


#define UPDATA_SIZE                      (114 * 1024) //114KBytes
#define UPDATA_START_ADDR                (MAIN_CODE_END_ADDR)
#define UPDATA_END_ADDR                  (UPDATA_START_ADDR + UPDATA_SIZE)

//last 2n page   0x08000000 + 0x40000 - 0x1000
#define SYS_PARA_SIZE                     (2* 1024) //2 Kbytes for setting
#define SYS_PARA_START_ADDR               (UPDATA_END_ADDR)
#define SYS_PARA_END_ADDR                 (SYS_PARA_START_ADDR + SYS_PARA_SIZE)

//last page  0x08000000 + 0x40000 - 0x800
#define INFO_SIZE                        (2* 1024) //2 Kbytes for infomation data
#define INFO_START_ADDR                  (ROM_ADDRESS+ROM_SIZE-INFO_SIZE)
#define INFO_END_ADDR                    (ROM_ADDRESS+ROM_SIZE)


#endif


#endif  /* _MEMORY_LAYOUT_H */
