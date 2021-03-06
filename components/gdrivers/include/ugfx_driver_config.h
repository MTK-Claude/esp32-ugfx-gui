#ifndef __IOT_UGFX_DRIVER_CONFIG_H__
#define __IOT_UGFX_DRIVER_CONFIG_H__

#include "sdkconfig.h"

#ifdef CONFIG_UGFX_USE_CONFIGURED_OPTIONS
	#define UGFX_GUI_ENABLE                    CONFIG_UGFX_GUI_ENABLE
	#define UGFX_PROJ_RESOURCE_PATH            CONFIG_UGFX_PROJ_RESOURCE_PATH
	#define UGFX_USE_CUSTOM_DRIVER             CONFIG_UGFX_USE_CUSTOM_DRIVER
	#define UGFX_CUSTOM_DRIVER_COMPONENT_NAME  CONFIG_UGFX_CUSTOM_DRIVER_COMPONENT_NAME
	#define UGFX_LCD_DRIVER_FRAMEBUFFER_MODE   CONFIG_UGFX_LCD_DRIVER_FRAMEBUFFER_MODE
	#define UGFX_LCD_DRIVER_API_MODE           CONFIG_UGFX_LCD_DRIVER_API_MODE
	#define UGFX_LCD_MISO_GPIO                 CONFIG_UGFX_LCD_MISO_GPIO
	#define UGFX_LCD_MOSI_GPIO                 CONFIG_UGFX_LCD_MOSI_GPIO
	#define UGFX_LCD_CLK_GPIO                  CONFIG_UGFX_LCD_CLK_GPIO
	#define UGFX_LCD_CS_GPIO                   CONFIG_UGFX_LCD_CS_GPIO
	#define UGFX_LCD_DC_GPIO                   CONFIG_UGFX_LCD_DC_GPIO
	#define UGFX_LCD_RESET_GPIO                CONFIG_UGFX_LCD_RESET_GPIO
	#define UGFX_LCD_BL_GPIO                   CONFIG_UGFX_LCD_BL_GPIO
	#define UGFX_TOUCH_CS_GPIO                 CONFIG_UGFX_TOUCH_CS_GPIO
	#define UGFX_TOUCH_IRQ_GPIO                CONFIG_UGFX_TOUCH_IRQ_GPIO
	#define UGFX_DRIVER_SCREEN_WIDTH           CONFIG_UGFX_DRIVER_SCREEN_WIDTH
	#define UGFX_DRIVER_SCREEN_HEIGHT          CONFIG_UGFX_DRIVER_SCREEN_HEIGHT
	#define UGFX_DRIVER_AUTO_FLUSH_ENABLE      CONFIG_UGFX_DRIVER_AUTO_FLUSH_ENABLE
	#define UGFX_DRIVER_AUTO_FLUSH_INTERVAL    CONFIG_UGFX_DRIVER_AUTO_FLUSH_INTERVAL
	#define UGFX_DRIVER_TOUCH_SCREEN_ENABLE    CONFIG_UGFX_DRIVER_TOUCH_SCREEN_ENABLE
	#define UGFX_DRIVER_TOUCH_XPT2046          CONFIG_UGFX_DRIVER_TOUCH_XPT2046
#else
	#define UGFX_GUI_ENABLE                    1
	#define UGFX_USE_CUSTOM_DRIVER             1
	#define UGFX_LCD_DRIVER_FRAMEBUFFER_MODE   1
	#define UGFX_LCD_DRIVER_API_MODE           0
	#define UGFX_LCD_MISO_GPIO                 25
	#define UGFX_LCD_MOSI_GPIO                 23
	#define UGFX_LCD_CLK_GPIO                  19
	#define UGFX_LCD_CS_GPIO                   22
	#define UGFX_LCD_DC_GPIO                   21
	#define UGFX_LCD_RESET_GPIO                18
	#define UGFX_LCD_BL_GPIO                   5
	#define UGFX_TOUCH_CS_GPIO                 26
	#define UGFX_TOUCH_IRQ_GPIO                4
	#define UGFX_DRIVER_SCREEN_WIDTH           320
	#define UGFX_DRIVER_SCREEN_HEIGHT          240
	#define UGFX_DRIVER_AUTO_FLUSH_ENABLE      1
	#define UGFX_DRIVER_AUTO_FLUSH_INTERVAL    50
	#define UGFX_DRIVER_TOUCH_SCREEN_ENABLE    1
	#define UGFX_DRIVER_TOUCH_XPT2046          1
#endif

#endif /* __IOT_UGFX_DRIVER_CONFIG_H__ */
