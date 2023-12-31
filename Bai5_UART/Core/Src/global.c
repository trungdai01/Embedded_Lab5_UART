/*
 * global.c
 *
 *  Created on: Dec 9, 2023
 *      Author: quoct
 */

#include "global.h"

int statusNORMAL_1;
int statusNORMAL_2;
int statusSEC_1 = 0; // Blink seconds
int statusSEC_2 = 0; // Increase
int statusSEC_3 = 0; // Save settings

int statusMIN_1 = 0;
int statusMIN_2 = 0;
int statusMIN_3 = 0;

int statusHOUR_1 = 0;
int statusHOUR_2 = 0;
int statusHOUR_3 = 0;

int statusDAY_1 = 0;
int statusDAY_2 = 0;
int statusDAY_3 = 0;

int statusDATE_1 = 0;
int statusDATE_2 = 0;
int statusDATE_3 = 0;

int statusMONTH_1 = 0;
int statusMONTH_2 = 0;
int statusMONTH_3 = 0;

int statusYEAR_1 = 0;
int statusYEAR_2 = 0;
int statusYEAR_3 = 0;

int statusNORMAL_ALARM = 0;

int statusHOUR_ALARM_1 = 0;
int statusHOUR_ALARM_2 = 0;
int statusHOUR_ALARM_3 = 0;

int statusMIN_ALARM_1 = 0;
int statusMIN_ALARM_2 = 0;
int statusMIN_ALARM_3 = 0;

int mode = 0;
int mode_alarm = 0;

uint8_t counterSec = 0;
uint8_t counterMin = 0;
uint8_t counterHour = 0;
uint8_t counterDay = 0;
uint8_t counterDate = 0;
uint8_t counterMonth = 0;
uint8_t counterYear = 0;
uint8_t counterHour_Alarm = 0;
uint8_t counterMin_Alarm = 0;
uint8_t counter_blink1 = 0;
uint8_t counter_blink2 = 0;

uint8_t counter_alert1 = 0;
uint8_t counter_alert2 = 0;

// LAB 5 Variables

int isSendStr = 0;
int uart_input = 0;
int uart_valid = 0;
int auto_change_mode = 0;
uint8_t counter_TimeOut = 0;
uint8_t counter_uartAlert = 0;
int flag_Invalid = 0;
int flag_TimeOut = 0;
int flag_Error_TimeOut = 0;
int number = 0;

uint8_t tempUart[MAX_BUFFER_SIZE] = {0};

void init_value(void)
{
    mode = MODE1;
    mode_alarm = ALARM_MODE1;

    statusNORMAL_1 = INIT;
    statusNORMAL_2 = INIT;
    statusSEC_1 = INIT;
    statusSEC_2 = INIT;
    statusSEC_3 = INIT;

    statusMIN_1 = INIT;
    statusMIN_2 = INIT;
    statusMIN_3 = INIT;

    statusHOUR_1 = INIT;
    statusHOUR_2 = INIT;
    statusHOUR_3 = INIT;

    statusDAY_1 = INIT;
    statusDAY_2 = INIT;
    statusDAY_3 = INIT;

    statusDATE_1 = INIT;
    statusDATE_2 = INIT;
    statusDATE_3 = INIT;

    statusMONTH_1 = INIT;
    statusMONTH_2 = INIT;
    statusMONTH_3 = INIT;

    statusYEAR_1 = INIT;
    statusYEAR_2 = INIT;
    statusYEAR_3 = INIT;

    statusHOUR_ALARM_1 = INIT;
    statusHOUR_ALARM_2 = INIT;
    statusHOUR_ALARM_3 = INIT;

    statusMIN_ALARM_1 = INIT;
    statusMIN_ALARM_2 = INIT;
    statusMIN_ALARM_3 = INIT;

    counter_blink1 = INIT;
    counter_blink2 = INIT;

    counter_alert1 = INIT;
    counter_alert2 = INIT;

    counter_uartAlert = 0;
    counter_TimeOut = 0;
    flag_TimeOut = 0;

    isSendStr = 0;
    flag_Error_TimeOut = 0;
}

