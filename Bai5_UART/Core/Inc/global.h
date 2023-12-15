/*
 * global.h
 *
 *  Created on: Dec 9, 2023
 *      Author: quoct
 */
#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "software_timer.h"
#include "led_7seg.h"
#include "button.h"
#include "lcd.h"
#include "picture.h"
#include "ds3231.h"
#include "uart.h"
#include "string.h"

#define MODE1 1
#define MODE2 2
#define MODE3 3
#define MODE4 4
#define MODE5 5
#define MODE6 6
#define MODE7 7
#define MODE8 8

#define ALARM_MODE1 10
#define ALARM_MODE2 11
#define ALARM_MODE3 12

#define INIT 0
#define NORMAL 1

#define HOUR 1
#define MIN 2
#define SEC 3
#define DAY 4
#define DATE 5
#define MONTH 6
#define YEAR 7
#define HOUR_A 10
#define MIN_A 11
#define SEC_A 12

extern int statusNORMAL_1;
extern int statusNORMAL_2;

extern int statusSEC_1; // Blink seconds
extern int statusSEC_2; // Increase
extern int statusSEC_3; // Save setting

extern int statusMIN_1; // Blink min
extern int statusMIN_2; // Increase
extern int statusMIN_3; // Save setting

extern int statusHOUR_1;
extern int statusHOUR_2;
extern int statusHOUR_3;

extern int statusDAY_1;
extern int statusDAY_2;
extern int statusDAY_3;

extern int statusDATE_1;
extern int statusDATE_2;
extern int statusDATE_3;

extern int statusMONTH_1;
extern int statusMONTH_2;
extern int statusMONTH_3;

extern int statusYEAR_1;
extern int statusYEAR_2;
extern int statusYEAR_3;

extern int statusNORMAL_ALARM;

extern int statusHOUR_ALARM_1;
extern int statusHOUR_ALARM_2;
extern int statusHOUR_ALARM_3;

extern int statusMIN_ALARM_1;
extern int statusMIN_ALARM_2;
extern int statusMIN_ALARM_3;

extern int mode;
extern int mode_alarm;

extern uint8_t counterSec;
extern uint8_t counterMin;
extern uint8_t counterHour;
extern uint8_t counterDay;
extern uint8_t counterDate;
extern uint8_t counterMonth;
extern uint8_t counterYear;
extern uint8_t counterHour_Alarm;
extern uint8_t counterMin_Alarm;
extern uint8_t counterSec_Alarm;
extern uint8_t counter_blink1;
extern uint8_t counter_blink2;

extern uint8_t counter_alert1;
extern uint8_t counter_alert2;


extern int isSendStr;
extern int uart_input;
extern int uart_valid;
extern int auto_change_mode;
extern uint8_t counter_TimeOut;
extern uint8_t counter_uartAlert;
extern int flag_Invalid;
extern int flag_TimeOut;
extern int flag_Error_TimeOut;
extern int number;


extern uint8_t tempUart[MAX_BUFFER_SIZE];

void init_value();
void init_counter();
void init_counter_alarm();
void blinky(int);
void blinkyAlarm(int);
void displayTime();
void displayAlarm();
void updateTime();
void updateAlarm();
void alert();
void save_ClockSettings();
void save_AlarmSettings();
void uart_Flag(char *);

#endif /* INC_GLOBAL_H_ */
