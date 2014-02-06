
obj-m := hello.o

all:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) V=1 modules

clean:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

