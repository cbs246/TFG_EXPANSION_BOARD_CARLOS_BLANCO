/**
 * @file port_keyboard.h
 * @brief Header for port_keyboard.c file.
 * @author Carlos Blanco Sevilla
 * @date 2024-12-01
*/

#ifndef PORT_KEYBOARD_H_
#define PORT_KEYBOARD_H_


/**
 * @brief GPIO and PIN configuration for the keyboard.
 * 
 * @retval None.
 */
void port_keyboard_gpio_setup(void);

/**
 * @brief Reads the matrix rows. If detects that one row is on, it returns an int corresponding to that row.  
 * 
 * @retval int32_t.
 */
uint8_t port_get_rows(void);

/**
 * @brief Toggle the selected column. If the selected column is on, it turns it off and vice versa.
 * 
 * @param column Position of the column.
 * 
 * @retval None.
 */
 void port_column_toggle(uint8_t col);

/**
 * @brief Prints the key pressed on the keyboard.
 * 
 * @retval None.
 */
void port_keyboard_result(void);

/**
 * @brief Contents the translation to the keys that are pressed.
 * 
 * @retval Char.
 */
char map_key(uint8_t col, uint8_t row);

#endif