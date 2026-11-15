#include "fatfs_sd.h"

DSTATUS USER_initialize (BYTE pdrv)
{
  /* USER CODE BEGIN INIT */
  return SD_disk_initialize(pdrv);
  /* USER CODE END INIT */
}

DSTATUS USER_status (BYTE pdrv)
{
  /* USER CODE BEGIN STATUS */
  return SD_disk_status(pdrv);
  /* USER CODE END STATUS */
}

DRESULT USER_read (BYTE pdrv, BYTE *buff, DWORD sector, UINT count)
{
  /* USER CODE BEGIN READ */
  return SD_disk_read(pdrv, buff, sector, count);
  /* USER CODE END READ */
}

#if _USE_WRITE == 1
DRESULT USER_write (BYTE pdrv, const BYTE *buff, DWORD sector, UINT count)
{
  /* USER CODE BEGIN WRITE */
  return SD_disk_write(pdrv, buff, sector, count);
  /* USER CODE END WRITE */
}
#endif

#if _USE_IOCTL == 1
DRESULT USER_ioctl (BYTE pdrv, BYTE cmd, void *buff)
{
  /* USER CODE BEGIN IOCTL */
  return SD_disk_ioctl(pdrv, cmd, buff);
  /* USER CODE END IOCTL */
}
#endif