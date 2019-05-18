#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readNextField(char *, int, FILE *);
void printNTasks(int);


int main(int argc, char *argv[]) {
  // printf("You've given %d argument(s):\n", argc);
  // for (int i = 0; i < argc; i++) {
  //   printf("\t%s\n", argv[i]);
  // }

  printNTasks(1);
}


void printNTasks(int n) {
  char buff[200];
  FILE *fp;
  fp = fopen("data", "r"); // read mode

  for (int i = 0; i < n; i++) {
    int len;
    len = readNextField(buff, 200, fp);
    if (len == 0) return;
    char title[len];
    strcpy(title, buff);

    len = readNextField(buff, 200, fp);
    char desc[len];
    strcpy(desc, buff);


    len = readNextField(buff, 200, fp);
    char date[len];
    strcpy(date, buff);

    readNextField(buff, 200, fp);
    int isDone = 0;
    if (buff[0] == 'T') isDone = 1;

    printf("%s : %s\n\t%s\n\n", date, title, desc);
  }
}

int readNextField(char *buff, int max_len, FILE *fp) {
  char ch;

  for (int i = 0; i < max_len-1; i++) {
    ch = fgetc(fp);
    // printf("%c|", ch);

    if (ch == ';' || ch == '\n' || ch == EOF) {
      buff[i] = '\0'; // add null terminator
      // printf("\n");
      if (ch == EOF) return 0;
      return i;
    }
    buff[i] = ch;
  }
}
