CFLAGS =	-O3 -g -Wall -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -fmessage-length=0

LIBS =	-lwiringPi

TARGET_1 =	mitsu.so
TARGET_2 =	mitsu

$(TARGET_1):
	@echo 'Building target: $@'
	gcc -shared $(CFLAGS) $(LIBS) -fPIC -o $(TARGET_1) mitsu.c
	gcc $(CFLAGS) $(LIBS) $(TARGET_1) -o $(TARGET_2) main.c  -L.

all: $(TARGET_1)

install:
	@echo 'Installing mitsu...'
	cp $(TARGET_1) /usr/lib
	cp $(TARGET_2) /usr/sbin
	ldconfig
	@echo 'Completed.'

clean:
	@echo 'Removing mitsu...'
	rm -f $(TARGET_1) $(TARGET_2)

uninstall:
	@echo 'Removing mitsu...'
	rm -f $(TARGET_1) $(TARGET_2)
	rm -f /usr/lib/mitsu.so
	rm -f /usr/sbin/mitsu
	ldconfig
