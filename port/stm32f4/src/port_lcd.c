/**
 * @file port_lcd.c
 * @brief File that defines the functions that are related to the functions of the LCD.
 * @author Carlos Blanco Sevilla
 * @date 2025-05-18
*/

/* Includes ------------------------------------------------------------------*/
/* Standard C libraries */
#include <stdio.h>
#include <unistd.h>

/* HW libraries */
#include "port_lcd.h"
#include "port_system.h"

/* Defines ------------------------------------------------------------------*/
// GPIOs
#define A0_GPIO   GPIOA // EN
#define D3_GPIO   GPIOB // INT
#define D4_GPIO   GPIOB // RS
#define D13_GPIO  GPIOA // DAT1
#define D12_GPIO  GPIOA // DAT2
#define D8_GPIO   GPIOA // DAT3  
#define D7_GPIO   GPIOA // DAT4
   
// Pins
#define A0_PIN    0     // EN  
#define D3_PIN    3     // INT   
#define D4_PIN    5     // RS
#define D13_PIN   5     // DAT1
#define D12_PIN   6     // DAT2
#define D8_PIN    9     // DAT3
#define D7_PIN    8     // DAT4

#define BASE_MASK  0x03

/* Functions -----------------------------------------------------------------*/
void port_lcd_gpio_setup(void){

    // Perpherial clock enabler
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // Clean the registers
    A0_GPIO->MODER &= ~(BASE_MASK << 2 * A0_PIN);
    A0_GPIO->PUPDR &= ~(BASE_MASK << 2 * A0_PIN);
    D13_GPIO->MODER &= ~(BASE_MASK << 2 * D13_PIN);
    D13_GPIO->PUPDR &= ~(BASE_MASK << 2 * D13_PIN);
    D3_GPIO->MODER &= ~(BASE_MASK << 2 * D3_PIN);
    D3_GPIO->PUPDR &= ~(BASE_MASK << 2 * D3_PIN);
    D4_GPIO->MODER &= ~(BASE_MASK << 2 * D4_PIN);
    D4_GPIO->PUPDR &= ~(BASE_MASK << 2 * D4_PIN);
    D12_GPIO->MODER &= ~(BASE_MASK << 2 * D12_PIN);
    D12_GPIO->PUPDR &= ~(BASE_MASK << 2 * D12_PIN);
    D8_GPIO->MODER &= ~(BASE_MASK << 2 * D8_PIN);
    D8_GPIO->PUPDR &= ~(BASE_MASK << 2 * D8_PIN);
    D7_GPIO->MODER &= ~(BASE_MASK << 2 * D7_PIN);
    D7_GPIO->PUPDR &= ~(BASE_MASK << 2 * D7_PIN);

    // Configure the registers
    A0_GPIO->MODER |= (GPIO_MODE_OUT << 2 * A0_PIN);
    A0_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * A0_PIN);
    D13_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D13_PIN);
    D13_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * D13_PIN);
    D3_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D3_PIN);
    D3_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * D3_PIN);
    D4_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D4_PIN);
    D4_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * D4_PIN);
    D12_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D12_PIN);
    D12_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * D12_PIN);
    D8_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D8_PIN);
    D8_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * D8_PIN);
    D7_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D7_PIN);
    D7_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * D7_PIN);
}

static inline void lcd_delay_cycles(uint32_t cycles) {
    for (volatile uint32_t i = 0; i < cycles; ++i) {
        __asm__("nop");
    }
}

void delay_ms(uint32_t ms) {
    while (ms--) {
        lcd_delay_cycles(16000); // 1 ms - 16 MHz
        port_system_delay_ms(1);
    }
}

void lcd_nibble_write(uint8_t data, uint8_t control){
    // RS (indicates if what we are receiving is data or a command)
    if(control & D4_PIN){
        GPIOB->BSRR = (1 << D4_PIN);        // RS = 1, data mode
    } else {
        GPIOB->BSRR = (1 << (D4_PIN + 16)); // RS = 0, command mode
    }

    // Data
    if(data & 0x01){
        GPIOA->BSRR = (1 << D13_PIN);
    }   
    else{
        GPIOA->BSRR = (1 << (D13_PIN + 16));
    } 
    if(data & 0x02){
        GPIOA->BSRR = (1 << D12_PIN);
    }  
    else{
        GPIOA->BSRR = (1 << (D12_PIN + 16));
    } 
    if(data & 0x04){
        GPIOA->BSRR = (1 << D8_PIN);
    }   
    else{
        GPIOA->BSRR = (1 << (D8_PIN + 16));
    }
    if(data & 0x08){
        GPIOA->BSRR = (1 << D7_PIN);
    }  
    else{
        GPIOA->BSRR = (1 << (D7_PIN + 16));
    }

    // EN
    GPIOA->BSRR = (1 << A0_PIN);        // EN = 1
    delay_ms(1);                      
    GPIOA->BSRR = (1 << (A0_PIN + 16)); // EN = 0
    delay_ms(1);                      
}


void lcd_com(uint8_t cmd){
    lcd_nibble_write(cmd >> 4, 0);   // Four most significant bits
    lcd_nibble_write(cmd & 0x0F, 0); // Four less significant bits
    delay_ms((cmd < 4) ? 2 : 1);
}

void lcd_data(uint8_t data){
    lcd_nibble_write(data >> 4, D4_PIN);
    lcd_nibble_write(data & 0x0F, D4_PIN);
    delay_ms(1);
}

void LCD_init(void){
    // Delay for stabilization.
    delay_ms(50); 

    // “Function Set” 0x03 → 8-bit mode, resets and assures that is 8-bit mode.
    lcd_nibble_write(0x03, 0); delay_ms(5);
    lcd_nibble_write(0x03, 0); delay_ms(5);
    lcd_nibble_write(0x03, 0); delay_ms(5);

    // Convert to 4-bit mode.
    lcd_nibble_write(0x02, 0); delay_ms(1);

    // Configure 4 bits, 2 lines, 5×8 dots.
    lcd_com(0x28);

    // Display ON, cursor OFF, blink OFF.
    lcd_com(0x0C);

    // Clear display.
    lcd_com(0x01); delay_ms(2);

    // Entry mode: increment, no displacement.
    lcd_com(0x06);
}

void LCD_SetCursor(uint8_t col, uint8_t row){
    uint8_t addr = (row == 0 ? 0x80 : 0xC0) + col; // If row = 0 poitns to first line(0x80) if not, points to second line(0xC0)
    lcd_com(addr); // Advises that this is an instruction.
}

void LCD_Print(const char *str){
    while(*str){
        lcd_data((uint8_t)(*str++));
    }
}