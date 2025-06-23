/**
 * @file port_keyboard.c
 * @brief File that defines the functions that are related to the functions of the keyboard.
 * @author Carlos Blanco Sevilla
 * @date 2025-05-18
*/

/* Includes ------------------------------------------------------------------*/
/* Standard C libraries */
#include <stdio.h>
#include <unistd.h>

/* HW libraries */
#include "stm32f4xx.h"
#include "port_system.h"
#include "port_keyboard.h"
#include "port_lcd.h"


/* Defines ------------------------------------------------------------------*/
// GPIOs
#define col_D6_GPIO   GPIOB // OUT DECOD 1 GPIO
#define col_D5_GPIO   GPIOB // OUT DECOD 2 GPIO
#define EN_D2_GPIO    GPIOA // ENABLE DECOD GPIO
   
#define row_A2_GPIO   GPIOA // OUT COD 1 GPIO
#define row_A3_GPIO   GPIOB // OUT COD 2 GPIO
#define row_A1_GPIO   GPIOA // OUT COD 3 GPIO
#define INT_A4_GPIO   GPIOC // INT COD GPIO
#define EN_A5_GPIO    GPIOC // ENABLE COD GPIO
   
// Pins
#define col_D6_PIN       10 // OUT DECOD 1 PIN
#define col_D5_PIN        4 // OUT DECOD 2 PIN
#define EN_D2_PIN        10 // ENABLE DECOD PIN

#define row_A2_PIN        4 // OUT COD 1 PIN
#define row_A3_PIN        0 // OUT COD 2 PIN
#define row_A1_PIN        1 // OUT COD 3 PIN
#define INT_A4_PIN        1 // INT COD PIN
#define EN_A5_PIN         0 // ENABLE COD PIN

#define BASE_MASK 0x03    

// LCD
static uint8_t lcd_col = 2; // Column to start writing
static uint8_t lcd_row = 1; // Row to start writing
#define LCD_COL_MAX 12      // Max columns number
#define LCD_ROW_MAX 2       // Max rows number


/* Functions -----------------------------------------------------------------*/
char map_key(uint8_t col, uint8_t row){
    static const char keys[4][4] = {
        {'1','2','3','A'},
        {'4','5','6','B'},
        {'7','8','9','C'},
        {'F','0','E','D'}
    };
    return (col>=1 && col<=4 && row>=1 && row<=4)
           ? keys[col-1][row-1]
           : 0;
}

void port_keyboard_gpio_setup(void){

    // Perpherial clock enabler
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // Clean the registers
    col_D6_GPIO->MODER &= ~(BASE_MASK << 2 * col_D6_PIN);
    col_D6_GPIO->PUPDR &= ~(BASE_MASK << 2 * col_D6_PIN);
    col_D5_GPIO->MODER &= ~(BASE_MASK << 2 * col_D5_PIN);
    col_D5_GPIO->PUPDR &= ~(BASE_MASK << 2 * col_D5_PIN);
    EN_D2_GPIO->MODER &= ~(BASE_MASK << 2 * EN_D2_PIN);
    EN_D2_GPIO->PUPDR &= ~(BASE_MASK << 2 * EN_D2_PIN);

    row_A2_GPIO->MODER &= ~(BASE_MASK << 2 * row_A2_PIN);
    row_A2_GPIO->PUPDR &= ~(BASE_MASK << 2 * row_A2_PIN);
    row_A3_GPIO->MODER &= ~(BASE_MASK << 2 * row_A3_PIN);
    row_A3_GPIO->PUPDR &= ~(BASE_MASK << 2 * row_A3_PIN);
    row_A1_GPIO->MODER &= ~(BASE_MASK << 2 * row_A1_PIN);
    row_A1_GPIO->PUPDR &= ~(BASE_MASK << 2 * row_A1_PIN);
    INT_A4_GPIO->MODER &= ~(BASE_MASK << 2 * INT_A4_PIN);
    INT_A4_GPIO->PUPDR &= ~(BASE_MASK << 2 * INT_A4_PIN);
    EN_A5_GPIO->MODER &= ~(BASE_MASK << 2 * EN_A5_PIN);
    EN_A5_GPIO->PUPDR &= ~(BASE_MASK << 2 * EN_A5_PIN);

    // Configure the registers
    col_D6_GPIO->MODER |= (GPIO_MODE_OUT << 2 * col_D6_PIN);
    col_D6_GPIO->PUPDR |= (GPIO_PUPDR_PDOWN << 2 * col_D6_PIN);
    col_D5_GPIO->MODER |= (GPIO_MODE_OUT << 2 * col_D5_PIN);
    col_D5_GPIO->PUPDR |= (GPIO_PUPDR_PDOWN << 2 * col_D5_PIN);
    EN_D2_GPIO->MODER |= (GPIO_MODE_OUT << 2 * EN_D2_PIN);
    EN_D2_GPIO->PUPDR |= (GPIO_PUPDR_PDOWN << 2 * EN_D2_PIN);

    row_A2_GPIO->MODER |= (GPIO_MODE_IN << 2 * row_A2_PIN);
    row_A2_GPIO->PUPDR |= (GPIO_PUPDR_PUP << 2 * row_A2_PIN);
    row_A3_GPIO->MODER |= (GPIO_MODE_IN << 2 * row_A3_PIN);
    row_A3_GPIO->PUPDR |= (GPIO_PUPDR_PUP << 2 * row_A3_PIN);
    row_A1_GPIO->MODER |= (GPIO_MODE_IN << 2 * row_A1_PIN);
    row_A1_GPIO->PUPDR |= (GPIO_PUPDR_PUP << 2 * row_A1_PIN);
    INT_A4_GPIO->MODER |= (GPIO_MODE_IN << 2 * INT_A4_PIN);
    INT_A4_GPIO->PUPDR |= (GPIO_PUPDR_PUP << 2 * INT_A4_PIN);
    EN_A5_GPIO->MODER |= (GPIO_MODE_OUT << 2 * EN_A5_PIN);
    EN_A5_GPIO->PUPDR |= (GPIO_PUPDR_PUP << 2 * EN_A5_PIN);

    EN_A5_GPIO->ODR |= (1 << EN_A5_PIN);
}

