# THỰC HÀNH DAY01 
## 🔥 THỬ THÁCH 1: Điều khiển Trình tối ưu hóa & Debug (Mức độ: Dễ)
Sếp giao cho bạn nhiệm vụ nạp code xuống một con chip STM32 đời cũ có bộ nhớ Flash cực kỳ nhỏ hẹp, đồng thời yêu cầu bạn phải chèn thêm thông tin để có thể cắm mạch debug (ST-Link) soi lỗi khi chip chạy.

**Yêu cầu** Bạn cần tinh chỉnh lại biến CFLAGS trong file Makefile hiện tại của bạn. Hãy viết lại dòng khai báo biến CFLAGS mới, trong đó kết hợp cờ tối ưu hóa dung lượng file ở mức nhỏ nhất và cờ bật tính năng chèn thông tin Debug.

## 🔥 THỬ THÁCH 2: Nâng cấp kịch bản tự động hóa Makefile (Mức độ: Trung bình)
Hiện tại file Makefile của bạn đang hoạt động rất tốt cho 1 file main.c. Bây giờ, dự án của bạn phát sinh thêm một file mã nguồn mới tên là gpio.c (chứa code cấu hình chân chip) đặt chung trong thư mục.

**Yêu cầu**: Bạn hãy sửa đổi hoặc viết lại toàn bộ nội dung file Makefile mới của bạn sao cho khi gõ lệnh make, hệ thống sẽ tự động dịch cả 2 file main.c và gpio.c thành main.o và gpio.o, sau đó liên kết (Linker) cả 2 file .o này lại để tạo ra file chạy program.bin cuối cùng.


(Gợi ý: Chú ý phần Dependencies - Đầu vào của bước Linker program.elf ).

## 🔥 THỬ THÁCH 3: Thám tử phân tích lỗi Hệ thống (Mức độ: Nâng cao)
Khi bạn đang làm việc nhóm, một người bạn cùng lớp gửi cho bạn một file kịch bản biên dịch bị lỗi hệ thống nghiêm trọng. Khi họ gõ lệnh make clean trên Terminal, thay vì xóa file rác thì Linux lại quăng ra lỗi sau:
make: *** [Makefile:22: clean] Error 1
Khi kiểm tra, bạn phát hiện ra trong thư mục của họ hoàn toàn không có file .i, .s, .o, .elf hay .bin nào cả (thư mục đang trống sạch sẽ).

**Yêu cầu**: Bằng kiến thức dòng lệnh Linux và Makefile đã học ngày hôm nay, bạn hãy giải thích tại sao lệnh rm -rf trong mục clean lại có thể gây ra lỗi dừng chương trình như vậy, và bạn sẽ sửa dòng lệnh rm -rf đó như thế nào để dù thư mục có trống rỗng thì gõ make clean vẫn chạy mượt mà không báo lỗi?