void init_counter(void)
{
    counterSec = ds3231_sec;
    counterMin = ds3231_min;
    counterHour = ds3231_hours;
    counterDay = ds3231_day;
    counterDate = ds3231_date;
    counterMonth = ds3231_month;
    counterYear = ds3231_year;
}

void init_counter_alarm(void)
{
    counterHour_Alarm = ds3231_alarm_hour;
    counterMin_Alarm = ds3231_alarm_min;
}

void blinky(int unit)
{

    counter_blink1 = (counter_blink1 + 1) % 5;
    counter_blink2 = (counter_blink2 + 1) % 10;
    if (unit == HOUR)
    {
        if (counter_blink1 == 0)
        {
            lcd_ShowIntNum(70, 100, counterHour, 2, GREEN, BLACK, 24);
        }
        if (counter_blink2 == 0)
        {
            lcd_ShowIntNum(70, 100, 0, 2, BLACK, BLACK, 24);
            // lcd_Clear(BLACK);
        }
    }
    if (unit == MIN)
    {
        if (counter_blink1 == 0)
        {
            lcd_ShowIntNum(110, 100, counterMin, 2, GREEN, BLACK, 24);
        }
        if (counter_blink2 == 0)
        {
            lcd_ShowIntNum(110, 100, 0, 2, BLACK, BLACK, 24);
        }
    }
    if (unit == SEC)
    {
        if (counter_blink1 == 0)
        {
            lcd_ShowIntNum(150, 100, counterSec, 2, GREEN, BLACK, 24);
        }
        if (counter_blink2 == 0)
        {
            lcd_ShowIntNum(150, 100, 0, 2, BLACK, BLACK, 24);
        }
    }
    if (unit == DAY)
    {
        if (counter_blink1 == 0)
        {
            lcd_ShowIntNum(20, 130, counterDay, 2, YELLOW, BLACK, 24);
        }
        if (counter_blink2 == 0)
        {
            lcd_ShowIntNum(20, 130, 0, 2, BLACK, BLACK, 24);
        }
    }
    if (unit == DATE)
    {
        if (counter_blink1 == 0)
        {
            lcd_ShowIntNum(70, 130, counterDate, 2, YELLOW, BLACK, 24);
        }
        if (counter_blink2 == 0)
        {
            lcd_ShowIntNum(70, 130, 0, 2, BLACK, BLACK, 24);
        }
    }
    if (unit == MONTH)
    {
        if (counter_blink1 == 0)
        {
            lcd_ShowIntNum(110, 130, counterMonth, 2, YELLOW, BLACK, 24);
        }
        if (counter_blink2 == 0)
        {
            lcd_ShowIntNum(110, 130, 0, 2, BLACK, BLACK, 24);
        }
    }
    if (unit == YEAR)
    {
        if (counter_blink1 == 0)
        {
            lcd_ShowIntNum(150, 130, counterYear, 2, YELLOW, BLACK, 24);
        }
        if (counter_blink2 == 0)
        {
            lcd_ShowIntNum(150, 130, 0, 2, BLACK, BLACK, 24);
        }
    }
}

void blinkyAlarm(int unit)
{
    counter_alert1 = (counter_alert1 + 1) % 5;
    counter_alert2 = (counter_alert2 + 1) % 10;
    if (unit == HOUR_A)
    {
        if (counter_alert1 == 0)
        {
            lcd_ShowIntNum(70, 200, counterHour_Alarm, 2, BLUE, BLACK, 24);
        }
        if (counter_alert2 == 0)
        {
            lcd_ShowIntNum(70, 200, 0, 2, BLACK, BLACK, 24);
        }
    }
    if (unit == MIN_A)
    {
        if (counter_alert1 == 0)
        {
            lcd_ShowIntNum(110, 200, counterMin_Alarm, 2, BLUE, BLACK, 24);
        }
        if (counter_alert2 == 0)
        {
            lcd_ShowIntNum(110, 200, 0, 2, BLACK, BLACK, 24);
        }
    }
}

