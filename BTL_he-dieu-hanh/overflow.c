#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Hàm đệ quy để làm tràn stack
void recurse(int n) {
    char dummy_array[1024]; // Chiếm 1KB mỗi tầng đệ quy
    dummy_array[0] = n;     

    // Lấy dummy_array[0] ra in để GCC không báo lỗi "unused" nữa
    if (n % 5 == 0) {
        printf("Dang o do sau: %d (dummy = %d)\n", n, dummy_array[0]);
    }
    
    // Điều kiện dừng giả để vượt qua cờ biên dịch
    if (n > 100000) {
        return;
    }

    recurse(n + 1);
}

int main(int argc, char *argv[]) {
    printf("Bat dau test co che Guard Page (Stack Overflow)...\n");
    recurse(1);
    
    printf("Test that bai! Stack khong bi tran.\n"); 
    exit(0);
}

