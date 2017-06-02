#ifndef MODULES_USAGE_USAGE_H_
#define MODULES_USAGE_USAGE_H_

#define CPU_USAGE_BIN_INTERVAL_MS 300
#define CPU_USAGE_HISTORY_SIZE 8

void cpu_usage_init(void);
float cpu_usage_get_recent(void);
float* cpu_usage_get_history(void);

#endif /* MODULES_USAGE_USAGE_H_ */
