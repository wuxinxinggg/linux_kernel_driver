# Linux kernel v0.11

This is a modified version of the linux kernel 0.11, which can be compiled on 64-bit Debian and run in the [bochs][1].

The version of tools on my machine are listed below:

* SMP Debian 3.11.6-1 (2013-10-27) x86_64 GNU/Linux
* gcc (Debian 4.8.2-5) 4.8.2
* GNU assembler (GNU Binutils for Debian) 2.23.90.20131116
* GNU ld (GNU Binutils for Debian) 2.23.90.20131116

I also provide a patch file `linux-0.11-deb64.patch` to modify the original version
(you can download the original kernel source code [here][2]).

To apply the patch, assume the source codes are decompressed to the directory `linux-0.11`, then
```
$ cd linux-0.11/
$ patch -p1 < ../linux-0.11-deb64.patch
``` 

## NOTE:

1. The root device is "FLOPPY". You can change it in `./Makefile` by modifying the `ROOT_DEV`.
2. You can use `make disk` to create a 1.44MB bootable image for bochs.
3. The `bochsrc.bxrc` is the config file for bochs to run this kernel. The images of root device and hard disk are provided [here][3].

[1]: http://bochs.sourceforge.net
[2]: http://www.oldlinux.org/Linux.old/Linux-0.11/sources/system/
[3]: http://www.oldlinux.org/Linux.old/images/Current/rootimage-0.11
