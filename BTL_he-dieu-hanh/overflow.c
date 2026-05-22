#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Hàm đệ quy để làm tràn stack
void recurse(int n) {
    char dummy_array[512]; 
    dummy_array[0] = 'x';  

    // Lừa trình biên dịch bằng một điều kiện dừng giả để tránh lỗi infinite recursion
    if (n == 999999) {
        return;
    }

    // Lừa trình biên dịch bằng cách in giá trị mảng ra để tránh lỗi set but not used
    printf("Dang o do sau: %d (Ky tu: %c)\n", n, dummy_array[0]);
    
    recurse(n + 1);
}

int main(int argc, char *argv[]) {
    printf("Bat dau test co che Guard Page...\n");
    recurse(1);
    exit(0);
}
