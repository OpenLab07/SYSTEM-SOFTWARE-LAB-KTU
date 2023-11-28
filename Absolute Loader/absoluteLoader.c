#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main() {
  FILE * fp;
  int i, addr1, l, j, staddr1;
  char name[10], line[50], name1[10], addr[10], rec[10], ch, staddr[10];
  printf("enter program name:");
  scanf("%s", name);
  fp = fopen("input.txt", "r");
  fscanf(fp, "%s", line);
  for (i = 2, j = 0; i < 8, j < 6; i++, j++)
    name1[j] = line[i];
  name1[j] = '\0';
  printf("name from object file:%s\n", name1);
  if (strcmp(name, name1) == 0) {
    do {
      fscanf(fp, "%s", line);
      if (line[0] == 'T') {
        for (i = 2, j = 0; i < 8, j < 6; i++, j++)
          staddr[j] = line[i];
        staddr[j] = '\0';
        staddr1 = atoi(staddr);
        i = 12;
        while (line[i] != '$') {
          if (line[i] != '^') {
            printf("00%d \t %c%c\n",
              staddr1, line[i], line[i + 1]);
            staddr1++;
            i = i + 2;
          } else i++;
        }
      } else if (line[0] = 'E') {
        fclose(fp);
        exit(0);
      }
    } while (!feof(fp));
  }
}

/*  

H^SAMPLE^001000^0035
T^001000^0C^001003^071009$
T^002000^03^111111$
E^001000 

enter program name:SAMPLE
name from object file:SAMPLE
001000 	 00
001001 	 10
001002 	 03
001003 	 07
001004 	 10
001005 	 09
002000 	 11
002001 	 11
002002 	 11

*/
