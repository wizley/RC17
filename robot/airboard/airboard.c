/*
 * boardio.c
 *
 *  Created on: Oct 27, 2016
 *      Author: Wizley
 */

#include "ch.h"
#include "udc.h"
#include "airboard.h"
#include "driving.h"

AirBoardObj airBoard = {.id = 0, .size = AIRBOARD_0_SIZE, .state=0x0000};

/*
 * Set/reset one channel of the specified AirBoardObj.
 * channel: 0 = Valve1...
 */
void airSetState(AirBoardObj* ab, uint8_t channel, uint8_t state){
	if (state > 0) {
		ab->state |= (1 << channel);
	}
	else {
		ab->state &= ~(1 << channel);
	}
}

/*
 * Toggles one channel of the air board.
 * Valve 1 = Channel 0
 */

void airToggleState(AirBoardObj* ab, uint8_t channel) {
    if ((ab->state & 1 << channel) > 0) {
        ab->state &= ~(1 << channel);
    } else {
        ab->state |= (1 << channel);
    }
}
