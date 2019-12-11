/*
#	IBANRechner
#   functions.c
#	Copyright (c) 2019 j-bill
#   github.com/j-bill
#	This file is part of "IBANRechner" which is released under the MIT license.
*/



//Header
void header()
{
    system("@cls||clear");
    printf("######################################################\n");
    printf("############# I B A N ################################\n");
    printf("########################## R E C H N E R #############\n");
    printf("######################################################\n");
}

//Funktion zur Wahl des Modus
//da getch() einen char kreiert wird das ganze mit atoi zu einem int umgewandelt und in einem switch ausgewertet.
int modusWahl()
{
    printf("\nZur Auswahl stehen die folgenden M\224glichkeiten:\n\n");
    printf("(1) Berechnung der IBAN\n");
    printf("(2) Pr\201fung der IBAN\n\n");
    printf("ESC Dr\201cken zum abbrechen.\n\n");
    printf("Wahl> ");
    //getch() zum abfangen vom input ohne das man die Eingabe mit Enter bestätigen muss.
    char wahl = getch();
    //wenn wahl 27, also Esc ist dann wird die Funktion beendet und -1 returned.
    if (wahl == 27)
        return -1;

    //da getch() einen char kreiert wird das ganze mit atoi zu einem int umgewandelt und in einem switch ausgewertet.
    int newWahl = atoi(&wahl);
    switch (newWahl)
    {
    case 1:
        return 1;
    case 2:
        return 2;
    default:
        header();
        printf("\nWahlm\224glichkeiten 1, 2, oder ESC zum Abbrechen.\n");
        modusWahl();
    }
    return 0;
}

//BLZ auf Buchstaben und Länge prüfen
int checkBLZ (char* blz)
{
    int i = 0;

    //solange blz[i] existiert
    while (blz[i])
    {
        //wenn blz[i] einen buchstaben enthält
        if (isalpha(blz[i]))
        {
            header();
            printf("\nFehler: Die eingegebene Bankleitzahl enth\204lt Buchstaben, dies ist nicht zul\204ssig.");
            printf("\n\nTaste dr\201cken um fortzufahren.");
            getch();
            //fliegt hier raus mit return 0 und bittet um erneute eingabe der Bankleitzahl
            return 0;
        }
        //um die nächste Stelle zu überprüfen
        i++;
    }
    if (strlen(blz) == 8)
        return 1;
    else
    {
        header();
        printf("\nFehler: Die eingegebene Bankleitzahl ist nicht 8 Ziffern lang, dies ist nicht zul\204ssig.");
        printf("\n\nTaste dr\201cken um fortzufahren.");
        getch();
        return 0;
    }
}

//Überprüft erst ob ktNr einen Buchstaben enthält, gleich wie checkBlz(), und kümmert sich dann um führende Nullen.
int checkKonto(char* ktNr)
{
    int i = 0;
    while (ktNr[i])
    {
        if (isalpha(ktNr[i]))
        {
            header();
            printf("\nFehler: Die eingegebene Kontonummer enth\204lt Buchstaben, dies ist nicht zul\204ssig.");
            printf("\n\nTaste dr\201cken um fortzufahren.");
            getch();
            return 0;
        }
        i++;
    }

    //Base Kontonummer zum auffüllen der Kontonummer mit führenden Nullen
    char base[] = "0000000000";

    if (strlen(ktNr) <= 10)
    {
        //Anzahl der Benötigten Nullen wird ausgerechnet
        int leadingZero = (10-(strlen(ktNr)));
        //Kontonummer wird auf leadingZero kopiert an die richtige Stelle
        strcpy(base+(leadingZero), ktNr);
        //der wert von base wird auf ktNr kopiert
        strcpy(ktNr, base);
        return 1;
    }
    else
    {
        header();
        printf("\nFehler: Die eingegebene Kontonummer ist zu lang, dies ist nicht zul\204ssig.");
        printf("\n\nTaste dr\201cken um fortzufahren.");
        getch();
        return 0;
    }
}

int checkIBAN(char* cc, char* pz, char* blz, char* ktNr)
{
    printf("checkIBAN\n");
    char de[3] = "DE";
    char temp[21];
    int i = 0;

    //überprüft ob es sich um eine Deutsche IBAN handelt
    //strupr falls DE kleingeschrieben ist
    if (strcmp(strupr(cc), de) != 0)
    {
        header();
        printf("\nFehler: Die L\204nder Kodierung der IBAN ist falsch. Dieser Rechner funktioniert nur mit deutschen IBANs.\n");
        printf("\n\nTaste dr\201cken um fortzufahren.");
        getch();
        return 0;
    }

    //nimmt pz, blz, ktNr und überprüft ob sich da ein Buchstabe versteckt wo er nicht hingehört
    strcat(temp, pz);
    strcat(temp, blz);
    strcat(temp, ktNr);

    while (temp[i])
    {
        if (isalpha(temp[i]))
        {
            header();
            printf("\nFehler: Die eingegebene IBAN enth\204lt nach dem L\204ndercode Buchstaben, dies ist nicht zul\204ssig.");
            printf("\n\nTaste dr\201cken um fortzufahren.");
            getch();
            return 0;
        }
        i++;
    }

    //wenn alles passt dann
    return 1;
}


