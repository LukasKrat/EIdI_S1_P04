#ifndef APPOINTMENTS_DEFINITIONS_H
#define APPOINTMENTS_DEFINITIONS_H
struct Termin{
    struct tm startdatum;
    //maximal 8 stunden
    int dauer;
    char titel[20];
};
typedef struct Termin termin;
#endif