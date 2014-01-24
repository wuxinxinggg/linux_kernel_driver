#
# Makefile for the FREAX-kernel character device drivers.
#
# Note! Dependencies are done automagically by 'make dep', which also
# removes any old dependencies. DON'T put your own dependencies here
# unless it's something special (ie not a .c file).
#

AR	=ar
AS	=as --32
LD	=ld -m elf_i386
LDFLAGS	=-x
CC	=gcc
CFLAGS	=-m32 -Wall -O -g -fstrength-reduce -fomit-frame-pointer  \
	-finline-functions  -nostdinc -I../../include -mtune=i386 -fno-stack-protector
CPP	=gcc -E -nostdinc -I../../include

.c.s:
	$(CC) $(CFLAGS) \
	-S -o $*.s $<
.s.o:
	$(AS) -c -o $*.o $<
.c.o:
	$(CC) $(CFLAGS) \
	-c -o $*.o $<

OBJS  = math_emulate.o

math.a: $(OBJS)
	$(AR) rcs math.a $(OBJS)
	sync

clean:
	rm -f core *.o *.a tmp_make
	for i in *.c;do rm -f `basename $$i .c`.s;done

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c;do echo -n `echo $$i | sed 's,\.c,\.s,'`" "; \
		$(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile

### Dependencies:
