//
// Created by Besitzer on 08.12.2023.
//

/*
 *
 *
 * aufgabe 1 a)
 *
 * Aufbau von struct tm:
 *
 *  - struct tm enthält die bestandteile eines datums
 *  aufgeteilt auf einzelne komponenten, die sind:
 *  sekunden, minuten, stunden, tage im monat, monate
 *  seit Januar, Jahre seit 1900 (startjahr), wochentag
 *  seit sonntag, die tage seit dem 1 Jannuar und, ob
 *  es gerade sommerzeit ist
 *
 * Feld tm_isdst:
 *
 *  - tm_isdst steht als kennzeichen für Sommerzeit
 *      - positiv wenn sommmerzeit gilt
 *      - null wenn sommerzeit nicht gilt
 *      - negativ wenn die information nicht verfügbar ist
 *
 * Unterschied tm_mday und tm_yday:
 *
 *  - tm_mday und tm_yday unterscheiden sich darin, dass
 *  mday die tage im monat (1-31) speichert, während
 *  yday die tage seit dem 1 Januar (0-365) speichert
 *
 *  Beschreibung von strftime():
 *
 * - strftime() nimmt ein Datum vom Typ struct, nimmt
 * tag im monat, monat, jahr mit jahrhundert, stunde, minute und wandelt diese
 * in einen string um. sind mehr zeichen im datum enthalten als gespeichert
 * werden können (100), soll anstelle dessen 0 zurückgegeben werden
 *
 * Ausgabe von strftime():
 *
 * - Die Ausgabe sollte lauten:
 *      - "4.7.2023 17:32"
 *
 *
 *
 * Beschreibung von doSomething:
 *
 *  - doSomething setzt den pointer für das aktuelle element auf die adresse
 * für start und prüft ob start noch < end, sonst soll die fkt stoppen
 *
 *  - solange start < end bleibt wird der tag im monat, von current, lokal um
 * 7 (eine woche) erhöht, dann ein TimeStamp dessen erstellt im Kalenderzeit
 * format, und darauffolgend der TimeStamp in Ortszeit umgewandelt und
 * wieder in current gespeichert.
 *
 * - kurz: erhöhe monats tage um 7, wandle sie in kalenderzeit um, wandle
 * zurück in localtime
 *
 *
 *
 * Zeile 12 gmtime() anstelle localtime()
 *
 *  - würde gmtime verwendet werden anstelle localtime wird von kalenderzeit in
 * UTC umgewandelt und nicht in Ortszeit, was bedeutet, dass zur momentanen
 * Winterzeit ein Unterschied von 1 Stunde besteht, der pro schleifenaufruf
 * kumulativ erhöht
 *
 */



