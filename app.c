#include "ch.h"
#include "hal.h"
#include "app.h"
#include "app_list.h"
#include "driving.h"

THD_WORKING_AREA(waApp, 2048);

int app_init(void) {
  chThdCreateStatic(waApp, sizeof(waApp), LOWPRIO, menu.main, NULL);
  InitDriving();
	return 0;
}

