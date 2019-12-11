/*
#	IBANRechner
#   main.c
#	Copyright (c) 2019 j-bill
#   github.com/j-bill
#	This file is part of "IBANRechner" which is released under the MIT license.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include "functions.c"
#include "calculator.c"
#include "validator.c"

int main()
{
    header();
    printf("\nDieses Tool berechnet die IBAN anhand von Kontonummer und Bankleitzahl, alternativ pr\201ft es ob eine IBAN korrekt ist.\n");

    int modus = modusWahl();

    switch (modus)
    {
        case 1:
            {
                IBANcalc();
                break;
            }
        case 2:
            {
                IBANval();
                break;
            }
        default:
            {
                header();
                printf("\nOperation Abgebrochen\n\n");
                return -1;
            }
    }
}
