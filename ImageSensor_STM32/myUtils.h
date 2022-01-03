
#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

char * FindNextNonWhitespace( char *str);
char * FindNextPunctuation( char *str);
char * FindLastCharOfArgument( char *str);
char * FindNextWord( char *str);
char * FindNextComma(char *str);
uint32_t WordSizeIs(const char *str);
uint32_t ReadPositiveNumber(const char *str);
//float ReadFloat(const char *str);
int ReadTrueOrFalse(const char *str);
bool WordIs(const char *wordToIdentify, const char *receivedString);

#endif
