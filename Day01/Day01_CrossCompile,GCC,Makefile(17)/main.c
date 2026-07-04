#define LED_PIN   13
#define SUCCESS   1

int main(void) {
    int status = LED_PIN; // Gán giá trị macro
    
    // Vòng lặpơ vô hạn mô phỏng vi điều khiển
    while(SUCCESS) {
        status = !status;
    }
    return 0;
}