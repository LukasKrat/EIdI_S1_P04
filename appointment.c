#include <time.h>

struct Termin{
    struct tm startdatum;
    //maximal 8 stunden
    int dauer;
    char titel[20];
};

typedef struct Termin termin;