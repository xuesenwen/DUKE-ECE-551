#include<stdio.h>
#include<stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y,unsigned expected_ans){
  if(expected_ans!=power(x,y)){
    exit(EXIT_FAILURE);
  }
}

int main(void){
  run_check(0,0,1);
  run_check(1,1,1);
  run_check(1,2,1);
  run_check(2,0,1);
  run_check(2,1,2);
  run_check(2,4,16);
  run_check(3,3,27);
  run_check(0,1,0);
  run_check(0,2,0);
  run_check(5,3,125);
  run_check(2,2,4);
  run_check(5,2,25);
  run_check(2,5,32);
  run_check(2,6,64);
  run_check(0,15,0);
   run_check(100,2,10000);
  run_check(2,2,4);
  run_check(1000,3,1000000000);
  
  /* run_check(0,0,1);
    run_check(1,1,1);
  run_check(2,1,1);
  run_check(0,2,1);
  run_check(1,2,2);
   run_check(4,2,16);
  run_check(3,3,27);
  run_check(-1,-1,0);
  run_check(1.2,1.1,0);
  run_check(1,0,0);
  run_check(2,0,0);
  run_check(3,5,125);
  run_check(2,2,4);*/
  return EXIT_SUCCESS;
}
