mname := example
$(mname)-objs := netlink-exam-kern.o
obj-m := $(mname).o

KERNELDIR := /lib/modules/`uname -r`/build

all:
	$(MAKE) -C $(KERNELDIR) M=`pwd` modules

clean:
	$(MAKE) -C $(KERNELDIR) M=`pwd` clean
