//
// Created by Besitzer on 10.12.2023.
//
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "appointment.h"
#include "myDateFunctions.h"

/// clears the input of the console
void clearInput() {
#if WIN32 || WIN64
    fflush(stdin);
#else
    getchar();
#endif
}

/// Fordert den Benutzer auf eine Option
/// des main menus aufzurufen
/// \return die jeweilig auszufuerende option
int getUserInputMainMenu(){
    puts("Bitte waehlen sie:");
    puts("1: Termin anlegen.");
    puts("2: Terminserie anlegen.");
    puts("3: Termin loeschen.");
    puts("4: Alle Termine anzeigen.");
    puts("5: naechsten Termin anzeigen.");
    puts("6: Kalenderausgabe.");
    puts("9: Programm beenden.");
    int option;
    scanf("%d", &option);
    return option;
}

int getDauer(){
    puts("Bitte geben sie die laenge ihres Termins ein, maximal 8 stunden aka 28.800 sekunden:");
    int dauerToGet;
    scanf("%d", &dauerToGet);
    if(dauerToGet > 28800){
        puts("der Termin geht zu lange.");
        return 0;
    }else return dauerToGet;
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

int resizeArray(struct Termin *ptr[], int elementsToAddCnt, int currentElementsCnt, struct Termin appointments[]) {
    if (currentElementsCnt == 0) {
        ptr[0] = appointments;
    }
    else {
        realloc(ptr, (sizeof(termin *)*currentElementsCnt + elementsToAddCnt));
    }

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



int main(void) {
    //maximale anzahl appointments per malloc
    struct Termin *appointmentsPtr[1];
    //struct Termin appointments[MAX_APPOINTMENTS];

    int countAppointments = 0, userInputMainMenu;

    while (1) {
        userInputMainMenu = getUserInputMainMenu();
        switch (userInputMainMenu) {
            case 1: {
                //Termin anlegen
                //appointments(countAppointments) = termintest;
                //termintest.startdatum = toScan();

                //struct Termin *appointments = (struct Termin *) malloc(1 * sizeof(struct Termin ));
                struct Termin appointments[2];
                countAppointments = resizeArray(appointmentsPtr, 1, countAppointments, appointments);
                (appointmentsPtr+(countAppointments-1))[0]->dauer = getDauer();
                char title[20];
                getTitel(title);
                stringcpy(appointmentsPtr[countAppointments-1][0].titel, title, 20);
                countAppointments = countAppointments +1;

            }break;
            case 2: {
                //Terminserie anlegen
                //braucht countappointments + 1 für speicheradresse auf terminserie

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
        clearInput();
    }
    return 0;
}