KERNELDIR := /home/xxx/linux-imx-rel-imx_4.1.15_2.1.0_ga_alientek
CURRENT_PATH := $(shell_pwd)

obj-m := leddevice.o leddriver.o

build: kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean