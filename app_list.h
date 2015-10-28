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
 * List of applications.
 */

#ifndef APP_LIST_H
#define APP_LIST_H

#include "app.h"

extern application menu;

extern application motor_test_app;
extern application encoder_test_app;
extern application servo_test_app;
extern application imu_test_app;
extern application line_sensor_test_app;
extern application mainboard_test_app;

extern application set_backlight;
extern application set_date;
extern application set_buzzer;
extern application set_logging;
extern application set_usb;

extern application start_robot;
extern application motor_tuning;
extern application console;
extern application game;
extern application reset;

extern application template;


#endif /* APP_LIST_H */

