#include "gfx.h"
#include "src/gwin/gwin_class.h"
#include "custom_draw.h"
#include "string.h"
#include "src/gdisp/mcufont/mf_font.h"

void CustomLabelDraw(GWidgetObject *gw, void *param) {
  (void) param;
  coord_t       w, h;
  color_t       c;

  char *old_string = (char *) param;

  w = (gw->g.flags & GLABEL_FLG_WAUTO) ? gdispGetStringWidth(gw->text, gw->g.font) + 2 : gw->g.width;
  h = (gw->g.flags & GLABEL_FLG_HAUTO) ? gdispGetStringWidth(gw->text, gw->g.font) + 2 : gw->g.height;
  c = (gw->g.flags & GWIN_FLG_SYSENABLED) ? gw->pstyle->enabled.text : gw->pstyle->disabled.text;

  if (gw->g.width != w || gw->g.height != h) {
    /* Only allow the widget to be resize if it will grow larger.
     * Growing smaller is problematic because it requires a temporary change in visibility.
     * This is a work-around for a crashing bug caused by calling gwinResize() in the draw function
     * (dubious) as it may try to reclaim the drawing lock.
     */
    if (gw->g.width < w || gw->g.height < h) {
      gwinResize(&gw->g, (w > gw->g.width ? w : gw->g.width), (h > gw->g.height ? h : gw->g.height));
      return;
    }
    w = gw->g.width;
    h = gw->g.height;
  }

  //gdispGFillStringBox(gw->g.display, gw->g.x, gw->g.y, w, h, gw->text, gw->g.font, c, gw->pstyle->background, justifyRight);
  //gdispGFillStringBox(pixmap, 0, 0, w, h, gw->text, gw->g.font, c, gw->pstyle->background, justifyRight);
  uint8_t len_old = strlen(old_string);
  uint8_t len_new = strlen(gw->text);
  if(len_old == 0 || len_new == 0)
    gdispGFillStringBox(gw->g.display, gw->g.x, gw->g.y, w, h, gw->text, gw->g.font, c, gw->pstyle->background, justifyRight);
  else{
    int n = len_old < len_new ? len_old : len_new;
    int i;
    char *str_old_ptr = old_string + len_old - 1;
    const char *str_new_ptr = gw->text + len_new - 1;
    uint8_t font_width = ((struct mf_font_s*)gw->g.font)->min_x_advance;
    uint8_t font_height = ((struct mf_font_s*)gw->g.font)->height;
    uint8_t height_offset = (h+1 - font_height)/2;
    for(i = 0; i < n; i++, str_old_ptr--, str_new_ptr--)
      if(*str_old_ptr != *str_new_ptr)
        gdispGFillChar(gw->g.display, gw->g.x + w - (i + 1) * font_width, gw->g.y + height_offset, *str_new_ptr, gw->g.font, c, gw->pstyle->background);
    if(len_old != len_new){
      if(len_new > len_old){
        for(; i < len_new; i++, str_new_ptr--)
          gdispGFillChar(gw->g.display, gw->g.x + w - (i + 1) * font_width, gw->g.y + height_offset, *str_new_ptr, gw->g.font, c, gw->pstyle->background);
      }
      else
        gdispGFillArea(gw->g.display, gw->g.x + w - len_old * font_width, gw->g.y + height_offset, (len_old - n) * font_width, h, gw->pstyle->background);
    }
  }

  // render the border (if any)
  if (gw->g.flags & GLABEL_FLG_BORDER)
    gdispGDrawBox(gw->g.display, gw->g.x, gw->g.y, w, h, (gw->g.flags & GWIN_FLG_SYSENABLED) ? gw->pstyle->enabled.edge : gw->pstyle->disabled.edge);

  strcpy(old_string, gw->text);

}
