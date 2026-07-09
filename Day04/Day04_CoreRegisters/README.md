# 📖 Ngày 4 - Các thanh ghi bên trong Cortex-M Core (Core Registers)

> **Tài liệu học**
>
> - Chương 05
> - Lesson 05 → Lesson 07

---

# 🎯 Mục tiêu bài học

Sau bài học cần trả lời được:

- [ ] CPU Cortex-M có những thanh ghi nào?
- [ ] Vì sao CPU cần Register?
- [ ] Vai trò của R0-R12 là gì?
- [ ] SP là gì?
- [ ] LR là gì?
- [ ] PC là gì?
- [ ] PSR dùng để làm gì?
- [ ] CONTROL Register dùng để làm gì?
- [ ] Khi gọi hàm CPU thay đổi Register nào?
- [ ] Khi Interrupt xảy ra CPU lưu Register nào?

---

# 1. Tổng quan Register

## Register là gì?

> Ghi chú:

---

## Vì sao CPU cần Register?

> Ghi chú:

---

## Register khác RAM như thế nào?

| Register | RAM |
|----------|-----|
| | |
| | |
| | |

---

# 2. General Purpose Registers

## R0 - R12

### Khái niệm
- Là các thanh ghi lõi - General Purpose Registers (R0 - R12)

> Ghi chú:Đều là cách thanh ghi 32bit

---

### Công dụng

- [xử lý các dữ liệu tính toán .... ]
- [ R0, R1, R2, R3: Là 4 thanh ghi "tiền tuyến". Chuyên dùng để truyền tham số vào hàm và trả về kết quả từ hàm.]
- [ R4 đến R11: Là các thanh ghi "hậu phương". Dùng để lưu các biến cục bộ lâu dài của hàm.]
- [ ]

---

### Ví dụ

```c
// Biến toàn cục nằm ở SRAM (Vùng .data)
int trang_thai_led = 0; 

void dao_trang_thai(void) {
    trang_thai_led = 1;
}

int main(void) {
    dao_trang_thai();
    while(1);
}
-> .s
; ĐỊA CHỈ TRONG FLASH         MÃ ASSEMBLY CỦA CPU

; --- HÀM DAO_TRANG_THAI ---
0x08000100                  dao_trang_thai:
0x08000100  LDR      R1, =0x20000004 ; Lệnh A: Nạp địa chỉ của biến 'trang_thai_led' vào R1
0x08000104  MOV      R2, #1          ; Lệnh B: Nạp giá trị 1 vào R2
0x08000106  STR      R2, [R1]        ; Lệnh C: Ghi giá trị từ R2 vào ô nhớ RAM có địa chỉ ở R1
0x08000108  BX       LR              ; Lệnh D: Quay về hàm main

; --- HÀM MAIN ---
0x08000110                  main:
0x08000110  BL       dao_trang_thai  ; Lệnh E: Gọi hàm dao_trang_thai
0x08000114  B        main            ; Lệnh F: Nhảy ngược lại chính nó while(1)
```

CPU sử dụng Register như thế nào?
- Kiến trúc Load-Store (LDR/STR): CPU không thể tính toán trực tiếp trên RAM. Muốn xử lý biến, bắt buộc phải: LDR (bốc từ RAM/Flash lên thanh ghi lõi) -> Xử lý trên thanh ghi -> STR (cất từ thanh ghi về lại RAM).

    + Lí do: 1 câu lệnh  máy có tối đa 32bit khôgn thể lưu trực tiếp MOV [0x20000004], #1 để nạp thẳng số 1 vào RAM cho nhanh mà (địa chỉ đã 32bit rồi còn các lệnh mov ... nữa)

- Sự thông minh của Compiler: Nó liên tục tối ưu hóa dựa trên "tuổi thọ" của biến. Biến xài tạm $\rightarrow$ R0-R3. Biến xài lâu dài $\rightarrow$ R4-R12 hoặc cất vào Stack.

- Bản chất của PC và LR: PC là vô tri, luôn đi thẳng thời gian thực. BL là lệnh gọi hàm $\rightarrow$ vừa bắt PC nhảy đi, vừa bắt LR giữ lại địa chỉ kế tiếp để làm bản đồ quay về.
> Ghi chú:Từ khoá volatile trong ide có cờ Os nên sẽ tối ưu lưu thằng giá trị trong thanh ghi lõi mà không dùng các lệnh ldr , mov str để liên tục cập nhật giá trị tại sram. 

