#ifndef __CONFIG_TASK_H__
#define __CONFIG_TASK_H__

extern TaskHandle_t config_task_handle;

void ConfigTaskSetup();
void ConfigTask(void * param);

#endif
