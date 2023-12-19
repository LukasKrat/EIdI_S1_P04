//
// Created by Besitzer on 10.12.2023.
//
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "appointment.h"
#include "myDateFunctions.h"

#define DAILY 1
#define WEEKLY 2
#define TWEEKLY 3

int getMaxSize(struct Termin **pTermin);

/// clears the input of the console
void clearInput() {
#if WIN32 || WIN64
    fflush(stdin);
#else
    getchar();
#endif
}

void stringcpy(char output[], char input[], int inputLength) {
    for (int i = 0; i < inputLength; i++) {
        output[i] = input[i];
    }
}

/// Function to set the elements of the given array to 0.
/// \param input The array which's elements should be set to 0.
/// \param arrayLength The length of the array.
void setTerminArrayToZero(struct Termin input[], int arrayLength) {
    for (int i = 0; i < arrayLength; i++) {
        input[i].startdatum.tm_year = 0;
        input[i].startdatum.tm_mon = 0;
        input[i].startdatum.tm_mday = 0;
        input[i].startdatum.tm_hour = 0;
        input[i].startdatum.tm_sec = 0;
        input[i].startdatum.tm_min = 0;
        input[i].startdatum.tm_wday = 0;
        input[i].startdatum.tm_yday = 0;
        input[i].startdatum.tm_isdst = 0;
        stringcpy(input[i].titel, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 20);
        input[i].dauer = 0;
    }
}


void toScan(int *mins1, int *hours1, int *day1, int *month1, int *years1, struct tm *Datum1) {
    puts("Den Tag:");

    scanf("%d", day1);
    clearInput();

    puts("Den Monat:");
    scanf("%d", month1);
    clearInput();

    puts("Das Jahr:");
    scanf("%d", years1);
    (*years1) -= 1900;
    clearInput();

    puts("Die Stunde:");
    scanf("%d", hours1);
    clearInput();

    puts("Die Minute:");
    scanf("%d", mins1);
    clearInput();

    (*Datum1) = (struct tm){0, (*mins1) , (*hours1), (*day1), (*month1), (*years1), 0, 0, 0};
}

/// Fordert den Benutzer auf eine Option
/// des main menus aufzurufen
/// \return die jeweilig auszufuerende option
void getUserInputMainMenu(int output[2]){
    puts("Bitte waehlen sie:");
    puts("1: Termin anlegen.");
    puts("2: Terminserie anlegen.");
    puts("3: Termin loeschen.");
    puts("4: Alle Termine anzeigen.");
    puts("5: naechsten Termin anzeigen.");
    puts("6: Kalenderausgabe.");
    puts("9: Programm beenden.");
    //int option;
    scanf("%d", &output[0]);
    //return option;
    clearInput();
}

void getDauer(int output[1]){
    puts("Bitte geben sie die laenge ihres Termins ein, maximal 8 stunden aka 28.800 sekunden:");
    int dauerToGet;
    printf("GetDauerCell: %p\n", output);
    scanf("%d", &output[0]);
    printf("GetDauer: %d\n", output[0]);

    clearInput();

    if(*output > 28800){
        puts("der Termin geht zu lange.");
        output = 0;
        //return 0;
    }//else return dauerToGet;
}

void getTitel(char output[]){
    puts("Bitte geben sie den Titel des Termins ein, maximal 20 zeichen");
    char titelToGet[20];
    //char titelToGet = (char) malloc(sizeof(char) * 20);
    scanf("%s", &output[0]);
    /*
    if(sizeof(titelToGet) > 20){
        puts("der Titel geht zu lange.");
        return;
    }
    */
    //output = titelToGet;
}

/*
 void erstelleTermin(int anzahl){
    getDauer();
    getTitel();

}
 */

int resizeArray(struct Termin *ptr, int elementsToAddCnt, int currentElementsCnt, struct Termin *outPtr) {
    outPtr = (struct Termin *) realloc(ptr, (sizeof(struct Termin)*(currentElementsCnt + elementsToAddCnt)));

    return currentElementsCnt + elementsToAddCnt;
}


