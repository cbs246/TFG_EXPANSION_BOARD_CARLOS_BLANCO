/**
 * @file test_lcd.c
 * @brief Integration test for LCD.
 * @author Carlos Blanco Sevilla
 * @date 2025-05-18
 */

/* Includes ------------------------------------------------------------------*/
/* Standard C libraries */
#include <stdio.h>

/* HW dependent libraries */
#include "port_system.h"
#include "port_lcd.h"


/**
 * @brief Main test function. Read the terminal for instructions.
 *
 * @return int
 */
int main(void)
{
    // Initialize the system
    port_system_init();

    // Configure the LCD GPIOs and init
    port_lcd_gpio_setup();
    LCD_init();

    printf("The message hello world should be printed on the LCD");

    /* LCD Print */
    LCD_SetCursor(0, 0);
    LCD_Print("Hello world");

    while (1){
        
    }
    return 0;
}
