/*
 * Copyright (C) 2014 Julian Lewis
 * @author Maciej Suminski <maciej.suminski@cern.ch>
 * @author Theodor Stana <theodor.stana@gmail.com>
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
 * Menu application.
 */
#include"status_bar.h"
#include "app_list.h"
#include "menu_struct.h"

#include <stdio.h>
#include "gfx.h"

static thread_t * ui_sync_up = NULL; uint8_t timer_sleep = 0;
extern THD_WORKING_AREA (wa_ui_udc_event, 64);
extern THD_FUNCTION(ui_udcupdate_evt, arg);

static font_t font1;

static int selected_item = 0;
static int offset = 0;
static int menu_size = 0;

//#ifndef STATUS_BAR_HEIGHT
//#define STATUS_BAR_HEIGHT   30
//#endif
#define LINE_HEIGHT         75
#define LEFT_MARGIN         0
#define MENU_SCREEN_HEIGHT  (480-STATUS_BAR_HEIGHT)
#define MENU_SCREEN_WIDTH   800
#define MAX_ENTRIES         (MENU_SCREEN_HEIGHT / LINE_HEIGHT)

// store menu states to navigate between menus
static menu_list *menu_stack[8] = { &main_menu, NULL, };
static menu_list **current_menu = &menu_stack[0];
menu_entry* current_running_menu = NULL;

// init function proto
static void menu_ui_init(void);

//static void menu_screen_redraw(struct ui_widget *w)
static void menu_screen_redraw(void)
{
    int i;
    int menu_limit = (menu_size < MAX_ENTRIES ? menu_size : MAX_ENTRIES);
    uint8_t font_height = (uint8_t) gdispGetFontMetric(font1, fontHeight);

    gdispClear(HTML2COLOR(0xEEEEEE));
    for(i = 0; i < menu_limit; ++i)
    {
        int pos = offset + i;

        // draw a green background for the selected entry
        if(pos == selected_item) {
          gdispFillArea(LEFT_MARGIN, (i * LINE_HEIGHT)+ STATUS_BAR_HEIGHT, MENU_SCREEN_WIDTH, LINE_HEIGHT, HTML2COLOR(0x48BC4D));
        }

        menu_entry *ent = &(*current_menu)->entries[pos];

        // draw icon
        //if(ent->icon)
        //    gfx_draw_bitmap(&w->dc, 0, i * LINE_HEIGHT, ent->icon);

        // display label (either app or submenu)
        if(ent->type == APP) {
            application *a = ent->data.app;

            gdispDrawString(LEFT_MARGIN, i * LINE_HEIGHT + (LINE_HEIGHT - font_height)/2 + STATUS_BAR_HEIGHT, a->name, font1, (i == selected_item) ? HTML2COLOR(0x09180A) : HTML2COLOR(0x09180A));

        } else if(ent->type == SUBMENU) {
            menu_list *l = ent->data.submenu;

            gdispDrawString(LEFT_MARGIN, i * LINE_HEIGHT + (LINE_HEIGHT - font_height)/2 + STATUS_BAR_HEIGHT, l->name, font1, (i == selected_item) ? HTML2COLOR(0x09180A) : HTML2COLOR(0x09180A));
//        } else if (ent->type == SETTING) {
//            char s[16];
//            setting_t *set = ent->data.setting;
//            sprintf(s, "%s: %d", set->name, set->val);
////            strcat(s, ": ")
////            strcat(s, set->val);
//            gfx_text(&w->dc, &font_helv17, LEFT_MARGIN,
//                     i * LINE_HEIGHT, s, i != selected_item);
        }
    }
}

