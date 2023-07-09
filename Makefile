obj-m += katana_usb_audio.o 

PWD := $(CURDIR)
KDIR := /lib/modules/$(shell uname -r)/build

katana_usb_audio-objs := src/card.o src/control.o src/pcm.o src/usb.o src/katana_usb_audio.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean: 
	make -C $(KDIR) M=$(PWD) clean