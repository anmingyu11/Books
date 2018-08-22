`grep`命令???????
`grep -E 正则`
`grep -o -E 'matcher'` 只输出文件匹配到的部分，使用选项-o
`grep -c "text" filename`统计文件或文本中包含匹配字符串的行数。只是统计匹配行的数量，并不是匹配的次数。
`grep "test_function()" .` -R -n 递归搜索当前目录并打出第几行
`grep -i ` 忽略大小写
`grep -e "p1" -e "p2"` -e匹配多个样式
`grep - f patternfile sourcefile`以patternfile的匹配样式匹配sourcefile
`grep "main" . -r --include \*.{c,cpp}`只在目录中递归搜索所有的.c和.cpp文件
`grep "main()" .-r --exclude "README"`在搜索中排除所有的README文件:w，如果需要排除目录，可以使用`---exclude-dir`选项。
####使用0值字节后缀的grep与xargs
当文件名用作命令行参数时，建议用0值字节作为文件名终止符，而不是用空格。因为一些文件名中会包含空格字符，一旦它被误解为终结符，那么单个文件名就会被认为是两个文件名。
下面的命令序列中，grep输出以0值字节作为终结符的文件名(\0)。这可以用`grep`的-Z选项来指定。xargs -0 读取输入并用0值字节终结符分隔文件名：
`grep "test" file* -lZ | xargs -0 rm`

####grep 的静默输出
`grep -q `
####打印出匹配文本之前或之后的行
要打印匹配某个结果之后的3行，使用-A选项:
`seq 10 | grep 5 -A 3`
之前的三行
`seq 10 | grep 5 -B 3`
之前以及之后的3行
`seq 10 | grep 5 -C 3`

####用cut按列切分文件
`cut -f1 student_data.txt`
`cut -f2,4 student_data.txt`
`cut -f3 --complement student_data.txt`

####sed入门
替换给定文本中的字符串。它可以利用正则表达式进行匹配
`sed 's/pattern/replace_string/' file`
或者
`cat file | sed 's/pattern/replace_str'`

`sed 's/text/replace/' file > newfile`
`mv newfile file`
之前的命令会讲每一行中第一处复合样式的内容替换掉，但是如果要替换所有内容，需要在命令尾部加上参数`g`
`sed 's/pattern/replace/g' file` 

####移除空白行
`sed '/^$/d' file`

####已匹配字符串标记&
`echo this is an example | sed 's/\w\+/[&]/g'`
`\w\+`匹配每一个单词，然后用【&】替换它

####awk入门
```
awk ' BEGIN{ print "start" } pattern
{ commands } END { print "end"} ' file
``` 
```
awk 'BEGIN { ST } { ST } END { END ST }'
awk "BEGIN { ST } { ST } END { END ST }"
```

BEGIN在awk开始从输入流中读取行之前被执行。这是一个可选的语句块。
END语句块和BEGIN语句块类似。END语句块在awk从输入流中读取完所有的行之后被执行
pattern语句块中的通用命令。

当使用不带参数的print时，它会打印出当前行。

####特殊变量
`NR`记录数量，在执行过程中对应于当前行号
`NF`字段数量，在执行过程中对应于当前行的字段数
`$0`包含执行过程中当前行的文本内容
`$1` 包含第一个字段的文本内容
`$2` 包含第二个字段的文本内容
```
seq 5 | awk ' BEGIN { sum=0; print "Summation:"}
{ print $1"+"; sum+=$1 }
END { print "=="; print sum } '
```

####将外部变量值传递给awk
借助选项-v，我们可以将外部值传递给awk

####getline读取行
####用样式对awk处理的行进行过滤

####替换文本或文件中的字符串
sed是类UNIX系统下用于文本或文件内容替换的通用工具

####迭代文件中的每一行
```
while read line;
do
echo $line;
done < file.txt
```
####迭代一行中的每一个单词
```
for word in $line;
do
echo $word;
done
```

####迭代一个单词中的每一个字符
```
for((i=0;i<$(#word);i++))
do
echo ${word:i:1};
done
```

####按列合并文件
`paste f1 f2 f3`

####打印文件或行中的第n个单词或列
`awk '{ print $5 }' filename`

####打印不同行或样式之间的文本
```
awk 'NR==M, NR==N' file
```
M和N换成具体的数字
```
seq 100 | awk 'NR==4 , NR==6'
```
####用脚本检验回文字符串
`sed`命令
`rev`命令
`tac`命令

####解析文本中的电子邮件地址和url
```
egrep -o '[A-Za-z0-9.]+@[A-Za-z0-9,] +\.[a-zA-Z]{2,4}'#匹配电子邮件地址
egrep -o 'http://[a-zA-Z0-9.]+\.[a-zA-Z]{2,3}' #解析http
```


