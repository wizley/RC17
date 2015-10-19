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

#include "app_list.h"
#include "menu_struct.h"

#include <stdio.h>
#include "gfx.h"

static int selected_item = 0;
static int offset = 0;
static int menu_size = 0;

#define LINE_HEIGHT         80
#define LEFT_MARGIN         0
#define MENU_SCREEN_HEIGHT  480
#define MENU_SCREEN_WIDTH   800
#define MAX_ENTRIES         (MENU_SCREEN_HEIGHT / LINE_HEIGHT)

// store menu states to navigate between menus
static menu_list *menu_stack[8] = { &main_menu, NULL, };
static menu_list **current_menu = &menu_stack[0];

// init function proto
static void menu_ui_init(void);

//static void menu_screen_redraw(struct ui_widget *w)
static void menu_screen_redraw(void)
{
    int i;
    int menu_limit = (menu_size < MAX_ENTRIES ? menu_size : MAX_ENTRIES);

    font_t font1;
    font1 = gdispOpenFont("DejaVuSans32");

//    gfx_clear(&w->dc, 0);
    gdispClear(Black);
    for(i = 0; i < menu_limit; ++i)
    {
        int pos = offset + i;

        // draw a white background for the selected entry
        if(pos == selected_item) {
//            gfx_box(&w->dc, LEFT_MARGIN, i * LINE_HEIGHT,
//                    MENU_SCREEN_WIDTH, (i + 1) * LINE_HEIGHT, 1);
          gdispFillArea(LEFT_MARGIN, i * LINE_HEIGHT, MENU_SCREEN_WIDTH, (i + 1) * LINE_HEIGHT, Blue);
        }

        menu_entry *ent = &(*current_menu)->entries[pos];

        // draw icon
        //if(ent->icon)
        //    gfx_draw_bitmap(&w->dc, 0, i * LINE_HEIGHT, ent->icon);

        // display label (either app or submenu)
        if(ent->type == APP) {
            application *a = ent->data.app;

//            gfx_text(&w->dc, &font_helv17, LEFT_MARGIN,
//                     i * LINE_HEIGHT, a->name, i != selected_item);

            gdispDrawString(LEFT_MARGIN, i * LINE_HEIGHT, a->name, font1, (i == selected_item) ? White : Yellow);

        } else if(ent->type == SUBMENU) {
            menu_list *l = ent->data.submenu;

//            gfx_text(&w->dc, &font_helv17, LEFT_MARGIN,
//                     i * LINE_HEIGHT, l->name, i != selected_item);
            gdispDrawString(LEFT_MARGIN, i * LINE_HEIGHT, l->name, font1, (i == selected_item) ? White : Yellow);
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

//static void menu_screen_event(struct ui_widget *w, const struct event *evt)
static void menu_screen_event(void)
{
    // scroll through the menu if a button was pressed
//    if(evt->type == BUTTON_PRESSED) {
//        if(evt->data.button == BUT_BR) {
//            if(selected_item < menu_size - 1) {
//                ++selected_item;
//
//                if(selected_item >= MAX_ENTRIES)
//                    offset = selected_item - MAX_ENTRIES + 1;
//            } else {
//                selected_item = 0;
//                offset = 0;
//            }
//
//            w->flags |= WF_DIRTY;
//        } else if(evt->data.button == BUT_BL) {
//            if(selected_item > 0) {
//                --selected_item;
//
//                if(selected_item < offset)
//                    offset = selected_item;
//            } else {
//                selected_item = menu_size - 1;
//                if (menu_size < MAX_ENTRIES)
//                    offset = selected_item - menu_size + 1;
//                else
//                    offset = selected_item - MAX_ENTRIES + 1;
//            }
//
//            w->flags |= WF_DIRTY;
//        }
//    }
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
        entry->data.app->main(NULL);
    } else if(entry->type == SUBMENU) {
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
    if(current_menu == menu_stack) {
//        clock_app.main(NULL);
    } else {
        menu_size = 0;
        selected_item = 0;
        offset = 0;
        --current_menu;
        menu_size = get_menu_size(*current_menu);
    }

    menu_ui_init();
}

void menu_main(void* params) {
    (void)(params);  // suppress unused parameter warning
//    struct event evt;

//    battery_update();
    menu_size = get_menu_size(*current_menu);

    // run clock as the the initial application
//    clock_app.main(NULL);
    menu_ui_init();

    // Once it is deactivated - display the menu
    while(1) {
//        if(xQueueReceive(appQueue, &evt, portMAX_DELAY)) {
//            switch(evt.type) {
//                case BUTTON_PRESSED:
//                    if(evt.data.button == BUT_TL) {
//                        go_back();
//                    } else if(evt.data.button == BUT_TR) {
//                        // run the selected application or submenu
//                        run(&(*current_menu)->entries[selected_item]);
//                    } else {
//                        ui_update(&evt);
//                    }
//                    break;
//
//                default:    // suppress warnings
//                    ui_update(&evt);
//                    break;
//            }
//        }
      chThdSleepMilliseconds(1000);
    }
}

application menu = {
    .name = "Menu",
    .main = menu_main
};

