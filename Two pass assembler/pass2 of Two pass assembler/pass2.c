#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void textRecordWriting(FILE *fp,int textlen,char *text){
    char inter[3];
    sprintf(inter, "%02x", (textlen*3));
    text[9] = inter[0]; text[10] = inter[1];
    fprintf(fp, "%s", text);
}
void display(char *fileName){
    FILE *fp = fopen(fileName,"r");
    char ch = fgetc(fp);
    while(ch != EOF){
        printf("%c",ch);
        ch = fgetc(fp);
    }    
    fclose(fp);
}
void passTwo(){
    FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6;
    char locctr[10],label[10],opcode[10],operand[10]; 
    char symbol[10],address[10] ,mnemonic[10],machineCode[10]; 
    char text[100],pgLengthH[3];
    int textlen = 0,count; 
    fp1 = fopen("intermediate.txt","r");
    fp2 = fopen("length.txt" ,"r");
    fp3 = fopen("optab.txt","r");
    fp4 = fopen("symtab.txt","r");
    fp5 = fopen("objectProgram.txt","w");
    fp6 = fopen("assemblyListing.txt","w");
    fscanf(fp2,"%s",pgLengthH);
    fscanf(fp1,"%s%s%s%s",locctr,label,opcode,operand);
    int pgLengthD = strtol(pgLengthH ,NULL,16); 
    int stAddressD = strtol(locctr,NULL,16);
    if(!strcmp(opcode,"START")){
        fprintf(fp5,"H^%s^%06x^%06x\n",label,stAddressD,pgLengthD);
        fprintf(fp6,"%s\t%s\t%s\t%s\t%s\n",locctr,label,opcode,operand,"**");
        sprintf(text,"T^%06x^",stAddressD);
        count = 11;
    }
    while(!feof(fp1)){
        fscanf(fp1,"%s%s%s%s",locctr,label,opcode,operand);  
        if(!strcmp(opcode,"END")){
            textRecordWriting(fp5,textlen,text);
            fprintf(fp5,"\nE^%06x",stAddressD);
            fprintf(fp6,"%s\t%s\t%s\t%s\t%s\n",locctr,label,opcode,operand,"**");
            break;
        }
        if(!strcmp(opcode,"RESW") || !strcmp(opcode,"RESB"))
            fprintf(fp6,"%s\t%s\t%s\t%s\t%s\n",locctr,label,opcode,operand,"**");
        else if(!strcmp(opcode,"WORD")){
            sprintf(text+count,"^%06x",atoi(operand));
            fprintf(fp6,"%s\t%s\t%s\t%s\t%s\n",locctr,label,opcode,operand,text+count+1);
            count += 7; textlen++;
        }
        else if (!strcmp(opcode, "BYTE")) {
            sprintf(text + count++, "%s", "^");
            char *formatSpecifier = (operand[0] == 'X') ? "%c" : "%x";
            int increment = (operand[0] == 'X') ? 1 : 2;
            int byteStart = count;
            for (int i = 2; i < strlen(operand) - 1; i++, count += increment)
                sprintf(text + count, formatSpecifier, operand[i]);
            fprintf(fp6, "%s\t%s\t%s\t%s\t%s\n", locctr, label, opcode, operand, text + byteStart);
            textlen++;
        }
        else{
            rewind(fp3);
            while(!feof(fp3)){
                fscanf(fp3,"%s%s", mnemonic,machineCode);
                if(!strcmp(mnemonic,opcode)){
                    rewind(fp4);
                    while (!feof(fp4)){
                        fscanf(fp4,"%s\t%s\n",symbol,address);
                        if(!strcmp(symbol,operand)){
                            sprintf(text+count,"^%s%s",machineCode,address);
                            fprintf(fp6,"%s\t%s\t%s\t%s\t%s\n",locctr,label,opcode,operand,text+count+1);
                            count +=7; textlen++; break;
                        }
                    } break;
                }
            }
        }
    }
    fclose(fp1);fclose(fp2);fclose(fp3);fclose(fp4);fclose(fp5);fclose(fp6);
}
int main(){
    passTwo();
    printf("Assembly Listing\n"); display("assemblyListing.txt");
    printf("\nObject Program\n");   display("objectProgram.txt");
}
/*
input
-----------------------------------------------------------
intermediate.txt
2000		SAMPLE	START	2000
2000		**		LDA		FIVE
2003		**		ADD		CONST
2006		**		STA		ALPHA
2009		FIVE	WORD	5
200c		CONST	RESW	1
200f		ALPHA	RESW	2
2015		EOF		BYTE	C'EOF'
2018		HEXF1	BYTE	X'F1'
2019		**		END		2000

length.txt 
19

symtab.txt
FIVE	2009
CONST	200c
ALPHA	200f
EOF	    2015
HEXF1	2018

optab.txt
LDA 00
STA 0C
ADD 18

output
---------------------------------------
Assembly Listing
2000    SAMPLE  START   2000    **
2000    **      LDA     FIVE    002009
2003    **      ADD     CONST   18200c
2006    **      STA     ALPHA   0C200f
2009    FIVE    WORD    5       000005
200c    CONST   RESW    1       **
200f    ALPHA   RESW    2       **
2015    EOF     BYTE    C'EOF'  454f46
2018    HEXF1   BYTE    X'F1'   F1
2019    **      END     2000    **

Object Program
H^SAMPLE^002000^000019
T^002000^12^002009^18200c^0C200f^000005^454f46^F1
E^002000
*/