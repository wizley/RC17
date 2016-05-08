
#include "ch.h"
#include "hal.h"
#include "usage.h"
#include "string.h"

uint32_t idle_ticks;
uint32_t idle_enter_systime;
float cpu_usage = 0.0f;
float cpu_usage_history[CPU_USAGE_HISTORY_SIZE] = {0.0f};

static THD_WORKING_AREA(wausage, 128);
static THD_FUNCTION(CPUUSAGE, arg) {
  (void)arg;
  chRegSetThreadName("CPU Usage");
  while (TRUE) {
    idle_ticks = 0;
    chThdSleepMilliseconds(CPU_USAGE_BIN_INTERVAL_MS);
    cpu_usage = (1.0f - (float) idle_ticks / MS2ST(CPU_USAGE_BIN_INTERVAL_MS)) * 100.0;
    memmove(&cpu_usage_history[1], cpu_usage_history, sizeof(float) * (CPU_USAGE_HISTORY_SIZE -1));
    cpu_usage_history[0] = cpu_usage;
  }
}

void cpu_usage_init(void){
  chThdCreateStatic(wausage, sizeof(wausage), LOWPRIO, CPUUSAGE, NULL);
}

float cpu_usage_get_recent(void){
  return cpu_usage;
}

float* cpu_usage_get_history(void){
 return cpu_usage_history;
}
