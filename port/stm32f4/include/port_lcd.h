/**
 * @file port_lcd.h
 * @brief Header for port_lcd.c file.
 * @author Carlos Blanco Sevilla
 * @date 2024-12-01
*/

#ifndef PORT_LCD_H_
#define PORT_LCD_H_

/**
 * @brief GPIO and PIN configuration for the LCD.
 * 
 * @retval None.
 */
void port_lcd_gpio_setup(void);

/**
 * @brief Delay function.
 * 
 * @param ms Time in miliseconds.
 * 
 * @retval None.
 */
void delay_ms(uint32_t ms);

/**
 * @brief This function is used for writing the data on the LCD. 
 *        In 4 bits mode, two pulses for enable are needed.
 * 
 * @param data Data to trnasfer.
 * @param control Indicates if the LCD is receiving an instruction or is receiving data.
 * 
 * @retval None.
 */
void lcd_nibble_write(uint8_t data, uint8_t control);

/**
 * @brief Converts an 8-bit instruction into a 4-bit instruction by dividing it in 2 nibbles.
 * 
 * @param cmd Instruction to be converted.
 * 
 * @retval None.
 */
void lcd_com(uint8_t cmd);

/**
 * @brief Sends 8-bit DATA converted into 4-bits DATA.
 * 
 * @param data Data to be sended.
 * 
 * @retval None.
 */
void lcd_data(uint8_t data);

/**
 * @brief Realizaes the initilization sequence necesary for the LCD controller.
 * 
 * @retval None.
 */
void LCD_init(void);

/**
 * @brief Calculates the memory address of the LCD controller for the corresponding row and column.
 *        Then, it sends that address as a comand to position the cursor.
 * 
 * @param col Column selected.
 * @param row Row selected.
 * 
 * @retval None.
 */
void LCD_SetCursor(uint8_t col, uint8_t row);

/**
 * @brief Prints the data on the display.
 * 
 * @param str Data to be printed.
 * 
 * @retval None.
 */
void LCD_Print(const char *str);

#endif