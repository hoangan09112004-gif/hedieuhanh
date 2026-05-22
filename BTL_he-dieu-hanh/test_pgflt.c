#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    printf("======================================\n");
    printf("[User] Bat dau test Paging Fault...\n");
    printf("[User] Chuan bi ghi vao dia chi NULL (0x0)\n");
    printf("======================================\n");

    int *p = (int *)0x0; 
    *p = 100; // Cố tình GHI vào vùng cấm (Gây ra Store Page Fault)

    printf("[User] Khong bao gio in ra duoc dong nay!\n"); 
    exit(0);
}
