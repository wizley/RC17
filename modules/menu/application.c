/*
 * Copyright (C) 2014 Julian Lewis
 * @author Maciej Suminski <maciej.suminski@cern.ch>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/gpl-3.0-standalone.html
 * or you may search the http://www.gnu.org website for the version 3 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

/**
 * User application data structures and routines.
 */

#include "application.h"
#include "event.h"
#include <FreeRTOSConfig.h>

///> Capacity of event queue
#define APP_QUEUE_LEN   16

///> Shared application stack size
#define APP_STACK_SIZE  (configMINIMAL_STACK_SIZE)

///> Prioriuty of application task
#define APP_PRIORITY    (tskIDLE_PRIORITY + 1)

xQueueHandle appQueue;

void startMain(application* app) {
    appQueue = xQueueCreate(APP_QUEUE_LEN, sizeof(struct event));
    if(!appQueue) {
        // TODO oops..
    }

    if(xTaskCreate(app->main, (const signed char*)app->name, APP_STACK_SIZE,
                   NULL, APP_PRIORITY, NULL) != pdPASS) {
        // TODO oops..
    }
}

