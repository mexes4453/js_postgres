
#include <stdio.h>
#include <string.h>

int XPARSER__StripLeadingWhiteSpace( char *strInput, char **strOutput);
int XPARSER__StripTrailingWhiteSpace( char *strInput, char **strOutput);
int XPARSER__StripWhiteSpace( char *strInput, char **strOutput);
int XPARSER__IsWhiteSpaceInStr( char *str);
int handleOpt( char *strOpt);
int processOptionChar( char *pChr);

int main(int argc, char *argv[])
{
    int  argIdx;
    int  retCode = 0;
    char *str = NULL;


    printf("Prog: %s\n", argv[0]);
    if (argc > 1)
    {
        argIdx = 1;
        while (argIdx < argc)
        {
            /* access and retrieve string at argv idx */
            // chr = argv[ argIdx ];

            /* stripwhitespace around string - leading and trailing */
            XPARSER__StripWhiteSpace( argv[ argIdx ], &str);

            printf("args(%s)\n", str);

            /* Check type of argument (option or ip addres ) */
            if ( str[0] == '-')
            {
                printf("opt: \n");
                retCode = handleOpt(str);
            }
            else
            {
                /* process ip address */
                printf("adr: \n");
            }

            /* Evaluate return Code */
            if (retCode != 0)
            {
                printf("Error: %d\n", retCode);
                goto labelExit;
            }
            argIdx++;
        }
    }
labelExit:
    return (retCode);
}




int XPARSER__StripLeadingWhiteSpace(char *strInput, char **strOutput)
{
    while ( strchr(" \n\r\v\t", *strInput) && (*strInput != '\0'))
    {
        strInput++;
    }
    *strOutput = strInput;
    return (strlen(strInput));
}




int XPARSER__StripTrailingWhiteSpace(char *strInput, char **strOutput)
{
    int lenStrInput = strlen(strInput);
    while (lenStrInput > 0)
    {
        if ( !strchr(" \n\r\v\t", *(strInput + lenStrInput - 1)) )
        {
            *(strInput + lenStrInput) = '\0';
            break ;
        }
        lenStrInput--;
    }
    *strOutput = strInput;
    return (lenStrInput);
}




int XPARSER__StripWhiteSpace(char *strInput, char **strOutput)
{
    int   lenStrOutput = 0;

    lenStrOutput = XPARSER__StripLeadingWhiteSpace(strInput, strOutput);
    //printf("string (%s), length(%d) \n", strOutput[0], lenStrOutput);

    /* use the output string as input string to remove trailing whitespace */
    lenStrOutput = XPARSER__StripTrailingWhiteSpace(strOutput[0], strOutput);
    //printf("string (%s), length(%d) \n", strOutput[0], lenStrOutput);
    return (lenStrOutput);
}



int XPARSER__IsWhiteSpaceInStr(char *str)
{
    int retCode = 0;

    while ( !strchr(" \n\r\v\t", *str) && (*str != '\0') )
    {
        str++;
    }
    retCode = (*str == '\0') ? 0 : 1;

    return (retCode);
}




int handleOpt(char *strOpt)
{
    int retCode = 0;

    /* check for any whitespace in option str */
    if (XPARSER__IsWhiteSpaceInStr(strOpt) || (strlen(strOpt) <= 1)) 
    {
        retCode = -500; /* invalid option format */
        goto labelExit;
    }

    do
    {
        /* Note that the first char in string is '-'. Hence, its skipped. */
        strOpt++;
        
        if ( *strOpt == '\0' )
        {
            break ;
        }
        retCode = processOptionChar( strOpt );
    } while ( retCode == 0);

labelExit:
    return (retCode);
}




int processOptionChar( char *pChr )
{
    int retCode = 0;
    char chr = *pChr;

    switch (chr)
    {
        case 'v':
            {
                printf("setting verbose flag\n");
                retCode = 0;
                break ;
            }
        case '?':
            {
                printf("show the program usage here\n");
                retCode = -501;
                break ;
            }
        case 'c':
            {
                if ( *(pChr + 1) != '\0' )
                {
                    printf("Invalid option format for (c)\n");
                    retCode = -502;
                }
                else
                {
                    printf("Retrieve count value from next argv[ idx ]\n");
                    printf("update the count value variable\n");
                    retCode = 0;
                }
                break ;
            }
        default:
            {
                printf("Unknown option\n");
                retCode = 503;
                break ;
            }
    }
    return (retCode);
}

