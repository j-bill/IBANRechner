/*
#	IBANRechner
#   calculator.c
#	Copyright (c) 2019 j-bill
#   github.com/j-bill
#	This file is part of "IBANRechner" which is released under the MIT license.
*/

void IBANcalc ()
{
    char blz[9], ktNr[11], temp1[9], temp2[9], temp3[9], temp4[9], land[7] = "131400", IBANroh[25]="";
    int i = 0;
    int k = 0;
    int blzChecked = 0;
    int ktNrChecked = 0;

    //Bankleitzahl eingeben
    while (blzChecked == 0)
    {
        header();
        printf("\nBitte achtstellige Bankleitzahl eingeben> ");
        gets(blz);
        blzChecked = checkBLZ(blz);
    }

    //Kontonummer eingeben
    while (ktNrChecked == 0)
    {
        header();
        printf("\nBitte Kontonummer eingeben> ");
        gets(ktNr);
        ktNrChecked = checkKonto(ktNr);
    }

    //IBAN verbinden
    strcat(IBANroh, blz);
    strcat(IBANroh, ktNr);
    strcat(IBANroh, land);

    //ibans auf 4 strings aufteilen
    for(i = 0; i < 6; i++)
    {
        temp1[i] = IBANroh[i];
    }
    temp1[i] = '\0';

    for(i = 6, k = 0; i < 12; i++, k++)
    {
        temp2[k] = IBANroh[i];
    }
    temp2[k] = '\0';

    for(i = 12, k = 0; i < 18; i++, k++)
    {
        temp3[k] = IBANroh[i];
    }
    temp3[k] = '\0';

    for(i = 18, k = 0; i < 24; i++, k++)
    {
        temp4[k] = IBANroh[i];
    }
    temp4[k] = '\0';

    //Modulo Berechnung
    int iban1 = atoi(temp1);
    int iban2 = atoi(temp2);
    int iban3 = atoi(temp3);
    int iban4 = atoi(temp4);

    iban1 %= 97;
    iban2 += (iban1*1000000);
    iban2 %= 97;
    iban3 += (iban2*1000000);
    iban3 %= 97;
    iban4 += (iban3*1000000);
    iban4 %= 97;
    iban4 = 98-iban4;


    //um die Kontonummer ordentlich anzuzeigen wird sie in einen Integer umgewandelt. Davor waren noch etwaige führende Nullen im String.
    int ktNrNeu = atoi(ktNr);

    //Finish
    header();
    printf("\nEingegebene Kontonummer: \t%i", ktNrNeu);
    printf("\nEingegebene Bankleitzahl: \t%s", blz);
    printf("\n\nErrechnete IBAN: \t\tDE%i%s%s\n\n", iban4, blz, ktNr);
}