void port_column_toggle(uint8_t column){

    EN_D2_GPIO->ODR |= (1 << EN_D2_PIN);        // Turns on the enable
    if(column == 1){      
        col_D6_GPIO->ODR &= ~(1 << col_D6_PIN); // 0
        col_D5_GPIO->ODR &= ~(1 << col_D5_PIN); // 0
    }
    else if(column == 2){
        col_D6_GPIO->ODR |= (1 << col_D6_PIN);  // 1
        col_D5_GPIO->ODR &= ~(1 << col_D5_PIN); // 0
    }
    else if(column == 3){
        col_D6_GPIO->ODR &= ~(1 << col_D6_PIN); // 0
        col_D5_GPIO->ODR |= (1 << col_D5_PIN);  // 1
    }
    else if(column == 4){
        col_D6_GPIO->ODR |= (1 << col_D6_PIN);  // 1
        col_D5_GPIO->ODR |= (1 << col_D5_PIN);  // 1
    }
    else{}
}

uint8_t port_get_rows(void){

    EN_A5_GPIO->ODR &= ~(1 << EN_A5_PIN);
    if(((row_A1_GPIO -> IDR & (0x01 << row_A1_PIN)) != 0)){
        return 0;
    }
    else{
        if( ((row_A2_GPIO -> IDR & (0x01 << row_A2_PIN)) == 0) && ((row_A3_GPIO -> IDR & (0x01 << row_A3_PIN)) == 0) ){
            return 1;
        }
        else if( ((row_A2_GPIO -> IDR & (0x01 << row_A2_PIN)) != 0) && ((row_A3_GPIO -> IDR & (0x01 << row_A3_PIN)) == 0) ){
            return 2;
        }
        else if( ((row_A2_GPIO -> IDR & (0x01 << row_A2_PIN)) == 0) && ((row_A3_GPIO -> IDR & (0x01 << row_A3_PIN)) != 0) ){
            return 3;
        }
        else if( ((row_A2_GPIO -> IDR & (0x01 << row_A2_PIN)) != 0) && ((row_A3_GPIO -> IDR & (0x01 << row_A3_PIN)) != 0) ){
            return 4;
        }
        else{
            return 0;
        }
    }
}

void port_keyboard_result(void){
    uint32_t now = port_system_get_millis();
    static uint32_t last_ms = 0;    // Last rising edge

    static uint8_t previousKey = 0; // Last key pressed
    uint8_t currentKey = 0;         // Current key pressed
    char key = 0;                   // Value of the key
     uint8_t row = 0;               // Value of the row pressed

    // port_column_toggle(1);
    //     row = port_get_rows();
    //     if(row != 0){
    //         currentKey = 1;              
    //         key = map_key(row, 1);
    //     }

    // port_column_toggle(2);
    //     row = port_get_rows();
    //     if(row != 0){
    //         currentKey = 1;              
    //         key = map_key(row, 2);
    //     }

    // port_column_toggle(4);
    //     row = port_get_rows();
    //     if(row != 0){
    //         currentKey = 1;              
    //         key = map_key(row, 4);
    //     }

    // port_column_toggle(3);
    //     row = port_get_rows();
    //     if(row != 0){
    //         currentKey = 1;              
    //         key = map_key(row, 3);
    //     }

    // Scan for active rows
    for(uint8_t column = 1; column <= 4; ++column){
        port_column_toggle(column);
        row = port_get_rows();
        if(row != 0){
            currentKey = 1;              
            key = map_key(row, column);
            break;
        }
    }

    // Debounce
    if(currentKey != 0){
        if(previousKey == 0 && (now - last_ms) >= 50){

            // LCD writing
            LCD_SetCursor(lcd_col, lcd_row);
            { char s[2] = { key, '\0' }; LCD_Print(s); }
            lcd_col++; // Next column to write

            // When reaches end, clear the display and set to position 0
            if(lcd_col >= LCD_COL_MAX){
                lcd_col = 0;
                lcd_row++;
                if(lcd_row >= LCD_ROW_MAX){
                    lcd_row = 0;
                    LCD_SetCursor(0,0);
                    LCD_Print("            ");
                    LCD_SetCursor(0,1);
                    LCD_Print("            ");
                    LCD_SetCursor(0,0);
                }
            }
            previousKey = 1;
            last_ms = now;
        }
    } 
    else {
        previousKey = 0;
    }
}