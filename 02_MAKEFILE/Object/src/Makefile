#Makefile中#代表单行注释


#第一版

#app:add.c mul.c des.c sub.c main.c
#	gcc add.c mul.c des.c sub.c main.c -I../include -o app 


#第二版 节省编译时间
#app:add.o sub.o mul.o des.o main.o
#	gcc add.o sub.o mul.o des.o main.o -o app


#add.o:add.c
#	gcc -c -I../include add.c
#sub.o:sub.c
#	gcc -c -I../include sub.c
#mul.o:mul.c
#	gcc -c -I../include mul.c
#des.o:des.c
#	gcc -c -I../include des.c
#main.o:main.c
#	gcc -c -I../include main.c


#第三版 提供复用性   
CC=gcc
INCLUDE=../include
CFLAGS=-I$(INCLUDE) -g -Wall -c
CPPFLAGS=-E -D
LDFLAGS=-L../lib -l
TARGET=app



FILENAME=$(wildcard *.c)
DESTNAME=$(patsubst %.c,%.o,$(FILENAME))

$(TARGET):$(DESTNAME)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) $<

output:
	echo $(FILENAME)
	echo $(DESTNAME)

clear:
	rm $(DESTNAME) -rf
	rm $(TARGET) -rf

install:
	sudo cp $(TARGET) /usr/bin/

distclear:
	sudo rm /usr/bin/$(TARGET)