static void menu_deselect_item(uint8_t index){
  menu_entry *ent = &(*current_menu)->entries[offset + index];
  if(ent->type == APP) {
    application *a = ent->data.app;
    gdispFillStringBox(LEFT_MARGIN, index * LINE_HEIGHT+ STATUS_BAR_HEIGHT, MENU_SCREEN_WIDTH, LINE_HEIGHT, a->name, font1, HTML2COLOR(0x09180A), HTML2COLOR(0xEEEEEE), justifyLeft);
  } else if(ent->type == SUBMENU) {
    menu_list *l = ent->data.submenu;
    gdispFillStringBox(LEFT_MARGIN, index * LINE_HEIGHT+ STATUS_BAR_HEIGHT, MENU_SCREEN_WIDTH, LINE_HEIGHT, l->name, font1, HTML2COLOR(0x09180A), HTML2COLOR(0xEEEEEE), justifyLeft);
  }

}

static void menu_select_item(uint8_t index){
  menu_entry *ent = &(*current_menu)->entries[offset + index];
  if(ent->type == APP) {
    application *a = ent->data.app;
    gdispFillStringBox(LEFT_MARGIN, index * LINE_HEIGHT+ STATUS_BAR_HEIGHT, MENU_SCREEN_WIDTH, LINE_HEIGHT, a->name, font1, HTML2COLOR(0x09180A), HTML2COLOR(0x48BC4D), justifyLeft);
  } else if(ent->type == SUBMENU) {
    menu_list *l = ent->data.submenu;
    gdispFillStringBox(LEFT_MARGIN, index * LINE_HEIGHT+ STATUS_BAR_HEIGHT, MENU_SCREEN_WIDTH, LINE_HEIGHT, l->name, font1, HTML2COLOR(0x09180A), HTML2COLOR(0x48BC4D), justifyLeft);
  }

}

//static void menu_screen_event(struct ui_widget *w, const struct event *evt)
static void menu_screen_event(ui_event *evt){

    // scroll through the menu if a button was pressed
    if(evt->type == UI_INPUT_BUTTON) {
        if(evt->data.button_state == UI_BUTTON_DOWN) {
            if(selected_item < menu_size - 1) {
                ++selected_item;

                if(selected_item >= MAX_ENTRIES){
                  if(offset == selected_item - MAX_ENTRIES){
                    offset = selected_item - MAX_ENTRIES + 1;
                    menu_screen_redraw();
                  } else {
                    offset = selected_item - MAX_ENTRIES + 1;
                    menu_deselect_item(selected_item - offset - 1);
                    menu_select_item(selected_item - offset);
                  }
//                  menu_screen_redraw();
                } else {
                  menu_deselect_item(selected_item - offset - 1);
                  menu_select_item(selected_item - offset);
//                  return;
                }
            } else {
//                selected_item = 0;
//                offset = 0;

            }

//            menu_screen_redraw();
        }else if(evt->data.button_state == UI_BUTTON_UP) {
            if(selected_item > 0) {
                --selected_item;

                if(selected_item < offset){
                    offset = selected_item;
                    menu_screen_redraw();
                } else {
                  menu_deselect_item(selected_item - offset + 1);
                  menu_select_item(selected_item - offset);
//                  return;
                }
            } else {
//                selected_item = menu_size - 1;
//                if (menu_size < MAX_ENTRIES)
//                    offset = selected_item - menu_size + 1;
//                else
//                    offset = selected_item - MAX_ENTRIES + 1;
            }
//
//            w->flags |= WF_DIRTY;
//            menu_screen_redraw();
        }
    }
}

//struct ui_widget menu_screen = {
//    menu_screen_redraw,
//    menu_screen_event,
//    { 0, STATUS_BAR_HEIGHT,
//      MENU_SCREEN_WIDTH, STATUS_BAR_HEIGHT + MENU_SCREEN_HEIGHT },
//    0,
//    WF_ACTIVE | WF_VISIBLE
//};

static void menu_ui_init(void) {
//    ui_clear();
//
//    ui_init_widget(&menu_screen);
  font1 = gdispOpenFont("SFNS Display Regular 32");

  menu_screen_redraw();
//    ui_add_widget(&menu_screen);
//
//    ui_init_widget(&status_bar);
//    ui_add_widget(&status_bar);
//
//    ui_update(NULL);
}

