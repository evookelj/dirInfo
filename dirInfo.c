#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int sumPrintDirFiles(DIR* dir, char* path, int sub) {
  int sum = 0;
  struct dirent* dp;
  if ((dir=opendir(path))==NULL) { return -1; }
  int i;
  for (i=0; i<sub; i++) { printf("\t"); }
  printf("REGULAR FILES: \n");
  while ((dp=readdir(dir))!=NULL) {
    if (dp->d_type == DT_REG) {
      i=0;
      for (i=0; i<sub; i++) { printf("\t"); }
      printf("\t%s\n", dp->d_name);
      struct stat buff;
      stat(dp->d_name, &buff);
      sum += buff.st_size;
    }
  }
  return sum;
}

int printDirRec(DIR* dir, int sub) {
  if ((dir=opendir("."))==NULL) { return -1; }
  struct dirent* dp;
  int i, sum;
  for (i=0; i<sub; i++) { printf("\t"); }
  printf("DIRECTORIES: \n");
  while ((dp=readdir(dir))!=NULL) {
    if (dp->d_type == DT_DIR) {
      for (i=0; i<sub; i++) { printf("\t"); }
      printf("\t%s\n", dp->d_name);
      sum = sumPrintDirFiles(opendir("."), ".", sub+1);
    }
  }
  return sum;
}

int main() {
  DIR* dir;
  struct dirent* dp;
  int sum = 0;
  if ((dir=opendir("."))==NULL) { return -1; }
  while ((dp=readdir(dir)) !=NULL) {
    
  }

  printDirRec(dir,0);
  sum = sumPrintDirFiles(dir, "." ,0);
  
  //ty william and grace for making right unit
  char units[4][4] = {" B"," KB"," MB"," GB"};
  int i=0;
  while (sum/1024 > 1) {
    sum = sum/1024;
    i++;
  }
  printf("\nTotal size of regular files: %d %s\n", sum, units[i]);
  closedir(dir);
  return 0;
}
