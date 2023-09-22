#include "helper.h"

size_t get_word(const char *src, char *dst, size_t starting_idx, size_t dst_buffer_size){
  if(!src || !dst || !dst_buffer_size) return 0;
  size_t i = starting_idx;
  size_t j = 0;
  for(; isspace(src[i]); i++);
  for(; j < dst_buffer_size && src[i] && !isspace(src[i]); i++, j++){
      dst[j] = src[i];
  }
  dst[j] = '\0';
  return i;
}

int get_line(const char *src, char *dst, size_t* starting_idx, size_t dst_buffer_size){
  if(!src || !dst || !dst_buffer_size) return 0;
  size_t i = *starting_idx;
  size_t j = 0;
  bool in_comment = false;
  for(; j < dst_buffer_size && src[i] && src[i] != '\n'; i++){
    if(src[i] == ';') in_comment = true;
    if(!in_comment){
      dst[j++] = src[i];
    }
  }
  dst[j] = '\0';
  *starting_idx = i + 1;
  
  if(!src[i] || src[i] == EOF){
    return -1;
  }
  return j;
}

char * strdup(const char *s){
  size_t len = strlen (s) + 1;
  char *result = calloc(len, sizeof(char));
  if (!result)
    return NULL;
  return (char*)memcpy(result, s, len);
}

char *strtolower(char *s){
  for(size_t i = 0; i < strlen(s) && isalpha(s[i]); i++){
    s[i] = tolower(s[i]);
  }
  return s;
}

char *ltrim(char *s){
  char *ptr = s;
  int i = 0;
  for(;isspace(*ptr); ptr++);
  for(i = 0; *ptr; i++, ptr++){
    s[i] = *ptr;
  }
  s[i] = '\0';
  return s;
}

char *rtrim(char *s){
  int i = 0;
  for(i = 0; isspace(s[i]); i++);
  for(; s[i] && !isspace(s[i]); i++);
  s[i] = '\0';
  return s;
}

