
#include "myUtils.h"

char * FindNextNonWhitespace( char *str){
  if(str[0] == '\0' || str == NULL)
    return NULL;
    
  uint32_t i = 0;
  while(isspace(str[i])){
    if(str[++i]=='\0')
      return NULL;
  }
  return &str[i];
}

char * FindNextPunctuation( char *str){
  if(str[0] == '\0')
    return NULL;
   
  uint32_t i = 0;
  while(str[i] != ':' && str[i] != ';'){
    if(str[++i] == '\0')
      return NULL;
  }
  
  return &str[i];
}


char * FindLastCharOfArgument( char *str){
  if(str == NULL || str[0] == '\0')
    return str;

  uint32_t i = 0;
  while(str[i] != ':' && str[i] != ';' && str[i] != '\n'){
    if(str[++i] == '\0')
      return &str[i-1];
  }
  return &str[i-1];
}

char * FindNextWord( char *str){
  if(str == NULL || str[0] == '\0'){
    return NULL;
  }
  
  uint32_t i = 0;
  while(str[i]<'A' || str[i]>'z'){
    if(str[++i] == '\0')
      return NULL;
  }
  return &str[i];
}

char * FindNextComma(char *str){
  if(str == NULL || str[0] == '\0'){
    return NULL;
  }
  
  uint32_t i = 0;
  while(str[i] != ','){
    if(str[++i] == '\0')
      return NULL;
  }
  return &str[i];
}

uint32_t WordSizeIs(const char *str){
  uint8_t i = 0;
  while(str[i] >= 'A' && str[i] <= 'z'){
    ++i;
  }
  return i;
}

uint32_t ReadPositiveNumber(const char *str){
  char tmp[20];
  uint8_t i=0, j=0;

  //Encontra primeiro algarismo
  while(str[i]<'0' || str[i]>'9'){
    if(str[++i] == '\0')
      return -1;
  }

  while((str[i] >= '0' && str[i] <= '9') && j<20){
    tmp[j++] = str[i++];    
  }
  tmp[j] = '\0';
  
  if(j>0)
    return strtoul(tmp,NULL, 10);
  else
    return -1;
}

bool WordIs(const char *wordToIdentify, const char *receivedString){
  if(wordToIdentify == NULL || receivedString == NULL){
    return false;
  }
  
  int i = 0;
  char c1, c2;
  int len = strlen(wordToIdentify);
  do{
    // Se forem diferentes compara novamente ignorando maiusculas e minusculas
    // Retorna zero na primeira diferenÃ§a detectada
    if(wordToIdentify[i] != receivedString[i]){ 
      if(wordToIdentify[i] >= 'A' && wordToIdentify[i] <= 'Z')
        c1 = wordToIdentify[i] + ('a'-'A');
      else
        c1 = wordToIdentify[i];
        
      if(receivedString[i] >= 'A' && receivedString[i] <= 'Z')
        c2 = receivedString[i] + ('a'-'A');
      else
        c2 = receivedString[i];
        
      if(c1 != c2)
        return false;
    }
    ++i;
  }while(wordToIdentify[i] != '\0' && receivedString[i] != '\0');
  //Se todos os caracteres igualaram mas a palavra Ã© mais curta que a chave
  if(i<len)
    return false;

  //Verifica se proximo caracter Ã© um espaÃ§o ou pontuaÃ§Ã£o
  if(isspace(receivedString[i]) > 0 || receivedString[i] == '\0' || receivedString[i] == ':' || receivedString[i] == ';' || receivedString[i] == '?')
    return true;
  else
    return false;
}


/*
 * Espera TRUE, FALSE, HIGH, LOW, 1, 0...
 */
int ReadTrueOrFalse(const char *str){
  int ret = ReadPositiveNumber(str);
  if(ret == 0)
    return 0;
  if(ret == 1)
    return 1;
  
  uint32_t i = 0;
  //Encontra a primeira letra
  while(str[i]<'A' || str[i]>'z'){
    if(str[++i] == '\0')
      return -1;
  }
  ret = WordSizeIs(&str[i]);
  if(ret < 2 || ret >5)
    return -1;
  
  if(WordIs("HIGH",&str[i])){
     return 1;
  }
  if(WordIs("LOW",&str[i])){
     return 0;
  }
  if(WordIs("TRUE",&str[i])){
     return 1;
  }
  if(WordIs("FALSE",&str[i])){
     return 0;
  }
  if(WordIs("ON",&str[i])){
     return 1;
  }
  if(WordIs("OFF",&str[i])){
     return 0;
  }
  return -1;
}