/*
///terminausgabe via 2 schleifen, druckt titel, dauer und startdatum aus
void terminAusgabe(*appointmentsPtr, int countAppointments){
    int aussendurchlauf = 0;
    int appointmentArrayEnde = countAppointments;

    //erste schleife, durchläuft alle pointer auf die einzelnen terminserien
    for(aussendurchlauf; aussendurchlauf < appointmentArrayEnde; aussendurchlauf++){

        int innendurchlauf = 0;
        //innere schleife, durchläuft die jeweiligen terminserien und gibt
        // termintitel, dauer, und startdatum aus
        for(innendurchlauf; innendurchlauf < sizeof(*appointmentsPtr); innendurchlauf++){
             printf("Termintitel: %c .", *appointmentsPtr.Titel);
             printf("Termindauer: %d sekunden .", *appointmentsPtr.Dauer);
             asctime(*appointmentsPtr);
        }

        printf("\n");
    }
}
*/

void bubblesort(struct Termin array[], int length)
{
    int i, j;
    struct Termin tmp;

    for (i = 1; i < length; i++)
    {
        for (j = 0; j < length - i; j++)
        {
            int dayOfSelectedWeekAsArray[] = {array[j].startdatum.tm_year+1900, array[j].startdatum.tm_mon, array[j].startdatum.tm_mday, array[j].startdatum.tm_hour,array[j].startdatum.tm_min,array[j].startdatum.tm_sec};
            int nextDayOfSelectedWeekAsArray[] = {array[j+1].startdatum.tm_year+1900, array[j+1].startdatum.tm_mon, array[j+1].startdatum.tm_mday, array[j+1].startdatum.tm_hour,array[j+1].startdatum.tm_min,array[j+1].startdatum.tm_sec};

            long long int unixDayOfSelectedWeek = toUnixtime(dayOfSelectedWeekAsArray);
            long long int unixNextDayOfSelectedWeek = toUnixtime(nextDayOfSelectedWeekAsArray);

            if (unixDayOfSelectedWeek > unixNextDayOfSelectedWeek)
            {
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}

///fordere den benutzer auf eine woche einzugeben fuer die die
/// termine als kalender ausgegeben werden sollen
void getWeek(){
    puts("Bitte geben sie die woche ein die sie ausgeben wollen");
    //erstelle ein tm struct mit eingaben für jahr, monat und tag und wochentag
    //verschiebe sodass unser eingegebener tag montag ist (tm_mday - tm_wday +1)

}

void setTerminCalendarArrayToZero(struct Termin **pTermin) {
    for (int i = 0; i < 7; i++) {
        int cnt = sizeof (pTermin[i]) / sizeof (struct Termin*);
        setTerminArrayToZero(pTermin[i], cnt);
    }
}

//
void kalenderAusgabe(struct Termin *appointmentPtr, struct tm selectedDayOfWeek, int sizeOfAppointmentsArray){
    //struct tm startpunkt = getWeek();

    //-> wieder 2 schleifen für alle werte
    //sortiert nach startzeit, aka stunden und minuten

    //drucke einen wert für montag, dann dienstag.... bis sonntag
    //mache eine neue zeile und wiederhole bis alle gedruckt

    struct Termin **appointmentsPtrWeek;
    appointmentsPtrWeek = (struct Termin**) malloc(sizeof *appointmentsPtrWeek * 7);
    for (int i = 0; i < 7; i++) {
        appointmentsPtrWeek[i] = malloc(sizeof *appointmentsPtrWeek[i] * 1);
    }

    setTerminCalendarArrayToZero(appointmentsPtrWeek);

    int daysSinceMonday = (selectedDayOfWeek.tm_wday + 7 - 1) % 7;
    struct tm mondayDayOfSelectWeek = selectedDayOfWeek;
    mondayDayOfSelectWeek.tm_mday -= daysSinceMonday;
    mktime(&mondayDayOfSelectWeek);

    int mondayDayOfSelectedWeekAsArray[] = {mondayDayOfSelectWeek.tm_year+1900, mondayDayOfSelectWeek.tm_mon, mondayDayOfSelectWeek.tm_mday, 0,0,0};
    long long int mondayDayOfSelectedWeekUnixTime = toUnixtime(mondayDayOfSelectedWeekAsArray);

    int sundayOfSelectedWeekAsArray[] = {mondayDayOfSelectWeek.tm_year+1900, mondayDayOfSelectWeek.tm_mon, mondayDayOfSelectWeek.tm_mday+6, 23,59,59};
    long long int sundayOfSelectedWeekUnixTime = toUnixtime(sundayOfSelectedWeekAsArray);

    // BEGIN: FILTERING

    //int sizeOfAppointmentsArray = sizeof(*appointmentPtr) / sizeof(struct Termin);
    struct Termin **tmp = NULL;

    for (int i = 0; i < sizeOfAppointmentsArray; i++) {
        int dayOfSelectedWeekAsArray[] = {appointmentPtr[i].startdatum.tm_year+1900, appointmentPtr[i].startdatum.tm_mon, appointmentPtr[i].startdatum.tm_mday, appointmentPtr[i].startdatum.tm_hour,appointmentPtr[i].startdatum.tm_min,appointmentPtr[i].startdatum.tm_sec};

        int isInRange = dateInRange(dayOfSelectedWeekAsArray, mondayDayOfSelectedWeekAsArray, sundayOfSelectedWeekAsArray);

        if (isInRange != 1) continue;

        int weekdayIndex = appointmentPtr[i].startdatum.tm_wday == 0 ? 6 :  appointmentPtr[i].startdatum.tm_wday - 1;
        int weekdaySize = sizeof(*appointmentsPtrWeek[weekdayIndex]) / sizeof(struct Termin);

        tmp = (struct Termin**) realloc(appointmentsPtrWeek,sizeof *appointmentsPtrWeek[weekdayIndex] * (weekdaySize+1));

        for (int pd = 0; pd < 7; pd++) {
            for (int pa = weekdaySize; pa < weekdaySize+1; pa++) {
                struct Termin *tmp2 = NULL;
                tmp2 = realloc(tmp[pd],sizeof(struct Termin) * (weekdaySize+1));
                if (tmp2 == NULL) continue;
                tmp[pd] = tmp2;
                //free(tmp2);
            }
        }

        appointmentsPtrWeek = tmp;

        for (int z = 0; z < 7; z++)
        {
            for (int j = weekdaySize; j < weekdaySize+1; j++) {
                appointmentsPtrWeek[z][j].startdatum.tm_year = 0;
                appointmentsPtrWeek[z][j].startdatum.tm_mon = 0;
                appointmentsPtrWeek[z][j].startdatum.tm_mday = 0;
                appointmentsPtrWeek[z][j].startdatum.tm_hour = 0;
                appointmentsPtrWeek[z][j].startdatum.tm_sec = 0;
                appointmentsPtrWeek[z][j].startdatum.tm_min = 0;
                appointmentsPtrWeek[z][j].startdatum.tm_wday = 0;
                appointmentsPtrWeek[z][j].startdatum.tm_yday = 0;
                appointmentsPtrWeek[z][j].startdatum.tm_isdst = 0;
                stringcpy(appointmentsPtrWeek[z][j].titel, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 20);
                appointmentsPtrWeek[z][j].dauer = 0;

                //setTerminArrayToZero(appointmentsPtrWeek[z][j],1);
            }
        }

        appointmentsPtrWeek[weekdayIndex][weekdaySize-1] = appointmentPtr[i];

        //free(tmp);
    }

    // END: FILTERING

    // BEGIN: SORTING

    for (int i = 0; i < 7; i++) {
        int size = sizeof (*appointmentsPtrWeek[i]) / sizeof(struct Termin);
        bubblesort(appointmentsPtrWeek[i], size);
    }

    // END: SORTING

    // BEGIN: PRINT

    int maxAppointsDay = getMaxSize(appointmentsPtrWeek);
    int currentAppointentIndex = 0;

    printf("%26s|%26s|%26s|%26s|%26s|%26s|%26s\n", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag", "Sonntag");

    for (int j = 0; j < maxAppointsDay+1; j++) {
        for (int i = 0; i < 7; i++) {
            int maxSizeDay = sizeof (*appointmentsPtrWeek[i]) / sizeof(struct Termin);
            if (maxSizeDay >= j)
                printf("%20s %2d:%2d|",appointmentsPtrWeek[i][j].titel,appointmentsPtrWeek[i][j].startdatum.tm_hour,appointmentsPtrWeek[i][j].startdatum.tm_min);

            //printf("%26s|", "appointment");
        }
        puts("\n");
    }

    // END: PRINT
    free(appointmentsPtrWeek);
    //free(tmp);
}

int getMaxSize(struct Termin **appointmentsOfWeek) {
    int maxCount = 0;

    for (int i = 0; i < 7; i++) {
        int size = sizeof (*appointmentsOfWeek[i]) / sizeof(struct Termin);
        maxCount = maxCount < size ? size : maxCount;
    }

    return maxCount;
}

/// @brief Creates a series if appointments.
/// @param input The input-parameters (start-date in UTC, interval-mode, number of appointments).
/// @param output The array to which the result should be written.
void createAppointmentsSeries(struct tm input, struct Termin output[], int modeIndex, int appc)
{
    int year = input.tm_year+1900;
    int month = input.tm_mon;
    int day = input.tm_mday;
    int hour = input.tm_hour;
    int minute = input.tm_min;
    int second = input.tm_sec;

    printf("%d\n", modeIndex);

    switch (modeIndex)
    {
    case DAILY:
    {
        /* code */
        for (int i = 0; i < appc; i++)
        {
            int d[] = {year, month, day + i, hour, minute, second};
            long long int unixTime = toUnixtime(d);
            output[i].startdatum = *localtime(&unixTime);
            printf("%d\n", d[0]);
        }

        break;
    }
    case WEEKLY:
    {
        for (int i = 0; i < appc; i++)
        {
            int d[] = {year, month, day + (i * 7), hour, minute, second};
            long long int unixTime = toUnixtime(d);
            output[i].startdatum = *localtime(&unixTime);
            printf("%d-%d-%d\n",output[i].startdatum.tm_year,output[i].startdatum.tm_mon,output[i].startdatum.tm_mday);
        }

        break;
    }
    case TWEEKLY:
    {
        for (int i = 0; i < appc; i++)
        {
            int d[] = {year, month, day + (i * 14), hour, minute, second};
            long long int unixTime = toUnixtime(d);
            output[i].startdatum = *localtime(&unixTime);
        }

        break;
    }
    default:
        break;
    }
}


int main(void) {
    //maximale anzahl appointments per malloc
    struct Termin *appointmentsPtr = NULL;
    appointmentsPtr = malloc(sizeof (struct Termin));
    //struct Termin appointments[MAX_APPOINTMENTS];

    int countAppointments = 0, userInputMainMenu;

    int mins1;
    int hours1;
    int day1;
    int month1;
    int years1;
    struct tm datumInput;

    while (1) {
        int tempUserInput[2];
        getUserInputMainMenu(tempUserInput);
        userInputMainMenu = tempUserInput[0];
        switch (userInputMainMenu) {
            case 1: {
                //Termin anlegen
                //appointments(countAppointments) = termintest;
                //termintest.startdatum = toScan();

                //struct Termin *appointments = (struct Termin *) malloc(1 * sizeof(struct Termin ));
                struct Termin *tmpptr;
                tmpptr = (struct Termin *) realloc(appointmentsPtr, (sizeof(struct Termin)*(countAppointments + 1)));
                countAppointments = countAppointments + 1;
                appointmentsPtr = tmpptr;

                toScan(&mins1,&hours1,&day1,&month1,&years1,&datumInput);

                printf("%d-%d-%d\n", datumInput.tm_year, datumInput.tm_mon, datumInput.tm_mday);

                appointmentsPtr[countAppointments-1].startdatum = datumInput;

                printf("StartDate: %d-%d-%d", (*(appointmentsPtr+(countAppointments-1))).startdatum.tm_year, (*(appointmentsPtr+(countAppointments-1))).startdatum.tm_mon, (*(appointmentsPtr+(countAppointments-1))).startdatum.tm_mday);

                int dauer[1];
                getDauer(dauer);

                printf("Dauer: %d\n", dauer[0]);

                (*(appointmentsPtr+(countAppointments-1))).dauer = dauer[0];
                char title[20];
                getTitel(title);
                stringcpy((*(appointmentsPtr+(countAppointments-1))).titel, title, 20);
                //countAppointments = countAppointments +1;

            }break;
            case 2: {
                //Terminserie anlegen
                //braucht countappointments + 1 für speicheradresse auf terminserie
                int numberOfAppointmentsForSeries = 5; //TODO: Needs to be changed to user-input;

                struct Termin *tmpptr;
                tmpptr = (struct Termin *) realloc(appointmentsPtr, (sizeof(struct Termin)*(countAppointments + numberOfAppointmentsForSeries)));
                //countAppointments = resizeArray(appointmentsPtr, numberOfAppointmentsForSeries, countAppointments, tmpptr);
                appointmentsPtr = tmpptr;
                countAppointments = countAppointments + numberOfAppointmentsForSeries;

                struct tm startDate;

                startDate.tm_year = 123;
                startDate.tm_mon = 11;
                startDate.tm_mday = 11;
                startDate.tm_hour = 9;
                startDate.tm_min = 13;
                startDate.tm_sec = 15;
                startDate.tm_wday = 0;
                startDate.tm_yday = 0;
                startDate.tm_isdst = 0;

                //toScan(&mins1,&hours1,&day1,&month1,&years1,&datumInput);

                //startDate = datumInput;

                char title[20] = "";
                getTitel(title);

                int dauer[1];
                getDauer(dauer);

                int intervalMode[1];
                puts("Bitte interval-modus eingeben:\n");
                scanf("%d", &intervalMode[0]);

                struct Termin series[numberOfAppointmentsForSeries];
                createAppointmentsSeries(startDate,series,intervalMode[0],numberOfAppointmentsForSeries);
                struct Termin *tptr = &appointmentsPtr[0];

                for (int i = 0; i < numberOfAppointmentsForSeries; i++)
                {
                    // Assign content of "series" to main-appointments-array;
                    (*(appointmentsPtr+(countAppointments-numberOfAppointmentsForSeries)+i)).startdatum = series[i].startdatum;
                    (*(appointmentsPtr+(countAppointments-numberOfAppointmentsForSeries)+i)).dauer = dauer[0];
                    
                    //printf("Year: %d\n", (*(appointmentsPtr+(countAppointments-numberOfAppointmentsForSeries)+i)).startdatum.tm_year);
                    //printf("Cell %d: %p\n", i, &(appointmentsPtr[(countAppointments-numberOfAppointmentsForSeries)+i].startdatum.tm_year));

                    stringcpy((*(appointmentsPtr+(countAppointments-numberOfAppointmentsForSeries)+i)).titel, title,20);

                }
                

                //braucht realloc speicherplatz für anzahl der zu speichernden
                // termine * größe des termin structs
            }break;
            case 3: {
                //Termin löschen
                puts("noch nicht implementiert, funktion optional");
            }break;
            case 4: {
                //Alle Termine anzeigen
                //ausgabe via 2 verlinkter schleifen
                //äußere läuft über das pointer-array von
                // appointments wo die terminserien drinstehen (bis appointmentcount)

                //innere schleife läuft über termine (1 element) oder terminserien (bis länge)
                //und gibt das Termin-Struct aus
                for (int i = 0; i < countAppointments; i++) {
                    struct Termin sapp = appointmentsPtr[i];//(*(appointmentsPtr+i));
                    printf("Cell %d: %p : %d\n", i, &(appointmentsPtr[i].startdatum.tm_year), appointmentsPtr[i].startdatum.tm_year);
                    printf("Print|%d-%d-%d\n",sapp.startdatum.tm_year, sapp.startdatum.tm_mon,sapp.startdatum.tm_mday);
                    char dateTime[80] = "";
                    time_t time = mktime(&(sapp.startdatum));
                    strftime(dateTime, 80,"%x",localtime(&time));
                    //printf("%80s\n",dateTime);
                    //printf("%20s\n",(sapp).titel);
                    printf("Datum: %80s, Titel: %20s, Dauer: %d Minuten\n", dateTime, sapp.titel, sapp.dauer);
                }
                //terminAusgabe(*appointmentsPtr, countAppointments);
            }break;
            case 5: {
                //nächsten Termin anzeigen
                puts("noch nicht implementiert, nur fuer Ingenierure verpflichtend");
            }break;
            case 6: {
                //Kalenderausgabe
                toScan(&mins1,&hours1,&day1,&month1,&years1,&datumInput);
                int testDay[] = {years1, month1, day1, hours1, mins1};

                printf("%d-%d-%d %d:%d\n",testDay[0],testDay[1],testDay[2],testDay[3],testDay[4]);

                long long int testDayUnix = toUnixtime(testDay);
                struct tm selectedDayOfWeek = *localtime(&testDayUnix);
                kalenderAusgabe(appointmentsPtr, selectedDayOfWeek, countAppointments);
            }break;
            case 9:
            {
                puts("Programm beendet.");
                return 0; //Programm beenden
            }
            default:
                puts("Ungueltige Eingabe!");
        }
        userInputMainMenu = 0;
        clearInput();
    }
    return 0;
}