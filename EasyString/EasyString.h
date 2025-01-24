
#ifndef EASYSTTRING_H

    #define EASYSTTRING_H

    #include "stdbool.h"

    /*alocate memory for dynamic string*/
    int allocateStringMem(char** str,int length);

    /*change size of a dynamic string, 1 is for success and 0 for failure*/
    int changeStringSize(char** str, int newLength, bool reset);

    /*get string allocated memeory size in bits*/
    int stringMemSize(char* str);

    /*init string with string*/
    int initWString(char** str, char* initstr);

    /*set character*/
    int initWChar(char** str, char initchr);

    /*insert string at position if shift is false the existing data will be overwritten 
    if true the existing data will be shifted to the right to make place for the new data*/
    int insertString(char** str, char* insertstr, int pos, bool isShifting);

    /*insert character at position same thing as the string version*/
    int insertChar(char** str, char insertchr, int pos, bool isShifting);

    /*copy string from string*/
    char* copyStr(char* str, int start, int end);

    /*search string*/
    int searchString(char* str, char* searchstr);

    /*search for a character \n the */
    int searchChar(char* str, char searchchr);

    /*
        compare two strings : 
        1 - means they are the same
        0 - means they are diff
        -1 - means they are not even the same length so diff        
    */
    int compareString(char* str, char* cmpstr); 

#endif 

