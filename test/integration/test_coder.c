/**
 * @file test_coder.c
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
#define D6_GPIO    GPIOB
#define D5_GPIO    GPIOB
#define D4_GPIO    GPIOB 
#define D3_GPIO    GPIOB 
#define EN_A5_GPIO GPIOC // ENABLE COD GPIO
   
// Pins
#define D6_PIN        10
#define D5_PIN         4
#define D3_PIN         3    
#define D4_PIN         5 
#define EN_A5_PIN      0 // ENABLE COD PIN


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
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // Clean the registers
    D6_GPIO->MODER &= ~(BASE_MASK << 2 * D6_PIN);
    D6_GPIO->PUPDR &= ~(BASE_MASK << 2 * D6_PIN);
    D5_GPIO->MODER &= ~(BASE_MASK << 2 * D5_PIN);
    D5_GPIO->PUPDR &= ~(BASE_MASK << 2 * D5_PIN);
    D4_GPIO->MODER &= ~(BASE_MASK << 2 * D4_PIN);
    D4_GPIO->PUPDR &= ~(BASE_MASK << 2 * D4_PIN);
    D3_GPIO->MODER &= ~(BASE_MASK << 2 * D3_PIN);
    D3_GPIO->PUPDR &= ~(BASE_MASK << 2 * D3_PIN);
    EN_A5_GPIO->MODER &= ~(BASE_MASK << 2 * EN_A5_PIN);
    EN_A5_GPIO->PUPDR &= ~(BASE_MASK << 2 * EN_A5_PIN);

    // Configure the registers
    D6_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D6_PIN);
    D6_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * D6_PIN);
    D5_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D5_PIN);
    D5_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D5_PIN);
    D4_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D4_PIN);
    D4_GPIO->PUPDR |= (GPIO_PUPDR_NOPULL << 2 * D4_PIN);
    D3_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D3_PIN);
    D3_GPIO->MODER |= (GPIO_MODE_OUT << 2 * D3_PIN);
    EN_A5_GPIO->MODER |= (GPIO_MODE_OUT << 2 * EN_A5_PIN);
    EN_A5_GPIO->MODER |= (GPIO_MODE_OUT << 2 * EN_A5_PIN);


    while (1){
    /* OFF */
    EN_A5_GPIO->ODR &= ~(1<<EN_A5_PIN); 
    // D6_GPIO->ODR &= ~(1<<D6_PIN); 
    // D5_GPIO->ODR &= ~(1<<D5_PIN);
    // D4_GPIO->ODR &= ~(1<<D4_PIN); 
    D3_GPIO->ODR &= ~(1<<D3_PIN);

    /* ON */
    // EN_A5_GPIO->ODR |= (1<<EN_A5_PIN); 
    D6_GPIO->ODR |= (1<<D6_PIN); 
    D5_GPIO->ODR |= (1<<D5_PIN); 
    D4_GPIO->ODR |= (1<<D4_PIN); 
    // D3_GPIO->ODR |= (1<<D3_PIN); 
    }
    return 0;
}