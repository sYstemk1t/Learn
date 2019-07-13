# 目标文件

## 目标文件格式

现在PC平台流行的可执行文件主要是Windows下的PE和Linux下的ELF，它们都是COFF格式的变种。

目标文件就是源代码编译后但是未进行了解的那些中间文件（Windows下的.obj，Linux下的.o）。



动态链接库（Windows下的.dll和linux下的.so）按照可执行文件格式存储

静态链接库（Windows下的.lib和Linux下的.a）按照可执行文件格式存储



在Windows下按照PE-COFF格式存储，Linux按照ELF格式存储。



静态链接库稍有不同，它是把很多目标文件捆绑在一个形成一个文件，再加上一些索引。

![](F:\Learn\4Week\misc\3\img\0.png)



## 目标文件是什么样的



目标文件中包含汇编后的机器指令代码、数据，还包括链接是所需要的一些信息，符号表、调试信息等。

一般目标文件将这些信息按不同的属性，以节的形式存储，有时候也称为段



程序源代码编译后的机器指令通常放在代码段，常见代码段名称有“.code”、“.text”，全局变量和局部静态变量数据通常放在数据段，数据段的名字一般叫“.data”。

```c
#include <stdio.h>
int init = 10;	//数据段(data)
int ubinit ；	//bss段，bss段是为未初始化的全局和静态变量预留位置
void fun(int i)
{
    printf("%d\r\n",i);	//代码段(text)
}

int main()
{
    static int static_var = 10;		//数据段(data)
    static int static_var2 = 20;
    int a = 1;
    int b;						//数据段(data)
    
    fun1(a);				//代码段(code、text)
    return 0;
}
```

![](F:\Learn\4Week\misc\3\img\1.png)



ELF文件的开头是一个“文件头”，它描述了整个文件的属性，包括文件是否可执行、静态链接还是动态链接及入口地址、目标硬件、目标系统等信息，文件头还包括一个段表，段表是一个描述文件中各个段的数组。



**c语言编译后执行语句都翻译成机器代码，存在.text段**

**已初始化的全局变量和静态变量都存在.data段**

**未初始化的全局变量和局部变量存在bbs段，bs段只是为未初始化的全局变量和静态全局变量预留位置**

**未初始化的变量都是0**



**程序源代码被编译以后主要分为两种段：程序指令和程序数据。代码段属于程序指令，数据段和.bss俗语程序数据**





## 挖掘SimpeSection.o







```c

#include <stdio.h>
int global_init_var = 84;
int global_ubinit_var;
void fun(int i)
{
        printf("%d\n",i);
}

int main()
{
        static int static_car = 85;
        static int static_var2;
        int a = 1;
        int b;
        fun(static_car + static_var2 + a + b);
        return a;
}

```



![](F:\Learn\4Week\misc\3\img\3.png)



除了最基本的代码段、数据段和BSS段以外，还有三个段分别是**只读数据段(.rodata)、注释信息段(.comment)、对战提示段(.note.GNU-stack)**



![](F:\Learn\4Week\misc\3\img\4.png)



hex表示长度和的十六进制



### 代码段

查看各个数据段的内容，使用objdujmp -s 参数可以将段的内容以十六进制的方式打印出来,-d参数可以将所有包含指令的段反汇编

```shell
objdump -s -d main.o
```

![](F:\Learn\4Week\misc\3\img\5.png)



.text的数据以十六进制方式打印出来的内容，总共0x51个字节，最左面的一列是偏移量，中间的4列是十六进制内容，最右面的一列是ascll码格式，对照反汇编的结果。





### 数据段和只读内容段

.data段中存放的是初始化过后的全局变量和局部静态变量，因为我们使用两个int型存放，所以占用的字节数是8



.rodata段存放的是只读数据，一般是程序里的只读数据，比如c语言中的const修饰符



![](F:\Learn\4Week\misc\3\img\6.png)

data段中存放的是已初始化的全局变量或者局部静态变量，把data段中的数据进行拆分

0x54、0x00、0x00、0x00

![](F:\Learn\4Week\misc\3\img\7.png)

然后可以看到是我们进行初始化的84



**大端模式和小端模式的使用场景不懂...**

### BSS段

.bss段存放是未初始化的全局变量和静态局部变量

```c
static int static_int_a = 0;
static int static_int_b = 1;
```

如书上所说，初始化的值为0，但是编译器并不认为0是一个初始化的值，因为前面说过，即使不初始化，static_int_a这个变量的存放在bss段中，也会被认为值是0，所以static_int_a这个变量存放的段应该是bss段。



### 其他段

![](F:\Learn\4Week\misc\3\img\8.png)



**我们在全局变量或函数前面加上“__attribute((section(“name”)))”属性就可以把相对应的变量或者函数放到以“name”作为段名的段中**







## ELF文件结构描述

ELF目标文件格式的最前不是ELF文件头，它描述整个问价你的基本属性，比如ELF文件版本、目标机器型号、程序入口地址等。



