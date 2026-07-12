# 📅 Ngày 5 - Inline Assembly (Chương 6)

---

# 🎯 Mục tiêu chương

> Học cách chèn lệnh Assembly vào chương trình C để điều khiển trực tiếp CPU ARM Cortex-M.

Sau chương này mình cần có thể:

- [ ] Hiểu Inline Assembly là gì
- [ ] Biết khi nào cần dùng Inline Assembly
- [ ] Viết được các câu lệnh Assembly đơn giản trong C
- [ ] Hiểu Input / Output Operand
- [ ] Hiểu Clobber List
- [ ] Đọc hiểu ví dụ Bootloader, RTOS sử dụng Inline Assembly

---

# 1. Inline Assembly là gì?

## Định nghĩa

> ...

---

## Tại sao phải dùng?

Ví dụ:

- Đọc MSP
- Đọc PSP
- Đọc CONTROL
- Disable Interrupt
- Enable Interrupt
- Thực hiện lệnh đặc biệt của CPU

Ví dụ C không làm được:

```asm
MRS R0, MSP
MSR CONTROL, R0
CPSID I
CPSIE I
```

---

# 2. Cú pháp Inline Assembly

```c
__asm volatile(
    "..."
);
```

Hoặc

```c
asm volatile(
    "..."
);
```

### Ý nghĩa từng thành phần

| Thành phần | Ý nghĩa |
|------------|----------|
| asm | Chèn Assembly |
| volatile | Không cho Compiler tối ưu bỏ lệnh |

---

# 3. Các thành phần của Inline Assembly

## Instruction

```asm
MOV
ADD
SUB
MRS
MSR
LDR
STR
```

Ghi chú:

...

---

## Input Operand

Ví dụ:

```c
:
: "r"(value)
```

Ý nghĩa:

...

---

## Output Operand

Ví dụ:

```c
: "=r"(result)
```

Ý nghĩa:

...

---

## Clobber List

Ví dụ:

```c
: "memory"
```

Ý nghĩa:

...

---

# 4. Các thanh ghi thường dùng

| Lệnh | Chức năng |
|------|-----------|
| MRS | Đọc System Register |
| MSR | Ghi System Register |
| MOV | Copy dữ liệu |
| ADD | Cộng |
| SUB | Trừ |
| BX | Nhảy |
| BL | Gọi hàm |

---

# 5. Các ví dụ trong bài học

## Ví dụ 1

Mục đích:

...

Code:

```c

```

Điều học được:

...

---

## Ví dụ 2

Mục đích:

...

Code:

```c

```

Điều học được:

...

---

# 6. Liên hệ với chương trước

Có thể đọc được:

- MSP
- PSP
- CONTROL
- xPSR

bằng Inline Assembly.

Ví dụ:

```asm
MRS R0, CONTROL
```

↓

CPU copy CONTROL → R0

---

# 7. Ứng dụng thực tế

Inline Assembly xuất hiện trong:

- Bootloader
- RTOS
- Startup Code
- Linker
- Driver
- Context Switch
- Interrupt

---

# 8. Những điều cần nhớ

✅ C không truy cập được mọi lệnh CPU.

✅ Inline Assembly dùng để gọi các lệnh đặc biệt của ARM.

✅ MRS dùng để đọc System Register.

✅ MSR dùng để ghi System Register.

✅ volatile tránh Compiler tối ưu bỏ lệnh.

---

# 9. Tổng kết chương

## Đã hiểu

- [ ]

- [ ]

- [ ]

---

## Chưa rõ

- [ ]

- [ ]

---

# 💡 Ghi chú của bản thân

...