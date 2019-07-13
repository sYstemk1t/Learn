首先确定是PE文件，然后使用PE指纹找到DOS Stub

![](F:\Learn\4Week\Window Pe\3\img\21.png)



然后继续去找PE头，向下数20个字节



![](F:\Learn\4Week\Window Pe\3\img\22.png)



然后继续找，然后继续向下找224个字节，是扩展PE头

![](F:\Learn\4Week\Window Pe\3\img\23.png)



计算找一下PE有多大

![](F:\Learn\4Week\Window Pe\3\img\24.png)



中间继续找成员

每个节占40字节

![](F:\Learn\4Week\Window Pe\3\img\25.png)



可以看到有5个节

![](F:\Learn\4Week\Window Pe\3\img\26.png)

然后去0400的地方找

从0400-0DF0的地方是第一个rdata的节数据

![](F:\Learn\4Week\Window Pe\3\img\27.png)



