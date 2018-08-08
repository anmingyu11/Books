cat命令:
	cat ~ concatenate
	cat file1 file2 file3 ..
	echo 'Text through stdin' | cat - file.txt -被作为来自stdin文本的额文件名
	cat -s file 压缩连续的空白行
	cat multi_blanks.txt | tr -s '\n' 用tr移除空白行
	cat -T 将制表符标记成 ^|
	cat -n 在每一行内容前加上行号
script- scriptreplay 录制与回放终端会话:

find命令:
	工作方式：沿着文件层次结构向下遍历，匹配符合条件的文件，并执行相应的操作。
	find base_path 列出当前目录及子目录下所有的文件和文件夹
find根据文件名或正则表达式匹配搜索:
	find . -name "*.txt" -print
	-iname选项，忽略字母大小写
	or条件操作: find . \( -name "*.txt" -o -name "*.pdf"\) -print
	-path参数可以使用通配符来匹配文件路径或文件 -name总是用给定的文件名进行匹配。-path则将文件路径作为一个整体进行匹配
	-regex和-path类似，不过-regex是基于正则表达式来匹配文件路径的 -iregex用于忽略正则表达式的大小写
	否定参数 find . ! -name "*.txt"
基于目录深度的搜索:
	find会遍历所有子目录 用-maxdepth和-mindepth来限制深度	
根据文件类型搜索:
	-type f 普通文件
	-type l 符号链接 ---???
	-type d 目录
	-type c 字符设备 ---???
	-type b 块设备   ---???
	-type s 套接字   ---???
	-type p Fifo     ---???
根据文件时间进行搜索
	-atime 访问时间
	-mtime 修改时间
	-ctime 文件元数据(例如权限或所有权)最后一次改变的时间
	计量单位 /天 -cmin 分钟
	Unix中并没有所谓"创建时间"的概念
	find -atime -7 7 +7 访问最近七天， 恰好七天， 超过七天
	find . -newer file 找出比file修改时间更长的文件
	find .-type -size +/-/2k 基于大小搜索 单位b/c/w/k/m/g
删除匹配的文件
	find . -type f -name "*.swp" -delete
文件权限和所有权的匹配
	find . -type f -perm 644 -print
结合find执行命令或动作
	find . -type f -user root -exec chown slynux {} \;
	{}会被该文件名所替换
	find命令找到的文件 file1 file2 会被解析为chown slynux file1 和 chown slynux file2
	find . -type f -name "*.c" -exec cat{} \; >allcfiles.txt 讲给定目录中的所有C程序文件拼接起来写入allcfiles.没有追加的原因是因为find命令的全部输出只是一个单数据流，而只有当多个数据流被追加到单个文件中的时候才有必要用>>
	find . -type f -mtime +10 -name "*txt" -exec cp {} OLD \;
	-exec只能够接受单个命令
让find跳过特定的目录
	find . \( -name ".git" -prune\) -o \( -type f -print)\
	\(-name ".git" -prune)\ 的作用是用于排除，它指明了排除.git目录 而后面致命了需要执行的动作

#### xargs
xargs命令应该紧跟在管道操作符之后。它以标准输入作为主要的源数据流，例如`command | xargs`
xargs命令把从stdin接收到的数据重新格式化，再将其作为参数提供给其他命令。

每一个参数都是由" "（空格）隔开的字符串。空格是默认的界定符。按照下面的方法可以将单行划分成多行：
`cat example | xargs -n 3`

用自己的界定符来分隔参数
`echo "splitXsplitXsplitXsplitX" | xargs -d X`
`echo "splitXsplitXsplitXsplitX" | xargs -d X -n 2`

xargs有一个选项-I，可以提供上面这种形式的命令执行序列。
`cat "./ceho ip fuck -l" | xargs -I {} ./cecho.sh -p {} -l`
-I{}指定了替换字符串。对于每一个命令参数，字符串{}会被stdin读取到的参数所替换。

用find匹配并列出所有的txt文件，然后用xargs将这些文件删除：
` find . -type f -name "*.txt" -print0 | xargs -0 rm -f ` 
xargs -0 将\0作为输入定界符。

统计源代码目录中所有C程序文件的行数
`find src -type f -name "*.c" -print0 | xargs -0 wc -l`

结合stdin，巧妙运用while语句和子shell
`cat files.txt | {while read arg; do cat $arg; done}`
等同于`cat files.txt | xargs -I {} cat {}`s

####tr
tr可以对来自标准输入的字符进行替换，删除，以及压缩。
`tr [options] set1 set2`

将输入字符由大写转换成小写
`echo "HELLO WHO IS THIS" | tr 'A-Z' 'a-z'`

加密解密
`echo 12345 | tr '0-9' '9876543210'`
`echo 87654 | tr '9876543210' '0-9'`

