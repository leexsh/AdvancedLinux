#!/bin/bash



#单行注释

#定义变量,赋值符左右两侧不允许有空格,会被shell错误识别成命令

#VAR=asdasdasdasdasdasd

#echo ${VAR}123

#位置变量为命令行参数

#echo 用户输入:$1 $2 $3


#echo $* #所有参数
#echo $# #参数个数
#echo $!	#上一个执行后台命令的进程的pid
#echo $? #上一个命令的返回值
#echo $$ #当前shell进程的pid

#三种修饰符 '' "" ``

#CAR=奔驰
#VAR='Hello '

#双引号可以识别特殊符号做特殊处理,单引号中都为纯字符串
#echo "${VAR}${CAR}"

#通过``修饰命令 执行命令并返回打印结果
#TIME=`date`

#echo ${TIME}


#expr命令完成四则运算

NUM=30
NUM2=50
NUM3=2

#expr `expr ${NUM} + ${NUM2}` \* ${NUM3}

#流程结构,if单选选择,case多项选择

#if test -a $1
#	then
#		echo "文件存在"
#	elif test 
#		then
#			if test
#			fi
#			echo "elif为真"
#else
#	echo "文件不存在"
#fi



#case多选

#read VAR

#case ${VAR} in
#	'1')
#		echo "拳头"
#		;;
#		
#	'2')
#		echo "剪刀"
#		;;
#	'3')
#		echo "布"
#		;;
#esac


#for循环,兼容传统风格

#for VAR in 1 2 3 4 5 6 7 8
#do
#	echo "${VAR}"
#done

#for((i=0;i<100;i++))
#{
#	echo ${i}
#}


#while循环,以真为条件执行

#while test 0
#do
#	echo runing....
#done

#until循环,以假为条件执行
#until test 1
#do
#	echo runing...
#done

#select选择循环
#select VAR in 猫 狗 鸡 鸭 鹅 猪
#do
#	echo "${VAR}"
#done


#shift指令参数左移,销毁参数

#for VAR in $1 $2 $3
#do
#	echo "${VAR}"
#	shift
#done
#
#echo $1 $2 $3

VAR=1000
VAR1=2000
MYFUNCTION()
{
	SUM=`expr ${VAR} + ${VAR1}`
	echo ${SUM}
}

#函数内部使用位置变量需要在调用函数时传递, 用户自定义变量不需要,直接使用变量即可
CODE=`MYFUNCTION`
echo ${CODE}


