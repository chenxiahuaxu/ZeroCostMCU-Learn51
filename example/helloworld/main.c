

/*
 * @Author: chenxiahuaxu
 * @Date: 2023-07-11 15:35:44
 * @LastEditTime: 2023-07-11 15:52:45
 * @LastEditors: chenxiahuaxu
 * @Description: Hello World实验
 * @FilePath: /ZeroCostMCU-Learn51/example/led/main.c
 */

#include <mcs51/8052.h>  // SDCC使用不同的头文件
#include <string.h>

#define FOSC 11059200L      // 晶振频率11.0592MHz
#define BAUD 19200           // 波特率19200

void UART_Init() //19200bps@11.0592MHz
{
    SCON = 0x50;        //8位数据,可变波特率
    TMOD |= 0x20;       //定时器1模式2（8位自动重装）
    PCON |= 0x80;       //SMOD=1 波特率加倍
    TH1 = TL1 = 0xFD;   //波特率19200（标准8051设置）
    TR1 = 1;            //启动定时器1
}

void UART_SendChar(char c) {
    SBUF = c;               // 将字符写入发送缓冲区
    while(!TI);             // 等待发送完成
    TI = 0;                 // 清除发送中断标志
}

void UART_SendString(char *str) {
    while(*str) {
        UART_SendChar(*str++);
    }
}

void main() {
    UART_Init();
    while(1) {
        UART_SendString("Hello World!\r\n");
        // 可以添加延时函数控制发送频率
    }
}