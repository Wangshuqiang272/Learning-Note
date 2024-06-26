# 嵌入式常用总线协议

## 总线概述

1. **总线定义**：计算机各功能部件之间传递信息的公共通信干线，可以理解为一根导线。通常分为地址总线、系统总线、数据总线。

2. **通信方式**：串行与并行

   1. 串行通信：通信时，采用一条传输线将数据一位一位的进行传输，适用于远距离传输，传输速度慢
   2. 并行通信：通信时，采用多条传输线一次性传输单个数据多个位的传输方式，传输速率块，但传输距离短，同时并行传输时各条数据线传输数据时容易产生干扰。

3. **通信方向**：双工（半双工、全双工）、单工

   1. 单工通信：信号只能在一个方向上传输，任何时候都不能改变传输方向。典型例子：收音机
   2. 双工通信：
      1. 半双工通信：通信双方可以相互发送数据，但是同一时间只能有一个方向的数据进行传输，典型案例：对讲机
      2. 全双工通信：通信双方可以相互发送数据，且同一时间双方都可以发送/接受数据。典型案例：串口。

4. **通信机制**：同步与异步

   1. 同步机制：同步模式一种阻塞模式，指一个进程执行请求后，若需要一段时间之后才能收到回复，那么这个进程会一直进行等待，直到收到回复。
   2. 异步机制：同步模式一种非阻塞模式，指一个进程执行请求后，若需要一段时间之后才能收到回复，那么这个进程会不会一直等待，会转头去执行接下来的任务。

   形象理解：A问B要数学选择题答案，A给B打电话，B此时正在忙，没有办法即使回复。

   ​		同步机制：A一直拿着电话等待，直到B完成工作后给A说明答案。

   ​		异步机制：A跟B说等你有时间将答案以短信形式告诉我，A先去做其他作业。



## UART串口总线

### 1.波特率概念：

​	每秒传输的码元(符号)的个数，而比特率的含义是每秒钟传输bit的个数。

​	由于串口传输的码元为高/低电平，因此，波特率等于比特率，从波特率中就可以得知每秒钟发送比特位的个数。

### 2.串口UART帧格式

​	1.UART串口空闲时，信号线中电平TTL为高电平。 

​	2.帧格式包含：起始位(1)  + 数据位(8)  + 校验位(可有可无)  + 停止位(1) 。

​	3.串口数据发送顺序遵守先发低位，后发高位的原则进行发送，即低位先行。



Q：**UART串口接收方如何判断数据发送端发送的是01还是0011呢？**

A：通过通信双方约定的波特率实现，波特率的确定进而确定了比特发送速率，进而确定了比特发送周期，当前平发生变化时开始计时，再次变化时截至，时间差值除以发送周期就可以得知发送了几个比特数据。

Q：**为什么串口每次只能发送1个字节呢？**

A：是为了降低通信偏差。设想，如果串口可以无限制字节发送，发送数据时，由于发送放与接收放各自计时，没有同步时钟措施，无法做到始终完全一致，只要双方之间有任何一点偏差，加之时间足够长，总有一个时间节点双方之间的通信偏差会差出一个比特的时间，此后，所有的数据都将乱套。而每次发送一个字节数据，保证了时间足够短，发送完成后，会将总线电平置高，再次发送时才会置低，此时通信双方又会重新计时，这种方式下，双方的通信偏差可以忽略不计。



## RS232协议

1.UART协议存在的问题：

​	1.只定义了数据的发送时序，并没有规定信号的电气特性。

​	2.不同的处理器默认的高低电平不同，导致各自的通信幅值不同，有的认为5V是高电平，有的认为3.3V是高电平。如此两种通信幅值的处理器接到一起会损坏电路。

​	3.抗干扰能力差。通常使用TTL信号表示0/1，数据传输过程中很容易出错。

​	4.由于抗干扰能力差，导致通信距离相对应的也很短，通常只有1两米左右。

2.接口标准：

RS232协议由1970年多个厂家共同制定的用于串口通讯的**标准**，该标准明确了通信时使用的连接器尺寸，规格，同时对于每根线的作用做了规定。最初规定了25个引脚，后续IBM将其简化为了9根，就是目前常说的DB9，通信中通常只用3根线。**TXD，RXD，GND**。



3.信号标准：

​	该标准规定，逻辑 "1" 为  **-5V ~  -15V**。逻辑 "0" 为  **+5V ~ +15V**。

​	目的在提升抗干扰能力，增加通信距离。，传输距离可达15m。

要采用232信号，需要在控制器外部增设一个232电平转换芯片，将处理器TTL信号转换为RS232信号或将RS232信号转换成TTL信号。



RS232协议在软件编程层面中与UART完全一致，它只在电气硬件层面做了一层封装，提升了电压赋值来抗干扰，同时增大传输距离。





