/*
#	IBANRechner
#   validator.c
#	Copyright (c) 2019 j-bill
#   github.com/j-bill
#	This file is part of "IBANRechner" which is released under the MIT license.
*/

void IBANval()
{
    char iban[23], blz[9], ktNr[11], cc[3], pz[3];
    char temp1[9], temp2[9], temp3[9], temp4[9], land[7] = "131400", IBANroh[25]="";
    int i = 0;
    int k = 0;
    int ibanChecked = 0;

    while (ibanChecked == 0)
    {
        //iban entleeren (macht probleme wenn die länge oder cc nicht gepasst hat)
        strcpy(iban, "");

        while ((strlen(iban) != 22))
        {

            header();
            printf("\nBitte geben Sie die zu pr\201fende IBAN ein> ");
            gets(iban);

            if (strlen(iban) < 22)
            {

                header();
                printf("\nFehler: Die eingegebene IBAN ist zu kurz, dies ist nicht zul\204ssig.");
                printf("\n\nTaste dr\201cken um fortzufahren.");
                getch();
            }
            if (strlen(iban) > 22)
            {

                header();
                printf("\nFehler: Die eingegebene IBAN ist zu lang, dies ist nicht zul\204ssig.");
                printf("\n\nTaste dr\201cken um fortzufahren.");
                getch();
            }

        }

        //aufteilen cc/pz/blz/ktNr
        for(i = 0; i < 2; i++)
        {
            cc[i] = iban[i];
        }
        cc[i] = '\0';

        for(i = 2, k = 0; i < 4; i++, k++)
        {
            pz[k] = iban[i];
        }
        pz[k] = '\0';

        for(i = 4, k = 0; i < 12; i++, k++)
        {
            blz[k] = iban[i];
        }
        blz[k] = '\0';

        for(i = 12, k = 0; i < 22; i++, k++)
        {
            ktNr[k] = iban[i];
        }
        ktNr[k] = '\0';

        ibanChecked = checkIBAN(cc, pz, blz, ktNr);
    }

    //IBAN verbinden
    strcat(IBANroh, blz);
    strcat(IBANroh, ktNr);
    strcat(IBANroh, land);

    //ibans auf 4 strings aufteilen
    //abgeleitet von https://www.techcrashcourse.com/2016/05/c-program-to-split-string-into-two-equal-strings.html
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

    //Modulo ausrechnen von den einzelnen iban[n], mit 1.000.000 multiplizieren und mit dem nächsten String addieren
    //abschließend von 98 abziehen um die Korrekte Iban zu bekommen.
    int iban1 = atoi(temp1);
    int iban2 = atoi(temp2);
    int iban3 = atoi(temp3);
    int iban4 = atoi(temp4);

    iban1 %= 97;
    iban2 = (iban1*1000000) + iban2;
    iban2 %= 97;
    iban3 = (iban2*1000000) + iban3;
    iban3 %= 97;
    iban4 += (iban3*1000000);
    iban4 %= 97;
    iban4 = 98-iban4;

    //Damit Kontonumme im folgenden nicht mit führender Null gezeigt wird
    int ktNrNeu = atoi(ktNr);

    //Finish
    if (iban4 == atoi(pz))
    {

        header();
        printf("\nDie von Ihnen eingegebene IBAN DE%s%s%s ist korrekt.\n", pz, blz, ktNr);
        printf("\n\nDie Bankleitzahl lautet:\t%s", blz);
        printf("\nDie Kontonummer lautet:\t\t%i\n\n", ktNrNeu);
    }
    else
    {

        header();
        printf("\nDie von Ihnen eingegebene IBAN DE%s%s%s ist nicht korrekt.\n", pz, blz, ktNr);
        printf("\n\nDie Bankleitzahl lautet:\t%s", blz);
        printf("\nDie Kontonummer lautet:\t\t%i", ktNrNeu);
        printf("\nDie korrekte Pr\201fziffer w\204re:\t%i\n\n", iban4);
    }
}
