/**
 * @file test_decoder.c
 * @brief Integration test for coder.
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
#define col_D6_GPIO GPIOB // IN DECOD 1 GPIO
#define col_D5_GPIO GPIOB // IN DECOD 2 GPIO
#define EN_D2_GPIO  GPIOA // ENABLE DECOD GPIO
   
// Pins
#define col_D6_PIN     10 // IN DECOD 1 PIN
#define col_D5_PIN      4 // IN DECOD 2 PIN
#define EN_D2_PIN      10 // ENABLE DECOD PIN


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
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Clean the registers
    EN_D2_GPIO->MODER &= ~(BASE_MASK << 2 * EN_D2_PIN);
    EN_D2_GPIO->PUPDR &= ~(BASE_MASK << 2 * EN_D2_PIN);
    col_D6_GPIO->MODER &= ~(BASE_MASK << 2 * col_D6_PIN);
    col_D6_GPIO->PUPDR &= ~(BASE_MASK << 2 * col_D6_PIN);
    col_D5_GPIO->MODER &= ~(BASE_MASK << 2 * col_D5_PIN);
    col_D5_GPIO->PUPDR &= ~(BASE_MASK << 2 * col_D5_PIN);

    // Configure the registers
    EN_D2_GPIO->MODER |= (GPIO_MODE_OUT << 2 * EN_D2_PIN);
    EN_D2_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * EN_D2_PIN);
    col_D6_GPIO->MODER |= (GPIO_MODE_OUT << 2 * col_D6_PIN);
    col_D6_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * col_D6_PIN);
    col_D5_GPIO->MODER |= (GPIO_MODE_OUT << 2 * col_D5_PIN);
    col_D5_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * col_D5_PIN);



    while (1){
        
    /* OFF */
    // EN_D2_GPIO->ODR &= ~(1<<EN_D2_PIN); // Uncomment to turn on A0
    // col_D6_GPIO->ODR &= ~(1<<col_D6_PIN); // Uncomment to turn on A0
    // col_D5_GPIO->ODR &= ~(1<<col_D5_PIN); // Uncomment to turn on A1

    /* ON */
    EN_D2_GPIO->ODR |= (1<<EN_D2_PIN); // Uncomment to turn off A0
    // col_D6_GPIO->ODR |= (1<<col_D6_PIN); // Uncomment to turn off A0
    // col_D5_GPIO->ODR |= (1<<col_D5_PIN); // Uncomment to turn off A1
        
    }
    return 0;
}