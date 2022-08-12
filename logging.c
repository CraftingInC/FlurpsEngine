
#include "logging.h"

void _log(const char* fmt, ...)
{
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
        wprintf(L"ERROR : Unable to create log file !!\n");

    } else {
        if(errno == 22)
        {
            errno = 0;
        }
        free(fileName);
        va_list ap;
        strftime(datestr, sizeof(datestr) - 1,  "%b/%d/%Y  %H:%M", localtime(&t));
        fprintf(file, "%s - ", datestr);
        va_start(ap, fmt);
        vfprintf(file, fmt, ap);
        va_end(ap);
        fprintf(file, "\n");
        fclose(file);
    }
}
