//
// Created by Besitzer on 10.12.2023.
//
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


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

char getTitel(){
    puts("Bitte geben sie den Titel des Termins ein, maximal 20 zeichen");
    char titelToGet[20];
    scanf("%c", &titelToGet);
    if(titelToGet > 20){
        puts("der Titel geht zu lange.");
        return 0;
    }else return titelToGet[];

}
void erstelleTermin(int anzahl){
    getDauer();
    getTitel();
}

void stringcpy(char output[], char input[], int inputLength) {
    for (int i = 0; i < inputLength; i++) {
        output[i] = input[i];
    }
}

int main(void) {
    struct Termin{
        struct tm startdatum;
        //maximal 8 stunden
        int dauer;
        char titel[20];
    }termintest;

    //maximale anzahl appointments per malloc
    struct Termin appointments[MAX_APPOINTMENTS];

    int countAppointments = 0, userInputMainMenu;

    while (1) {
        userInputMainMenu = getUserInputMainMenu();
        switch (userInputMainMenu) {
            case 1: {
                //Termin anlegen
                appointments(countAppointments) = termintest;
                //termintest.startdatum = toScan();
                termintest.dauer = getDauer();
                stringcpy(termintest.titel, getTitel(), 20);
                countAppointments = countAppointments +1;

            }break;
            case 2: {
                //Terminserie anlegen
                //braucht countappointments + 1 für speicheradresse auf terminserie
                //braucht realloc speicherplatz für anzahl der zu speichernden termine * größe des termin structs
            }break;
            case 3: {
                //Termin löschen
                puts("noch nicht implementiert, funktion optional");
            }break;
            case 4: {
                //Alle Termine anzeigen
                //ausgabe via 2 sc
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