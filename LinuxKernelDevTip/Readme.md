Collect the tips of linux kernel development

## Example1
The simplest kernel module demo

## Example2
Enhance Example0, append module infomation, parameter 

Parameter Passing: insmod example.ko debug_enable=1 dispstr="World"

Dyanamicly change the parameter via sysfs

List Module Info: modinfo brook.ko

## Example3
DebugFS Example

Dynamicly change the variable via debugfs

Need to mount debugfs

## Example4
Sysctl Example
Register sysctl_table and it becomes a subdir of /proc/sys

Can read/write value via /proc/sys

After kernel 2.6.33, sysctl is only the wrapper of procfs.

It cannot viist from syscall anymore.

## Example5
Syscall Example

Register a misc device, communicate between user space and kernel space.

Implement file_operation, mmap, ioctl

## Example6
ProcFS Example(Without seq_file)

## Example7
ProcFS Example(With seq_file example)

## Example8
Netlink Example (Communicate between user space and kernel space)
