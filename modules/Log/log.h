
#ifndef MODULES_LOG_LOG_H_
#define MODULES_LOG_LOG_H_

#include "chprintf.h"
#include "start_robot_page_gui.h"
#include "RTTLog.h"

//#define log_i(...) do {} while(0)
//TODO : better gwinconsole handling
#define log_i(...) do {                                   \
  if(ghConsole != NULL)chprintf(gwinConsoleGetStream(ghConsole), __VA_ARGS__); \
  chprintf((BaseSequentialStream*)&RTT_Log, __VA_ARGS__); \
} while(0)

#endif /* MODULES_LOG_LOG_H_ */
