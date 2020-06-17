#include <stdint.h>
#include <am_util_delay.h>
#include "main.h"

#define EPOCH_DEEPSLEEP 1
#define EPOCH_CONFIG	5
static uint32_t jiffies = 0;

TaskHandle_t config_task_handle;

void ConfigTaskSetup()
{
	uprintf("%s initialization...\r\n", __FUNCTION__);
}

void ConfigTask(void * param)
{
}
