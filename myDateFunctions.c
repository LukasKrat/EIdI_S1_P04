#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ENGLISH_US 0
#define ENGLISH_UK 1
#define GERMAN 2
#define SPANISH 3
#define ITALIAN 4

#define ONEDAY 86400
#define ONEHOUR 3600

/// @brief This function checks whether the passed year (y) is a secular-year.
/// @param y The year to check.
/// @return 1 in case it is a secular-year, otherwise 0.
int checkSecYear(int y)
{
    return y % 100 == 0 ? 1 : 0;
}

/// @brief This function checks whether the passed year (y) is a leap-year.
/// @param y The year to check.
/// @return 1 in case it is a leap-year, otherwise 0.
int checkLeapYear(int y)
{
    /// Checks whether the year is a secular-year and stores the return-value in isSecYear.
    int isSecYear = checkSecYear(y);

    return (y % 4 == 0 && isSecYear == 0) || (y % 4 == 0 && isSecYear == 1 && y % 400 == 0) ? 1 : 0;
}

/// @brief This function checks whether the passed month (m) is valid.
/// @param m The month to check, with 1=January (...) 12=December.
/// @return 1 in case the month is valid, otherwise 0.
int checkMonthValid(int m)
{
    return m > 0 && m < 13 ? 1 : 0;
}

/// @brief This function checks whether the passed day for the passed month and information whether the related year is a leap-year or not is valid or not.
/// @param d The day, with 1 being the first day of the month.
/// @param m The month to check, with 1=January (...) 12=December.
/// @param isLY Whether the related year is a leap-year (1) or not (1).
/// @return 1 in case the day is valid for the passed month and leap-year-information, otherwise 0.
int checkDayValid(int d, int m, int isLY)
{
    if (d < 1)
        return 0;

    /// An array of the number of days per month for a non-leap-year. The first element is January, the last December.
    const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // int isEvenMonth = m % 2 == 0 ? 1 : 0;

    int isFebruary = m == 2 ? 1 : 0;

    /*
    return ((isEvenMonth == 1 && isFebruary == 0) && d <= 31) ||
           ((isEvenMonth == 1 && isLY == 1 && isFebruary == 1) && d <= 29) ||
           ((isEvenMonth == 1 && isLY == 0 && isFebruary == 1) && d <= 28) ||
           ((isEvenMonth == 0) && d <= 30);
    */

    return ((isLY == 1 && isFebruary == 1) && d <= monthDays[m - 1] + 1) || (d <= monthDays[m - 1]);
}

/// @brief This function checks whether the passed date-components (year, month, day) are a valid date.
/// @param y The year-component.
/// @param m The month to check, with 1=January (...) 12=December.
/// @param d The day, with 1 being the first day of the month.
/// @return 1 in case the date is valid, otherwise 0.
int checkDateValid(int y, int m, int d)
{
    int isLeapYear = checkLeapYear(y);

    int isMonthValid = checkMonthValid(m);

    int isDayValid = checkDayValid(d, m, isLeapYear);

    return isDayValid == 1 && isMonthValid == 1;
}

/// @brief Returns the name of the day of the week provided as components of a date.
/// @param y The year-component.
/// @param m The month to check, with 1=January (...) 12=December.
/// @param q The day, with 1 being the first day of the month.
/// @return The name of the week-day.
char *getDayOfWeek(int y, int m, int q)
{
    y = 0 < m && m < 3 ? y - 1 : y;
    int K = y % 100;
    int J = y / 100;
    int mAdjusted = 0 < m && m < 3 ? m + 12 : m;
    int stepOne = (13 * (mAdjusted + 1)) / 5;
    int stepTwo = (K / 4);
    int stepThree = (J / 4);
    int h = (q + stepOne + K + stepTwo + stepThree - (2 * J)) % 7;

    switch (h)
    {
    case 0:
        return "Samstag";
        break;
    case 1:
        return "Sonntag";
        break;
    case 2:
        return "Montag";
        break;
    case 3:
        return "Dienstag";
        break;
    case 4:
        return "Mittwoch";
        break;
    case 5:
        return "Donnerstag";
        break;
    case 6:
        return "Freitag";
        break;
    default:
        break;
    }
}

/// @brief The function returns the 0-based index of a weekday provided as date-components.
/// @param y The year-component.
/// @param m The month to check, with 1=January (...) 12=December.
/// @param q The day, with 1 being the first day of the month.
/// @return The 0-based index of a weekday provided by the date-components.
int getDayOfWeekIndex(int y, int m, int q)
{
    y = 0 < m && m < 3 ? y - 1 : y;
    int K = y % 100;
    int J = y / 100;
    int mAdjusted = 0 < m && m < 3 ? m + 12 : m;
    int stepOne = (13 * (mAdjusted + 1)) / 5;
    int stepTwo = (K / 4);
    int stepThree = (J / 4);
    int h = (q + stepOne + K + stepTwo + stepThree - (2 * J)) % 7;
    if (h < 0)
        h += 7;

    switch (h)
    {
    case 0:
        return 5;
        break;
    case 1:
        return 6;
        break;
    case 2:
        return 0;
        break;
    case 3:
        return 1;
        break;
    case 4:
        return 2;
        break;
    case 5:
        return 3;
        break;
    case 6:
        return 4;
        break;
    default:
        return -1;
        break;
    }
}

