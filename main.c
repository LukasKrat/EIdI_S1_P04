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

/// clears the input of the console
void clearInput() {
#if WIN32 || WIN64
    fflush(stdin);
#else
    getchar();
#endif
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
        input[i].startdatum.tm_sec = 0;
        input[i].startdatum.tm_wday = 0;
        input[i].startdatum.tm_yday = 0;
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

void stringcpy(char output[], char input[], int inputLength) {
    for (int i = 0; i < inputLength; i++) {
        output[i] = input[i];
    }
}

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


///fordere den benutzer auf eine woche einzugeben fuer die die
/// termine als kalender ausgegeben werden sollen
void getWeek(){
    puts("Bitte geben sie die woche ein die sie ausgeben wollen");
    //erstelle ein tm struct mit eingaben für jahr, monat und tag und wochentag
    //verschiebe sodass unser eingegebener tag montag ist (tm_mday - tm_wday +1)

}


//
void kalenderAusgabe(){
    //struct tm startpunkt = getWeek();

    //-> wieder 2 schleifen für alle werte
    //sortiert nach startzeit, aka stunden und minuten

    //drucke einen wert für montag, dann dienstag.... bis sonntag
    //mache eine neue zeile und wiederhole bis alle gedruckt

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

                //(*(appointmentsPtr+(countAppointments-1))).startdatum = datumInput;
                appointmentsPtr[countAppointments-1].startdatum = datumInput;

                //(*(appointmentsPtr+(countAppointments-1))).dauer = getDauer();

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
                startDate.tm_mon = 10;
                startDate.tm_mday = 11;
                startDate.tm_hour = 9;
                startDate.tm_min = 13;
                startDate.tm_sec = 15;
                startDate.tm_wday = 0;
                startDate.tm_yday = 0;
                startDate.tm_isdst = 0;

                char title[20];
                getTitel(title);

                int dauer[1];
                getDauer(dauer);

                struct Termin series[numberOfAppointmentsForSeries];
                createAppointmentsSeries(startDate,series,WEEKLY,numberOfAppointmentsForSeries);
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
            }break;
            case 9:
                puts("Programm beendet.");
                return 0; //Programm beenden
            default:
                puts("Ungueltige Eingabe!");
        }
        userInputMainMenu = 0;
        clearInput();
    }
    return 0;
}