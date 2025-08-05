
#include <stdio.h>
#include <string.h>



int main(int argc, char *argv[])
{
    int  idxArgs;
    int  retCode = 0;
    char *chr = NULL;
    char *str = NULL;
    int  lenToken = 0;


    printf("Prog: %s\n", argv[0]);
    if (argc > 1)
    {
        idxArgs = 1;
        while (idxArgs < argc)
        {
            /* access and retrieve string at argv idx */
            chr = argv[ idxArgs ];

            /* stripwhitespace and return first non-whitespace */
            while ( strchr(" \n\r\v\t", *chr) && (*chr != '\0'))
            {
                chr++;
            }
            /* stripwhitespace from string end */
            lenToken = strlen(chr);
            while (lenToken > 0)
            {
                if ( !strchr(" \n\r\v\t", *(chr + lenToken - 1)) )
                {
                    *(chr + lenToken) = '\0';
                    break ;
                }
                lenToken--;
            }
            printf("string (%s), length(%d) \n", chr, lenToken);

            /* check is arg is of type (option or ip addres ) */
            if (*chr == '-')
            {
                /* process option */
                printf("opt: ");
            }
            else
            {
                /* process ip address */
                printf("adr: ");
            }
            
            printf("args(%s)\n", chr);
            idxArgs++;
        }
    }
    return (retCode);
}



int handleOpt(char *opt)
{
    int retCode = 0;
}
