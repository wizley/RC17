/*
 * widgets.c
 *
 *  Created on: Apr 21, 2016
 *      Author: Melvin
 */
#include "widgets.h"


//GWidgetInit wi;

GHandle  createConsole(GHandle* container, int x, int y, int width, int height){
  GWidgetInit wi;
  gwinWidgetClearInit(&wi);
  wi.g.show = TRUE;
  wi.g.x = x;
  wi.g.y = y;
  wi.g.width = width;
  wi.g.height = height;
  if (container != NULL)
     wi.g.parent = (*container);
  return gwinConsoleCreate(0, &wi.g);


  return;
}

GHandle  createProgressBar( const char* text, int x, int y, int width, int height){
   GWidgetInit   wi;
   gwinWidgetClearInit(&wi);
   wi.g.show = TRUE;
   wi.g.x = x; wi.g.y = y;
   wi.g.width = width; wi.g.height = height;
   wi.text = text;
   return gwinProgressbarCreate(NULL,&wi);
}

GHandle  createProgressBarInContainer(GHandle* container, const char* text, int x, int y, int width, int height){
   GWidgetInit   wi;
   gwinWidgetClearInit(&wi);
   wi.g.show = TRUE;
   wi.g.parent = (*container);
   wi.g.x = x; wi.g.y = y;
   wi.g.width = width; wi.g.height = height;
   wi.text = text;
   return gwinProgressbarCreate(NULL,&wi);
}

//GHandle  createGraph(GHandle* container, GGraphObject* gobj, int x, int y, int width, int height){
//    GWidgetInit graphContainerInit; GWindowInit wi;
//    gwinWidgetClearInit(&graphContainerInit);
//    graphContainerInit.g.show = FALSE;
//    graphContainerInit.g.x = x; graphContainerInit.g.y = y;
//    graphContainerInit.g.width = width; graphContainerInit.g.height = height;
//    (*container) = gwinContainerCreate(0, &graphContainerInit, GWIN_CONTAINER_BORDER);
//
//    gwinClearInit(&wi);
//    wi.show = FALSE;
//    wi.parent = (*container);
//    wi.x = 0; wi.y = y;
//    wi.width = wi.parent->width; wi.height = wi.parent->height;
//    (*graph) = gwinGraphCreate(gobj, &wi);
//    gwinGraphSetOrigin(*graph, 0, 0);
//    gwinGraphSetStyle(*graph,&defaultGraphStyle);
//    gwinGraphDrawAxis(*graph);
//    return;
//}
//GHandle  updateGraph(float data_cache[GRAPH_CACHE_SIZE], const float* data, int data_length){
//  gwinGraphStartSet(*graph);
//  for(_i=0;_i<GRAPH_CACHE_SIZE-data_length;_i++)
//    data_cache[_i] = data_cache[_i+data_length];
//  for(_i=GRAPH_CACHE_SIZE-data_length;_i<GRAPH_CACHE_SIZE;_i++)
//    data_cache[_i] = data[_i-(GRAPH_CACHE_SIZE-data_length)];
//  for(_i=0;_i<GRAPH_CACHE_SIZE;_i++)
//    gwinGraphDrawPoint(*graph,_i,data_cache[_i]);
//  return;
//}
GHandle  createContainer(int x, int y, int width, int height, uint8_t needBorder){
    GWidgetInit wi;
    gwinWidgetClearInit(&wi);
    wi.g.show = FALSE;
    wi.g.x = x; wi.g.y = y;
    wi.g.width = width; wi.g.height = height;
    wi.g.parent = 0; wi.text = "Container";
    wi.customDraw = 0;
    wi.customParam = 0;
    wi.customStyle = 0;
    if(needBorder)
        return gwinContainerCreate(0, &wi, GWIN_CONTAINER_BORDER);
    else
        return gwinContainerCreate(0, &wi, 0);
}

/**
 * @brief Create a button
 * @param aButton   a button object
 * @param text      text shown on the button
 * @param x         x coordinate
 * @param y         y coordinate
 * @param width     width of the button
 * @param height    height of the button
 */
GHandle  createButton(const char* text, int x, int y, int width, int height){
  GWidgetInit   wi;
  gwinWidgetClearInit(&wi);
  wi.g.show = TRUE;
  wi.g.x = x; wi.g.y = y;
  wi.g.width = width; wi.g.height = height;
  wi.text = text;
  return gwinButtonCreate(NULL,&wi);
}
GHandle  createButtonInContainer(GHandle* container, const char* text, int x, int y, int width, int height){
  GWidgetInit   wi;
  gwinWidgetClearInit(&wi);
  wi.g.show = TRUE;
  wi.g.parent = (*container);
  wi.g.x = x; wi.g.y = y;
  wi.g.width = width; wi.g.height = height;
  wi.text = text;
  return gwinButtonCreate(NULL,&wi);
}

/**
 * @brief Create a label
 * @param aLabel    a label object
 * @param text      text shown on the label
 * @param x         x coordinate
 * @param y         y coordinate
 * @param width     width of the label
 * @param height    height of the label
 */
GHandle  createLabel(const char* text, int x, int y, int width, int height){
  GWidgetInit     wi;
  // Apply some default values for GWIN
  wi.customDraw = 0;
  wi.customParam = 0;
  wi.customStyle = 0;
  wi.g.show = TRUE;
  wi.g.x = x; wi.g.y = y;
  wi.g.width = width; wi.g.height = height;
  wi.text = text;
  return gwinLabelCreate(NULL, &wi);
}
GHandle  createLabelInContainer(GHandle* container, const char* text, int x, int y, int width, int height){
      GWidgetInit     wi;
      // Apply some default values for GWIN
      wi.customDraw = 0;
      wi.customParam = 0;
      wi.customStyle = 0;
      wi.g.show = TRUE;
      wi.g.parent = (*container);
      wi.g.x = x; wi.g.y = y;
      wi.g.width = width; wi.g.height = height;
      wi.text = text;
      return gwinLabelCreate(NULL, &wi);
}

/**
 * @brief   update the text of the label with an integer
 * @param   label   label object
 * @param   show    integer value to be shown on the label
 */
void  updateLabel(GHandle *label, int show){
  char _buffer[20];
  sprintf(_buffer, "%d", show);
  gwinSetText(*label,_buffer,TRUE);
}
