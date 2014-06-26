/*
 * devone_ioctl.h
 *
 */
#ifndef _DEVONE_IOCTL_H
#define _DEVONE_IOCTL_H

#include <linux/ioctl.h>

struct ioctl_cmd {
	unsigned int reg;
	unsigned int offset;
	unsigned int val;
};

#define IOC_MAGIC 'd'

#define IOCTL_VALSET _IOW(IOC_MAGIC, 1, struct ioctl_cmd)
#define IOCTL_VALGET _IOR(IOC_MAGIC, 2, struct ioctl_cmd)

#endif

