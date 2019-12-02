CC=gcc
INCLUDE=../include
CFLAGS=-g -Wall -c -I$(INCLUDE)
TARGET=Download
LDFLAGS=-lssl -lcrypto
SRCFILE=$(wildcard *.c)
DESFILE=$(patsubst %.c,%.o,$(SRCFILE))



$(TARGET):$(DESFILE)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.c
	$(CC) $(CFLAGS) $<

clean:
	rm $(TARGET) -rf
	rm $(DESFILE) -rf
	rm *.j* -rf

print:
	-@echo $(SRCFILE)
	-@echo $(DESFILE)
