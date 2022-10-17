/* 
 * Conversion of FreeRTOS's definitions/types/functions in embeddedRTPS
 * 
 * Copyright (c) 2022 mROS-base
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef RTPS_CONVERSION_H
#define RTPS_CONVERSION_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
typedef uint32_t TickType_t;
#define configTICK_RATE_HZ ((TickType_t)1000)

#ifndef pdMS_TO_TICKS
#define pdMS_TO_TICKS(xTimeInMs) ((TickType_t)(((TickType_t)(xTimeInMs) * (TickType_t)configTICK_RATE_HZ) / (TickType_t)1000))
#endif

#define xTaskGetTickCount osKernelGetTickCount
#define vTaskDelay osDelay

void sys_msleep(unsigned int ms);
#ifdef __cplusplus
}
#endif

#endif /* RTPS_CONVERSION_H */