#include <stdio.h>
#include <stdlib.h>

int readNextField(char *, int, FILE *);


int main(int argc, char *argv[]) {
  // printf("You've given %d argument(s):\n", argc);
  // for (int i = 0; i < argc; i++) {
  //   printf("\t%s\n", argv[i]);
  // }


  char buff[200];

  FILE *fp;
  fp = fopen("data", "r"); // read mode

  while(1) {
    int len = readNextField(buff, 200, fp);
    printf("'%s'\n", buff);
    if (len == 0) break;
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
