# 📚 Ngày 09 - Chương 10: Stack (MSP & PSP)

## 🎯 Mục tiêu bài học

Hiểu cơ chế hoạt động của Stack trên ARM Cortex-M và vai trò của hai Stack Pointer (MSP và PSP).

Sau bài học cần trả lời được:

- Stack là gì? Tại sao CPU cần Stack?
- Stack hoạt động theo nguyên lý LIFO như thế nào?
- Stack trên ARM Cortex-M tăng hay giảm địa chỉ?
- Thanh ghi SP (R13) là gì?
- MSP là gì?
- PSP là gì?
- Khi nào CPU sử dụng MSP?
- Khi nào CPU sử dụng PSP?
- Handler Mode luôn dùng Stack nào?
- Thread Mode có thể dùng những Stack nào?
- CONTROL.SPSEL quyết định điều gì?
- Tại sao RTOS cần PSP?
- Exception Entry và Exception Return tác động đến Stack như thế nào?
- PUSH/POP thực chất làm gì với SP?
- Hàm C sử dụng Stack để lưu những gì?

---
# 📚 Các kiểu Stack trên ARM

Có 4 cách tổ chức Stack:

```text
                    Stack Types

        +-------------------------------+
        |                               |
        ▼                               ▼

    Full Stack                    Empty Stack
        |                               |
   +----+----+                     +-----+-----+
   |         |                     |           |
   ▼         ▼                     ▼           ▼

Descending Ascending        Descending    Ascending

(FD)       (FA)             (ED)          (EA)
```

---

# ⭐ ARM Cortex-M sử dụng: Full Descending Stack (FD)

## Quy tắc

- Stack tăng theo nguyên lý **LIFO (Last In - First Out)**.
- Stack phát triển từ **địa chỉ cao xuống địa chỉ thấp**.
- Stack Pointer (SP) **luôn trỏ vào phần tử vừa được PUSH gần nhất**.
- Phần tử được PUSH đầu tiên sẽ nằm ở địa chỉ cao hơn.

```text
Địa chỉ cao
0x20002000
     │
     ▼
+-------------+
|             |  ← Stack rỗng
+-------------+

Địa chỉ thấp
```

---

## PUSH lần 1

```text
PUSH R0
```

```text
Địa chỉ cao
0x20002000
     │
     ▼
+-------------+
|             |
+-------------+
|     R0      |  ← SP
+-------------+
0x20001FFC
```

---

## PUSH lần 2

```text
PUSH R1
```

```text
Địa chỉ cao
0x20002000
     │
     ▼
+-------------+
|             |
+-------------+
|     R0      |
+-------------+
|     R1      |  ← SP (Dữ liệu mới nhất)
+-------------+
0x20001FF8
```

---

## PUSH lần 3

```text
PUSH R2
```

```text
Địa chỉ cao
0x20002000
     │
     ▼
+-------------+
|             |
+-------------+
|     R0      |  ← Dữ liệu cũ nhất
+-------------+
|     R1      |
+-------------+
|     R2      |  ← SP (Dữ liệu mới nhất)
+-------------+
0x20001FF4
```

---

## POP

```text
POP R2
```

```text
Địa chỉ cao
0x20002000
     │
     ▼
+-------------+
|             |
+-------------+
|     R0      |
+-------------+
|     R1      | ← SP
+-------------+
|     R2      |
+-------------+
0x20001FF8
```

R2 được lấy ra trước.

Đúng nguyên tắc:

```text
LIFO

Last In
↓

First Out
```

---

# Đặc điểm của Full Descending

```text
PUSH

SP = SP - 4

Memory[SP] = Data
```

```text
POP

Data = Memory[SP]

SP = SP + 4
```

Do đó:

- PUSH ⇒ Địa chỉ giảm.
- POP ⇒ Địa chỉ tăng.

---

# Vì sao gọi là Full Descending?

## Full

```text
SP luôn trỏ vào ô đã chứa dữ liệu.
```

Ví dụ

```text
      SP
       │
       ▼

+---------+
|   R2    |
+---------+
```

---

## Descending

```text
Stack phát triển

Địa chỉ cao
      │
      ▼

0x20002000

↓

0x20001FFC

↓

0x20001FF8

↓

0x20001FF4
```

Địa chỉ giảm dần.

---

# Ba kiểu Stack còn lại

## Full Ascending (FA)

```text
Stack tăng lên địa chỉ cao.

SP luôn trỏ vào dữ liệu.
```

---

## Empty Descending (ED)

```text
Stack giảm xuống địa chỉ thấp.

SP luôn trỏ vào ô trống.
```

---

## Empty Ascending (EA)

```text
Stack tăng lên địa chỉ cao.

SP luôn trỏ vào ô trống.
```

---

# So sánh

| Kiểu | Stack tăng theo | SP trỏ vào |
|------|-----------------|------------|
| Full Descending (FD) | Địa chỉ giảm | Ô chứa dữ liệu |
| Full Ascending (FA) | Địa chỉ tăng | Ô chứa dữ liệu |
| Empty Descending (ED) | Địa chỉ giảm | Ô trống kế tiếp |
| Empty Ascending (EA) | Địa chỉ tăng | Ô trống kế tiếp |

