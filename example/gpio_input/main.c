/*
 * @Author: chenxiahuaxu
 * @Date: 2023-07-11 15:35:44
 * @LastEditTime: 2023-07-11 15:52:45
 * @LastEditors: chenxiahuaxu
 * @Description: 流水灯实验
 * @FilePath: /ZeroCostMCU-Learn51/example/led/main.c
 */

#include <mcs51/8052.h>

// 简单延时函数
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = ms; i > 0; i--)
        for(j = 110; j > 0; j--);
}
// LED驱动函数
void led_write(unsigned char pattern) {
    P1 = pattern;
}
// 按键扫描函数
unsigned char key_scan() {
    unsigned char key_value = 0;
    static unsigned char last_key = 0;
    // 读取P2端口状态
    key_value = P2;
    // 简易消抖处理
    if(key_value != last_key) {
        delay_ms(10);
        key_value = P2;
    }
    last_key = key_value;
    return key_value;
}

void main() {
    // 初始化端口
    P2 = 0xFF;  // 设置P2口为输入模式
    while(1) {
        unsigned char keys = key_scan();
        // 按键状态直接控制LED
        led_write(keys);
    }
}