用tr删除字符
`cat file | tr -d '[set1]'`
例如
`echo "Hello 123 world 456" | tr -d '0-9'`

字符集补集
`tr -c [set1] [set2]`
将不在补集中的所有字符全部删除。
`echo hello 1 char 2 next 4 | tr -d -c '0-9 \n'`
`1 2 4`
在这里，补集包含了除数字、空格字符和换行符之外的所有字符。因为指定了-d，所以这些字符全部都被删除。

tr压缩字符
tr的-s选项可以压缩输入中重复的字符，方法如下：
`echo "fuck      you mo ther" | tr -s ' '`
`tr -s '[set]'`

tr废物点心
```shell
cat sum.txt
1
2
3
4
cat sum.txt | echo $[ $(tr '\n' '+') 0 ]
10
```
`echo $[ 1+2+3+4+5+0 ]`


###校验和 ---???
`md5sum file > file_sum.md5`
`md5sum -c file_sum.md5` 用生成的文件核实数据完整性
还有一个sh1sum
`md5deep` 和`sha1deep`能够对目录进行校验

####排序、单一与重复
`sort file1 file2 > sorted`
`sort file1 file2 -o sorted`
找出已排序文件中不重复的行
`cat sorted | uniq > uniqlines`

####sort
按数字进行排序
`sort -n file.txt`
按逆序进行排序
`sort -r file`
按月份进行排序
`sort -M months`
测试一个文件是否已经被排过序
```
sort -C file;
if[ $? -eq 0 ]; 
then
	echo Sorted;
else
	echo Unsorted;
fi
#要检查是否按数字进行排序，应该使用sort -nC
```
要合并两个排过序的文件，而且不需要对合并后的文件再进行排序
`sort -m sort1 sort2`

-k指定了排序应该按照哪个键进行，键指的是列号，而列号就是执行排序时的依据，-r告诉sort命令按照逆序进行排序，-n代表数字
`sort -nrk 1 data` 依据一列进行排序
`sort -bd unsorted` 忽略空格类的不必要的字符 -b用于忽略文件中的前导空白字符，-d用于指明以字典序进行排序。

####uniq
uniq命令通过消除重复内容，从给定输入中找出单一的行，只能用于排过序的数据输入。
`uniq sort`
`sort unsorted.txt | uniq`
`sort -u unsorted.txt`
`sort unsorted.txt | uniq -c`统计各行在文件中出现的次数
`sort unsorted.txt | uniq -d` 找出文件中重复的行

uniq命令生成包含0值字节终止符的输出：
`uniq -z file.txt`
下面的命令讲删除所有指定的文件，而这些文件的名字是从file.txt中读取的
`uniq -z file.txt | xargs -0 rm`

####临时文件命名与随机数
最适合存储临时数据的位置是`/tmp`（该目录中的内容在系统重启后会被清空）。
环境变量$RANDOM总是返回一个随机数
`.$$`作为添加的后缀会被扩展成当前运行脚本的进程ID

####分隔文件和数据
生成一个大小为100KB的测试文件
`dd if=/dev/zero bs=100k count =1 of=data.file`
上面的命令会创建一个大小为100KB二文件内容全部是0的文件
你可以指定分割大小，将文件分割成多个更小的文件：
```
split -b 10k data.file
```

####csplit
split只能够根据数据大小或行数分割文件，而csplit可以根据文本自身的特点进行分割。
`csplit server.log /SERVER/ -n 2 -s {*} -f server -b "%02d.log" ; `
`/SERVER/`用来匹配某一行/[REGEX]/
`{*}`表示根据匹配重复执行分割，知道文件末尾为止。
`-s` 使命令进入静默模式，不打印其他信息。
`-n`指定分割后文件名后缀的数字个数
`-f`指定分割后的文件名前缀
`-b`指定后缀格式

####批量重命名和移动
```
count =1;
for img in *.jpg *.png
	do
	new =image-$count.${img##*.}
	
	mv "$img" "$new" 2 > /dev/null
	
	if [ $? -eq 0 ];
	then
	
	echo "renaming $img to $new"
	let count++
	
	fi
	
	done
```

####
`renmae *.JPG *.jpg`
将文件名中的空格替换成字符"_"
`rename 's/ /_/g' *`

将所有的.mp3文件移入给定的目录
`find path -type f -name "*.mp3" -exec mv {} targetDir \;`

####拼写检查与词典操作
`aspell`来核查某个单词是否在词典中：
`aspell list`检查给定的输入是不是一个词典单词

####交互输入自动化
```
read -p "enter number : " no;
read -p "enter name : " name
echo You have entered $no, $name;
```
`echo -e "1\nhello\n" | ./interactive.sh`