CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS  = -mcpu=cortex-m3 -mthumb -O0 -Wall

# Mục tiêu tối cao (Mặc định khi gõ lệnh make)
all: program.bin

# Bước 1: Dịch file .c thành file mã máy cục bộ .o (Bao gồm cả Tiền xử lý và Biên dịch)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
# tương ứng với arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -Wall -c main.c -o main.o
# Bước 2: Liên kết (Linker) - Gom file .o lại để định vị ô nhớ tạo file .elf tổng chỉnh
program.elf: main.o
	$(CC) $(CFLAGS) main.o -o program.elf --specs=nosys.specs

# Bước 3: Cắt gọt (Objcopy) - Chuyển đổi .elf thành .bin thuần túy nhẹ nhất để nạp chip
program.bin: program.elf
	$(OBJCOPY) -O binary program.elf program.bin

# Mục tiêu dọn dẹp bộ nhớ: Xóa sạch các file build khi cần làm lại từ đầu
clean:
	rm -rf *.i *.s *.o *.elf *.bin