---

# 3. Special Registers

---

## R13 - Stack Pointer (SP)

### Khái niệm:
- Là thanh ghi lõi giữ số địa chỉ RAM của đỉnh Stack. Trong Thread Mode có thể chọn vỏ R13 trỏ vào MSP hoặc PSP bằng cách gạt công tắc bit SPSEL trong thanh ghi CONTROL. Trong Handler Mode (Ngắt) phần cứng ép buộc vỏ R13 phải nối với MSP.

> Ghi chú:

---

### Vai trò


## R14 - Link Register (LR)
### Khái niệm
- Là thanh ghi giúp lưu trữ địa chỉ cần thực hiện kế tiếp, CPU có thể quay lại thực thi sau khi gọi hàm con, ngắt .
> Ghi chú:Khi dùng lệnh B main thì thanh ghi không thay đổi , chỉ khi có lệnh BL thì thanh ghi LR mới được kích hoạt.

---

### Khi gọi hàm

```c
foo();
```

LR sẽ lưu địa chỉ của hàm kế tiếp, khi kết thúc hàm foo  thực hiện xong câu lệnh cuối cùng là BX LR (Branch and Exchange to LR) $\rightarrow$ CPU sẽ "bốc" giá trị đang được bảo vệ an toàn trong LR nạp ngược lại vào PC

> Ghi chú:

---

## R15 - Program Counter (PC)

### Khái niệm
- Thanh ghi R15 (PC) được gọi là Con trỏ lệnh. Đây là thanh ghi quyền lực nhất quyết định CPU đang làm gì ở thời gian thực.

> Ghi chú:

---

### Vai trò
- PC luôn luôn lưu trữ địa chỉ của câu lệnh tiếp theo trong bộ nhớ FLASH mà CPU chuẩn bị bốc về để giải mã và thực thi.
- Ở trạng thái bình thường mỗi khi thực hiện xong 1 câu lệnh địa chỉ sẽ dược cộng 2/4 byte vào thanh ghi PC nhớ đó mới cso thể thực thi câu lệnh tiếp theo
- Khi hàm while/for hay BL cpu sẽ đè 1 địa chỉ mới vào thanh ghi PC và nhớ đó có thể quay vè hàm ban đầu.

> Ghi chú:

---

### Ví dụ

```text
Flash

0x08000000

↓

0x08000004

↓

0x08000008
```

PC thay đổi như thế nào?

---

## III. NHÓM THANH GHI TRẠNG THÁI CHƯƠNG TRÌNH (xPSR)
> *Bản chất là 1 thanh ghi 32-bit vật lý duy nhất trong Core, được chia làm 3 góc nhìn logic:*

### 1. APSR (Application Program Status Register)
* **Vị trí:** Các bit cao nhất `[31:28]`.
* **Nhiệm vụ:** Lưu cờ trạng thái kết quả của phép tính vừa thực hiện trong ALU.
* **4 Cờ Cốt Lõi:**
  * **N (Negative):** Bằng `1` nếu kết quả phép tính là **Số âm**.
  * **Z (Zero):** Bằng `1` nếu kết quả phép tính **Bằng đúng 0**.
  * **C (Carry):** Bằng `1` nếu phép tính có **Số dư mang đi** (Tràn số không dấu).
  * **V (Overflow):** Bằng `1` nếu phép tính bị **Tràn số có dấu**.
* **Ứng dụng:** Phục vụ 100% cho các lệnh rẽ nhánh điều kiện `if-else`, vòng lặp `for/while` (Lệnh `CMP` gạt cờ $\rightarrow$ Lệnh `BEQ/BNE` nhìn cờ để nhảy).

### 2. IPSR (Interrupt Program Status Register)
* **Vị trí:** Các bit thấp nhất `[8:0]`.
* **Nhiệm vụ:** Lưu **ISR_NUMBER** (Số hiệu ngắt/Exception) mà CPU đang thực thi thời gian thực.
  * Nếu `ISR_NUMBER == 0`: Chip đang chạy bình thường ở Thread Mode.
  * Nếu `ISR_NUMBER > 0`: Chip đang bận xử lý một hàm ngắt khẩn cấp.
