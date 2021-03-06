// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/* C Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* RTOS Includes */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"

/* SPI Includes */
#include "lcd_com.h"
#include "screen_NT35510.h"
#include "lcd_adapter.h"

/* ESP Includes */
#include "sdkconfig.h"
#include "esp_log.h"

/* uGFX Include */
#include "ugfx_driver_config.h"

static lcd_dev_t *lcd_obj = NULL;
static uint16_t *pFrameBuffer = NULL;
lcd_dev_t *LcdNt35510Create(uint16_t x_size, uint16_t y_size);

void board_lcd_init()
{
    /*Initialize LCD*/
    if (lcd_obj == NULL) {
        lcd_obj = LcdNt35510Create(UGFX_DRIVER_SCREEN_WIDTH, UGFX_DRIVER_SCREEN_HEIGHT);
    }
}

void board_lcd_flush(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h)
{
    lcd_obj->lcd.LcdDrawBmp(bitmap, x, y, UGFX_DRIVER_SCREEN_WIDTH, UGFX_DRIVER_SCREEN_HEIGHT);
}

void board_lcd_blit_area(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h)
{
    lcd_obj->lcd.LcdDrawBmp(bitmap, x, y, w, h);
}

void board_lcd_write_cmd(uint16_t cmd)
{
    WriteCmd(cmd);
}

void board_lcd_write_data(uint16_t data)
{
    WriteData(data);
}

void board_lcd_write_data_byte(uint8_t data)
{
    WriteData(data);
}

void board_lcd_write_datas(uint16_t data, uint16_t x, uint16_t y)
{
    lcd_obj->lcd.LcdFillArea(data, x, y);
}

void board_lcd_write_cmddata(uint16_t cmd, uint32_t data)
{
    WriteCmdData(cmd, data);
}

void board_lcd_set_backlight(uint16_t data)
{
    /* Code here*/
}
