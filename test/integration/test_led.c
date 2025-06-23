/**
 * @file test_led.c
 * @brief Integration test for the LED RGB.
 * @author Carlos Blanco Sevilla
 * @date 2025-05-18
 */

/* Includes ------------------------------------------------------------------*/
/* Standard C libraries */
#include <stdio.h>

/* HW dependent libraries */
#include "port_system.h"

/* Defines ------------------------------------------------------------------*/
// GPIOs
#define D9_GPIO  GPIOC // Blue
#define D10_GPIO GPIOB // Green
#define D11_GPIO GPIOA // Red
   
// Pins
#define D9_PIN       7 // Blue
#define D10_PIN      6 // Green    
#define D11_PIN      7 // Red


#define BASE_MASK  0x03


/**
 * @brief Main test function. Read the terminal for instructions.
 *
 * @return int
 */
int main(void)
{
    // Initialize the system
    port_system_init();

    // Perpherial clock enabler
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // Clean the registers
    D9_GPIO->MODER &= ~(BASE_MASK << 2 * D9_PIN);
    D9_GPIO->PUPDR &= ~(BASE_MASK << 2 * D9_PIN);
    D10_GPIO->MODER &= ~(BASE_MASK << 2 * D10_PIN);
    D10_GPIO->PUPDR &= ~(BASE_MASK << 2 * D10_PIN);
    D11_GPIO->MODER &= ~(BASE_MASK << 2 * D11_PIN);
    D11_GPIO->PUPDR &= ~(BASE_MASK << 2 * D11_PIN);

    // Configure the registers
    D9_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D9_PIN);
    D9_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * D9_PIN);
    D10_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D10_PIN);
    D10_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D10_PIN);
    D11_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * D11_PIN);
    D11_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D11_PIN);


    /* ON */
    // D9_GPIO->ODR &= ~(1<<D9_PIN); // Uncomment to turn on blue
    // D10_GPIO->ODR &= ~(1<<D10_PIN); // Uncomment to turn on green
    // D11_GPIO->ODR &= ~(1<<D11_PIN); // Uncomment to turn on red

    /* OFF */
    // D9_GPIO->ODR |= (1<<D9_PIN); // Uncomment to turn off blue
    // D10_GPIO->ODR |= (1<<D10_PIN); // Uncomment to turn off green
    // D11_GPIO->ODR |= (1<<D11_PIN); // Uncomment to turn off red

    while (1){    
    }

    return 0;
}
