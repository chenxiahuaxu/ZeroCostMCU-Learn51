#include <mcs51/8052.h>

// 简单延时函数
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = ms; i > 0; i--)
        for(j = 110; j > 0; j--);
}

void main() {
    unsigned char led = 0xFE;  // 初始状态：LED0点亮
    
    while(1) {
        P1 = led;
        delay_ms(500);
        
        // 手动实现循环左移
        if(led & 0x80) {    // 检查最高位
            led = (led << 1) | 0x01;  // 左移后补1
        } else {
            led = led << 1; // 普通左移
        }
        
        // 当所有LED熄灭时重置状态
        if(led == 0xFF) {
            led = 0xFE;
        }
    }
}