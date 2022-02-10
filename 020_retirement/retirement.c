#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void helperF(int startAge, double balance) {
  int yearsOld = startAge / 12;
  int monthsOld = startAge % 12;
  printf("Age %3d month %2d you have $%.2lf\n", yearsOld, monthsOld, balance);
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;
  for (int i = 0; i < working.months; i++) {
    helperF(startAge, balance);
    startAge++;
    balance += balance * working.rate_of_return + working.contribution;
  }

  for (int i = 0; i < retired.months; i++) {
    helperF(startAge, balance);
    startAge++;
    balance += balance * retired.rate_of_return + retired.contribution;
  }
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  retirement(327, 21345, working, retired);
  return EXIT_SUCCESS;
}
