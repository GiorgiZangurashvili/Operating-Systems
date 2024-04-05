#include "kernel/types.h"
#include "kernel/syscall.h"
#include "user/user.h"

void print_primes(int fds[]){
    int fds2[2];

    int first_num;
    read(fds[0], &first_num, sizeof(int));

    int pid = fork();
    int nums_read = 0;
    close(fds[1]);
    if(pid == 0){
        printf("prime %d\n", first_num);
        exit(0);
    }else{close(fds[1]);
        wait((int*)0);
        int buf;
        pipe(fds2);
        while(read(fds[0], &buf, sizeof(int)) != 0){
            nums_read++;
            if(buf % first_num != 0){
                write(fds2[1], &buf, sizeof(int));
            }
        }
        close(fds[0]);
        if(nums_read == 0) return;
        print_primes(fds2);
    }
}

int main(){
    int fds[2];

    pipe(fds);
    for(int i = 2; i <= 35; i++){
        write(fds[1], &i, sizeof(int));
    }

    print_primes(fds);
    exit(0);
}