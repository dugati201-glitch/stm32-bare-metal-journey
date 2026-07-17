#include "stm32f10x.h"                  // Device header

// Hàm thu?n Assembly (Embedded Assembler) c?a ARMCC 5
__asm void Switch_to_PSP(void){
    // 1. S? d?ng EQU (ho?c .equ) d? khai báo h?ng s? cho Trình biên d?ch Assembly
STACK_MSP_END   EQU  0x20004E00  // Ð?nh nghia d?a ch? tr?c ti?p ? dây
    
    // 2. Th?c thi các l?nh Assembly chuy?n d?i Stack
    LDR R0, =STACK_MSP_END
    MSR PSP, R0
    
    MRS R0, CONTROL
    ORR R0, R0, #2
    MSR CONTROL, R0
    
    ISB
    BX LR                        // Thoát hàm, quay l?i main
}

int main(){
    Switch_to_PSP();
    while(1);
}