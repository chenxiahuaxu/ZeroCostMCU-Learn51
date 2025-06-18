
# 概述

&emsp;&emsp;`Hello World`程序通常是学习任何新编程语言或开发环境的第一个项目。对于51单片机来说，我们的`Hello World`程序将通过串口发送`Hello World`字符串，并在仿真环境中验证其功能。

&emsp;&emsp;通过这个简单的项目，大家将学习如何编写代码、编译程序、转换文件格式以及进行仿真测试。

# 目标

- 学习如何编写51单片机的C语言代码。
- 学习如何编译程序并生成可烧录文件。
- 学习如何在仿真环境中运行程序并验证功能。

# 编写代码

&emsp;&emsp;以下是实现`Hello World`功能的代码。虽然这是我们的第一个程序，但代码中包含了51单片机串口通信的基本实现。我们无需深入理解代码的具体含义，只需按照教程逐步操作即可。

```bash
#include <mcs51/8052.h>  // SDCC使用不同的头文件
#include <string.h>
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
```

# 编译代码

## 编译过程

1. **打开终端（Linux）或命令提示符（Windows）**

   - 在Windows系统下，可以通过开始菜单找到命令提示符并打开。
   - 在Linux系统下，可以通过快捷键`Ctrl+Alt+T`打开终端。

2. **切换到代码所在的目录**

&emsp;&emsp;假设代码文件`main.c`位于`~/example/helloworld`目录下，可以通过以下命令切换到该目录：

```bash
cd ~/example/helloworld
```

3. **运行编译命令**

&emsp;&emsp;在终端或命令提示符中，运行以下命令进行编译（`-mmcs51`参数指定目标芯片为8051系列）：

```bash
sdcc -mmcs51 main.c
```

4. **查看生成的文件**

&emsp;&emsp;编译完成后，查看当前目录下的文件：

```bash
ls
```

&emsp;&emsp;会看到生成了多个文件，如`main.asm`、`main.ihx`、`main.hex`等。其中，`main.ihx`是编译后的中间文件，`main.hex`是最终的可烧录文件。


## 转换为HEX文件

&emsp;&emsp;SDCC编译生成的是`.ihx`文件，而`Edsim51`仿真软件需要`.hex`文件。因此，需要将`.ihx`文件转换为`.hex`文件。

1. **运行转换命令**

&emsp;&emsp;在终端或命令提示符中，运行以下命令进行转换：

```bash
packihx main.ihx > main.hex
```

&emsp;&emsp;`packihx`是`SDCC`提供的工具，用于将`.ihx`文件转换为`.hex`文件。

3. **验证转换结果**

&emsp;&emsp;转换完成后，再次查看当前目录下的文件：

```bash
ls
main.asm  main.c  main.ihx  main.lk  main.lst  main.map  main.mem  main.rel  main.rst  main.sym
```

&emsp;&emsp;确保`main.hex`文件已经生成。这个文件是我们在仿真环境中运行程序的关键文件。

# 仿真测试

&emsp;&emsp;在进行仿真测试之前，需要确保`Edsim51`仿真软件已经正确安装，并且`main.hex`文件已经准备好。

&emsp;&emsp;启动`Edsim51`，你会看到一个包含多个功能模块的界面。这个软件提供了一个虚拟的硬件环境，可以模拟51单片机的运行状态。

## 配置仿真环境

### 配置系统时钟

&emsp;&emsp;在仿真软件中，找到系统时钟设置选项，将其设置为`11.0592MHz`。这是我们在代码中定义的晶振频率，仿真环境需要与代码中的设置保持一致。

### 设置模拟器频率

&emsp;&emsp;将模拟器的频率设置为最大值`5000`。虽然模拟器的运行速度比真实硬件要慢，但将频率设置为最大值可以加快仿真速度，方便我们观察程序的运行效果。

### 修改串口波特率

&emsp;&emsp;将串口的波特率设置为`19200`。这与我们在代码中初始化串口时设置的波特率一致，确保仿真环境能够正确接收和显示串口数据。

### 加载HEX文件

&emsp;&emsp;点击`Load`按钮，选择之前编译生成的`main.hex`文件。加载完成后，仿真软件会将程序加载到虚拟的单片机中。

![输入图片说明](https://raw.githubusercontent.com/chenxiahuaxu/stackedit-app-data-img/master/imgs/2025-06-18/kfzligVvxTVPhJ8g.png)

### 运行仿真

&emsp;&emsp;点击`Run`按钮，开始仿真。在仿真过程中，可以观察到以下现象：

- **串口数据输出**
  - 在`Edsim51`的串口RX区域，你会看到`Hello World!`字符串不断重复输出。这是因为我们在代码中使用了一个无限循环来发送字符串。

![输入图片说明](https://raw.githubusercontent.com/chenxiahuaxu/stackedit-app-data-img/master/imgs/2025-06-18/BYuRk0XddQ1DgM45.png)

- **系统时钟和波特率的作用**
  - 通过调整系统时钟频率和串口波特率，你可以观察到串口数据输出速度的变化。

# 总结

&emsp;&emsp;通过本教程，我们已经成功编写了一个简单的`Hello World`程序，并通过串口发送字符串。在仿真环境中验证了程序的功能。
