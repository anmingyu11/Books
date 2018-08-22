###wget
`wget`命令
```
wget url -O 指定输出文件名 f.img -o log #-o指定一个日志文件，从而不必将日志信息打印到stdout
```
`wget -t 5 url`指定重试次数

`wget --limit-rate 20k url` 用k和m指定速度限制
`wget -quota 100m url ` 下载量进行限制
`wget -c url` 断点续传

####复制或镜像整个网站
`wget --mirror exampledomain.com`
`wget -r -N -l DEPTH URL` -r递归 -N对文件使用时间戳
####访问需要认证的HTTP或FTP页面
`wget --user username --password pass url`

####lynx命令
-dump将网页以ASCII字符的形式下载到文本文件中。

####cURL
`curl url > index.html` curl并不将下载数据写入文件，而是写入标准输出
`--slient`
`-O`
`--progress`
`-C`

设置cookie
`curl url --cookie "user=a;pass=k"`
`curl url --cookie-jar cookiefile`

设置用户代理字符串
`curl url --user-agent "Mozilla/5.0"`
`curl -H :"Host: www.slyunux.org" -H "Accept-language:en" URL`  HTTP头部信息
`curl url --limit-rate 20k`
`curl url --max-filesize bytes`
`curl -u user:pass url`
`curl -I url`

####制作图片抓取器及下载工具
```
#!/bin/bash

if [ $# -ne 3 ]
then
	echo "Usage: $0 URL -d DIRECTORY"
	exit -1

for i in {1..4}
do
	case $1 in
	-d) shift; directory=$1; shift ;;
	*) url=${url:-$1}; shift;;
	esac
done

mkdir -p $directory;
baseurl=$(echo $url | epgrep -o "https?://[a-z.]+")

curl -s $url | egrep -o "<img src=[^>]*>>" | sed 's/<img src\*\([^"]*\).*/\1/g' > /tmp/$$.list

sed -i "s|^/|baseurl/|" /tmp/$$.list

cd $directory;

while read file;
do
	curl -s -O "$filename" --silent
done < /tmp/$$.list
```
shift用来移动参数

curlTweets
```
#!/bin/bash
USERNAME="PUT_USERNAME_HERE"
PASSWORD="PUT_PASSWORD_HERE"
COUNT="PUT_NO_OF_TWEETS"

if [[ "$1" != "read" ]] && [[ "$1" != "tweet"]];
then
echo -e "Usage: $0 send status_message\n OR\n $0 read\n"
exit -1;
fi
if [[ "$1" = "read" ]];
then
	curl --silent -u $USERNAME:$PASSWORD http://twitter.com/statuses/
friends_timeline.rss | \
grep title | \
tail -n +2 | \
head -n $COUNT | \
	sed 's:.*<title>\([^<]*\).*:\n\1:'
elif [[ "$1" = "tweet" ]];
then 
	status=$(echo $@ | tr -d '"' | sed 's/.*tweet //')
	curl --silent -u $USERNAME:$PASSWORD -d status="$status" /
	http://twiter.com/statuses/update.xml > /dev/null
	echo 'Tweeted :)'
fi

if [ $# -eq 2 ];
then 
	echo
```

`POST`方式和`GET`方式
curl 发送POST请求 -d选项

####tar命令

`tar -rvf original.tar newfile`
`tar -tf archive.tar`
`tar -tvvf archive.tar`
`tar -xf archive.tar`
`tar -xvf file.tar file1 file4`
SSH
`tar -Af file1.tar file2.tar`
`tar -uvvf archive.tar filea`
`tar -df archive.tar afile bfile`
`tar -f archive.tar --delete file file2`
tar命令只能用来归档，并不具备压缩功能
`tar -cf arch.tar *--exclude "*.txt"`
`cat list`
`tar -cf arch.tar * -X list`
`tar -z `压缩归档文件
`zcat`直接读取gzip格式文件并打印到stdout
`bzip2 file`
`tar -xjvvf archive.tar.bz2 -C edirectory`

####lzma压缩

####加密工具与散列
u
