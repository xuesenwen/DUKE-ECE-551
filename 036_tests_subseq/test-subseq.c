#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array,size_t n);

void run_check(int * array,size_t n,size_t expected_ans){
  if(expected_ans!=maxSeq(array,n)){
    exit(EXIT_FAILURE);
  }
}

int main(void){
   int a1[6]={0,2,4,6,8,10};
   int a2[6]={0,0,0,0,0,0};
  
    int a5[1]={0};
    int a12[0];
    run_check(a12,0,0);
  run_check(a1,6,6);
  run_check(a2,6,1);
  
   run_check(a5,1,1);
  
  int a10[6]={0,2,4,4,6,8};
  run_check(a10,6,3);

  int a3[10]={0,2,1,2,-2,1,2,4,6,8};
    run_check(a3,10,6);
    int a4[]={2,3,4,5,6,7,8,7};
    run_check(a4,8,7);

     int a9[13]={1,2,1,0,1,2,1,0,-1,1,2,1,0};
     run_check(a9,13,3);

     return EXIT_SUCCESS;
  
  
  
}
