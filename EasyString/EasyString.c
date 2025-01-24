#include "EasyString.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int allocateStringMem(char** str, int length)
{
    // Allocate memory for a string of length
    *str = (char*)malloc(length * sizeof(char));
    if (str == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 0; // Exit if memory allocation fails
    }
    // set allocated memory to zero all bytes are set to 
    memset(*str, 0, length * sizeof(char));
    return 1;
}

int changeStringSize(char** str, int newLength, bool reset)
{
    // Resize the string to hold more characters
    *str = (char*)realloc(*str, newLength * sizeof(char));
    if (str == NULL)
    {
        fprintf(stderr, "Memory reallocation failed\n");
        return 0; // Exit if memory reallocation fails
    }
    if (reset)
    {
        // set allocated memory to zero all bytes are set to 
        memset(*str, 0, newLength * sizeof(char));
    }

    return 1;
}

int stringMemSize(char* str)
{
    // Get the length of the string
    int length = strlen(str);
    
    // Calculate total memory size (length + 1 for the null terminator)
    int totalSize = length + 1; // +1 for the null terminator
    return totalSize * 8;
}

int initWString(char** str, char* initstr)
{
    //alocate string memory
    allocateStringMem(str,strlen(initstr));
    strcpy(*str, initstr); // Now copy a string into it
    return 1;
}

int initWChar(char** str, char initchr)
{
    //alocate string memory but with size of 1 for some reason we don't count the '\0' got to research
    allocateStringMem(str,1);
    (*str)[0] = initchr; // Not a very wise move but what can i say
    (*str)[1] = '\0'; // it is what it is
    return 1;
}

int insertString(char** str, char *insertstr, int pos, bool isShifting)
{
    // Calculate the lengths of the original and the string to insert
    size_t strLength = strlen(*str);
    size_t insertLength = strlen(insertstr);

    // Check if the position is valid
    if (pos > strLength) {
        fprintf(stderr, "Invalid position for insertion. Maybe set isDynamic to true\n");
        return -1;
    }

    if (isShifting)
    {
        // Change the size of the string to fit both variables 
        changeStringSize(str,strLength + insertLength + 1,false);
        /* 
            In this loop we simply move the characters to the right 
            by setting j in the new indew and setting i in the original 
            index and then moving the characters one by one 
        */
        int j = strLength + insertLength - 1;
        for (int i = strLength - 1; i >= pos ; i--)
        {
            (*str)[j] = (*str)[i];
            j--;
        }
        j = 0;
        for (int i = 0; i < insertLength; i++)
        {
            (*str)[i + pos] = insertstr[j];
            j++;
        }        
    }
    else
    {
        int j = 0;
        for (int i = pos; i <= insertLength; i++)
        {
            (*str)[i] = insertstr[j];
            j++;
        }
    }        
    return 1;
}


int insertChar(char** str, char insertchr, int pos, bool isShifting)
{
    // Calculate the lengths of the original and the string to insert
    size_t strLength = strlen(*str);
    // Check if the position is valid
    if (pos > strLength) 
    {
        fprintf(stderr, "Invalid position for insertion. Maybe set isDynamic to true\n");
        return -1;
    }
    if (isShifting)
    {
        // change string size to fit the newly added character
        changeStringSize(str,strLength + 1,false);
        /*in this loop we simply move the characters to the right by setting j in the new indew 
        and setting i in the original index and then moving the characters one by one */
        int j = strLength;
        for (int i = strLength - 1; i >= pos ; i--)
        {
            (*str)[j] = (*str)[i];
            j--;
        }
        (*str)[pos] = insertchr;
    }
    else
    {
        (*str)[pos] = insertchr;
    }
    return 1;
}

char *copyStr(char* str,int start, int end)
{
    // if end or start are out of bound then exit or if start is greater than end 
    if (end > strlen(str) || start < 0 || start > end)
    {
        fprintf(stderr, "Invalid start or end\n");
        return NULL;
    }
    char* temp;
    allocateStringMem(&temp,end - start);    
    int j = 0;
    for (int i = start; i <= end; i++)
    {
        temp[j] = str[i];
        j++;
    }
    return temp;
}

int searchString(char* str, char* searchstr)
{
    // Calculate the lengths of the original and the searchstr
    size_t strLength = strlen(str);
    size_t searchLength = strlen(searchstr);
    
    if (strLength < searchLength)
    {
        fprintf(stderr, "Invalid string length too long man\n");
        return -2; 
    }
    int j;
    for (int i = 0; i < strLength; i++)
    {
        j = 0;
        while (str[i + j] == searchstr[j] && j < searchLength)
        {
            //printf("%c",searchstr[i]);
            j++;
        }
        if (j == searchLength)
        {
            return i;
        }
    }
    return -1;
}

int searchChar(char* str, char searchchr)
{
    // Calculate the lengths of the original and the searchstr
    size_t strLength = strlen(str);
    for (int i = 0; i < strLength; i++)
    {
        if (searchchr == str[i])
        {
            return i;
        }
    }
    return -1;
}

int compareString(char *str, char *cmpstr)
{
    // Calculate the lengths of the original and the string to compare with
    size_t strLength = strlen(*str);
    size_t cmpstr = strlen(cmpstr);

    if (cmpstr != strLength)
    {
        fprintf(stderr, "they arent even the same bruh\n");
        return -2; 
    }

    for (int i = 0; i < strLength; i++)
    {
        if (str[i] != cmpstr[i])
        {
            return 0;
        }   
    }
    return 1;
}
