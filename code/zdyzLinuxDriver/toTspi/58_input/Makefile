KERNELDIR := /home/auser/tspi/linux/kernel
CURRENT_PATH ?= $(shell pwd)
KCONFIG_FILE := $(KERNELDIR)/.config

CROSS_COMPILE ?= /home/auser/tspi/linux/prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
CC := $(CROSS_COMPILE)gcc

obj-m += keyinput.o

build: kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) ARCH=arm64 modules
	# $(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) KCONFIG_CONFIG=$(KCONFIG_FILE) ARCH=arm64 modules
	$(CC) keyinputApp.c -o keyinputApp
clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean
	rm keyinputApp
