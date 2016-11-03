#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int sumPrintDirFiles(char* path, int sub) {
  DIR* dir;
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
  closedir(dir);
}

int printDirRec(char* path, int sub) {
  DIR* dir;
  if ((dir=opendir(path))==NULL) { return -1; }
  struct dirent* dp;
  int i;
  int sum = 0;
  for (i=0; i<sub; i++) { printf("\t"); }
  printf("DIRECTORIES: \n");
  while ((dp=readdir(dir))!=NULL) {
    if (dp->d_type == DT_DIR) {
      for (i=0; i<sub; i++) { printf("\t"); }
      printf("\t%s\n", dp->d_name);
      if ((dp->d_name)[0] != '.') {
	sum += printDir(dp->d_name, sub+1);
      }
    }
  }
  closedir(dir);
  return sum;
}

int printDir(char* path, int sub) {
  DIR* dir;
  int sum = 0;
  if ((dir=opendir("."))==NULL) { return -1; }
  else {
    sum += printDirRec(path, sub);
    sum += sumPrintDirFiles(path, sub);
  }
  closedir(dir);
  return sum;
}

int main() {
  int sum = printDir(".",0);
  
  //ty william and grace for making right unit
  char units[4][4] = {" B"," KB"," MB"," GB"};
  int i=0;
  while (sum/1024 > 1) {
    sum = sum/1024;
    i++;
  }
  printf("\nTotal size of regular files: %d %s\n", sum, units[i]);
  return 0;
}
