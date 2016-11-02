#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
  DIR* dir;
  int sum = 0;
  struct dirent* dp;
  if ((dir=opendir("."))==NULL) {
    return -1;
  }
  while ((dp=readdir(dir))!=NULL) {
    if (dp->d_type == DT_DIR) { printf("DIRECTORY: %s\n",dp->d_name); }
    else {
      printf("%s\n", dp->d_name);
      struct stat buff;
      stat(dp->d_name, &buff);
      sum += buff.st_size;
    }
  }
  printf("\nFile size sum: %d\n", sum);
  closedir(dir);
  return 0;
}
