/*
 * uart_comm.c
 *
 *  Created on: Dec 11, 2023
 *      Author: quoct
 */

#include "uart_comm.h"

uint8_t command_status = START_COMMAND;
uint8_t uart_status = START_UART;

uint8_t command_flag = 0;
uint8_t command_data[MAX_BUFFER_SIZE];
uint8_t index_cmd_data = 0;

uint8_t empty_str[MAX_BUFFER_SIZE] = {0};

void str_cpy(uint8_t *str1, uint8_t *str2)
{
    for (int i = 0; i < MAX_BUFFER_SIZE; i++)
    {
        str1[i] = str2[i];
    }
}

void comm_parser_fsm(void)
{
    switch (command_status)
    {
    case START_COMMAND:
        if (buffer_byte[index_buffer - 1] == '!')
        {
            command_status = READING;
            str_cpy(command_data, empty_str);
            index_cmd_data = 0;
        }
        command_flag = 0;
        break;
    case READING:
        if (buffer_byte[index_buffer - 1] != '!' && buffer_byte[index_buffer - 1] != '#')
        {
            command_data[index_cmd_data] = buffer_byte[index_buffer - 1];
            index_cmd_data++;
        }
        if (buffer_byte[index_buffer - 1] == '#')
        {
            for (int i = 0; i < index_cmd_data; i++)
            {
                if (command_data[i] <= 47 || command_data[i] >= 58)
                {
                    flag_Invalid = 1;
                    break;
                }
            }
            str_cpy(buffer_byte, empty_str);
            index_buffer = 0;
            uart_status = END_UART;
            command_status = START_COMMAND;
            command_flag = 1;
        }
        else if (buffer_byte[index_buffer - 1] == '!')
        {
            str_cpy(buffer_byte, empty_str);
            str_cpy(command_data, empty_str);
            index_buffer = 0;
            index_cmd_data = 0;
            buffer_byte[index_buffer] = '!';
            index_buffer++;
            command_status = READING;
            command_flag = 0;
        }
        break;
    default:
        break;
    }
}

void uart_communication(void)
{
    switch (uart_status)
    {
    case PROCESSING_DATA:
        break;
    case END_UART:
        if (command_flag == 1)
        {
            command_flag = 0;
            str_cpy(tempUart, empty_str);
            str_cpy(tempUart, command_data);
            lcd_Fill(0, 40, 240, 70, BLACK);
            lcd_ShowStr(70, 50, "INPUT: ", GREEN, BLACK, 16, 1);
            lcd_ShowStr(140, 50, tempUart, GREEN, BLACK, 16, 1);
            if (flag_Invalid == 0)
            {
                uart_valid = 1;
                number = atoi((void *)tempUart);
                // number = (int)tempUart;
                lcd_Fill(0, 70, 240, 100, BLACK);
                lcd_ShowStr(70, 70, "NUMBER: ", GREEN, BLACK, 16, 1);
                lcd_ShowStr(140, 70, tempUart, GREEN, BLACK, 16, 1);
            }
            flag_TimeOut = 0;
            counter_TimeOut = 0;
        }
        break;
    default:
        break;
    }
}
