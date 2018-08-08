###UNIX文件系统 ---???
###mount命令 ---???
###dd命令 ---???
创建特定大小的大文件最简单的方法就是利用dd命令
`dd if=/dev/zero of=junk.data bs=1M count=1`
if代表输入文件，of代表输出文件，bs代表以字节为单位的块大小，count代表需要被赋值的块数。

/dev/zero是一个字符设备，它会不断返回0值字节。

####comm命令
可用于两个文件之间的比较。