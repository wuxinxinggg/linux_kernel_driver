obj-m:= chrdev_reg.o

all:
	make -Wall -C /lib/modules/`uname -r`/build M=`pwd` modules
clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
