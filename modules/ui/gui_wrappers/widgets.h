/*
 * widgets.h
 *
 *  Created on: Apr 21, 2016
 *      Author: Melvin
 */

#ifndef MODULES_UI_GUI_WRAPPERS_WIDGETS_H_
#define MODULES_UI_GUI_WRAPPERS_WIDGETS_H_

#include "gfx.h"
/* Creating container */
GHandle  createContainer(int x, int y, int width, int height, uint8_t needBorder);
//#define createContainer  createContainer

/* Creating graph */
//GHandle  createGraph(GHandle* container, GGraphObject* gobj, int x, int y, int width, int height);

/* Creating button */
GHandle  createButton(const char* text, int x, int y, int width, int height);
GHandle  createButtonInContainer(GHandle* container, const char* text, int x, int y, int width, int height);
//#define createButton  createButton

/* Creating label */
GHandle  createLabel(const char* text, int x, int y, int width, int height);
GHandle  createLabelInContainer(GHandle* container, const char* text, int x, int y, int width, int height);
void  updateLabel(GHandle *label, int show);

GHandle  createProgressBar(const char* text, int x, int y, int width, int height);
GHandle  createProgressBarInContainer(GHandle* container, const char* text, int x, int y, int width, int height);
//#define createProgressBar  createProgressBar

GHandle createConsole(GHandle* container, int x, int y, int width, int height);
//#define createConsole _createConsole

#endif /* MODULES_UI_GUI_WRAPPERS_WIDGETS_H_ */
