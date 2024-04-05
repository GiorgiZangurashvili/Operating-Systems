#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(2, "Too few arguments\n");
        exit(1);
    }

    char* exec_args[MAXARG];
    for(int i = 0; i < argc - 1; i++){
        exec_args[i] = argv[i + 1];
    }

    char buf;
    char* param = malloc(512);
    int curr_index = 0;
    exec_args[argc - 1] = param;
    while(read(0, &buf, 1) != 0){
        if(buf == '\n'){
            param[curr_index] = '\0';

            int pid = fork();

            if(pid == 0){
                exec(exec_args[0], exec_args);
                exit(0);
            }else{
                wait((int*)0);
            }
            memset(param, 0, 512);
            curr_index = 0;
        }else if(buf == ' '){
            param[curr_index] = '\0';
            curr_index++;
        }else{
            param[curr_index] = buf;
            curr_index++;
        }
    }
    free(param);

    exit(0);
}