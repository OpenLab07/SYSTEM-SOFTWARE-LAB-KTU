#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void display(char *filename){
    FILE *fp = fopen(filename, "r");
    char ch = fgetc(fp);
    while (ch != EOF){
        printf("%c", ch);
        ch = fgetc(fp);
    }printf("\n");
    fclose(fp);
}
void onePassMacro()
{
    FILE *fin, *f_namtab, *f_deftab, *f_argtab, *f_expand;
    int len, i, pos = 1;
    char arg[20], opcode[20], operand[20], label[20], name[20];
    char opcode1[20], operand1[20], pos1[10], pos2[10];
    fin = fopen("minput.txt", "r");
    f_namtab = fopen("namtab.txt", "w+");
    f_deftab = fopen("deftab.txt", "w+");
    f_argtab = fopen("argtab.txt", "w+");
    f_expand = fopen("op.txt", "w+");
    fscanf(fin, "%s%s%s", label, opcode, operand);
    while (strcmp(opcode, "END") != 0){
        if (strcmp(opcode, "MACRO") == 0){
            fprintf(f_namtab, "%s\n", label);
            fseek(f_namtab, SEEK_SET, 0);
            fprintf(f_deftab, "%s\t%s\n", label, operand);
            fscanf(fin, "%s%s%s", label, opcode, operand);
            while (strcmp(opcode, "MEND") != 0){
                if (operand[0] == '&'){
                    sprintf(pos1, "%d", pos);
                    strcpy(pos2, "?");
                    strcpy(operand, strcat(pos2, pos1));
                    pos = pos + 1;
                }
                fprintf(f_deftab, "%s\t%s\n", opcode, operand);
                fscanf(fin, "%s%s%s", label, opcode, operand);
            }
            fprintf(f_deftab, "%s", opcode);
        }
        else{
            fscanf(f_namtab, "%s", name);
            if (strcmp(opcode, name) == 0){
                len = strlen(operand);
                for (i = 0; i < len; i++){
                    if (operand[i] != ',')
                        fprintf(f_argtab, "%c", operand[i]);
                    else
                        fprintf(f_argtab, "\n");
                }
                fseek(f_deftab, SEEK_SET, 0);
                fseek(f_argtab, SEEK_SET, 0);
                fscanf(f_deftab, "%s%s", opcode1, operand1);
                fprintf(f_expand, ".\t%s\t%s\n", opcode1, operand);
                fscanf(f_deftab, "%s%s", opcode1, operand1);
                while (strcmp(opcode1, "MEND") != 0){
                    if (operand[0] == '?'){
                        fscanf(f_argtab, "%s", arg);
                        fprintf(f_expand, "-\t%s\t%s\n", opcode1, arg);
                    }else
                        fprintf(f_expand, "-\t%s\t%s\n", opcode1, operand1);
                    fscanf(f_deftab, "%s%s", opcode1, operand1);
                }
            }
            else
                fprintf(f_expand, "%s\t%s\t%s\n", label, opcode, operand);
        }
        fscanf(fin, "%s%s%s", label, opcode, operand);
    }
    fprintf(f_expand, "%s\t%s\t%s", label, opcode, operand);
    fclose(fin); fclose(f_namtab); fclose(f_deftab); 
    fclose(f_argtab);  fclose(f_expand);
}
int main(){
    onePassMacro();
    printf("\nArgument table:\n\n"); display("argtab.txt");
    printf("\nName table:\n\n"); display("namtab.txt");
    printf("\nDefinition table:\n\n"); display("deftab.txt");
    printf("\nExpanded code:\n\n"); display("op.txt");
}

/*
INPUT

EX1 MACRO &A,&B
- LDA &A
- STA &B
- MEND -
SAMPLE START 1000
- EX1 N1,N2
N1 RESW 1
N2 RESW 1
- END -

OUTPUT
Argument table:

N1
N2

Name table:

EX1


Definition table:

EX1     &A,&B
LDA     ?1
STA     ?2
MEND

Expanded code:

SAMPLE  START   1000
.       EX1     N1,N2
-       LDA     ?1
-       STA     ?2
N1      RESW    1
N2      RESW    1
-       END     -

*/