紧接着是ELF文件各个段，其中ELF文件中与段有关的重要结构就是段表，该表描述了ELF文件包含的所有段的信息，比如每个段的段名，长度，在文件中的偏移，读写权限以及段的其他属性。



![](F:\Learn\4Week\misc\3\img\9.png)



```c
typedef struct
{
    unsigned char e_ident[16];	//class、data、Vaersion、Os、ABI
    Elf32_Half e_type;			//ELF文件类型
    Elf32_Half e_machine;		//ELF文件的CPU平台属性
    Elf32_Wold e_version;		//ELF版本号
    Elf32_Addr e_entry;			//入口地址，规定ELF程序的入口虚拟地址
    Elf32_Off e_phoff;			//暂时不关心
    Elf32_Off e_shoff;			//段表在文件中的偏移，上面的例子是这个值是276
    Elf32_Word e_flags;			//ELF标志位，用来标志一些ELF文件平台相关的属性	
    Elf32_Half e_ehsize;		//ELF文件头大小，这个例子中为52
    Elf32_Half e_phentsize;		//这个不关心
    Elf32_Half e_phnum;			//这个不关心
    Elf32_Half e_shentt_zize;	//描述段表的大小，这个一般等于sizeof(Elf32_Shdr)
    Elf32_Half e_shnum;			//段表描述符数量
    Elf32_Half e_shstrndx;		//段表字符所在的段在段表中的下标。
}Elf32_Ehdr;
```

![](F:\Learn\4Week\misc\3\img\10.png)

![](F:\Learn\4Week\misc\3\img\11.png)



ELF魔数，前面16个字节被ELF标准规定用来标识ELF文件的平台属性。

![](F:\Learn\4Week\misc\3\img\12.png)





最开始的4个字节是所有ELF文件都必须相同的标识码，分别是0x7f、0x45、0x4c、0x46，第一个字节对应ASCII字符里面的DEL控制符，后面三个字节刚好是ELF这三个字母的ASCII码。

![](F:\Learn\4Week\misc\3\img\13.png)



这里设计一个Windows Pe的，加载一个exe文件查看

![](F:\Learn\4Week\misc\3\img\14.png)

Pe文件中最开始的两个字节为0x4d、0x5a，即ASCII码中的MZ，这种魔数用来确定文件的类型，操作系统在加载可执行文件的时候会确定魔数是否正确，如果不正确会被拒绝



第五个字节是用来标识ELF的文件类的，0x01是表示32位，0x02表示的是64位



第六个字节是字节序，规定该ELF文件是大端还是小端存放



第七个字节规定ELF的主版本号，一般是1，因为ELF标准从1.2以后没有更新了。



![](F:\Learn\4Week\misc\3\img\15.png)

这个是64位下的编译后的.o文件查看出来的，可以看到和32位有很大的区别。



### 文件类型

e_type成员表示ELF文件类型，三种文件类型分别是：

ET_REL = 1	//可重定位文件,一般为.0文件

ET_EXEC = 2	//可执行文件

ET_DYN = 3	//可共享文件，一般为.so文件



![](F:\Learn\4Week\misc\3\img\16.png)



### 段表

ELF文件有各种各样的端，这个标段就是保存这些端的基本属性的结构。

标段描述了ELF各个段的信息，比如每个段的段名、段的长度、在文件中的偏移、读写权限及段的其他属性。

ELF文件的段结构就是由标段决定的，编译器、连接器和装在其都是依靠段表来定位和访问各个段的属性的。



段表在ELF文件中的位置是由ELF文件头的“e_shoff”成员决定的

```c
typedef struct
{
  Elf32_Word	sh_name;		//段名是个字符串，它位于一个叫做“.shstrtab”的字符串表，sh_name是段名字符串在“.shstrtab”的偏移
  Elf32_Word	sh_type;		//段的类型
  Elf32_Word	sh_flags;		//段的标志位
  Elf32_Addr	sh_addr;		//如果该段可以被加载，则sh_addr为该段加载后在进程地址空间中的虚拟地址，否则为0
  Elf32_Off	sh_offset;			//如果该段存在于文件中，则表示该段在文件中的偏移
  Elf32_Word	sh_size;		//段的长度	
  Elf32_Word	sh_link;		//
  Elf32_Word	sh_info;		//和上一个一起是段的链接信息
  Elf32_Word	sh_addralign;	//对段地址对齐要求
  Elf32_Word	sh_entsize;		//段的大小
} Elf32_Shdr;

```

![](F:\Learn\4Week\misc\3\img\17.png)

**段的名字只是在表一和链接过程中有意义，但它并不能真正的表示段的类型**



### 重定位表





.rel.text段，它的类型为SHT_REl，也就是说它是一个重定位表





### 字符串表

![](F:\Learn\4Week\misc\3\img\18.png)



一般字符串在ELF文件中以段的方式保存，常见的段由“.strtab”或“.shstrtab”。这两个字符串分别为字符串表和段表字符串表。







## 链接的接口--符号

