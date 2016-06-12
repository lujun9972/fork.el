# 设置emacs源代码路径
# (你可以在makefile中直接设置,也可以make时在命令行中提供)
#ROOT    =
CC      = gcc
LD      = gcc
CFLAGS  = -ggdb3 -Wall
LDFLAGS =

all: fork-core.so

# make shared library out of the object file
%.so: %.o
	$(LD) -shared $(LDFLAGS) -o $@ $<

# compile source file to object file
%.o: %.c
	$(CC) $(CFLAGS) -I$(ROOT)/src -fPIC -c $<
