#include "kernel/types.h"
#include "kernel/syscall.h"
#include "user/user.h"

int main(int argc, char** argv){
    int pipefds[2];
    char parent_buf;
    char child_buf;

    pipe(pipefds);
    int pid = fork();
    if(pid == 0){
        read(pipefds[0], &child_buf, 1);
        printf("%d: received ping\n", getpid());
        write(pipefds[1], &child_buf, 1);
        exit(0);
    }else if(pid > 0){
       write(pipefds[1], "B", 1);
       wait((int*) 0);
       read(pipefds[0], &parent_buf, 1);
       printf("%d: received pong\n", getpid());
       close(pipefds[0]);
       close(pipefds[1]);
       exit(0); 
    }else{
        printf("error occured\n");
        exit(1);
    }

    return 0;
}