static void run(menu_entry *entry) {
    if(entry->type == APP) {
      current_running_menu = entry;
      if (entry->data.app->syn_flg == sync){
        if (timer_sleep){
          //wake up suspended synchronous screen update thread
         chSysLock();
        if (ui_sync_up) {
          ui_sync_up = NULL;
          chSchWakeupS(ui_sync_up, MSG_OK);
        }
        chSysUnlock();
        }
      }
      if(entry->data.app->main == NULL)
        template.main(NULL);
      else{
        entry->data.app->main(NULL);
        timer_sleep = 1;current_running_menu = NULL;
      }
    } else if(entry->type == SUBMENU) {
      //TODO : implement stack to save previous offset
      selected_item = 0;
      offset = 0;
      menu_size = 0;
      // keep the operation separate to avoid crashes
      // when an interrupt goes off between the two following lines
      *(current_menu + 1) = entry->data.submenu;
      ++current_menu;
      menu_size = get_menu_size(*current_menu);
    } else if (entry->type == SETTING) {
//        setting_change(entry->data.setting);
    }
    menu_ui_init();
}

static void go_back(void) {
  if ((*current_menu) != &main_menu){//prevent go back re-printing the screen in main menu
    if(current_menu == menu_stack ) {
      current_running_menu = NULL;//control loop won't run on submenu anyway
      timer_sleep = 1;//suspend the synchronous update thread
    } else {
        //TODO : implement stack to save previous offset
        menu_size = 0;
        selected_item = 0;
        offset = 0;
        --current_menu;
        menu_size = get_menu_size(*current_menu);
    }
    menu_ui_init();
  }
}

void menu_main(void* params) {
    (void)(params);  // suppress unused parameter warning
    chRegSetThreadName(menu.name);

    ui_event *evt = NULL;
//    struct event evt;

//    battery_update();
    menu_size = get_menu_size(*current_menu);

    // run clock as the the initial application
//    clock_app.main(NULL);
    menu_ui_init();
    // Once it is deactivated - display the menu
    //starts the synchronous update
    chThdCreateStatic(wa_ui_udc_event, sizeof(wa_ui_udc_event), LOWPRIO, ui_udcupdate_evt, NULL);
    while(1) {

      if(chMBFetch(&app_mb, (msg_t*)(&evt), TIME_INFINITE) == MSG_OK){

        switch(evt->type){
          case UI_INPUT_BUTTON:
            if(evt->data.button_state == UI_BUTTON_BACK){
              go_back();
            } else if(evt->data.button_state == UI_BUTTON_ENTER){
              run(&(*current_menu)->entries[selected_item]);
            } else {
              menu_screen_event(evt);
            }
            break;
          case UI_STATUSBAR_TICK:
            //update status_bar, try to get it written in statusbar.c and forced everypage to have it...
            //maybe using macro in every app to force this entry
            break;
          default:
            //ui_update(&evt);
            break;
        }
      }
    }
}

application menu = {
    .name = "Menu",
    .main = menu_main,
    .syn_flg = no_sync
};

THD_WORKING_AREA (wa_ui_udc_event, 64);
THD_FUNCTION(ui_udcupdate_evt, arg){
  (void) arg;
  ui_event evt1;
  evt1.type = UI_UDC_UPDATE;
  uint32_t time = chVTGetSystemTimeX();
  while (true) {
     if (timer_sleep){
       ui_sync_up = chThdGetSelfX();
       chSchGoSleepS(CH_STATE_SUSPENDED);
     }else{
       if (timer_sleep)//woke up
           timer_sleep = 0;
      time += MS2ST(UI_UDC_UPDATE_INTERVAL);
      chMBPost(&app_mb, (msg_t)&evt1, TIME_IMMEDIATE);
      chThdSleepUntil(time);
     }
    }
}