void displayTime()
{
    lcd_ShowIntNum(70, 100, ds3231_hours, 2, GREEN, BLACK, 24);
    lcd_ShowIntNum(110, 100, ds3231_min, 2, GREEN, BLACK, 24);
    lcd_ShowIntNum(150, 100, ds3231_sec, 2, GREEN, BLACK, 24);
    lcd_ShowIntNum(20, 130, ds3231_day, 2, YELLOW, BLACK, 24);
    lcd_ShowIntNum(70, 130, ds3231_date, 2, YELLOW, BLACK, 24);
    lcd_ShowIntNum(110, 130, ds3231_month, 2, YELLOW, BLACK, 24);
    lcd_ShowIntNum(150, 130, ds3231_year, 2, YELLOW, BLACK, 24);
}

void updateTime()
{
    ds3231_Write(ADDRESS_YEAR, 23);
    ds3231_Write(ADDRESS_MONTH, 10);
    ds3231_Write(ADDRESS_DATE, 15);
    ds3231_Write(ADDRESS_DAY, 6);
    ds3231_Write(ADDRESS_HOUR, 15);
    ds3231_Write(ADDRESS_MIN, 30);
    ds3231_Write(ADDRESS_SEC, 35);
}

void displayAlarm(void)
{
    lcd_ShowIntNum(70, 200, ds3231_alarm_hour, 2, BLUE, BLACK, 24);
    lcd_ShowIntNum(110, 200, ds3231_alarm_min, 2, BLUE, BLACK, 24);
}

void updateAlarm(void)
{
    ds3231_Write(ADDRESS_HOUR_ALARM, 0);
    ds3231_Write(ADDRESS_MIN_ALARM, 0);
}

void alert(void)
{
    counter_alert1 = (counter_alert1 + 1) % 5;
    counter_alert2 = (counter_alert2 + 1) % 10;
    if (counter_alert1 == 0)
    {
        lcd_Clear(RED);
    }
    if (counter_alert2 == 0)
    {
        lcd_Clear(BLACK);
    }
}

void save_ClockSettings(void)
{
    ds3231_Write(ADDRESS_YEAR, counterYear);
    ds3231_Write(ADDRESS_MONTH, counterMonth);
    ds3231_Write(ADDRESS_DATE, counterDate);
    ds3231_Write(ADDRESS_DAY, counterDay);
    ds3231_Write(ADDRESS_SEC, counterSec);
    ds3231_Write(ADDRESS_MIN, counterMin);
    ds3231_Write(ADDRESS_HOUR, counterHour);
}

void save_AlarmSettings(void)
{
    ds3231_Write(ADDRESS_HOUR_ALARM, counterHour_Alarm);
    ds3231_Write(ADDRESS_MIN_ALARM, counterMin_Alarm);
}

void uart_Flag(char *str)
{
    counter_TimeOut = (counter_TimeOut + 1) % 200;
    if (counter_TimeOut == 0)
    {
        flag_TimeOut++;
        uart_Rs232SendString(str);
    }
    if (flag_TimeOut == 3)
    {
        counter_uartAlert = (counter_uartAlert + 1) % 60;
        lcd_StrCenter(0, 270, "ERROR!!!", GREEN, BLACK, 16, 1);
        if (counter_uartAlert == 0)
        {
            flag_Error_TimeOut = 1;
            return;
        }
    }
    if (flag_Invalid == 1)
    {
        counter_uartAlert = (counter_uartAlert + 1) % 60;
        lcd_StrCenter(0, 270, "INVALID", GREEN, BLACK, 16, 1);
        if (counter_uartAlert == 0)
        {
            lcd_Fill(0, 270, 240, 290, BLACK);
            flag_Invalid = 0;
        }
    }
}
