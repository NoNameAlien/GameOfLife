#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#define rows 25
#define columns 30

void begin();
char *create();
double getRandomDoubleInRange(double min, double max);
void display(char *simulation);
int countNeighborhood(int x, int y, char *simulation);
char *step(char *prevSimulation);

int main() {
  initscr();
  noecho();
  raw();
  //   while (1) {
  //   halfdelay(1);

  begin();

  //   refresh();
  //   delay_output(100);
  //   clear();
  // }
}

void begin() {
  printw("Begin!\n");
  char *simulation = create();
  if (simulation == NULL) return;
  display(simulation);

  while (1) {
    halfdelay(1);

    char *newSim = step(simulation);
    if (newSim == NULL) return;

    free(simulation);
    simulation = newSim;
    display(simulation);

    refresh();
    delay_output(1000);
    clear();
  }
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
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printw("%c ", *(simulation + i * columns + j));
    }
    printw("\n");
  }
}

int countNeighborhood(int x, int y, char *simulation) {
  int count = 0;
  int pivot = y * columns + x;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      char c = *(simulation + pivot + (i * columns) + j);

      if (c == '#') count++;
    }
  }
  return count;
}

char *step(char *prevSimulation) {
  char *steppedSimulation = calloc(rows * columns, sizeof(int));

  if (steppedSimulation == NULL) return NULL;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      int live = countNeighborhood(j, i, prevSimulation);
      char cell = *(prevSimulation + i * columns + i);
      if (cell == '#') live--;
      *(steppedSimulation + i * columns + i) = cell;

      if (live < 2) {
        *(steppedSimulation + i * columns + j) = '.';
      } else if ((live == 2 || live == 3) && cell == '#') {
        *(steppedSimulation + i * columns + j) = '#';
      } else if (live > 3 && cell == '#') {
        *(steppedSimulation + i * columns + j) = '.';
      } else if (live > 3 && cell == '.') {
        *(steppedSimulation + i * columns + j) = '#';
      }
    }
  }
  return steppedSimulation;
}
