#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "phrases.h"


bool is_terminal(char c){
    return (c == '.' || c == '!' || c == '?');
}

void print_phrase_no(int n){
    printf("[%d] ", n);
}

void read_phrases(FILE *f, bool list_phrases)
{
    char c;
    int phrasesno = 1;
    if (list_phrases){                          /* If the flag is set */
        print_phrase_no(phrasesno);             /* Print the phrase number */
        while ((c = fgetc(f)) != EOF){
            printf("%c", c);                    /* Print the character */
            if (is_terminal(c)){                /* If the character is a terminal character */
                c = fgetc(f);                   /* This is done to remove whitespace after a terminal character */
                if (c != ' ')                   /* Cover the case in which there is no whitespace after a terminal character */
                    ungetc(c, f);               /* Push back the read character into the stream */
                printf("\n");                   /* Print new line */
                if ((c = getc(f)) != EOF){      /* If the next character is not the end of the file */
                    phrasesno++;                /* Increment number of phrases */
                    print_phrase_no(phrasesno); /* Print the number of the phrase */
                    printf("%c", c);            /* Print the character */
                }
            }
        }
    }
    else {                                      /* If the flag is not set */
        while ((c = fgetc(f)) != EOF){
            if (is_terminal(c)){                /* If the character is a terminal character */
                if ((c = getc(f)) != EOF)       /* And if the next one is not the end of the file */
                    phrasesno++;                /* Increment number of phrases */
            }
        }
        printf("%d\n", phrasesno);
    }
}

int main(int argc, char **argv)
{
    bool list_phrases = false;
    FILE *f;

    if (argc < 2)
    {
        printf("usage: phrases [-l] file\n");
        exit(EXIT_FAILURE);
    }

    if ((strcmp(argv[1], "-l") == 0) && (argc == 3))
    {
        f = fopen(argv[2], "r");

        if (f == NULL)
        {
            printf("Could not open file %s\n", argv[2]);
            exit(EXIT_FAILURE);
        }

        list_phrases = true;
    }
    else if (argc == 2)
    {
        f = fopen(argv[1], "r");
        if (f == NULL)
        {
            printf("Could not open file %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
    }
    read_phrases(f, list_phrases);
    return 0;
}