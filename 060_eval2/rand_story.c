#include "rand_story.h"
#include <string.h>
#include <stdio.h>

int error(char *s){
  perror(s);
  exit(EXIT_FAILURE);
}

int checkLine(char *line){
  size_t i = 0;
  size_t num = 0;
  while(line[i] != '\n'){
    if(line[i] == '_'){
      num++;
    }
    i++;
  }
  if((num % 2) != 0){
    error("invalid input file: each blank must begin and end with an underscore '_' on the same line");
  }
  return EXIT_SUCCESS;
}

char *replace(char *s, char *s1,const char *s2){
  char *f = strstr(s,s1);
  if(f != NULL){
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    if(len1 != len2){
      memmove(f + len2, f + len1, strlen(f) + 1 - len1);
    }
    memcpy(f, s2, len2);
  }
  return s;
}

void replaceLine(char *line){
  size_t i = 0;
  int flag = 0;
  size_t s = 0;
  size_t e = 0;
  //char *cur;
  //cur = strchr(line,'_');
  while(line[i] != '\n'){
    if(line[i] == '_' && flag == 0){
      s = i;
      flag = 1;
      i++;
    }
    else if(line[i] == '_' && flag == 1){
      e = i;
      flag = 0;
      char s1[e - s + 1 + 1];
      strncpy(s1, line + s, e - s + 1);
      s1[e - s + 1] = '\0';
      const char *s2 = chooseWord("verb",NULL);
      line = replace(line, s1, s2);
      i = s + strlen(s2);
    }
    else{
      i++;
    }
  }
}

void freeLines(char **lines, size_t i){
  for(size_t j = 0; j < i; j++){
    free(lines[j]);
  }
  free(lines);
}

void parseLine(FILE *f){
  char **lines  = NULL;
  char *cur = NULL;
  size_t sz;
  size_t i = 0;
  while(getline(&cur, &sz, f) >= 0){
    lines = realloc(lines, (i+1) * sizeof(*lines));
    checkLine(cur);
    lines[i] = cur;
    cur = NULL;
    i++;
  }
  free(cur);
  for(size_t j = 0; j < i; j++){
    replaceLine(lines[j]);
    printf("%s",lines[j]);
  }
  freeLines(lines, i);
}

void stripNewline(char * str){
  char * p = strchr(str, '\n');
  if(p != NULL){
    *p = '\0';
  }
}

/*
bool checkColon(char * line){
  size_t i = 0;
  size_t n = 0;
  while(line[i] != '\n'){
    if(line[i] == ':'){
      n++;
    }
    i++;
  }
  if(n>=1){
    return true;
  }
  else{
    return false;
  }
}
*/

catarray_t * createCatarray(void){
  catarray_t * catarray = malloc(sizeof(*catarray));
  catarray->arr = NULL;
  catarray->n = 0;
  return catarray;
}

void addNewCategory(catarray_t * c, char * name, char * word){
  c->n++;
  c->arr = realloc(c->arr, c->n * sizeof(*c->arr));
  // c->arr[c->n - 1] = malloc(sizeof(*c->arr[c->n - 1]));
  c->arr[c->n - 1].name = strdup(name);
  c->arr[c->n - 1].words = malloc(sizeof(*c->arr[c->n - 1].words));
  c->arr[c->n - 1].words[0] = strdup(word);
  c->arr[c->n - 1].n_words = 1;
}

void addWord(catarray_t * c, char * name, char * word){
  size_t flag = 1;
  for(size_t i = 0; i < c->n; i++){
    if(strcmp(name,c->arr[i].name) == 0){
      c->arr[i].n_words++;
      c->arr[i].words = realloc(c->arr[i].words, c->arr[i].n_words * sizeof(*c->arr[i].words));
      c->arr[i].words[c->arr[i].n_words - 1] = strdup(word);
      flag = 0;
      break;
    }
  }
  if(flag){
    addNewCategory(c, name, word);
  }
}

void freeCatarray(catarray_t * c){
  for(size_t i = 0; i < c->n; i++){
    for(size_t j = 0; j < c->arr[i].n_words; j++){
      free(c->arr[i].words[j]);
    }
    free(c->arr[i].name);
    free(c->arr[i].words);
    //free(c->arr[i])
  }
  free(c->arr);
  free(c);
}


