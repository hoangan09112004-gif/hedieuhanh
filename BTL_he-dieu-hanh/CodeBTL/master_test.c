#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Ham thuc thi kich ban T2
void run_t2(char *target_prog) {
    printf("\n--- Bat dau T2: 3 tien trinh chay [%s] cung luc ---\n", target_prog);
    int num_processes = 3;
    
    for(int i = 0; i < num_processes; i++) {
        if(fork() == 0) {
            char *args[] = {target_prog, 0};
            exec(target_prog, args);
            exit(1); 
        }
    }
    
    // Cha cho 3 con bi kill xong
    for(int i = 0; i < num_processes; i++) {
        wait(0);
    }
    printf("--- Ket thuc T2: Shell van song va hoat dong tot! ---\n\n");
}

// Ham thuc thi kich ban T3
void run_t3(char *target_prog) {
    printf("\n--- Bat dau T3: Tien trinh loi [%s] xen ke tien trinh binh thuong ---\n", target_prog);
    
    // Nhanh 1: Sinh ra loi
    if(fork() == 0) {
        char *args[] = {target_prog, 0};
        exec(target_prog, args);
        exit(1);
    }
    
    // Nhanh 2: Tien trinh song khoe
    if(fork() == 0) {
        for(int i = 1; i <= 3; i++) {
            printf("[Tien trinh Binh thuong] Dang lam viec (buoc %d)...\n", i);
            
            // Tao do tre gia lap thay cho sleep() de khong bi loi bien dich
            for(volatile int delay = 0; delay < 20000000; delay++) {} 
        }
        printf("[Tien trinh Binh thuong] Hoan thanh an toan!\n");
        exit(0);
    }
    
    wait(0);
    wait(0);
    printf("--- Ket thuc T3 ---\n\n");
}

// Ham thuc thi kich ban T4
void run_t4(char *target_prog) {
    printf("\n--- Bat dau T4: Stress test 30 vong voi [%s] ---\n", target_prog);
    int rounds = 30;
    
    for(int i = 1; i <= rounds; i++) {
        if(fork() == 0) {
            char *args[] = {target_prog, 0};
            exec(target_prog, args);
            exit(1);
        }
        wait(0); // Cho kernel don dep roi moi di tiep
        
        if(i % 10 == 0) {
            printf("[System] Da hoan thanh %d vong lap...\n", i);
        }
    }
    printf("--- Ket thuc T4: He thong khong bi Kernel Panic! ---\n\n");
}

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Cach dung: master_test [kich_ban] [ten_bai_test]\n");
        printf("Vi du 1  : master_test t2 stackoverflow\n");
        printf("Vi du 2  : master_test t4 test_pgflt\n");
        exit(1);
    }

    char *scenario = argv[1];
    char *target_prog = argv[2];

    if(strcmp(scenario, "t2") == 0) {
        run_t2(target_prog);
    } else if(strcmp(scenario, "t3") == 0) {
        run_t3(target_prog);
    } else if(strcmp(scenario, "t4") == 0) {
        run_t4(target_prog);
    } else {
        printf("Loi: Kich ban '%s' khong hop le.\n", scenario);
    }
    
    exit(0);
}