* **Ứng dụng:** Giúp hệ điều hành (RTOS) nhận biết Core có đang bận xử lý ngắt hay không để điều phối Task, và giúp lập trình viên Debug khi chip bị sập (`HardFault` tương ứng với số hiệu `3`).

### 3. EPSR (Execution Program Status Register)
* **Nhiệm vụ cốt lõi:** Quản lý trạng thái thực thi lệnh.
* **Bit T (Thumb State - Bit 24):** Lõi Cortex-M bắt buộc bit này **luôn luôn bằng 1** để chạy tập lệnh Thumb. Nếu bit T vô tình bị xóa về `0`, CPU lập tức kích hoạt ngắt báo tử `UsageFault` để khóa chip.
* **Ứng dụng:** Giải thích tại sao địa chỉ hàm lưu trong `LR` hay `PC` luôn là số lẻ (Ví dụ `0x08000177`). Bit lẻ thừa ra này chính là để nạp vào bit T của EPSR, đảm bảo CPU luôn chạy ở chế độ Thumb Mode.

💡 *Mẹo đọc/ghi dòng PSR:* Phải dùng câu lệnh đặc quyền: `MRS R0, XPSR` (Đọc ra) và `MSR XPSR, R0` (Ghi vào).

# 5. CONTROL Register

## Khái niệm

> Ghi chú: XEM LẠI DAY03 >.<

---

## Liên hệ với bài trước

Thread Mode

↓

CONTROL Register

↓

Privileged / Unprivileged

---

## Các bit quan trọng

| Bit | Ý nghĩa |
|------|----------|
| nPRIV | |
| SPSEL | |
| FPCA | |

---

# 6. Luồng hoạt động của CPU

Ví dụ

```c
foo();
```

CPU thay đổi Register như thế nào?

```text
PC

↓

LR

↓

SP

↓

R0-R3

↓

Return
```

> Ghi chú:

---

# 7. Khi Interrupt xảy ra

CPU tự động làm gì?

- [ ]
- [ ]
- [ ]
- [ ]

Register nào được lưu xuống Stack?

> Ghi chú:

---

# 8. Liên hệ với Startup Code

Startup Code khởi tạo Register nào?

> Ghi chú:

---

# 9. Liên hệ với Bootloader

Bootloader thay đổi Register nào?

> Ghi chú:

---

# 10. Liên hệ với RTOS

RTOS cần lưu Register nào khi Context Switch?

> Ghi chú:

---

# 📝 Cheat Sheet

```text
General Purpose

R0-R12
│
└── Biến tạm
    Tham số
    Kết quả

--------------------------

Special Register

R13 → SP

R14 → LR

R15 → PC

--------------------------

System Register

PSR

CONTROL
```

---

# 📌 Quan hệ giữa các Register

```text
main()

↓

PC

↓

Instruction

↓

ALU

↓

R0-R12

↓

SP

↓

Memory
```

---

# ❓ Câu hỏi cần tự trả lời sau bài học

## Register

- Register khác RAM ở điểm nào?
- Vì sao Register nhanh hơn RAM?
- CPU có bao nhiêu General Register?
- Khi nào CPU dùng R0-R12?

---

## SP

- SP là gì?
- Stack Pointer luôn trỏ tới đâu?
- Vì sao gọi hàm phải thay đổi SP?

---

## LR

- LR lưu thông tin gì?
- Vì sao gọi hàm xong CPU quay lại đúng vị trí?

---

## PC

- PC dùng để làm gì?
- Vì sao thay đổi PC thì chương trình nhảy sang chỗ khác?

---

## PSR

- PSR lưu trạng thái gì?
- Cờ Zero là gì?
- Cờ Carry là gì?

---

## CONTROL

- CONTROL liên quan gì tới Thread Mode?
- CONTROL liên quan gì tới Privileged?
- Bit nPRIV có ý nghĩa gì?
- Bit SPSEL có ý nghĩa gì?

---

# 📌 Tổng kết

> Viết lại bằng lời của chính mình

....................................................................

....................................................................

....................................................................

....................................................................