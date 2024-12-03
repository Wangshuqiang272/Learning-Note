#                            Linux嵌入式C语言学习笔记



## 一、C语言编程时需要注意的问题

### 					1.头文件必须要正确包含

​				使用函数时，必须考虑该函数的声明所在的头文件是否被包含进程序中，头文件参考手册为准

### 2.以函数为单位进行程序编写

​				每个功能需要独立封装为一个单独的函数，供其他程序进行调用。

### 3.声明部分+实现部分

### 4.return 0

### 5.多用空格以及空行

​				空格和空行可以使程序变得更加的美观，方便查看

### 6.添加注释

   			  	1. 单独行注释采用`//`形式
   			  	2. 多行注释采用`/*  */`形式，或者`#if 0    #endif`形式

### 7.考虑资源合理性

​			编写程序时，必须时刻注意四项原则

   - 防止写越界
   - 防止内存泄漏
   - 谁打开谁关闭
   - 谁申请谁释放

## (二)、数据类型、运算符、表达式

### 1.数据转换问题

​	数据强制转换之间涉及到失真和精度加强的问题

​	当大精度范围向小精度范围进行转换时，会出现数据失真的情况

​	当小精度范围向大精度范围进行转换时，会出现数据精确增加，数据不会出现失真的情况      

### 2.float类型数据

​	float类型数据不是一个精确的数值，是一个较模糊的精度概念

```C
float a = 0.01;
if (a >= 0)
    return 0;.
```

**以上程序为错误程序**，float是一个非精确的数据类型，无法与精确的整型值进行对比。

正确写法

```c
#include <math.h>
if (fabs(a-0) <= 1e-6)
    return 0;
```



### 3.不同形式的`0`值

- <kbd>0</kbd>
- <kbd>'0'</kbd>
- <kbd>"0"</kbd>
- <kbd>\0</kbd>

### 4.数据类型与后续代码使用的输入输出要相匹配

​		例子：小明写了一个变量用`unsigned int`进行定义，后续过程中，为了调试代码，小明用`printf("%d",&n);`进行输出

​		错误原因：变量定义时<kbd>unsigned int</kbd>,表示无符号整型，而后续使用<kbd>%d</kbd>来输出，<kbd>%d</kbd>表示将当前某一个值按照有符号十进制数进行输出，与定义有出入，会造成数据的失真

## (二)、变量与常量

1. 常量：在程序执行过程中值不会发生变化的量

   分类：整型常量，字符常量，实型常量，字符串常量，标识常量

   ​			整型常量：123

   ​			实型常量：3.1415926

   ​			字符常量：由单引号引起来的单个字符或转义字符，`'a'`  `'\n'`   `\t`

   ​								`'\012'`表示\后接的是8进制数据

   ​								`\x7A`	表示\后接的是16进制数据

   ​			字符串常量：有双引号引起来的一个或多个字符组成的序列

   ​									`""`表示空串，空串也会占空间，每一个字符串后边都会跟一个`\0`作为结束符，故，空串也会有`\0`,也占空间，									双引号不占空间

   ​			标识常量：#define PI  3.1415926        `PI 宏名`     `3.1415926  宏体`  写程序时可以使用宏名，等到预编译阶段，宏明会被宏								体全部替换掉。预编译时只是纯机械的将程序中的宏名替换成宏体，不会进行语法检查。因此原则上要将宏体用括								号括起来，使其成为一个完整的个体。

   ​								示例：

   ```c
   #define Max(a,b) a > b ? a : b
   int main()
   {
       int i = 5,j = 3;
   	printf("%d\n",Max(i,j));
       return 0;
   }
   ```

   预编译结果

   ```C
   #define Max(a,b) a > b ? a : b
   int main()
   {
       int i = 5,j = 3;
   	printf("%d\n",i > j ? i : j);
       return 0;
   }
   ```

   

2. 变量：用来保存一些内容，并且在程序执行过程中值随时会更改的量

   ​	定义：`[存储类型] 数据类型 标识符 = 值`

   ​				标识符定义应做到见名知意，不要写a,b,result这种单词，谁TM知道啥意思

   ​				数据类型：基本数据类型 + 构造类型

    				存储类型：auto，static，register，extern(说明型)

   ​				auto：默认，自动分配空间，自动回收空间

   ​				register：建议编译器将定义的该变量（十分常用）放到CPU寄存器中，只是建议，但是放不放还是有CPU决定，毕竟资源								极度缺少。

   ​				static：静态型，自动初始化为0或空值，，并且修饰的变量具有继承性

   ​				extern：说明型关键字，意味着不能改变修饰变量的值，只是告诉编译器我调用的变量定义不在该源文件中，去别的源文件中找，找到之后 拿来吧你  ，绝不能更改变量类型和变量值否则会出现重复定义。例 extern int i

   ​	变量的生命周期和作用范围

   ​			变量的作用范围永远是内部的屏蔽外部的，举例：

   ```C
   #include <stdio.h>
   int a = 100;
   int main(void)
   {
       
       int a = 10;
       printf("%d\n",a);//输出的值为10，既printf看到的变量为局部变量i，屏蔽了全局变量i
       return 0; 
   }
   ```

   ​			全局变量缺陷，允许多个程序进行读写，一旦顺序处理不当会造成程序无法达到预期的目标






























