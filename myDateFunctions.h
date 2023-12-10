#ifndef MY_DATE_FUNCTIONS
#define MY_DATE_FUNCTIONS

int checkSecYear(int y);
int checkLeapYear(int y);
int checkMonthValid(int m);
int checkDayValid(int d, int m, int isLY);
int checkDateValid(int y, int m, int d);
char *getDayOfWeek(int y, int m, int q);
int getDayOfWeekIndex(int y, int m, int q);
void printDate(int y, int m, int d, int country);
void setMonthArrayToZero(int days[6][7]);
void printCalendarMonthOfYear(int y, int m);
void printCalendarForYear(int y);
long long toUnixtime(int date[]);
const char *unixtimeToString(long long timeStamp);
int compare(int first[], int second[]);

#endif