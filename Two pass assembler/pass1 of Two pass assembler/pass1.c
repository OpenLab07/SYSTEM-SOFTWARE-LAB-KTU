#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
void display(char *fileName){
    FILE *fp = fopen(fileName,"r");
    char ch = fgetc(fp);
    while(ch != EOF){
        printf("%c",ch);
        ch = fgetc(fp);
    }    
    fclose(fp);
}
void onepass(){ // pass1 of Two pass assembler
    char label[30], opcode[30], operand[30];
    char code[10],mnemonic[10];
    int startAddress, locctr = 0, i,validOpcode;
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt","r");
    fp3 = fopen("symtab.txt","w");
    fp4 = fopen("intermediate.txt", "w");
    fp5 = fopen("length.txt","w");
    fscanf(fp1, "%s%s%s", label, opcode, operand);
    if (!strcmp(opcode, "START")){ // 1. if opcode is "START" 
            startAddress = strtol(operand,NULL,16);
            locctr = startAddress;
            fprintf(fp4, "%x\t\t%s\t\t%s\t\t%s\n", locctr, label, opcode, operand);
            fscanf(fp1, "%s%s%s", label, opcode, operand);
    }else locctr = 0;
    while (strcmp(opcode,"END") !=  0){// 2.reading each input line until opcode is 'END'
        fprintf(fp4, "%x\t\t%s\t\t%s\t\t%s\n", locctr, label, opcode, operand);  //4.intermediate file writing.
        if (strcmp(label, "**") != 0){ //if label field contain a valid symbol then write it to symtab
            fprintf(fp3,"%s\t%x\n",label,locctr);
        }
        validOpcode = 0; // 3.opcode validation and locctr updation
        rewind(fp2);
        while (!feof(fp2)) {
            fscanf(fp2, "%s\t%s", code, mnemonic);
            if (!strcmp(opcode, code)) {                
                locctr += 3;
                validOpcode = 1;
                break;
            }
        }
        if(!validOpcode){
            if (!strcmp(opcode, "WORD"))        locctr += 3;
            else if (!strcmp(opcode, "RESW"))   locctr += atoi(operand) * 3;
            else if (!strcmp(opcode, "RESB"))   locctr += atoi(operand);
            else if (!strcmp(opcode, "BYTE")){
                int len = strlen(operand) -3;
                if(operand[0] == 'C')           locctr += len;
                else                            locctr += ceil(len/2.0);
            }
            else{
                printf("\ninvalid opcode %s  !!!",opcode);
                exit(1);
            }    
        }
        fscanf(fp1, "%s%s%s", label, opcode, operand); 
    }
    fprintf(fp4, "%x\t\t%s\t\t%s\t\t%s\n", locctr, label, opcode, operand);
    fprintf(fp5, "%x",locctr - startAddress);// 5.calculation of program length
    fclose(fp1);    fclose(fp2);    fclose(fp3);    fclose(fp4);
    fclose(fp5);
}
int  main(){
    onepass();
    printf("SYMBOL TABLE\n");           display("symtab.txt");
    printf("\nINTERMEDIATE FILE \n");   display("intermediate.txt");
    printf("\nPROGRAM LENGTH : ");      display("length.txt");
}
/*
SYMBOL TABLE
FIVE    2009
CONST   200c
ALPHA   200f
EOF     2015
HEXF1   2018

INTERMEDIATE FILE
2000            SAMPLE          START           2000
2000            **              LDA             FIVE
2003            **              ADD             CONST
2006            **              STA             ALPHA
2009            FIVE            WORD            5
200c            CONST           RESW            1
200f            ALPHA           RESW            2
2015            EOF             BYTE            C'EOF'
2018            HEXF1           BYTE            X'F1'
2019            **              END             2000

PROGRAM LENGTH : 19
*/