/// @brief This function prints the date in a country-specific format.
/// @param y The year-component.
/// @param m The month to check, with 1=January (...) 12=December.
/// @param d The day, with 1 being the first day of the month.
/// @param country The country-code.
void printDate(int y, int m, int d, int country)
{
    switch (country)
    {
    case ENGLISH_US:
        printf("%d/%d/%d", m, d, y);
        break;
    case ENGLISH_UK:
        printf("%2d/%2d/%4d", d, m, y);
        break;
    case GERMAN:
        printf("%2d.%2d.%4d", d, m, y);
        break;
    case SPANISH:
        printf("%2d/%2d/%4d", d, m, y);
        break;
    case ITALIAN:
        printf("%2d/%2d/%4d", d, m, y);
        break;
    default:
        printf("%4d-%2d-%2d", y, m, d);
        break;
    }
}

/// @brief This function sets all elements of the passed integer-array to the value of 0.
/// @param days The integer-array which's elements should be set to the value of 0.
void setMonthArrayToZero(int days[6][7])
{
    for (int w = 0; w < 6; w++)
    {
        for (int d = 0; d < 7; d++)
        {
            days[w][d] = 0;
        }
    }
}

/// @brief This function prints the days of a month for a specified in a calendar-format.
/// @param y The year-component.
/// @param m The month to check, with 1=January (...) 12=December.
void printCalendarMonthOfYear(int y, int m)
{
    int days[6][7];
    setMonthArrayToZero(days);

    // # Code-Region-Start: Create array-representation of days in month
    int currentDayOfMonthIndex = 0;

    for (int currentWeekOfMonthIndex = 0; currentWeekOfMonthIndex < 6; currentWeekOfMonthIndex++)
    {
        for (int currentDayOfWeekIndex = 0; currentDayOfWeekIndex < 7; currentDayOfWeekIndex++)
        {
            int currentWeekdayIndex = getDayOfWeekIndex(y, m, currentDayOfMonthIndex + 1);
            currentDayOfWeekIndex = currentWeekdayIndex;

            int isDateValid = checkDateValid(y, m, currentDayOfMonthIndex + 1);

            days[currentWeekOfMonthIndex][currentDayOfWeekIndex] = isDateValid == 1 ? currentDayOfMonthIndex + 1 : 0;
            currentDayOfMonthIndex++;
        }
    }
    // # Code-Region-End: Create array-representation of days in month

    // # Code-Region-Start: Print month
    printf("%d %d\n", m, y);
    for (int weekIndex = 0; weekIndex < 6; weekIndex++)
    {
        for (int dayIndex = 0; dayIndex < 7; dayIndex++)
        {
            if (days[weekIndex][dayIndex] < 1)
                printf("   ");
            else if (days[weekIndex][dayIndex] < 10)
                printf(" %d ", days[weekIndex][dayIndex]);
            else
                printf("%d ", days[weekIndex][dayIndex]);
        }

        printf("\n");
    }
    // # Code-Region-End: Print month
}

/// @brief This function prints all days for all months of a specified year in a calendar-format.
/// @param y The year for which the calendar should be printed.
void printCalendarForYear(int y)
{
    if (y < 1582)
    {
        puts("Ungueltiges Jahr! Das Jahr muss mindestens 1582 sein.\n");
    }

    for (int month = 1; month < 13; month++)
    {
        printCalendarMonthOfYear(y, month);
        puts("-------");
    }
}

long long toUnixtime(int date[])
{
    int j = date[0];
    int m = date[1];
    int D = date[2];
    int h = date[3];
    int M = date[4];
    int s = date[5];

    // printf("%d\n",j);
    // printf("%d\n",m);
    // printf("%d\n",D);
    // printf("%d\n",h);
    // printf("%d\n",M);
    // printf("%d\n",s);

    int dj[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

    int dl = checkLeapYear(j) == 1 && m > 2 ? 1 : 0;
    // printf("dl: %d\n",dl);

    long long Ul = (j - 1 - 1968) / 4 - (j - 1 - 1900) / 100 + (j - 1 - 1600) / 400;
    // printf("Ul: %d\n",Ul);

    long long Ud = (j - 1970) * 365 + Ul + dj[m - 1] + D - 1 + dl;
    // printf("Ud: %d\n",Ud);

    // Old: //long long UH = Ud * 24 + h;
    long long UH_s = Ud * ONEDAY + h * ONEHOUR;
    // printf("UH: %d\n",UH);

    // Old: //long long UM = UH * 60 + M;
    long long UM = /*UH * 60 +*/ M;
    // printf("UM: %d\n",UM);

    long long Us = UM * 60 + s;
    // printf("Us: %d\n",Us);

    return Us + UH_s;
}

/// Returns the given timestamp as a string, formatted as german short date
const char *unixtimeToString(long long timeStamp)
{
    struct tm *date;
    date = localtime(&timeStamp);
    static char str[20];
    strftime(str, sizeof(str), "%d.%m.%Y %H:%M:%S", date);
    return str;
}

/// Compares two dates ’first’ and ’second’
/// \param first
/// \param second
/// \return Returns 1 if ’first’ > ’second’, -1 if ’first’ \< ’second’,
/// if ’first’ equals ’second’
int compare(int first[], int second[]) {
    long long int ufirst = toUnixtime(first);
    long long int usecond = toUnixtime(second);
    
    if (ufirst > usecond) return 1;
    else if (ufirst < usecond) return -1;
    else if (ufirst == usecond) return 0;
}

int dateInRange(int date[], int dateLowerLimit[], int dateUpperLimit[]) {
    long long int udate = toUnixtime(date);
    long long int udateLL = toUnixtime(dateLowerLimit);
    long long int udateUL = toUnixtime(dateUpperLimit);

    return udateLL <= udate && udate <= udateUL ? 1 : 0;
}