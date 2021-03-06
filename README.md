
## LIB123简介
```
https://github.com/whysoft/LIB123

LIB123
是一个可重用C++库
面向应用开发。
没有使用C++11特有的部分，以便尽量兼容旧的编译器。
全部由C++源码实现。表现为.h文件的源代码。

用于苹果macOS/windowsXP/win7/win10以及x86系Linux，ARM系列嵌入式linux。

目标可执行文件只依赖标准C/C++库，没有其它依赖。

不适用于驱动开发。在用于驱动开发时需要裁剪。

其中
1.h是主体部分
2.h是对1.h的编译开关切换和常用宏
以上就是123当中的12的含义
3代表了用户自己编写的部分

1.h内容是用ANSI ASCII的文本文件，
1_u8.h内容与1.h内容本质一样，只是转成了utf8，
原因是构造LL（1）语法分析器时，采用了自展结构算法。内部采用的虚拟机层的符号表为了编程时好理解和记忆所以用了汉字符号，
这些内容纯属内部运行需要不会对外暴露，但是IOS下编译时会对不是UTF8编码的汉字字符串进行警告，所以产生了1_u8.h
这些过程全是内部运算过程。与对外接口无关，也与LL（1）的处理能力以及能处理的语言的编码无关。

edition4是功能最小版本，也是兼容性最好的版本。
其它的edition1~3中，有的使用了windows特有的ADO读写数据库的功能，从而造成无法移植。
有的版本内置了一个LL(1)语法分析器，从而造成代码庞大。
可以根据特定需求选用。

开发者可以在vs ide中编写和调试，几乎没有移植工作，
只需要在目标编译器中编译即可完成。
这样的设计利用了vs ide的调试功能，降低了对开发者的技术要求。
```


## 主要模块
```
相关的基础数据结构
内存式微型数据表穦SDB
文件打包
线程
锁与互斥
消息队列与处理
bmp/framebuffer图片处理
TCP通信、串口通信的流式通信的数据处理
http请求的实现
内置一个基本符合rfc1945标准的web server实现
一个LL(1)文法的实现
```


## 适用场景
```
设备控制
自助设备
物联网
办公数据处理
```


## 使用方法
```
根据各例子程序，先在vc2003或更高版本中编写和调试
再在目标系统特定的编译环境下编译即可使用。
```

