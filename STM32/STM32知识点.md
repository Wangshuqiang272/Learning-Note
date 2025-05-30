# STM32知识点基础篇梳理分析

## 1.中断篇

### 1.什么是中断

​	CPU在执行当前程序时，因应系统出现的紧急情况而暂停，转而去执行处理紧急事件的特殊程序。处理完毕后，CPU会自动返回到原先暂停的程序中继续执行。这种因外界原因导致程序执行被打断的情况称为中断

### 2.STM32中断触发过程

1. **中断源触发**：外部设备触发相应中断源，系统检测到中断源触发
2. **中断控制器进行处理分析**：根据初始化时配置的中断源的抢占优先级和响应优先级，决定当前是否处理该中断以及是否由需要暂时挂起的其他优先级中断。
3. **查找中断处理函数地址**：CPU根据中断号，在中断向量表中进行查找相对应的中断处理函数。中断向量表维护在启动文件中，放置在Flash中（0x080000 + 4）。4是栈指针地址。如果有bootloader程序，则需要偏移中断向量表的位置。
4. **保存上下文**：系统将当前任务的寄存器值压栈，保存现场。
5. **执行中断服务程序**：CPU转而执行中断服务程序，执行该程序必须快进快出。且不可以调用不可重入函数。
6. **恢复现场**：执行完中断之后，将之前压栈的现场弹栈，已回复之前保存的现场。
7. **返回主程序**：中断程序执行之后，弹栈完成后，继续执行主程序

### 3.中断优先级

​	STM32中，中断分为抢占优先级与响应优先级，这两点在使用时需要遵循。

1. 第一，如果两个中断的抢占优先级和响应优先级都是一样的话，则看哪个中断先发生就先执行。		
2. 高优先级的抢占优先级是可以打断正在进行的低抢占优先级中断的，而抢占优先级相同的中断，高优先级的响应优先级中断不可以打断低响应优先级的中断。
3. 如果两个中断的 **抢占优先级不同**，那么 **抢占优先级高的中断** 将会先被处理，不论它们的 **响应优先级** 是否相同，**响应优先级相同** 只会在抢占优先级相同的情况下才起作用

### 4.中断优先级管理 

​	STM32中断是通过配置寄存器NVIC寄存器进行管理	，其中，`ISER`寄存器是一个中断使能寄存器组，支持256个中断，F103只用了其中的前60位。	若要使能某个中断，只需要将中断对应的`ISER`位置1即可。`ICER`寄存器，是一个中断除能寄存器组，位数与`ISER`寄存器相同，但是功能作用与其相反，若想要清除某个中断的使能，只需要将`ICER`寄存器中断对应的位置1即可。注意：对于NVIC的这些寄存器而言，都是写1有效，写0无效。与平常寄存器中写1使能，写0失能不同。

​	寄存器`IP`：全称是：Interrupt Priority Registers，是一个中断优先级控制的寄存器组，这是一个数组，控制着M3内核的256个中断，数组类型为`uint8_t`,而每个可屏蔽中断占用的8bit并没有全部使用，而是 只用了高4位,这4位，又分为抢占优先级和子优先级。抢占优先级在前，子优先级在后。这里说明的子优先级就是上边提到的响应优先级。这两个优先级各占几个位又要根据SCB->AIRCR中的中断分组设置来决定。

​	这里简单介绍一下STM32的中断分组：STM32将中断分为5个组，组0~4。该分组的设置是由SCB->AIRCR寄存器的bit10~8来定义的。

| 组    | AIRCR[10：8] | bit[7：4]分配情况 | 分配结果             |      |      |
| ---- | ----------- | ------------ | ---------------- | ---- | ---- |
| 0    | 111         | 0：4          | 0 位抢占优先级，4位响应优先级 |      |      |
| 1    | 110         | 1：3          | 1 位抢占优先级，3位响应优先级 |      |      |
| 2    | 101         | 2：2          | 2 位抢占优先级，2位响应优先级 |      |      |
| 3    | 100         | 3：1          | 3 位抢占优先级，1位响应优先级 |      |      |
| 4    | 011         | 4：0          | 4 位抢占优先级，0位响应优先级 |      |      |

