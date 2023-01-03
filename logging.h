
/*
  NOTE : To use this you need to add the define ONCE in your project.

  #define LOGGER_IMPLEMENTATION
  #include "logging.h"

  To use the logger, write how you want to use it.
  EXAMPLE 1 : logging("INFO : Hello there!");

  This will write this chineese characters using   \xe4\xb8\xad\xe6\x96\x87   or   中文
  EXAMPLE 2 : logging("Characters in chineese : \xe4\xb8\xad\xe6\x96\x87    -----    中文");

  EXAMPLE 3 : int totalmistakes = 5;
              logging("ERROR : You have made %d mistakes !", totalmistakes);
*/

#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>   // FILE  fopen()   fclose()  fprintf()   sprintf()
#include <string.h>  // strcpy()   strcat()
#include <stdlib.h>  // malloc()   free()
#include <stdarg.h>  // va_start    va_end   va_list    va_arg
#include <time.h>    // time()   localtime()   tzset()   strftime()
#include <errno.h>   // errno

#define logging(...) _logging(__VA_ARGS__)

void _logging(const char* fmt, ...);

#endif // LOGGING_H

#ifdef LOGGER_IMPLEMENTATION

void tzset(void);      // Added for linux

void _logging(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    char destStr[1024] = {0};
    sprintf(destStr, fmt, va_arg(ap, char*));
    va_end(ap);

    char datestr[51];
    time_t t = time(NULL);
    tzset();
    char* fileName = malloc(sizeof(char) * 19);
    strftime(datestr, sizeof(datestr) - 1,  "%m-%d-%Y", localtime(&t));
    strcpy(fileName, "log-");
    strcat(fileName, datestr);
    strcat(fileName, ".txt");
    FILE *file = fopen(fileName, "a+");
    if(file == NULL)
    {
        free(fileName);
    } else {
        if(errno == 22)
        {
            errno = 0;
        }
        free(fileName);
        strftime(datestr, sizeof(datestr) - 1,  "%b/%d/%Y  %H:%M", localtime(&t));
        fprintf(file, "%s - ", datestr);
        fprintf(file, "%s", destStr);
        fprintf(file, "\n");
        fclose(file);
    }
}

#endif // LOGGER_IMPLEMENTATION