void readFile(FILE * f){
  catarray_t *ans = createCatarray();
  char *cur = NULL;
  size_t sz;
  //size_t i = 0;
  while(getline(&cur, &sz, f) >= 0){
    //char * c = strchr(cur, ':');
    char * p = strchr(cur,':');
    if(p == NULL){
      error("Each line of the input file must have a colon!");
    }
    char s1[p - cur + 1];
    strncpy(s1, cur, p - cur);
    s1[p - cur] = '\0';
      
    char s2[strlen(p + 1)];
    strcpy(s2, p + 1);
    stripNewline(s2);
    addWord(ans, s1, s2);
  }
  free(cur);
  printWords(ans);
  freeCatarray(ans);
}
/*
void freeCatarray(catarray_t c){
  for(size_t i = 0; i < c->n; i++){
    for(size_t j = 0; j < c->arr[i]->n_words; j++){
      free(c->arr[i]->words[j]);
    }
    free(c->arr[i]->name);
    free(c->arr[i]->words);
    //free(c->arr[i]);
    free(c->arr);
  }
  free(c);
  
}
*/

//update

/*char *replace(char *s, char *s1,const char *s2){
  char *f = strstr(s,s1);
  if(f != NULL){
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    if(len1 != len2){
      memmove(f + len2, f + len1, strlen(f) + 1 - len1);
    }
    memcpy(f, s2, len2);
  }
  return s;
  }*/
/*
void replaceLinestep3(char *line, catarray_t * cats, char ** ref, long int numReplace){
  size_t i = 0;
  int flag = 0;
  size_t s = 0;
  size_t e = 0;
  //long int numReplace = 0;
  char ** ref = NULL;
  //char *cur;
  //cur = strchr(line,'_');
  while(line[i] != '\n'){
    if(line[i] == '_' && flag == 0){
      s = i;
      flag = 1;
      i++;
    }
    else if(line[i] == '_' && flag == 1){
      e = i;
      flag = 0;
      char s1[e - s + 1 + 1];
      strncpy(s1, line + s, e - s + 1);
      s1[e - s + 1] = '\0';
      //char *ss = "kule";
      //printf("%s\n",ss);
      printf("%s:", s1);
      const char *s2 = checkChoose(s1, ref, numReplace, cats);
      printf("chossen string:%s\n",s2);
      //char *ss = "kule";
      //printf("%s\n",ss);
      line = replace(line, s1, s2);
      //  printf("%s\n",line);
      //trace
      numReplace++;
      printf("numReplace:%ld\n", numReplace);
      ref = realloc(ref, numReplace * sizeof(*ref));
      ref[numReplace - 1] = strdup(s2);
      i = s + strlen(s2);
      printf("store:%s\n",ref[numReplace - 1]);
    }
    else{
      i++;
    }
  }
}

const char *checkChoose(char *s,char ** ref, long int numReplace, catarray_t * cats){
  char c[strlen(s) - 1];
  strncpy(c, s + 1, strlen(s) - 2);
  c[strlen(s) - 2] = '\0';
  printf("%s\n",c);
  char * e;
  long int num = strtol(c, &e, 10);
  printf("obtained long int:%ld\n",num);
  printf("e-c: %ld strlen(c)-1: %ld",e - c,strlen(c) - 1);
  if((e - c) == (strlen(c))){
    if(num <= numReplace){
      //const char * ans = ref[numReplace - num];
      //printf("%s","kule");
      return ref[numReplace - num];
    }
    else{
      error("reference number too large");
    }
  }
    return chooseWord(c, cats);
}


void parseLineStep3(FILE *f, catarray_t * cats){
  long int numReplace = 0;
  char ** ref = NULL;
  char **lines  = NULL;
  char *cur = NULL;
  size_t sz;
  size_t i = 0;
  while(getline(&cur, &sz, f) >= 0){
    lines = realloc(lines, (i+1) * sizeof(*lines));
    checkLine(cur);
    lines[i] = cur;
    cur = NULL;
    i++;
  }
  free(cur);
  //char *s = "kule";
  //printf("%s\n",s);
  for(size_t j = 0; j < i; j++){
    replaceLinestep3(lines[j], cats);
    //char *s = "kule";
    //printf("%s\n",s);
    printf("%s",lines[j]);
  }
  freeLines(lines, i);
}

void readFileStep3(FILE * f, FILE * w){
  catarray_t *ans = createCatarray();
  char *cur = NULL;
  size_t sz;
  //size_t i = 0;
  while(getline(&cur, &sz, f) >= 0){
    //char * c = strchr(cur, ':');
    char * p = strchr(cur,':');
    if(p == NULL){
      error("Each line of the input file must have a colon!");
    }
    char s1[p - cur + 1];
    strncpy(s1, cur, p - cur);
    s1[p - cur] = '\0';
      
    char s2[strlen(p + 1)];
    strcpy(s2, p + 1);
    stripNewline(s2);
    addWord(ans, s1, s2);
  }
  free(cur);
  //printWords(ans);
  //char *s = "kule";
  //printf("%s\n",s);
  parseLineStep3(w, ans);
  //printWords(ans);
  //freeCatarray(ans);
}
*/