​	通过这个表，我们就可以清楚的看到组0~4对应的配置关系，例如组设置为3，那么此时
所有的60个中断，每个中断的中断优先寄存器的高四位中的最高3位是抢占优先级，低1位是
响应优先级。每个中断，你可以设置抢占优先级为0~7，响应优先级为1或0。抢占优先级的
级别高于响应优先级。而数值越小所代表的优先级就越高。



## 2.外部中断篇

### 1.什么是外部中断（EXTI）

​	外部中断是[单片机](https://baike.baidu.com/item/%E5%8D%95%E7%89%87%E6%9C%BA/102396?fromModule=lemma_inlink)实时地处理外部事件的一种内部机制。当某种外部事件发生时，单片机的[中断系统](https://baike.baidu.com/item/%E4%B8%AD%E6%96%AD%E7%B3%BB%E7%BB%9F/10480702?fromModule=lemma_inlink)将迫使[CPU](https://baike.baidu.com/item/CPU/120556?fromModule=lemma_inlink)暂停正在执行的[程序](https://baike.baidu.com/item/%E7%A8%8B%E5%BA%8F/13831935?fromModule=lemma_inlink)，转而去进行中断事件的处理；中断处理完毕后．又返回被中断的程序处，继续执行下去。

### 2.外部中断资源

​	STM32的每个IO都可以作为外部中断的中断输入口，然而，STM32F103的总共支持19个外部中断，其中，**线0-15**对应外部IO的输入中断，**线16**连接到PVD输出，**线17**连接到RTC闹钟事件，**线18**连接到USB唤醒事件。由上述资源说明可以观察出，STM32中断线数量远小于GPIO个数，因此需要进行映射设计。

​	如何将16个中断线与全部GPIO构建映射关系？我们知道，GPIO每一个port都有15个引脚端口，即0-15，因此，我们将每一个port上的引脚分别映射到编号为0-15的中断线中。即中断线0上连接着PA0，PB0，PC0...PG0，中断线1连接着PA1，PB1，PC1...PG1。由此，便实现了16根线控制所有的GPIO引脚。

### 3.外部中断配置方法

1. 使能复用时钟，配置GPIO为输入模式

2. 首先需要明确将GPIO与中断线的映射关系，调用函数接口绑定二者关系

   ```c
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);//将GPIOE.3与中断线3进行绑定
   ```

3. 配置外部中断EXTI寄存器结构体

   需要配置的选项有，中断线、中断模式以及中断触发源。

4. 配置NVIC中断优先级

   配置NVIC中断源，中断抢占优先级及响应优先级，使能中断

5. 编写外部中断线对应的中断处理函数

   1. 检测是否是正确的中断线触发中断
   2. 实现业务逻辑
   3. 清除中断标志位

## 3.时钟篇

​	单片机时钟是单片机工作的基础，它为单片机提供了必要的时序信号，确保单片机按照既定的节奏执行指令和操作。时钟信号可以看作是单片机的“心跳”，它决定了单片机的工作频率和执行速度。单片机各种外设都需要时钟的参与，如何配置系统的时钟，就需要了解STM32的时钟树配置。通过配置时钟树，我们可以初始化各个外设的时钟频率。

​	以下分析STM32F103控制板默认时钟配置。

​	STM32包含四种时钟源，高速外部时钟（HSE），高速内部时钟（HSI），低速内部时钟（LSI），低速外部时钟（LSE）。通常，高速时钟用来作为系统时钟的时钟源，低速内部时钟频率为40K，用作系统独立看门狗使用。低速外部时钟时钟频率大多为32.768K，通常用作RTC时钟使用。

​	题外话，通常实时时钟RTC采用的晶振频率为32.768KHZ，是因为32.768KHZ是**2的15次方**，只需要将该时钟源进行15次二分频，即可得到频率为1HZ的时钟频率，这对于以秒为单位的计时功能实现非常关键。同时，该频率的晶体振荡器具有较高的稳定性，能够在不同的环境条件下保持相对稳定的输出，从而为电路提供准确可靠的时钟信号。

### STM32默认时钟配置

​	STM32单片机在上电时，运行启动文件，初始阿堆栈指针，初始化中断向量表，响应复位中断程序，在复位中断程序中，进行系统初始化，随后跳转至main函数。

​	在上述熊初始化过程中，系统调用System_Init()函数，在该函数中设置系统时钟为72MHZ。

​	具体方式为设置RCC时钟控制器的**CFGR**以及**CR**寄存器。 

​	![](imageshack/qq.png)



​	STM32时钟采用高速外部时钟作为时钟源，硬件板中焊接8M外部晶振，直接传输值PLL锁相环进行倍频，这里可以看到，PLL锁相环有两种源，一种是由8M的内部高速时钟进行2分频，另一种就是直接由PLLXTYPE进行供给，STM32默认采用后者。时钟信号经过PLL锁相环9倍倍频，输出72M赫兹频率，并在SW处选择PLL锁相环时钟作为系统时钟输入，由此，系统时钟频率设置为72MHZ。

​	与此同时，PLL锁相环输出端经过USB时钟预分频器，1.5倍分频，得到48MHZ频率作为USB接口时钟频率。

​	系统时钟经过AHB预分频器不分频，直接供给SDIOCLK、FSMCCLK、核心存储器以及DMA总线，由此，上述说明的外设时钟频率皆为72MHZ。

​	经过APB1分频器2分频的时钟信号将直接供给与APB1外设总线，挂载至APB1总线上的外设，时钟频率为36MHZ，同时，由于APB1的分频系数为2，因此，定时器2-7的时钟频率为PCLK1时钟频率的2倍，即72MHZ。

​	经过APB2分频器的时钟频率将不分频，以72MHZ频率输出至PCLK2总线。由于APB2分频系数为1，则PCLK2总线时钟将直接输出至定时器1、定时器8。

​	经过APB2分频器的时钟频率，输出至ADC预分频器时为72MHZ，使用ADC模块时，需要配置ADC预分频系数，推荐使用6分频或8分频，ADCCLK不建议超过14MHZ。

​	综上所述，定时器1-8的时钟频率都是72MHZ。

## 4.定时器篇 

### 1.定时器分类

​	STM32F103共有8个定时器资源，共分为三种定时器，基本定时器（TIME6、TIME7），通用定时器（TIME2-TIME5），以及高级定时器（TIME1、TIME8）。

- 基本定时器的功能相对简单，通常用于 **延时操作** 和 **周期性中断**。
- 通用定时器比基本定时器功能更加丰富，支持 **输入捕获**、**输出比较**、**PWM 生成**、**时间测量**等功能，适合用来处理更复杂的任务。
- 高级定时器具有更多的控制功能，适合复杂的 **电机控制**、**高精度时间控制** 等任务。它们不仅支持常规的功能，还支持 **死区时间控制**、**互补 PWM 输出**、**高速脉冲宽度调制**等高级特性。


### 2.通用定时器设置时间间隔配置

1. 使能通用定时器时钟
2. 配置定时器结构体参数
   1. 配置自动重装载寄存器周期的值
   2. 配置时钟频率的预分频值
   3. 配置时钟分割系数，输入捕获功能常用
   4. 设置定时器计数模式
   5. 配置定时器中断类型并使能定时器

​       说明:定时器触发周期是通过上述1，2参数配置而成。我们在时钟篇提到过，定时器的时钟周期为72M，经过定时器分频后得到定时器计时频率，此时剋计算出定时器计时周期，将计时周期乘以自动重装载寄存器值即可得到定时器溢出中断的周期。

​	举例如下：想要配置500ms的定时器，自动重装载寄存器数值以及预分频值？

​	500ms = （预分频系数/72M） * 自动重装载寄存器数值

​	定时器demo中，自动重装载寄存器数值为4999，预分频值为7199。

### 3.通用定时器框图理解

![](imageshack/123.png)

​	针对通用定时器，将其整体划分为5部分，其中，第一部分为时钟发生器，第二部分为时基单元，第三部分为输入捕获部分，第四部分为捕获/比较寄存器，第五部分为输出比较部分。

​	**第一部分：**该部分为时钟发生器，通过时钟篇我们了解到，定时器的时钟源由四种，内部高速，外部高速，外部高速，外部低速，最终产生**TIMXCLK**时钟信号输出至第一部分中，作为时钟源一种来源。当然还有其他几种来源，我们暂不分析。

​	**第二部分：**第二部分包含PSC预分频器、自动重装载寄存器和CNT计数器。来自第一部分的时钟源经过预分频器后分频得到时钟信号CK_CNT，使得CNT计数器加1或者减1，此时在自动重装载寄存器中有一个预先设定的装载值，当计数器的值达到装载值的时候，会产生溢出事件，然后触发中断。

​	**第三部分：**该部分为输入捕获部分，主要用来捕获外部信号，如脉冲宽度等。TIMx_CH1——TIMx_CH4 这四个通道，在芯片中都有对应的引脚，当脉冲从通道口进入时，经过输入滤波器（抗干扰的作用），然后经过边沿检测器检测到上升沿（下降沿），经过分频器，输入到第四部分中的捕获寄存器中，然后捕获寄存器记录此刻CNT计数器的值，当下一次下降沿（上升沿）过来时，也记录下CNT计数器的值，这样就可以计算出输入脉冲的宽度。

​	**第五部分**：该部分为输出比较部分，通常用来输出PWM波等。由框图可知，同一个通道输入捕获与输出比较不可以同时进行。在比较寄存器中预先设定一个值，计数器从初始值到装载值之间计数时，当正好等于比较寄存器中的预设值时，控制TIMx_CH1——TIMx_CH4通道输出低电平或者高电平，这样随着计数器不断的计数，就可以获得一个脉冲，通过调整预设值，就可以调整脉冲宽度，调整初始值和装载值就可以调整周期。

​	定时器寄存器中有两个捕获/比较模式寄存器，分别为**TIMx_CCMR1**与**TIMx_CCMR2**，每个捕获/比较模式寄存器可以控制两个通道的捕获/比较配置，因此，两个寄存器共可以配置定时器的四个通道。



## 5.GPIO篇

​	STM32单片机中，GPIO模式共有以下八种模式：

- GPIO_Mode_AIN **模拟输入**

- GPIO_Mode_IN_FLOATING **浮空输入**

- GPIO_Mode_IPD **下拉输入**

- GPIO_Mode_IPU **上拉输入**

- GPIO_Mode_Out_OD **开漏输出**

- GPIO_Mode_Out_PP **推挽输出**

- GPIO_Mode_AF_OD **复用开漏输出**

- GPIO_Mode_AF_PP **复用推挽输出**


  STM32中每一个GPIO端口都有如下的结构：

  ![](imageshack/111.png)

    1. **保护二极管作用**：IO引脚上下两边两个二极管用于防止引脚外部过高、过低的电压输入。当引脚电压高于VDD时，上方的二极管导通；当引脚电压低于VSS时，下方的二极管导通，防止不正常电压引入芯片导致芯片烧毁。
    2. TTL肖特基触发器：信号经过触发器后，模拟信号转化为0和1的数字信号。



### 1.输入模式：

**模拟输入**：模拟输入模式下，I/O端口的模拟信号（电压信号，而非电平信号）直接模拟输入到片上外设模块。信号流向如下图所示：

![](imageshack/122.jpg)

**浮空输入：**浮空输入模式下，I/O端口的电平信号直接进入输入数据寄存器。也就是说，I/O的电平状态是不确定的，完全由外部输入决定；如果在该引脚悬空（在无信号输入）的情况下，读取该端口的电平是不确定的，信号流向如下图所示：

![](imageshack/121.jpg)

**上拉输入：**上拉输入模式下，I/O端口的电平信号直接进入输入数据寄存器。但是在I/O端口悬空（在无信号输入）的情况下，输入端的电平可以保持在高电平；并且在I/O端口输入为低电平的时候，输入端的电平也还是低电平。

![](imageshack/123.jpg)

**下拉输入：**下拉输入模式下，I/O端口的电平信号直接进入输入数据寄存器。但是在I/O端口悬空（在无信号输入）的情况下，输入端的电平可以保持在低电平；并且在I/O端口输入为高电平的时候，输入端的电平也还是高电平。

![](imageshack/124.jpg)

### 2.输出模式：	

**开漏输出**：开漏输出模式下，通过设置位设置/清除寄存器或者输出数据寄存器的值，途经N-MOS管，最终输出到I/O端口。这里要注意N-MOS管，当设置输出的值为高电平的时候，N-MOS管处于关闭状态，此时I/O端口的电平就不会由输出的高低电平决定，**而是由I/O端口外部的上拉或者下拉决定**；当设置输出的值为低电平的时候，N-MOS管处于开启状态，此时I/O端口的电平就是低电平。同时，I/O端口的电平也可以通过输入电路进行读取；注意，I/O端口的电平不一定是输出的电平。
![](imageshack/121.png)

**推挽输出：**

​	推挽输出模式下，通过设置位设置/清除寄存器或者输出数据寄存器的值，途经P-MOS管和N-MOS管，最终输出到I/O端口。这里要注意P-MOS管和N-MOS管，当设置输出的值为高电平的时候，P-MOS管处于开启状态，N-MOS管处于关闭状态，此时I/O端口的电平就由P-MOS管决定：高电平；当设置输出的值为低电平的时候，P-MOS管处于关闭状态，N-MOS管处于开启状态，此时I/O端口的电平就由N-MOS管决定：低电平。同时，I/O端口的电平也可以通过输入电路进行读取；注意，此时I/O端口的电平一定是输出的电平。
![](imageshack/122.png)

​	输出模式中，主要由开漏输与推挽输出，另外还有复用推挽和复用开漏模式，带有复用与没带有开漏的区别主要是：在**推挽以及开漏模式**中，IO端口的输出电平主要由CPU直接写输出数据寄存器，随后经过输出驱动器后给到IO端口。而在**复用推挽以及复用开漏模式**中，高低电平的来源是通过片上外设模块的复用功能传输到输出驱动器模块进而驱动IO端口。

​	

**开漏输出与推挽输出的区别：**

- 开漏输出：只可以输出强低电平，高电平得靠外部电阻拉高。输出端相当于三极管的集电极。适合于做电流型的驱动，其吸收电流的能力相对强(一般20ma以内)；
- 推挽输出:可以输出强高、低电平，连接数字器件。



### 3.GPIO速率：

STM32GPIO配置时，通常需要我们设置GPIO速率，以下我们需要对GPIO速率做出一些分析：

​	在STM32微控制器中，**GPIO速率**（或称为**GPIO时钟速度**、**GPIO频率**）是指通过STM32的GPIO引脚传输数据的速度。它对GPIO端口的**数据输入和输出速率**有直接影响，决定了信号传输的速度和响应时间。

​	首先，GPIO速率影响数据在GPIO引脚上的传输速率。当我们通过GPIO发送数据（例如输出高低电平），这个速率决定了数据能够传输的频率。例如，如果GPIO速率较低，数据传输的速度就会受到限制，可能导致数据更新的延迟或不稳定。在STM32中，GPIO经常用作与外部设备（如传感器、显示器、LED、按键等）的接口。如果外部设备对输入信号的频率有要求，GPIO速率就会影响设备与MCU的通信效率。对于需要高频率操作的外设（例如SPI、I2C、PWM信号等），GPIO速率会影响信号的稳定性和精确度。

​	同样的，GPIO速速率对于输入信号速率也有影响。对于一些高频输入信号，如脉冲计数、捕获输入、PWM信号采样等，GPIO的输入速率决定了它能够多快地响应输入信号的变化。如果GPIO的速率较低，可能会导致采样的时间窗口过长，从而错过高频信号的某些变化。

​	但是，并不是说信号速率越高越好，**1.高频率的GPIO操作通常会消耗更多的功率**。因此，在功耗要求较高的应用中，可能会考虑降低GPIO速率来节省能源。其次，**2.较高的GPIO速率有时可能会引入噪声和信号完整性问题**。特别是在高频操作下，GPIO引脚可能更容易受到电磁干扰，因此需要使用适当的设计方法（如滤波、屏蔽等）来保证信号的稳定性。



## 6.PWM篇

PWM全程脉冲宽度调制，是一种控制占空比进而控制平均电压/功率的一种技术。占空比越高，输出信号的平均电压/功率就越高，占空比越低，输出信号的平均电压/功率就越低。

​    **占空比：**表示一个周期中高电平持续时间占整个周期的笔比例

​    **周期:** 一个脉冲信号的时间。

​    **脉宽时间：**高电平的时间。

​    例子： 周期时间位10ms的脉冲信号，脉宽时间位8ms，则低电平时间就是2ms，占空比为80%

​    STM32单片机输出PWM方波需要配置的步骤，以下以一个呼吸灯的效果作为例子：

### 1.配置GPIO为复用推挽输出模式

​    为什么需要配置为复用推挽输出模式，可以在GPIO篇找到答案。大体上就是需要使得GPIO端口输出的信号不经过CPU至输出寄存器，而是从片上外设输出到GPIO端口中。由此达到GPIO端口的输出电压由PWM输出信号控制。另外，需要注意的是，PWM方波输出的GPIO端口有定时器的通道对应的GPIO口控制。在本例子来说，如果想要控制LED灯。需要将PWM信号输出至LED灯的GPIO中。由此，可能需要定时器的通道做复用。

### 2.配置定时器

​    配置定时器时，需要明确控制的LED的GPIO为哪一个，并查看数据手册确认哪个定时器的哪个通道可以输出信号到LED的GPIO，必要时可以做复用功能重映射。

​    明确定时器以及通道后，就需要确定PWM输出信号的周期，本例中，信号周期为80Khz的信号频率。

​    根据该周期，需要设置定时器的自动重装载寄存器数值以及预分频系数。

​    由定时器框图以及时钟配置可以得知，定时器的时钟频率首先需要经过预分频器进行降频，进行降频之后的时钟频率才是定时器的时钟频率，分频器倍数由**TIM_Prescaler**成员变量决定，分频之后即为定时器的计数频率，随后需要设置自动重装载数值，每次计数周期到达时计数器值加一，当计数器值达到自动重装载值时，为一个信号周期。

### 3.配置定时器输出比较模式

​	配置PWM需要配置定时器输出比较结构体，配置该寄存器的作用是确认PWM输出模式。可以理解为设定阈值，当定时器计数值小于该值时，输出低电平，当大于该值时，输出高电平。由此，控制该阈值即可控制占空比。

​	在配置输出比较模式时，支持两种模式，模式1与模式2

- 模式1：  向上计数时，CNT < CCR时通道为有效电平，CNT > CCR时，通道为无效电平

  ​		向下计数时，CNT > CCR时通道为无效电平，CNT < CCR时，通道为有效电平

- 模式2：  向上计数时，CNT < CCR时通道为无效电平，CNT > CCR时，通道为有效电平

  ​		向下计数时，CNT > CCR时通道为有效电平，CNT < CCR时，通道为无效电平

  上述说明中的**有效/无效**电平，说的不是高电平/低电平，具体输出的是高电平还是低电平需要根据**TIMx_CCER**寄存器的**CCXP**位来确定。该位表示输入/捕获1输出极性。在通道配置为输出模式下，该位0时表示高电平有效，该位为1表示低电平有效。

## 7.输入捕获篇

## 8.RTC实时时钟篇

## 9.待机唤醒篇

## 10.ADC篇

## 11.DAC篇

## 12.DMA篇

## 13.IIC篇

## 14.SPI篇

## 15.CAN总线篇

## 16.红外编解码篇



# STM32知识点进阶篇

## 1.FATFS文件系统篇

## 2.IAP程序升级篇

## 3.SD卡篇

