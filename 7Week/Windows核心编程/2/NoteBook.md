# Unicode

## 字符集

在双字符集中，字符串中的每个字符可以包含一个字节或者两个字节。比如中文一个字占两个字节





## 单字节与双字节字符集

在双字节字符集中，字符串中的每个字符可以包含一个字节或包含两个字节。





## 宽字节字符集

U n i c o d e提供了一种简单而又一致的表示字符串的方法。 U n i c o d e字符串中的所有字符都是1 6位的（两个字节）。它没有专门的字节来指明下一个字节是属于同一个字符的组成部分，还是一个新字符。

![](F:\Learn\7Week\Windows核心编程\2\Img\1.png)





## Windows中Unicode函数和Ansi函数

CreatWindowEx：接受Unicode字符串

CreatWindowEx：接受Ansi字符串

