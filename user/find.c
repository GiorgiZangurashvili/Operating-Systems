#include "kernel/types.h"
#include "kernel/syscall.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

//copied important part from ls.c file
void recurseInDirs(char* path, char* name){
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_DEVICE:
  case T_FILE:
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      if(strcmp(de.name, name) == 0){
        printf("%s\n", buf);
      }
      p[DIRSIZ] = 0;
      recurseInDirs(buf, name);
    }
    break;
  }
  close(fd);
}

int main(int argc, char* argv[]){
    if(argc < 3) printf("Too few arguments\n");
    else if(argc > 3) printf("Too many arguments\n");

    recurseInDirs(argv[1], argv[2]);

    return 0;
}