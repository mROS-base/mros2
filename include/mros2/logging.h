#ifndef _MROS2_LOGGING_H_
#define _MROS2_LOGGING_H_

#ifndef __MBED__
#include "cmsis_impl_logger.h"
#endif /* __MBED__ */

#define MROS2_LOG_MIN_SEVERITY_DEBUG 0
#define MROS2_LOG_MIN_SEVERITY_INFO 1
#define MROS2_LOG_MIN_SEVERITY_WARN 2
#define MROS2_LOG_MIN_SEVERITY_ERROR 3
#define MROS2_LOG_MIN_SEVERITY_FATAL 4
#define MROS2_LOG_MIN_SEVERITY_NONE 5

#ifndef MROS2_LOG_MIN_SEVERITY
#define MROS2_LOG_MIN_SEVERITY MROS2_LOG_MIN_SEVERITY_DEBUG
#endif

#if (MROS2_LOG_MIN_SEVERITY > MROS2_LOG_MIN_SEVERITY_DEBUG)
#define MROS2_DEBUG(...)
// TODO,,,
#define MROS2_DEBUG_ONCE(...)
#define MROS2_DEBUG_EXPRESSION(...)
#define MROS2_DEBUG_FUNCTION(...)
#define MROS2_DEBUG_SKIPFIRST(...)
#else
#ifdef __MBED__
#define MROS2_DEBUG(...)  do{ printf(__VA_ARGS__); printf("\r\n"); }while(0)
#else /* __MBED__ */
#define MROS2_DEBUG(...)  CMSIS_IMPL_DEBUG(__VA_ARGS__)
#endif /* __MBED__ */
#endif

#if (MROS2_LOG_MIN_SEVERITY > MROS2_LOG_MIN_SEVERITY_INFO)
#define MROS2_INFO(...)
#else
#ifdef __MBED__
#define MROS2_INFO(...)  do{ printf(__VA_ARGS__); printf("\r\n"); }while(0)
#else /* __MBED__ */
#define MROS2_INFO(...)  CMSIS_IMPL_INFO(__VA_ARGS__)
#endif /* __MBED__ */
#endif

#if (MROS2_LOG_MIN_SEVERITY > MROS2_LOG_MIN_SEVERITY_WARN)
#define MROS2_WARN(...)
#else
#ifdef __MBED__
#define MROS2_WARN(...)  do{ printf(__VA_ARGS__); printf("\r\n"); }while(0)
#else /* __MBED__ */
#define MROS2_WARN(...)  CMSIS_IMPL_WARN(__VA_ARGS__)
#endif /* __MBED__ */
#endif

#if (MROS2_LOG_MIN_SEVERITY > MROS2_LOG_MIN_SEVERITY_ERROR)
#define MROS2_ERROR(...)
#else
#ifdef __MBED__
#define MROS2_ERROR(...)  do{ error(__VA_ARGS__); printf("\r\n"); }while(0)
#else /* __MBED__ */
#define MROS2_ERROR(...)  CMSIS_IMPL_ERROR(__VA_ARGS__)
#endif /* __MBED__ */
#endif

#if (MROS2_LOG_MIN_SEVERITY > MROS2_LOG_MIN_SEVERITY_FATAL)
#define MROS2_FATAL(...)
#else
#ifdef __MBED__
#define MROS2_FATAL(...)  do{ error(__VA_ARGS__); printf("\r\n"); }while(0)
#else /* __MBED__ */
#define MROS2_FATAL(...)  CMSIS_IMPL_FATAL(__VA_ARGS__)
#endif /* __MBED__ */
#endif

#endif /* _MROS2_LOGGING_H_ */
