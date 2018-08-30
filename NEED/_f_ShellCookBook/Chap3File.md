###UNIX文件系统 ---???
###mount命令 ---???
###dd命令 ---???
创建特定大小的大文件最简单的方法就是利用dd命令
`dd if=/dev/zero of=junk.data bs=1M count=1`
if代表输入文件，of代表输出文件，bs代表以字节为单位的块大小，count代表需要被赋值的块数。

/dev/zero是一个字符设备，它会不断返回0值字节。

####comm命令
可用于两个文件之间的比较。

####AWK---???
####查找并删除重复文件
awk中，外部命令的输出可以用下面的方法读取`"cmd" | getline` 随后可以获取命令的输出，在$1,$2,...$n中获取命令输出中的每一列。

####创建多级目录树
创建多级目录，忽略所有已存在的目录，同时创建缺失的部分。
```
mkdir -p /home/slynux/test/hello/child
```

####文件权限，所有权和粘滞位
chmod u=rwx g=rw o=r filename
 - u=指定用户权限
 - g=指定用户组权限
 - o=指定其他实体权限
chmod用+添加权限，用-删除权限

####更改所有权
chown user.group filename

####设置粘滞位
通过设置粘滞位，使得只有目录的所有者才能够删除目录中的文件，及时用户组和其他用户拥有足够的权限也不能执行该删除操作
`chmod a+t diretory_name`

####以递归的方式修改权限
chomod +x . -R
####setuid---???
####以不同的用户运行可执行文件
```
chmod +s file #将该文件的所有权替换为该用户
chown root.root file
chmod +s file
./file
#这个文件实际上每次都是以超级用户的身份来执行
```
####创建不可修改文件
`/etc/mtab`
`chattr`将文件设置为不可修改
`/etc/shadow`文件就是不可修改的属性，不可修改属性是保护文件不被修改的安全手段之一。
`passwd`命令修改自己的密码。执行passwd时，它实际上就修改了`/etc/shadow`文件。
`chattr +i file` 将一个文件设置为不可修改
`chattr -i file` 移除不可修改属性

####批量生成空白文件
`touch`命令可以用来生成空白文件，如果文件存在，则而已用它修改文件的时间戳。
```
#批量生成名字不同的空白文件
for name in (1..100).txt#{1..100}会扩展成一个字符串"1,2,3,4,5,6...100"
	do
	touch $name
	done
```
`touch -a`只更改文件访问时间
`touch -m`只更改文件内容修改时间
`touch -d`指定特定的时间和日期

####查找符号链接及其指向目标
####符号链接
####`ln`命令---???
`ls -l | grep "^l"| awk '{ print $8} ' `
`^l`代表以字母l作为起始
####列举文件类型统计信息
`file fileName` 用下列命令打印文件类型信息
`file -b fileName` 打印不包括文件名在内的文件类型信息

filestat.sh
```
#!/bin/bash

if [ $# -ne 1 ];
then
	echo $0 basepath;
	echo
fi
path=$1

declare -A statarray;

while read line;
do
	ftype='file -b "$line"'
	let statarray["$ftype"]++
done < < (find $path -type f -print)

echo ===== File types and counts =====
for ftype in "${!statarray[@]}";
do
	echo $ftype: ${statarray["$ftype"]}
done
```

###环回文件与挂载
####环回文件系统??????
####挂载点??????
####mount unmount命令???
####`mkfs`命令??????
`mount -o loop loopback.img /mnt/loopback` -o loop 用来挂在环回文件系统
####什么是硬盘分区??????
####`sync`命令
####生成ISO文件及混合ISO
`dd if=/dev/cdrom of=image.iso`
`mkisofs`??????
`cdrecord`??????
`isohybrid`???????
`eject`命令  弹出光驱 `-t`合上
####查找文件差异并进行修补
`patch`命令
`diff`命令
####修补文件
`diff -u ver1 ver2 > ver.patch`
`patch -p1 ver1 < vedr.patch`

####head与tail
`head -n 4 file`指定打印文件的前4行
`head -n -N file`打印除了最后N行之外的所有的行 -N表示一个负数
`tail -n 5 file`打印最后5行
`tail -n +(N+1)`打印除了前N行之外所有的行
`tail -f`监视文件内容增加的命令
####`dmesg`?????????????????
`tail -f`也可以加入一个睡眠间隔 `-s`
####列出当前路径下的目录
`ls -d */`
`ls -F | grep "/$"`
`ls -l | grep "^d"`
`ls -F | grep "/$"` grep ls
只过滤那些以`/$`作为行尾标记的输出项
####pushd popd快速定位
pushd和popd可以用于在多个目录之间进行切换而无需复制并粘贴目录路径。
`cd -`命令

####统计文件的行数，单词数和字符数
`wc`命令
`wc -l file`统计行数
`wc -w file`统计单词数
`wc -c file`统计字符数
`wc file`他会打印出文件的行数，单词数和字符数
`wc file -L`打印最长行的长度

####打印目录树
`tree`命令
`tree path -P PARTTERN`只重点标记出匹配某种样式的文件
`tree path -I PARTTERN` 只重点标记出除符合某种样式之外的那些文件
`tree -h `同时打印出文件和目录的大小
`tree`命令可以生成HTML输出。例如，用下面的命令可以创建一个包含目录树输出的HTML文件
`tree PATH -H http://localhost -o out.html`
将`http://localhost`替换为适合存放输出文件的URL