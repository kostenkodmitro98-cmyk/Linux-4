#ifndef STRING_PROCESSOR
#define STRING_PROCESSOR
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define STRING_MAX 512ull

int32_t get_str(const char* msg, char* str, int32_t limit)
{
    if (msg)
        printf("%s", msg);
    if (!fgets(str, limit, stdin))
        return -1;


    size_t i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\n') { str[i] = '\0'; break; }
        i++;
    }
    return (int32_t)i;
}

size_t strlenn(const char* str)
{
    size_t len = 0;
    while (str[len] != '\0') len++;
    return len;
}

void strcopy(char* fStr, const char* sStr, size_t until)
{
    for (size_t i = 0; i < until && sStr[i] != '\0'; i++)
        fStr[i] = sStr[i];
    fStr[until] = '\0';
}

int32_t strcmpp(const char* fStr, const char* sStr)
{
    size_t i = 0;
    while (fStr[i] != '\0' && sStr[i] != '\0')
    {
        if ((unsigned char)fStr[i] != (unsigned char)sStr[i])
            return ((unsigned char)fStr[i] - (unsigned char)sStr[i]);
        i++;
    }
    return ((unsigned char)fStr[i] - (unsigned char)sStr[i]);
}

char* strcatt(char* fStr, const char* sStr)
{
    char* ptr = fStr + strlenn(fStr);
    while (*sStr != '\0') *ptr++ = *sStr++;
    *ptr = '\0';
    return fStr;
}

bool is_string_valid(const char* str)
{
    bool isThereString = false;
    bool isThereColon = false;
    const size_t size = strlenn(str);
    for (size_t i = 0; i < size; i++)
    {
        if ((str[i] == ':' || str[i] == ';' || str[i] == ',') && i == 0ull)
            return false;
        if (str[i] == ':')
            isThereColon = true;
        else if (isThereColon)
        {
            if (str[i] == ',')
            {
                if (!isalpha((unsigned char)str[i - 1ull]) && str[i - 1ull] != ' ')
                    return false;
                else
                    isThereString = true;
            }
            if (str[i] == ';')
            {
                if (!isThereString || (!isalpha((unsigned char)str[i - 1ull]) && str[i - 1ull] != ' '))
                    return false;
                else
                    isThereColon = false;
            }
            if (str[i] == ':')
                return false;
        }
        else
            isThereString = false;
    }
    return true;
}

void quick_sort(char** arr, size_t length);

char* process_string(const char* str)
{
    const size_t length = strlenn(str);
    char* result = (char*)calloc(length + 1, sizeof(char));
    if (!result) return NULL;

    for (size_t i = 0; i < length; i++)
    {
        if (str[i] != ':')
        {
            char temp[2] = { str[i], '\0' };
            strcatt(result, temp);
            continue;
        }
        if (i + 1 >= length || str[i + 1] != ' ')
        {
            free(result);
            return NULL;
        }

        strcatt(result, ": ");

        const size_t strsPreCnt = 100;
        char** arr = (char**)calloc(strsPreCnt, sizeof(char*));
        if (!arr)
        {
            free(result);
            return NULL;
        }

        for (size_t strsCnt = 0; strsCnt < strsPreCnt; strsCnt++)
        {
            arr[strsCnt] = (char*)calloc(STRING_MAX, sizeof(char));
            if (!arr[strsCnt])
            {
                for (size_t k = 0; k < strsCnt; k++) free(arr[k]);
                free(arr);
                free(result);
                return NULL;
            }
        }

        size_t strRealCnt = 0;
        bool foundSemicolon = false;

        for (size_t j = i + 2; j < length; j++)
        {
            if (str[j] == ',')
            {
                strRealCnt++;
                if (strRealCnt >= strsPreCnt - 1) break;
            }
            else if (str[j] == ';')
            {
                quick_sort(arr, strRealCnt + 1);
                for (size_t k = 0; k <= strRealCnt; k++)
                {
                    strcatt(result, arr[k]);
                    if (k == strRealCnt) strcatt(result, ";");
                    else strcatt(result, ", ");
                }
                i = j;
                foundSemicolon = true;
                break;
            }
            else
            {
                char temp[2] = { str[j], '\0' };
                strcatt(arr[strRealCnt], temp);
            }
        }

        if (!foundSemicolon)
        {
            for (size_t strsCnt = 0; strsCnt < strsPreCnt; strsCnt++)
                free(arr[strsCnt]);
            free(arr);
            free(result);
            return NULL;
        }

        for (size_t strsCnt = 0; strsCnt < strsPreCnt; strsCnt++)
            free(arr[strsCnt]);
        free(arr);
    }
    return result;
}

#endif 