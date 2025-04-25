# 题目一

## 描述：

​	请生成日期格式为yyyy-MM-dd的日志文件，每日生成一个文件， 例如生成的文件名为2024-04-28.log， 并且把磁盘的使用情况写到到这个文件中，同时将文件放到指定目录中。



```shell
#!/usr/bin/bash
echo "开始运行shell脚本"

while :
do
    name=`date +%Y-%m-%d-%H:%M:%S.log`
    touch ${name}

    if [ -f $name ]
    then
        echo "创建文件 ${name} 成功" 
    else
        echo "创建文件 ${name} 失败"
    fi

    df -h > ${name}
    echo "磁盘使用情况记录成功"

    mkdir -p "record"

    mv $name ./record
    sleep $((60 * 60 * 24))s
done
```



# 题目二：

## 描述：写一个脚本计算一下[linux系统](https://so.csdn.net/so/search?q=linux%E7%B3%BB%E7%BB%9F&spm=1001.2101.3001.7020)所有进程占用内存大小的和。



