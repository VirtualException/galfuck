#include <stdio.h> 
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define INST_NUM 11

typedef struct
{
    char* strIn[8];
    char* strOut;

} instruction;

enum InstID
{
    HEAD,
    END,
    UP,
    DOWN,
    ADD,
    SUB,
    IN,
    OUT,
    WHILE,
    TOP,
    BOT,
    ERR
};

#include "config.h"

int     gcc_comp(char* cpath, char* outpath);
void    die(int code, char* str);
int     getInstructionID(FILE* file);

int
gcc_comp(char* cpath, char* outpath) {

    char *comp_args[]= { "gcc", "-O2", "-s", cpath, "-o", outpath, NULL};

    execvp(comp_args[0], comp_args);

    printf("end?\n");
    return 0;
}

void
die(int code, char* str) {

    // Print error string and exit

    fprintf(stderr, str); 
    exit(code);
}

int
getInstructionID(FILE* file) {

    char word[255];

    // Scan word
    memset(word, 0, sizeof(word));
    if(fscanf(file, "%s", word) == EOF) return EOF;

    // Loop all the instructions
    for (size_t i = 0; i <= INST_NUM; i++) {

        // Loop all the words on the instruction
        for (size_t w = 0; str_table[i].strIn[w] != NULL; w++) {

            // Compare strings
            if (strcmp(word, str_table[i].strIn[w])) {
                if (w == 0) goto next;  // This is not the one
                else return ERR;        // There is a syntax error, previous word was ok
            }
            // Scan next word only if it has one more check to do
            else if (str_table[i].strIn[w+1] != NULL) {
                memset(word, 0, sizeof(word));
                if(fscanf(file, "%s", word) == EOF) return EOF;
            }
        }

        return i;
next:
    }

    // Any instruction is suitable
    return ERR;

}

int
main(int argc, char* argv[]) {

    if (argv[1] == NULL || argv[3] != NULL)
    {
        die(EXIT_FAILURE, "Usage: galfuckc SOURCE OUTPUT\n");
    }

    // Setup paths for io

    char* inpath    = argv[1];
    char* outpath   = argv[2];

    // Setup files

    FILE* infile;
    FILE* cfile;

    // Path of the output c file that we compile

    char cpath[255];
    strcpy(cpath, argv[1]);
    strcat(cpath, ".c");

    // Open files

    infile = fopen(inpath, "r");
    if (infile == 0) {
        die(EXIT_FAILURE, "The input file couldn't be opened\n");
    }
    
    cfile = fopen(cpath, "w");
    if (cfile == 0) {
        die(EXIT_FAILURE, "The output destination is invalid\n");
    } 

    int t = 0;
    int code = 0;
    int err = 0;

    // Scan every instruction in the file 
    while((code = getInstructionID(infile)) != EOF) {

        if (code == ERR) {
            err++;
            printf("Syntax error in word Nº %d\n", t+1);
        }
        else {
            fprintf(cfile, str_table[code].strOut);
        }
        t++;
    };

    fclose(infile);
    fclose(cfile);

    if (!err) {
        printf("Compiling...\n");
        gcc_comp(cpath, outpath);
    }

    return EXIT_SUCCESS;

}
