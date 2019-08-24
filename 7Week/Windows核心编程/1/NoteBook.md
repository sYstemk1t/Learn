# 程序错误

## 程序错误处理

Windows函数常用的返回值类型：

V O I D	该函数的运行不可能失败。Wi n d o w s函数的返回值类型很少是V O I D

B O O L 	如果函数运行失败，那么返回值是0，否则返回的是非0值。最好对返回值进行测试，以确定它是0还是非0。不要测试返回值是否为T R U E

H A N D L E 	如果函数运行失败，则返回值通常是N U L L，否则返回值为H A N D L E，用于标识你可以操作的一个对象。注意，有些函数会返回一个句柄值I N VALID_ HANDLE_VA L U E，它被定义为- 1。函数的Platform SDK文档将会清楚地说明该函数运行失败时返回的是N U L L还是I N VA L I D _ H A N D L E _ VA L I D

P V O I D 如果函数运行失败，则返回值是N U L L，否则返回P V O I D，以标识数据块的内存地址

L O N G / D W O R D 这是个难以处理的值。返回数量的函数通常返回 L O N G或D W O R D。如果由于某种
原因，函数无法对想要进行计数的对象进行计数，那么该函数通常返回 0或- 1（根据函数而定）。如果调用的函数返回了 L O N G / D W O R D，那么请认真阅读Platform SDK文档，以确保能正确检查潜在的错误



**WinError.h头文件中包含了Microsoft公司定义的错误代码的列表**





## 定义自己的错误代码

**错误代码是个32位的数字**

![](F:\Learn\7Week\Windows核心编程\1\Img\0.png)

