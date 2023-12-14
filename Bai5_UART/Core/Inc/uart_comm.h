/*
 * uart_comm.h
 *
 *  Created on: Dec 11, 2023
 *      Author: quoct
 */

#ifndef INC_UART_COMM_H_
#define INC_UART_COMM_H_

#include "global.h"

#define START_COMMAND 0
#define READING     1

#define START_UART 3
#define PROCESSING_DATA 4
#define END_UART 5

extern uint8_t command_status;
extern uint8_t uart_status;

extern uint8_t command_flag;
extern uint8_t command_data[MAX_BUFFER_SIZE];
extern uint8_t index_command_data;

extern uint8_t empty_str[MAX_BUFFER_SIZE];

void str_cpy(uint8_t *str1, uint8_t *str2);

void comm_parser_fsm();
void uart_communication();
// void process_clock_Uart(char*);

#endif /* INC_UART_COMM_H_ */
