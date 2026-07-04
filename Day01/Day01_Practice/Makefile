CC 	= arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
#Hoan thanh buoc 1 khai bao bien
CFLAGS  = -mcpu=cortex-m3 -mthumb -Os -g

all: program.bin

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
gpio.o: gpio.c
	$(CC) $(CFLAGS) -c gpio.c -o gpio.o 
program.elf: main.o gpio.o 
	$(CC) $(CFLAGS) main.o gpio.o -o program.elf --specs=nosys.specs
program.bin: program.elf
	$(OBJCOPY) -O binary program.elf program.bin

clean:
	rm -rf *.i *.s *.o *.elf *.bin
