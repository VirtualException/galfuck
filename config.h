instruction str_table[INST_NUM] =
{
//     Galfuck keywords | C code 
    { {"imos", "alá", NULL}, "#include <stdio.h>\n"
      "char arr[4096] = {0};\n"
      "char* ptr = arr;\nint main() " },                // Header
    { {"acabouse", NULL},   "return (int) *ptr;\n" },   // End

    { {"dereita", NULL},    "++ptr;\n"     },           // Increment pointer. %d is Nº of "dereita" kywords in the line     --.
    { {"esquerda", NULL},   "--ptr;\n"     },           // Decrease pointer. %d is Nº of "esquerda" kywords in the line     --|
                                                        //                                                                    |
    { {"máis", NULL},       "++*ptr;\n"    },           // Increment pointer value. %d is Nº of "máis" kywords in the line  --|
    { {"menos", NULL},      "--*ptr;\n"    },           // Decrease pointer value. %d is Nº of "menos" kywords in the line  --|
                                                                       //                                                     |- Brainfuck instructions
    { {"que", "dis?", NULL},              "*ptr = getchar();\n" },     // Get character from stdin                          --|
    { {"éche", "o",  "que", "hai", NULL}, "putchar(*ptr);\n" },        // Print character to stdout                         --|
                                                                       //                                                     |
    { {"se", "non", "é", "boi", "é", "baca", NULL}, "while(*ptr)\n" }, // Start of while loop                               --'

    { {"a", "ver", NULL},   "{\n"},                     // Start bracket
    { {"e", "xa", NULL},    "}\n"}                      // End bracket
};
