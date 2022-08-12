
/*  EXAMPLE : log("INFO : Hello there!"); */

#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>   // FILE  fopen()   fclose()  wprintf()  fprintf()
#include <string.h>  // strcpy()   strcat()
#include <stdlib.h>  // malloc()   free()
#include <stdarg.h>  // va_start    va_end   va_list
#include <time.h>    // time()   localtime()   tzset()   strftime()
#include <errno.h>   // errno

#define log(...) _log(__VA_ARGS__)

void _log(const char* fmt, ...);

#endif // LOGGING_H


