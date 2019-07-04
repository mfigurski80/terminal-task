#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addTask(char *, char *, char *);
void printNTasks(int);
void printAllTasks();
int readNextTask(char *, int, FILE *);
int readNextField(char *, int, FILE *);
void printHelp();


char fileName[] = "./data";

void main(int argc, char *argv[]) {

  // default: no arguments
  if (argc == 1) return printNTasks(1);

  // read second argument, switch second character...
  switch(argv[1][1]) {

    case 'a':
      addTask(argv[2], argv[3], argv[4]);
      break;

    case 'p':
      printAllTasks();
      break;

    case 'd':
      break;

    case 'h':
    default:
      // Display help
      printHelp();
  }


}


/**
 * Adds a task to end of file
 * @param title       String pointer to title
 * @param description String pointer to description
 * @param importance  String pointer to importance (should be 0-9 int tho)
 */
void addTask(
  char *title,
  char *description,
  char *importance
) {
  printf("TITLE: %s\nDESCRIPTION: %s\nIMPORTANCE: %s\n", title, description, importance);
  FILE *fp;
  fp = fopen(fileName, "a"); // append mode
  fprintf(fp, "%s;%s;%s;F\n", title, description, importance);
}


/**
 * Prints given amount of tasks
 * @param n Number of tasks to print
 */
void printNTasks(int n) {
  char buff[600];
  FILE *fp;
  fp = fopen(fileName, "r"); // read mode

  int len;

  for (int i = 0; i < n; i++) {
    len = readNextTask(buff, 600, fp);
    if (len == 0) return;
    printf("%s\n", buff);
  }
}

/**
 * Prints all tasks
 */
void printAllTasks() {
  char buff[600];
  FILE *fp;
  fp = fopen(fileName, "r");

  int len = 1;

  while (len != 0) {
    len = readNextTask(buff, 600, fp);
    printf("%s\n", buff);
  }
}





/**
 * Reads a single task from data
 * @param  buff    String to output into
 * @param  max_len Maximum length to allow
 * @param  fp      File to read from
 * @return         Real return string length
 */
int readNextTask(char *buff, int max_len, FILE *fp) {
  buff[0] = '\0'; // begin with null terminator
  int len;
  char bff[200];

  len = readNextField(bff, 200, fp); // read title
  if (len == 0) return 0;            // if EOF
  char title[len];
  strcpy(title, bff);
  // printf("%s\n", title);

  len = readNextField(bff, 200, fp); // read description
  char desc[len];
  strcpy(desc, bff);

  len = readNextField(bff, 200, fp); // read importance level
  char imp[len];
  strcpy(imp, bff);

  readNextField(bff, 200, fp);       // read if is complete
  int isDone = 0;
  if (bff[0] == 'T') isDone = 1;

  int totalLen = (sizeof(title) / sizeof(title[0])) + (sizeof(desc) / sizeof(desc[0])) + 3;
  if (totalLen > max_len) { // if can't fit in buff
    printf("[readNextTask] buffer overflow");
    return 0;
  }

  strcpy(buff, title);
  strcat(buff, ":\n\t");
  strcat(buff, desc);
  buff[totalLen] = '\0'; // add null terminator

  return totalLen;
}


/**
 * Reads next field from given file
 * @param  buff    String to output into
 * @param  max_len Maximum length to expect
 * @param  fp      File to read from
 * @return         True length of read string
 */
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



void printHelp() {
    printf("\nTask Manager: arguments\n\n");
    printf("\t-p : print all tasks\n");
    printf("\t-a <title> <description> <importance> : add task\n");
    printf("\t-d <title> : toggle task-complete\n");
    printf("\t-x <title> : delete task\n");
    printf("\t-h : this help manual\n");
}
