#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    printf("======================================\n");
    printf("[User] Bat dau test Paging Fault...\n");
    printf("[User] Chuan bi ghi vao dia chi NULL (0x0)\n");
    printf("======================================\n");

    // Bắt buộc phải dùng 'volatile' để ngăn GCC tối ưu hóa và xóa mất lệnh này
    volatile int *p = (int *)0x0; 
    *p = 100; // Cố tình GHI vào vùng cấm (Gây ra Store Page Fault mã 15)

    // Nếu lệnh exit(-1) trong trap.c hoạt động, tiến trình sẽ chết ngay tại dòng trên.
    printf("[User] Test that bai! Kernel da bo lot loi.\n"); 
    exit(0);
}
