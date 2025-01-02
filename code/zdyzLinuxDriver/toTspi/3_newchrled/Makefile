KERNELDIR := /home/auser/tspi/linux/kernel
CURRENT_PATH ?= $(shell pwd)
KCONFIG_FILE := $(KERNELDIR)/.config

obj-m += newchrled.o

build: kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) ARCH=arm64 modules
	# $(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) KCONFIG_CONFIG=$(KCONFIG_FILE) ARCH=arm64 modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean