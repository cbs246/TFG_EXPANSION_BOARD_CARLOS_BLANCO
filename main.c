/**
 * @file main.c
 * @brief Main file.
 * @author Carlos Blanco Sevilla
 * @date 2025-05-18
 */


/* Includes ----------------------------------------------------------------- */
/* Standard C libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* HW libraries */
#include "port_system.h"
#include "port_lcd.h"
#include "port_keyboard.h"

/* Defines ------------------------------------------------------------------ */

/* Functions ---------------------------------------------------------------- */
/**
 * @brief  The application entry point.
 * 
 * @retval int
 */
int main(void)
{
    /* Init board */
    port_system_init();

    /* Init keyboard and LCD */
    port_keyboard_gpio_setup();
    port_lcd_gpio_setup();
    LCD_init();

    /* LCD Print */
    LCD_SetCursor(0, 0);
    LCD_Print("Pulsa teclas");
    LCD_SetCursor(0, 1);
    LCD_Print(">");

    /* Infinite loop */
    while(1){  
        port_keyboard_result();
    }   
    return 0;
}
