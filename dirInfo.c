#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
  DIR* dir;
  int sum = 0;
  struct dirent* dp;
  if ((dir=opendir("."))==NULL) {
    return -1;
  }
  
  while ((dp=readdir(dir))!=NULL) {
    if (dp->d_type == DT_DIR) { printf("DIRECTORY: %s\n",dp->d_name); }
  }
  dir=opendir(".");
  while ((dp=readdir(dir))!=NULL) {
    if (dp->d_type == DT_REG) {
      printf("%s\n", dp->d_name);
      struct stat buff;
      stat(dp->d_name, &buff);
      sum += buff.st_size;
    }
  }
  
  //ty william and grace
  char units[4][4] = {" B"," KB"," MB"," GB"};
  int i=0;
  printf("Size: %d bytes\n", sum);
  while (sum/1024 > 1) {
    sum = sum/1024;
    i++;
  }
  printf("\nFile size sum: %d %s\n", sum, units[i]);
  closedir(dir);
  return 0;
}
