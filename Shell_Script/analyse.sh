#！/usr/bin/bash

echo "analyse log begin..."

echo "input file name"

# 获取从键盘中输入的文件名称
read filename 

# 判断文件是否存在
if [ -e "${filename}" ]
then
    echo ""
else
    echo "analyse file didn't exist"
    exit
fi


echo "input user name"
# 获取要分析的用户缩写
read -a userbuf
# echo ${userbuf[@]}
# echo "${filename}"


# 判断是否输入了用户缩写
if [[ ${#userbuf} -eq 0 ]]
then
    echo "no user or file name support to analyse!!! exit"
    exit
fi

# 定义输出分析日志文件
outputfile="analyse.log"

# 如果输出文件存在，则覆盖输出文件
if [ -e ${outputfile} ]
then
    echo -n > ${outputfile}    
fi
# echo "analyse user name: ${@}"
# echo -e "\n"

# echo ${#userbuf[*]}
# echo "[${userbuf[*]}]"

# 使用grep分析日志文件 追加信息输出到输出文件
for ((i=0; i<${#userbuf[*]}; i++))
do
    echo "begin analyse user:${userbuf[i]}" >>${outputfile}
    echo "-------------------------------------------------------" >> ${outputfile}
    grep -nw "\[${userbuf[i]}\]" ${filename} >> ${outputfile}
    echo -e "\n" >> ${outputfile}
done

echo -e "run the command \ncat ${outputfile}\nto see the output"

