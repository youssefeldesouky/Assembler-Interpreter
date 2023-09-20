#include "helper.h"

char * strdup(const char *s)
{
  size_t len = strlen (s) + 1;
  char *result = (char*) malloc (len);
  if (result == (char*) 0)
    return (char*) 0;
  return (char*) memcpy (result, s, len);
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
  for(; !isspace(s[i]); i++);
  s[i] = '\0';
  return s;
}