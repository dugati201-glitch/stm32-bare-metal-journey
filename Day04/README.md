🚨 KỊCH BẢN THỬ THÁCH: "NGÀY ĐẦU LÀM KERNEL"
Giả sử bạn đang tự tay viết một Hệ điều hành RTOS nhỏ. Hệ thống của bạn vừa mới khởi động xong, đang chạy trong hàm main() (Thread Mode).

Hiện tại, các thanh ghi đang có giá trị như sau:

MSP (Main Stack Pointer) = 0x20002000

PSP (Process Stack Pointer) = 0x20001000

Thanh ghi CONTROL đang có giá trị là 0x00000003 (tức là bit nPRIV = 1 và bit SPSEL = 1).

Thanh ghi PC đang trỏ ở địa chỉ 0x08000200 để thực thi câu lệnh tính toán bình thường.

⚡ SỰ KIỆN XẢY RA:
Đột nhiên, một người dùng nhấn nút trên kit STM32, kích hoạt một ngắt ngoại vi khẩn cấp (EXTI Exception). CPU lập tức bỏ dở câu lệnh tại main() và nhảy vào hàm ngắt EXTI0_IRQHandler().

🧠 CÂU HỎI DÀNH CHO BẠN:
Câu 1 (Về Quyền hạn & Chế độ lõi):
Khi CPU vừa bước chân vào câu lệnh đầu tiên bên trong hàm ngắt EXTI0_IRQHandler():

CPU đang chạy ở Chế độ lõi (Mode) nào?

Quyền hạn thực thi của CPU lúc này là gì (PAL hay NPAL)? Giá trị của bit nPRIV trong thanh ghi CONTROL lúc này có bị ảnh hưởng gì bởi giá trị cũ (1) ở hàm main không?

Câu 2 (Trò chơi tráo vỏ R13 - SP):
Ngay bên trong hàm ngắt EXTI0_IRQHandler(), trình biên dịch có sinh ra một câu lệnh: PUSH {R4, R5} (Cất dữ liệu R4, R5 vào ngăn xếp).

Theo bạn, phần cứng CPU lúc này sẽ lấy giá trị của MSP hay PSP để làm điểm tựa trỏ vào RAM thực hiện việc cất đồ này?

Địa chỉ RAM chính xác mà dữ liệu sẽ ghi vào sẽ quay quanh vùng 0x20002000 hay vùng 0x20001000?

Câu 3 (Soi kính hiển vi vào xPSR):
Nếu lúc này bạn bật trình gỡ lỗi (Debug Keil C) lên và quan sát thanh ghi trạng thái xPSR:

Phân vùng thanh ghi logic IPSR (các bit từ 0 đến 8) lúc này sẽ bằng 0 hay sẽ là một số hiệu lớn hơn 0? Tại sao?

Câu 4 (Kịch bản hiểm họa):
Trong lúc đang ở trong hàm ngắt, bạn (Kỹ sư hệ thống) vô tình viết một dòng lệnh Assembly nhằm gạt bit SPSEL trong thanh ghi CONTROL về lại 0 hòng ép hệ thống dùng MSP:

Theo luật chơi của ARM, câu lệnh can thiệp vào CONTROL này bên trong hàm ngắt (Handler Mode) có được CPU chấp nhận thực thi không? Và phần cứng ARM Cortex-M quy định như thế nào về việc dùng Stack bên trong Handler Mode?