#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int findLargestIndex(int *array, size_t n){
  if(n<=0)
    return -1;
  int largestIndex=0;
  for(size_t i=1;i<n;i++){
    if(array[i]>array[largestIndex]){
      largestIndex=i;
    }
  }
  return largestIndex;
}

int count(FILE * f){
  int num[26]={0};
  int c;
  while((c=fgetc(f))!=EOF){
    if(isalpha(c)){
      c=tolower(c);
      c -= 'a';
      num[c]++;
    }
  }
  return findLargestIndex(num,26);
}

int findkey(int n){
  return (n-4)>=0 ? (n-4) : (n-4+26); 
}

int main(int argc, char **argv) {
  if(argc !=2) {
    fprintf(stderr,"Usage: decreypt key inputFileNmae\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1],"r");
  if(f==NULL){
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  printf("%d\n",findkey(count(f)));
    if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
  



}
