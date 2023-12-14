/*
 * fsm_clock.c
 *
 *  Created on: Dec 11, 2023
 *      Author: quoct
 */

#include "fsm_clock.h"

void fsm_clock()
{
    if (mode == MODE1)
    {
        switch (statusNORMAL_1)
        {
        case INIT:
            statusNORMAL_1 = NORMAL;
            break;
        case NORMAL:
            ds3231_ReadTime();
            displayTime();
            if (mode_alarm == ALARM_MODE1)
                lcd_StrCenter(0, 20, "MODE NORMAL", YELLOW, BLACK, 16, 1);
            break;
        default:
            break;
        }
    }
    if (mode == MODE2)
    {
        switch (statusHOUR_1) // Status blink digit and request uart input
        {
        case INIT:
            statusHOUR_1 = NORMAL;
            break;
        case NORMAL:
            lcd_StrCenter(0, 2, "UPDATING HOURS...", GREEN, BLACK, 16, 1);
            lcd_StrCenter(0, 20, "MODE CLOCK", YELLOW, BLACK, 16, 1);
            if (isSendStr == 0)
            {
                uart_Rs232SendString("Request hours: ");
                isSendStr = 1;
            }
            uart_Flag("Request hours: ");
            blinky(HOUR);
            break;
        default:
            break;
        }
        switch (statusHOUR_2) // Status to control the input digit from both the MCU and the uart
        {
        case INIT:
            statusHOUR_2 = NORMAL;
            break;
        case NORMAL:
            if (button_count[3] == 1 || (button_count[3] > 40 && button_count[3] % 4 == 0))
            {
                counterHour++;
                if (counterHour >= 24)
                    counterHour = 0;
            }
            if (uart_input == 1)
            {
                counterHour = number;
                if (counterHour >= 24)
                {
                    counterHour = counterHour % 24;
                }
                uart_input = 0;
                auto_change_mode = 1;
                counterTimeOut = 0;
                flag_Error = 0;
                flag_TimeOut = 0;
            }
            break;
        default:
            break;
        }
        switch (statusHOUR_3) // Status to save the settings, only applicable for lab 4. For lab 5, it is not necessary
        {
        case INIT:
            statusHOUR_3 = NORMAL;
            break;
        case NORMAL:
            if (button_count[12] == 1)
            {
                ds3231_Write(ADDRESS_HOUR, counterHour);
            }
            break;
        default:
            break;
        }
    }
    if (mode == MODE3) // MODE MINS
    {
        switch (statusMIN_1)
        {
        case INIT:
            statusMIN_1 = NORMAL;
            break;
        case NORMAL:
            lcd_StrCenter(0, 2, "UPDATING MINS...", GREEN, BLACK, 16, 1);
            lcd_StrCenter(0, 20, "MODE CLOCK", YELLOW, BLACK, 16, 1);
            if (isSendStr == 0)
            {
                uart_Rs232SendString("Request mins: ");
                isSendStr = 1;
            }
            uart_Flag("Request mins: ");
            blinky(MIN);
            break;
        default:
            break;
        }
        switch (statusMIN_2)
        {
        case INIT:
            statusMIN_2 = NORMAL;
            break;
        case NORMAL:
            if (button_count[3] == 1 || (button_count[3] > 40 && button_count[3] % 4 == 0))
            {
                counterMin++;
                if (counterMin >= 60)
                    counterMin = 0;
            }
            if (uart_input == 1)
            {
                counterMin = number;
                if (counterMin >= 60)
                {
                    counterMin = counterMin % 60;
                }
                uart_input = 0;
                auto_change_mode = 1;
                counterTimeOut = 0;
                flag_Error = 0;
                flag_TimeOut = 0;
            }
            break;
        default:
            break;
        }
        switch (statusMIN_3)
        {
        case INIT:
            statusMIN_3 = NORMAL;
            break;
        case NORMAL:
            if (button_count[12] == 1)
            {
                ds3231_Write(ADDRESS_MIN, counterMin);
            }
            break;
        default:
            break;
        }
    }
    if (mode == MODE4)
    {
        switch (statusSEC_1)
        {
        case INIT:
            statusSEC_1 = NORMAL;
            break;
        case NORMAL:
            lcd_StrCenter(0, 2, "UPDATING SECONDS...", GREEN, BLACK, 16, 1);
            lcd_StrCenter(0, 20, "MODE CLOCK", YELLOW, BLACK, 16, 1);
            if (isSendStr == 0)
            {
                uart_Rs232SendString("Request secs: ");
                isSendStr = 1;
            }
            uart_Flag("Request secs: ");
            blinky(SEC);
            break;
        default:
            break;
        }
        switch (statusSEC_2)
        {
        case INIT:
            statusSEC_2 = NORMAL;
            break;
        case NORMAL:
            if (button_count[3] == 1 || (button_count[3] > 40 && button_count[3] % 4 == 0))
            {
                counterSec++;
                if (counterSec >= 60)
                    counterSec = 0;
            }
            if (uart_input == 1)
            {
                counterSec = number;
                if (counterSec >= 60)
                {
                    counterSec = counterSec % 60;
                }
                uart_input = 0;
                auto_change_mode = 1;
                counterTimeOut = 0;
                flag_Error = 0;
                flag_TimeOut = 0;
            }
            break;
        default:
            break;
        }
        switch (statusSEC_3)
        {
        case INIT:
            statusSEC_3 = NORMAL;
            break;
        case NORMAL:
            if (button_count[12] == 1)
            {
                ds3231_Write(ADDRESS_SEC, counterSec);
            }
            break;
        default:
            break;
        }
    }
    if (mode == MODE5)
    {
        switch (statusDAY_1)
        {
        case INIT:
            statusDAY_1 = NORMAL;
            break;
        case NORMAL:
            lcd_StrCenter(0, 2, "UPDATING DAYS...", GREEN, BLACK, 16, 1);
            lcd_StrCenter(0, 20, "MODE CLOCK", YELLOW, BLACK, 16, 1);
            if (isSendStr == 0)
            {
                uart_Rs232SendString("Request days: ");
                isSendStr = 1;
            }
            uart_Flag("Request days: ");
            blinky(DAY);
            break;
        default:
            break;
        }
        switch (statusDAY_2)
        {
        case INIT:
            statusDAY_2 = NORMAL;
            break;
        case NORMAL:
            if (button_count[3] == 1 || (button_count[3] > 40 && button_count[3] % 4 == 0))
            {
                counterDay++;
                if (counterDay >= 8)
                    counterDay = 1;
            }
            if (uart_input == 1)
            {
                counterDay = number;
                if (counterDay >= 8)
                {
                    if (counterDay == 8)
                    {
                        counterDay = 1;
                    }
                    counterDay = counterDay % 8;
                }
                uart_input = 0;
                auto_change_mode = 1;
                counterTimeOut = 0;
                flag_Error = 0;
                flag_TimeOut = 0;
            }
            break;
        default:
            break;
        }
        switch (statusDAY_3)
        {
        case INIT:
            statusDAY_3 = NORMAL;
            break;
        case NORMAL:
            if (button_count[12] == 1)
            {
                ds3231_Write(ADDRESS_DAY, counterDay);
            }
            break;
        default:
            break;
        }
    }
    if (mode == MODE6)
    {
        switch (statusDATE_1)
        {
        case INIT:
            statusDATE_1 = NORMAL;
            break;
        case NORMAL:
            lcd_StrCenter(0, 2, "UPDATING DATES...", GREEN, BLACK, 16, 1);
            lcd_StrCenter(0, 20, "MODE CLOCK", YELLOW, BLACK, 16, 1);
            if (isSendStr == 0)
            {
                uart_Rs232SendString("Request dates: ");
                isSendStr = 1;
            }
            uart_Flag("Request dates: ");
            blinky(DATE);
            break;
        default:
            break;
        }
        switch (statusDATE_2)
        {
        case INIT:
            statusDATE_2 = NORMAL;
            break;
        case NORMAL:
            if (button_count[3] == 1 || (button_count[3] > 40 && button_count[3] % 4 == 0))
            {
                counterDate++;
                if (counterDate >= 32)
                    counterDate = 1;
            }
            if (uart_input == 1)
            {
                counterDate = number;
                if (counterDate >= 32)
                {
                    if (counterDate == 32)
                    {
                        counterDate = 1;
                    }
                    counterDate = counterDate % 32;
                }
                uart_input = 0;
                auto_change_mode = 1;
                counterTimeOut = 0;
                flag_Error = 0;
                flag_TimeOut = 0;
            }
            break;
        default:
            break;
        }
        switch (statusDATE_3)
        {
        case INIT:
            statusDATE_3 = NORMAL;
            break;
        case NORMAL:
            if (button_count[12] == 1)
            {
                ds3231_Write(ADDRESS_DATE, counterDate);
            }
            break;
        default:
            break;
        }
    }
    if (mode == MODE7)
    {
        switch (statusMONTH_1)
        {
        case INIT:
            statusMONTH_1 = NORMAL;
            break;
        case NORMAL:
            lcd_StrCenter(0, 2, "UPDATING MONTHS...", GREEN, BLACK, 16, 1);
            lcd_StrCenter(0, 20, "MODE CLOCK", YELLOW, BLACK, 16, 1);
            if (isSendStr == 0)
            {
                uart_Rs232SendString("Request months: ");
                isSendStr = 1;
            }
            uart_Flag("Request months: ");
            blinky(MONTH);
            break;
        default:
            break;
        }
        switch (statusMONTH_2)
        {
        case INIT:
            statusMONTH_2 = NORMAL;
            break;
        case NORMAL:
            if (button_count[3] == 1 || (button_count[3] > 40 && button_count[3] % 4 == 0))
            {
                counterMonth++;
                if (counterMonth >= 13)
                    counterMonth = 1;
            }
            if (uart_input == 1)
            {
                counterMonth = number;
                if (counterMonth >= 13)
                {
                    if (counterMonth == 13)
                    {
                        counterMonth = 1;
                    }
                    counterMonth = counterMonth % 13;
                }
                uart_input = 0;
                auto_change_mode = 1;
                counterTimeOut = 0;
                flag_Error = 0;
                flag_TimeOut = 0;
            }
            break;
        default:
            break;
        }
        switch (statusMONTH_3)
        {
        case INIT:
            statusMONTH_3 = NORMAL;
            break;
        case NORMAL:
            if (button_count[12] == 1)
            {
                ds3231_Write(ADDRESS_MONTH, counterMonth);
            }
            break;
        default:
            break;
        }
    }
    if (mode == MODE8)
    {
        switch (statusYEAR_1)
        {
        case INIT:
            statusYEAR_1 = NORMAL;
            break;
        case NORMAL:
            lcd_StrCenter(0, 2, "UPDATING YEARS...", GREEN, BLACK, 16, 1);
            lcd_StrCenter(0, 20, "MODE CLOCK", YELLOW, BLACK, 16, 1);
            // uart_Flag("Request years: ");
            if (isSendStr == 0)
            {
                uart_Rs232SendString("Request years: ");
                isSendStr = 1;
            }
            blinky(YEAR);
            break;
        default:
            break;
        }
        switch (statusYEAR_2)
        {
        case INIT:
            statusYEAR_2 = NORMAL;
            break;
        case NORMAL:
            if (button_count[3] == 1 || (button_count[3] > 40 && button_count[3] % 4 == 0))
            {
                counterYear++;
                if (counterYear >= 100)
                    counterYear = 0;
            }
            if (uart_input == 1)
            {
                if (number < 0)
                {
                    lcd_StrCenter(0, 250, "INVALID VALUE!!!", GREEN, BLACK, 16, 1);
                }
                else
                {
                    counterYear = number;
                    counterYear = counterYear % 100;
                    uart_input = 0;
                    auto_change_mode = 1;
                    counterTimeOut = 0;
                    flag_Error = 0;
                    flag_TimeOut = 0;
                }
            }
            break;
        default:
            break;
        }
        switch (statusYEAR_3)
        {
        case INIT:
            statusYEAR_3 = NORMAL;
            break;
        case NORMAL:
            if (button_count[12] == 1)
            {
                ds3231_Write(ADDRESS_YEAR, counterYear);
            }
            break;
        default:
            break;
        }
    }

    switch (mode)
    {
    case MODE1:
        if (button_count[0] == 1)
        {
            mode = MODE2;
            isSendStr = 0;
            init_counter();
            lcd_Fill(0, 20, 240, 40, BLACK); // Clear "MODE NORMAL" on the LCD
        }
        break;
    case MODE2:
        if (button_count[0] == 1 || auto_change_mode == 1)
        {
            mode = MODE3;
            isSendStr = 0;
            auto_change_mode = 0;
            lcd_ShowIntNum(70, 100, counterHour, 2, GREEN, BLACK, 24);
            lcd_Fill(0, 0, 240, 20, BLACK); // Clear "UPDATING HOURS..."
            lcd_Fill(0, 20, 240, 40, BLACK); // Clear "MODE LOCK"
            lcd_Fill(0, 270, 240, 290, BLACK); 
            uart_Rs232SendString("\n");
        }
        break;
    case MODE3:
        if (button_count[0] == 1 || auto_change_mode == 1)
        {
            mode = MODE4;
            isSendStr = 0;
            auto_change_mode = 0;
            lcd_ShowIntNum(110, 100, counterMin, 2, GREEN, BLACK, 24);
            lcd_Fill(0, 0, 240, 20, BLACK);
            lcd_Fill(0, 20, 240, 40, BLACK);
            uart_Rs232SendString("\n");
        }
        break;
    case MODE4:
        if (button_count[0] == 1 || auto_change_mode == 1)
        {
            mode = MODE5;
            isSendStr = 0;
            auto_change_mode = 0;
            lcd_ShowIntNum(150, 100, counterSec, 2, GREEN, BLACK, 24);
            lcd_Fill(0, 0, 240, 20, BLACK);
            lcd_Fill(0, 20, 240, 40, BLACK);
            uart_Rs232SendString("\n");
        }
        break;
    case MODE5:
        if (button_count[0] == 1 || auto_change_mode == 1)
        {
            mode = MODE6;
            isSendStr = 0;
            auto_change_mode = 0;
            lcd_ShowIntNum(20, 130, counterDay, 2, YELLOW, BLACK, 24);
            lcd_Fill(0, 0, 240, 20, BLACK);
            lcd_Fill(0, 20, 240, 40, BLACK);
            uart_Rs232SendString("\n");
        }
        break;
    case MODE6:
        if (button_count[0] == 1 || auto_change_mode == 1)
        {
            mode = MODE7;
            isSendStr = 0;
            auto_change_mode = 0;
            lcd_ShowIntNum(70, 130, counterDate, 2, YELLOW, BLACK, 24);
            lcd_Fill(0, 0, 240, 20, BLACK);
            lcd_Fill(0, 20, 240, 40, BLACK);
            uart_Rs232SendString("\n");
        }
        break;
    case MODE7:
        if (button_count[0] == 1 || auto_change_mode == 1)
        {
            mode = MODE8;
            isSendStr = 0;
            auto_change_mode = 0;
            lcd_ShowIntNum(110, 130, counterMonth, 2, YELLOW, BLACK, 24);
            lcd_Fill(0, 0, 240, 20, BLACK);
            lcd_Fill(0, 20, 240, 40, BLACK);
            uart_Rs232SendString("\n");
        }
        break;
    case MODE8:
        if (button_count[0] == 1 || auto_change_mode == 1)
        {
            mode = MODE1;
            isSendStr = 0;
            auto_change_mode = 0;
            lcd_ShowIntNum(150, 130, counterYear, 2, YELLOW, BLACK, 24);
            lcd_Fill(0, 0, 240, 20, BLACK);
            lcd_Fill(0, 20, 240, 40, BLACK);
            uart_Rs232SendString("\n");
            save_ClockSettings();
        }
        break;
    default:
        break;
    }

    if (flag_Error == 2)
    {
        mode = MODE1;
        isSendStr = 0;
        auto_change_mode = 0;
        flag_TimeOut = 0;
        flag_Error = 0;
        save_ClockSettings();
        lcd_Fill(0, 0, 240, 20, BLACK); 
        lcd_Fill(0, 20, 240, 40, BLACK);
        lcd_Fill(0, 270, 240, 290, BLACK);
    }
}
