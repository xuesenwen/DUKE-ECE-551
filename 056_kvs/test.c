#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>
struct _kvpair_t { 
  //DEFINE ME!
  char *key;
  char *value;
};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t { 
  //DEFINE ME!
  kvpair_t **pairs;
  int numPairs;
};
typedef struct _kvarray_t kvarray_t;

void stripNewline(char *str){
  char *p=strchr(str,'\n');
  if(p!=NULL){
    *p='\0';
  }
}

kvpair_t *splitOnepair(char *str){
  kvpair_t *p = malloc(sizeof(*p));
  char *f = strtok(str, "=");
  if(f == NULL){
    perror("Invalid first type of input file");
    return NULL;
  }
  p->key =malloc(strlen(f)* sizeof(*p->key));
  p->key = f;
  char *l = strtok(NULL,"\0");
  p->value = malloc(strlen(l)* sizeof(*p->value));
  p->value = l;
  return p;
}

int main(int argc, char ** argv){
  char *string = "Will Luc Picard=Captain";
  kvpair_t *t=splitOnepair(string);
printf("%s\n",t->key);
printf("%s\n",t->value);
return 0;
}
