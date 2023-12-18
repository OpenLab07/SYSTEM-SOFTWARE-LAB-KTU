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

void readFile(FILE *file, char *label, char *opcode, char *operand) {
  fscanf(file, "%s%s%s", label, opcode, operand);
}

void onePassMacro()
{
  FILE *fin, *namtab, *deftab, *argtab, *output;//datastructures 
  int len, i, posInt= 1;
  char arg[20], opcode[20], operand[20], label[20], name[20];// for instruction reading 
  char opcode1[20], operand1[20]; //for deftab reading
  char  posStr[10], questionMark[5];
  fin = fopen("minput.txt", "r");
  namtab = fopen("namtab.txt", "w+");
  deftab = fopen("deftab.txt", "w+");
  argtab = fopen("argtab.txt", "w+");
  output = fopen("op.txt", "w+");
  readFile(fin, label, opcode, operand);
  while (strcmp(opcode, "END") != 0){
      if (strcmp(opcode, "MACRO") == 0){
        // the current line macro definition.
          fprintf(namtab, "%s\n", label);//writing macro name into namtab
          fprintf(deftab, "%s\t%s\n", label, operand);//writing macroname and paramter list into deftab
          readFile(fin, label, opcode, operand);
          while (strcmp(opcode, "MEND") != 0){
              if (operand[0] == '&'){
                sprintf(posStr, "%d", posInt);
                strcpy(questionMark, "?");
                strcpy(operand, strcat(questionMark, posStr));//creating positional notation for operand in deftab
                posInt++;
              }
              fprintf(deftab, "%s\t%s\n", opcode, operand);//writing to deftab
              readFile(fin, label, opcode, operand);
          }
          fprintf(deftab, "%s", opcode);// writing mend to the deftab.
      }
      else{
          rewind(deftab);rewind(namtab);
          fscanf(namtab, "%s", name);
          if (strcmp(opcode, name) == 0){
            // the current line is macro call. 
            //- ex1 a,b  
              len = strlen(operand);
              // add arguments to the argtab by reading the actual parameterlist (here operand,argument separated by ",").
              for (i = 0; i < len; i++){
                if (operand[i] != ',')
                    fprintf(argtab, "%c", operand[i]);
                else
                    fprintf(argtab, "\n");
              }
              rewind(argtab);
              fscanf(deftab, "%s%s", opcode1, operand1); // macrname parameterlist
             // fprintf(output, "//\t%s\t%s\n", opcode1, operand);
              fscanf(deftab, "%s%s", opcode1, operand1);
              while (strcmp(opcode1, "MEND") != 0){
                if (operand1[0] == '?'){
                    //  instruction that to be replace the operand with actaul parameter
                    fscanf(argtab, "%s", arg);
                    fprintf(output, "-\t%s\t%s\n", opcode1, arg);
                }else
                    fprintf(output, "-\t%s\t%s\n", opcode1, operand1);//instuction tha contain operand which is not an paremeter.(may be registers)
                fscanf(deftab, "%s%s", opcode1, operand1);
              }
          }
          else
              fprintf(output, "%s\t%s\t%s\n", label, opcode, operand);// writing the readed line without any change since it is not a macro call.
      }
      readFile(fin, label, opcode, operand);
  }
  fprintf(output, "%s\t%s\t%s", label, opcode, operand);// writing - END - to ouput file(expanded code)
  fclose(fin); fclose(namtab); fclose(deftab); 
  fclose(argtab); fclose(output);
}

int main(){
  onePassMacro();
  printf("\nArgument table:\n\n"); display("argtab.txt");
  printf("\nName table:\n\n"); display("namtab.txt");
  printf("\nDefinition table:\n\n"); display("deftab.txt");
  printf("\nExpanded code:\n\n"); display("op.txt");
}
/*
input

EX1 MACRO &A,&B
- LDA &A
- STA &B
- MEND -
SAMPLE START 1000
- EX1 N1,N2
N1 RESW 1
N2 RESW 1
- END -

output

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
-       LDA     N1
-       STA     N2
N1      RESW    1
N2      RESW    1
-       END     -
*/