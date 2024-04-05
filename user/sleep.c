#include "kernel/types.h"
#include "kernel/syscall.h"
#include "user/user.h"

int main(int argc, char** argv){
    if(argc <= 1){
        fprintf(2, "You should pass arguments\n");
        exit(1);
    }

    if(argc > 2){
        fprintf(2, "Too many arguments\n");
        exit(1);
    }

    sleep(atoi(argv[1]));
    exit(0);
}