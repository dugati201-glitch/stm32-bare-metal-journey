# Ngày 1: Cross-Compilation & GCC ARM Toolchain

## 🎯 Mục tiêu
- Hiểu được khái niệm **Cross-compile** (biên dịch chéo).
- Biết cách sử dụng dòng lệnh thay vì dùng nút bấm đồ họa của IDE.
- Làm quen với cấu trúc `Makefile` cơ bản.

## 📝 Kiến thức cốt lõi
1. **Native Compilation:** Biên dịch code trên PC và chạy luôn trên chip của PC (x86_64).
2. **Cross Compilation:** Biên dịch code trên PC nhưng file đầu ra dùng để chạy dưới vi điều khiển ARM Cortex-M3.
3. 
## 💻 Các câu lệnh đã dùng
Lệnh biên dịch file `main.c` đầu tiên:
```bash
arm-none-eabi-gcc -c main.c -o main.o -mcpu=cortex-m3 -mthumb