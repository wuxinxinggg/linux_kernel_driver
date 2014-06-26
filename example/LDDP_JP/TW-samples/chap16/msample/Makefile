
CFILES = main.c sub.c

CFLAGS_sub.o := -DDEBUG
obj-m += sample.o
sample-objs := $(CFILES:.c=.o)

all:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

