#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#define rows 25
#define columns 80

void begin();
char *create();
double getRandomDoubleInRange(double min, double max);
void display(char *simulation);

int main() {
  initscr();
  noecho();
  raw();
  //   while (1) {
  halfdelay(1);

  begin();

  refresh();
  delay_output(100);
  clear();
  // }
}

void begin() {
  printw("Begin!");
  char *simulation = create();
  if (simulation == NULL) return;
  display(simulation);
}

char *create() {
  char *simulation = (char *)calloc(rows * columns, sizeof(char));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (getRandomDoubleInRange(0.0, 1.0) <= 0.35) {
        *(simulation + i * columns + j) = '#';
      } else {
        *(simulation + i * columns + j) = '.';
      }
    }
  }
  return simulation;
}

double getRandomDoubleInRange(double min, double max) {
  return ((double)rand() / RAND_MAX) * (max - min) + min;
}

void display(char *simulation) {
  printw("\n\n\n\n\n");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printw("%c ", *(simulation + i * columns + j));
    }
    printw("\n");
  }
}