---

# Điều cần nhớ

✅ ARM Cortex-M sử dụng **Full Descending Stack**.

Đặc điểm:

- Stack phát triển từ địa chỉ cao xuống địa chỉ thấp.
- SP luôn trỏ vào dữ liệu vừa PUSH gần nhất.
- Dữ liệu PUSH đầu tiên nằm ở địa chỉ cao hơn.
- Dữ liệu PUSH cuối cùng nằm ở địa chỉ thấp hơn.
- POP luôn lấy dữ liệu mới nhất trước (LIFO).
- Có thể sử dụng phần đầu làm phân vùng bộ nhớ cho heap,.data... và stack ở trên cùng lưu trữ không lo phải căn chỉnh sao cho tránh hiện tượng stackoverflow
# 📖 Kiến thức trọng tâm

## 1. Khái niệm Stack

- Định nghĩa
- Nguyên lý LIFO
- Stack Frame
- Stack Pointer

Ghi chú:

---

## 2. Thanh ghi R13 (SP)

### SP là gì?

### Vai trò

### Stack Pointer thay đổi khi nào?

Ghi chú:

---

## 3. MSP (Main Stack Pointer)

### Khái niệm

### Khi nào sử dụng

### Ưu điểm

### Ví dụ

Ghi chú:

---

## 4. PSP (Process Stack Pointer)

### Khái niệm

### Khi nào sử dụng

### Ưu điểm

### Ví dụ

Ghi chú:

---

## 5. MSP vs PSP

| Tiêu chí | MSP | PSP |
|----------|-----|-----|
| Mục đích | | |
| Thread Mode | | |
| Handler Mode | | |
| RTOS | | |
| Sau Reset | | |

---

## 6. CONTROL Register

### Bit SPSEL

### Bit nPRIV

### Ví dụ chuyển Stack

Ghi chú:

---

## 7. PUSH / POP

Ví dụ Assembly

```asm

```

SP thay đổi như thế nào?

Ghi chú:

---

## 8. Stack Frame

CPU lưu gì khi:

- Gọi hàm
- Exception
- Interrupt

Ghi chú:

---

## 9. Liên hệ với Startup

Tại sao CPU phải nạp MSP trước Reset_Handler?

Liên hệ:

- Reset Sequence
- Startup Code

---

## 10. Liên hệ với RTOS

Tại sao mỗi Task cần PSP riêng?

Tại sao Kernel dùng MSP?

Ghi chú:

---

# 🧠 Sau bài học phải tự trả lời được

## Câu 1

Tại sao ARM Cortex-M cần hai Stack Pointer?

---

## Câu 2

Nếu Thread Mode đang dùng PSP thì khi xảy ra Interrupt CPU sẽ chuyển sang Stack nào?

---

## Câu 3

Sau khi Interrupt kết thúc CPU quay lại Stack nào?

---

## Câu 4

Nếu chỉ có MSP thì RTOS sẽ gặp vấn đề gì?

---

## Câu 5

Compiler sử dụng Stack trong lời gọi hàm như thế nào?

---

## Câu 6

PUSH và POP thay đổi giá trị SP ra sao?

---

## Câu 7

Tại sao Stack thường nằm trong SRAM?

---

## Câu 8

Nếu Stack Pointer bị sai điều gì sẽ xảy ra?

---

# 🔗 Liên hệ các chương trước

## Chương 05

- R13 (SP)
- MSP
- PSP
- CONTROL.SPSEL
- Thread Mode
- Handler Mode

---

## Chương 07

Reset Sequence

CPU nạp:

- Initial MSP
- Reset_Handler

---

## Startup File

Reset_Handler cần MSP hợp lệ trước khi:

- PUSH
- POP
- BL
- Gọi main()

---

## Linker Script

Stack được đặt ở đâu trong SRAM?

_estack là gì?

---

# 🚀 Liên hệ các chương sau

## Exception

CPU tự PUSH bao nhiêu thanh ghi?

Exception Return POP như thế nào?

---

## RTOS

Mỗi Task có PSP riêng.

Kernel luôn chạy bằng MSP.

Context Switch chỉ cần đổi PSP.

---

## Bootloader

Bootloader phải khởi tạo MSP của Application trước khi nhảy.

---

## Embedded Linux

Mỗi Process/Thread đều có Stack riêng.

Kernel Stack và User Stack hoạt động tương tự MSP/PSP.

---

# 💡 Tổng kết

> Stack là vùng nhớ trong SRAM dùng để lưu tạm dữ liệu trong quá trình thực thi.

> MSP phục vụ Kernel/Exception.

> PSP phục vụ Thread/Task.

> Đây là nền tảng quan trọng để hiểu Exception, RTOS, Context Switch và Bootloader.

---

# ⭐ Từ khóa

- Stack
- Stack Pointer
- R13
- MSP
- PSP
- CONTROL
- SPSEL
- PUSH
- POP
- Stack Frame
- Exception Entry
- Exception Return
- Context Switch
- RTOS