reference_t * createNewRef(void){
  reference_t *ref = malloc(sizeof(*ref));
  ref->word = NULL;
  ref->n_words = 0;
  return ref;
}

void addRefWord(reference_t * ref, const char* word){
  ref->n_words++;
  ref->word = realloc(ref->word, ref->n_words * sizeof(*ref->word));
  ref->word[ref->n_words - 1] = word;
}

void freeRef(reference_t *ref){
  //for(size_t i = 0; i < ref->n_words; i++){
    
  //}
  free(ref->word);
  free(ref);
}

void replaceLinestep3(char *line, catarray_t * cats, reference_t * ref){
  size_t i = 0;
  int flag = 0;
  size_t s = 0;
  size_t e = 0;
  //char *cur;
  //cur = strchr(line,'_');
  while(line[i] != '\n'){
    if(line[i] == '_' && flag == 0){
      s = i;
      flag = 1;
      i++;
    }
    else if(line[i] == '_' && flag == 1){
      e = i;
      flag = 0;
      char s1[e - s + 1 + 1];
      strncpy(s1, line + s, e - s + 1);
      s1[e - s + 1] = '\0';
      //char *ss = "kule";
      //printf("%s\n",ss);
      // printf("%s:", s1);
      const char *s2 = checkChoose(s1, ref, cats);
      //printf("chossen string:%s\n",s2);
      //char *ss = "kule";
      //printf("%s\n",ss);
      line = replace(line, s1, s2);
      //  printf("%s\n",line);
      //trace
      //numReplace++;
      //printf("numReplace:%ld\n", numReplace);
      //ref = realloc(ref, numReplace * sizeof(*ref));
      //ref[numReplace - 1] = strdup(s2);
      addRefWord(ref, s2);
      i = s + strlen(s2);
      //printf("store:%s\n",ref[numReplace - 1]);
    }
    else{
      i++;
    }
  }
}

const char *checkChoose(char *s, reference_t *ref, catarray_t * cats){
  char c[strlen(s) - 1];
  strncpy(c, s + 1, strlen(s) - 2);
  c[strlen(s) - 2] = '\0';
  //printf("%s\n",c);
  char * e;
  long int num = strtol(c, &e, 10);
  //printf("obtained long int:%ld\n",num);
  //printf("e-c: %ld strlen(c)-1: %ld",e - c,strlen(c) - 1);
  if((e - c) == (strlen(c))){
    if(num <= ref->n_words){
      //const char * ans = ref[numReplace - num];
      //printf("%s","kule");
      return ref->word[ref->n_words - num];
    }
    else{
      error("reference number too large");
    }
  }
    return chooseWord(c, cats);
}


void parseLineStep3(FILE *f, catarray_t * cats, reference_t *ref){
  char **lines  = NULL;
  char *cur = NULL;
  size_t sz;
  size_t i = 0;
  while(getline(&cur, &sz, f) >= 0){
    lines = realloc(lines, (i+1) * sizeof(*lines));
    checkLine(cur);
    lines[i] = cur;
    cur = NULL;
    i++;
  }
  free(cur);
  //char *s = "kule";
  //printf("%s\n",s);
  for(size_t j = 0; j < i; j++){
    replaceLinestep3(lines[j], cats, ref);
    //char *s = "kule";
    //printf("%s\n",s);
    printf("%s",lines[j]);
  }
  freeLines(lines, i);

}

void readFileStep3(FILE * f, FILE * w){
  reference_t *ref = createNewRef();
  catarray_t *ans = createCatarray();
  char *cur = NULL;
  size_t sz;
  //size_t i = 0;
  while(getline(&cur, &sz, f) >= 0){
    //char * c = strchr(cur, ':');
    char * p = strchr(cur,':');
    if(p == NULL){
      error("Each line of the input file must have a colon!");
    }
    char s1[p - cur + 1];
    strncpy(s1, cur, p - cur);
    s1[p - cur] = '\0';
      
    char s2[strlen(p + 1)];
    strcpy(s2, p + 1);
    stripNewline(s2);
    addWord(ans, s1, s2);
  }
  free(cur);
  //printWords(ans);
  //char *s = "kule";
  //printf("%s\n",s);
  parseLineStep3(w, ans, ref);
  //printWords(ans);
  freeCatarray(ans);
  freeRef(ref);
}
