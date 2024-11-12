#include "wireminnow.h"

/*
    Converts and prints epoch time to readable time.
*/
void print_epoch(int epoch) {
  
  int cur_year = 1970;
  while (1) {
    if (cur_year % 100 == 0 && cur_year % 400 == 0 
        || cur_year % 4 == 0) {
      if (epoch - SECONDS_LEAP_YEAR >= 0) {
        epoch -= SECONDS_LEAP_YEAR;
      } else {
        break;
      }
    } else {
      if (epoch - SECONDS_YEAR >= 0) {
        epoch -= SECONDS_YEAR;
      } else {
        break;
      }
    }
    cur_year++;
  }

  int days = epoch / 86400;
  epoch -= days * 86400;

  char * month_name[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  
  if (cur_year % 100 == 0 && cur_year % 400 == 0) {
    month_days[1] += 1; 
  }
  if (cur_year % 4 == 0) {
    month_days[1] += 1;
  }

  int month;
  int day;
  for (int i = 0; i < 12; i++) {
    if (days - month_days[i] >= 0) {
      days -= month_days[i];
    } else {
      month = i;
      day = days + 1;
      break;
    }
  }

  int hour = epoch / 3600;
  epoch -= hour * 3600;
  int min = epoch / 60;

  printf("%s %d, %d %02d:%02d", month_name[month], day, cur_year, hour, min);

}

/*********************/