## RS485协议

​	RS485协议采用差分信号进行数据传输。使用两根线进行通信。两线电压差值为 **+2V ~ +6V**表示逻辑 "1",电压差值为 **-2V ~ -6V**表示逻辑  "0"。以此来减少共模干扰对于通信的影响。通常来时，RS485通信距离可达1500m。电压幅值的降低也不容易损坏接口芯片。



1.接口：

​	1.RS485采用两线制通信，为总线拓扑结构，在同一个总线上可以挂载多个节点。

​	2.由于采用两线制，同时采用差分信号，因此同一时间只能保证单向数据传输，由此，发送的时候无法接收，接收时无法发送。为半双工通信协议。



2.程序应用层面：

​	1.RS485协议在硬件上不提供区分主从机的能力，区分主从机完全由软件程序逻辑控制，该逻辑可以参考IIC主从逻辑处理。

3.RS485和IIC的区别：

​	IIC协议在协议层面规定了主从机通信过程以及准则，而485协议没有规定，只规定了电气标准以及支持总线拓扑结构，至于这些器件之间的主从机通信处理逻辑没有规定。要实现485通信处理，可以参考IIC协议处理，是完全兼容的。



## IIC协议

### 1.概述

​	IIC总线由Philips公司推出，是一种串行的半双工协议总线协议。适用于近距离，低俗芯片之间通信。协议中规定使用两根线进行通信。一根时钟线（SCL），一根数据线（SDA）。时钟线用于信号同步，数据线用于传输数据。

​	IIC总线是一种多主机总线，在通信时，主机有权发起或者结束一次通信，从机只能被主机呼叫。IIC总线上多个主机同时启用总线时，应具备总线仲裁以及解决冲突的能力。每个连接到IIC总线上的器件都有一个唯一的地址（7bit）。总线中增加/删除器件都不会影响其他器件正常工作。



### 2.通信过程

1. 主机发起起始信号启用总线
2. 主机发送一个字节数据表明主机地址+后续数据方向
   1. 从机地址占据第1位至第七位，数据方向占据第0位。**0表示主机向从机发数据，1表示从机向主机发数据。**
3. 被寻址从机发送应答信号回复主机。
4. 发送器发送一个字节数据，随后接收器发送应答信号回复发送器
   1. **注意**，IIC协议中只有第一个字节数据能偶明确发送器是主机，其余的时刻都无法明确发送器/接收器是主机/从机，因为主机/从机既可以作为发送器也可以作为接收器。
   2. 另外，第二部完成后，就确定了后续的数据发送方向，无论后续发送多少字节数据，发送方向是不能改变的，想要改变发送方向就需要主机发送停止信号先释放总线，随后重新从第一步开始执行。
5. 循环第四步 
6. 通信完成后，主机发送停止信号释放总线。


### 3.通信信号分析

​	起始信号：**SCL时钟线为高电平时，SDA信号线由高电平变为低电平。**

​	停止信号：**SCL时钟线为低电平时，SDA信号线为低电平变为高电平。**

起始信号与停止信号只能由主机发出，起始信号发送后，总线处于占用状态，其他信号不可以占用总线。

​	通信时，每个字节为8位长度，传输比特位时，先发高位，后发低位（**高位先行**）。此处与串口不同，串口协议是低位先行。主机每发送一个字节数据后， 从机都需要发送一个应答位（**低电平**）来回复主机。  

​	IIC总线进行数据传输时，**时钟线SCL位低电平期间，SDL数据线信号允许发生变化， 时钟线为高电平期间，接收器从SDL信号线中接受一位数据，此时，SDL信号线中不允许更改信号电平。**

典型时序：

主机先向从机发送数据，然后从机向主机发送数据

```c
|  S  | 从机地址 |  0  |  A  |  数据  |  A  |  S  |  从机地址  |  1  |  A  |  数据  | A  |  P  |
```

​	主机发送起始信号表明要占据总线一段时间，紧接着发送从机地址+后续数据方向0，等待从机应答，从机应答后，主机开始一个字节一个字节的发送数据。从机每接收到一个字节发送一位应答位。当主机发送最后一个字节数据后，从机可以选择应答或者不应答。随后，主机重新发起起始信号以及从机地址字节，只不过此时改变第0位数据，使得数据传递方向发生改变。随后，从机开始发送数据，主机进行应答。从机数据发送完毕后，主机发送停止信号，依一次完整通信过程结束。 

​	**注意：**上述协议中，主机想要改变传输方向，此时主机并没有发送停止信号，而是直接发送起始信号，这样做的目的是防止主机中途发送起始信号后，总线上其他主机会抢占总线控制权，导致主机无法占用总线导致通信超时失败。


## SPI协议

