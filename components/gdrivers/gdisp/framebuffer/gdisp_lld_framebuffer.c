/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */
/* uGFX Includes  */
#include "iot_ugfx.h"
#include "ugfx_driver_config.h"

#if CONFIG_UGFX_LCD_DRIVER_FRAMEBUFFER_MODE

/* uGFX Includes */
#include "gos_freertos_priv.h"
#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT            GDISPVMT_FRAMEBUFFER

/* Disp Includes */
#include "gdisp_lld_config.h"
#include "src/gdisp/gdisp_driver.h"
#include "lcd_adapter.h"
#include "board_framebuffer.h"

typedef struct fbPriv {
    fbInfo_t fbi;            // Display information
} fbPriv_t;

#define PIXIL_POS(g, x, y)        ((y) * ((fbPriv_t *)(g)->priv)->fbi.linelen + (x) * sizeof(LLDCOLOR_TYPE))
#define PIXEL_ADDR(g, pos)        ((LLDCOLOR_TYPE *)(((char *)((fbPriv_t *)(g)->priv)->fbi.pixels)+pos))

LLDSPEC bool_t gdisp_lld_init(GDisplay *g)
{
    // Initialize the private structure
    if (!(g->priv = gfxAlloc(sizeof(fbPriv_t)))) {
        gfxHalt("GDISP Framebuffer: Failed to allocate private memory");
    }
    ((fbPriv_t *)g->priv)->fbi.pixels = 0;
    ((fbPriv_t *)g->priv)->fbi.linelen = 0;

    // Initialize the GDISP structure
    g->g.Orientation = GDISP_ROTATE_0;
    g->g.Powermode = powerOn;
    g->board = 0;                            // preinitialize
    board_init(g, &((fbPriv_t *)g->priv)->fbi);

    return TRUE;
}

#if GDISP_HARDWARE_FLUSH
LLDSPEC void gdisp_lld_flush(GDisplay *g)
{
    board_flush(g);
}
#endif

LLDSPEC void gdisp_lld_draw_pixel(GDisplay *g)
{
    unsigned pos;

#if GDISP_NEED_CONTROL
    switch (g->g.Orientation) {
    case GDISP_ROTATE_0:
    default:
        pos = PIXIL_POS(g, g->p.x, g->p.y);
        break;
    case GDISP_ROTATE_90:
        pos = PIXIL_POS(g, g->p.y, g->g.Width - g->p.x - 1);
        break;
    case GDISP_ROTATE_180:
        pos = PIXIL_POS(g, g->g.Width - g->p.x - 1, g->g.Height - g->p.y - 1);
        break;
    case GDISP_ROTATE_270:
        pos = PIXIL_POS(g, g->g.Height - g->p.y - 1, g->p.x);
        break;
    }
#else
    pos = PIXIL_POS(g, g->p.x, g->p.y);
#endif

    PIXEL_ADDR(g, pos)[0] = gdispColor2Native(g->p.color);
}

LLDSPEC color_t gdisp_lld_get_pixel_color(GDisplay *g)
{
    unsigned pos;
    LLDCOLOR_TYPE color;

#if GDISP_NEED_CONTROL
    switch (g->g.Orientation) {
    case GDISP_ROTATE_0:
    default:
        pos = PIXIL_POS(g, g->p.x, g->p.y);
        break;
    case GDISP_ROTATE_90:
        pos = PIXIL_POS(g, g->p.y, g->g.Width - g->p.x - 1);
        break;
    case GDISP_ROTATE_180:
        pos = PIXIL_POS(g, g->g.Width - g->p.x - 1, g->g.Height - g->p.y - 1);
        break;
    case GDISP_ROTATE_270:
        pos = PIXIL_POS(g, g->g.Height - g->p.y - 1, g->p.x);
        break;
    }
#else
    pos = PIXIL_POS(g, g->p.x, g->p.y);
#endif

    color = PIXEL_ADDR(g, pos)[0];
    return gdispNative2Color(color);
}

#if GDISP_NEED_CONTROL
LLDSPEC void gdisp_lld_control(GDisplay *g)
{
    switch (g->p.x) {
    case GDISP_CONTROL_POWER:
        if (g->g.Powermode == (powermode_t)g->p.ptr) {
            return;
        }
        switch ((powermode_t)g->p.ptr) {
        case powerOff: case powerOn: case powerSleep: case powerDeepSleep:
            board_power(g, (powermode_t)g->p.ptr);
            break;
        default:
            return;
        }
        g->g.Powermode = (powermode_t)g->p.ptr;
        return;

    case GDISP_CONTROL_ORIENTATION:
        if (g->g.Orientation == (orientation_t)g->p.ptr) {
            return;
        }
        switch ((orientation_t)g->p.ptr) {
        case GDISP_ROTATE_0:
        case GDISP_ROTATE_180:
            if (g->g.Orientation == GDISP_ROTATE_90 || g->g.Orientation == GDISP_ROTATE_270) {
                coord_t        tmp;
                tmp = g->g.Width;
                g->g.Width = g->g.Height;
                g->g.Height = tmp;
            }
            break;
        case GDISP_ROTATE_90:
        case GDISP_ROTATE_270:
            if (g->g.Orientation == GDISP_ROTATE_0 || g->g.Orientation == GDISP_ROTATE_180) {
                coord_t        tmp;
                tmp = g->g.Width;
                g->g.Width = g->g.Height;
                g->g.Height = tmp;
            }
            break;
        default:
            return;
        }
        g->g.Orientation = (orientation_t)g->p.ptr;
        return;

    case GDISP_CONTROL_BACKLIGHT:
        if ((unsigned)g->p.ptr > 100) {
            g->p.ptr = (void *)100;
        }
        board_backlight(g, (unsigned)g->p.ptr);
        g->g.Backlight = (unsigned)g->p.ptr;
        return;

    case GDISP_CONTROL_CONTRAST:
        if ((unsigned)g->p.ptr > 100) {
            g->p.ptr = (void *)100;
        }
        board_contrast(g, (unsigned)g->p.ptr);
        g->g.Contrast = (unsigned)g->p.ptr;
        return;
    }
}
#endif // GDISP_NEED_CONTROL

#endif /* GFX_USE_GDISP */

#endif /* CONFIG_UGFX_LCD_DRIVER_FRAMEBUFFER_MODE */
