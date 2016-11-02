#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

int listDirFiles() {
  DIR* dir;
  struct dirent* dp;
  if ((dir=opendir("."))==NULL) {
    return -1;
  }
  while ((dp=readdir(dir))!=NULL) {
    printf("%s\n", dp->d_name);
  }
  closedir(dir);
}

int main() {
  int ret = listDirFiles();
  return 0;
}
