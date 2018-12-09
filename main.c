#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const long int NESPRAVNY_VSTUP = -1;

struct usek {
    long int zaciatok;  /*zaciatok useku*/
    long int koniec;
    double myto[26];    /*pole pre myto A..Z*/
};
struct usek *useky;

long int maxPocet = 100, pocetKrok = 100;   /*maxPocet alokovanych usekov, a kolko bude realloc*/
long int pocet;     /*skutocny pocet usekov*/

char preskocMedzery(){
    char tmp;
    do {
        tmp = getchar();
    }while (tmp == ' ' || tmp== '\n' || tmp== '\t' || tmp== '\r'); /*preskocim vsetky medzery*/
    return tmp;
}
long int nacitajVstupy() {
    /*nacita hodnoty zo stdin. Ak je chyba -> NESPRAVNY_VSTUP*/
    char myto, tmpOddelovac;
    int tmp, j;
    long int i = 0, km;
    double cena;
    printf("Myto:\n");

    tmp=preskocMedzery();
    if (tmp != '{')
        return NESPRAVNY_VSTUP;
    do {
        tmp = scanf(" [ %li ", &km);
        if (tmp != 1 || km <= 0)
            return NESPRAVNY_VSTUP;
        useky[i].koniec = useky[i].zaciatok + km;

        tmp=preskocMedzery();
        if (tmp != ':')
            return NESPRAVNY_VSTUP;

        do {
            tmp = scanf(" %c = %lf %c", &myto, &cena, &tmpOddelovac);
            if (tmp != 3 || myto < 'A' || myto > 'Z' || cena < 0 || (tmpOddelovac != ',' && tmpOddelovac != ']'))
                return NESPRAVNY_VSTUP;
            useky[i].myto[myto - 'A'] = cena;

        } while (tmpOddelovac != ']');
        tmp=preskocMedzery();
        if (tmp == '}')
            return i + 1;

        if (tmp != ',')
            return NESPRAVNY_VSTUP;

        if (++i >= maxPocet) { /*treba alokovat dalsi usek*/
            maxPocet = maxPocet + pocetKrok;
            useky = (struct usek *) realloc(useky, maxPocet * (sizeof(struct usek)));
        }

        useky[i].zaciatok = useky[i - 1].koniec;    /*stary koniec => novy zaciatok, prekopirujem stare poplatky*/
        for (j = 0; j < 26; ++j)
            useky[i].myto[j] = useky[i - 1].myto[j];

    } while (1);    /*rob furt*/
}

int urciMyto(long int zaciatok, long int koniec) {
    /*nacita hodnoty zo stdin a urci myto. Ak je chyba -> NESPRAVNY_VSTUP*/
    long int i = 0, j, vzdialenost = 0, zx, kx;
    double zaplat[26];
    int somNaKonci, uzJeDacoVypisane;

    /*init*/
    for (j = 0; j < 26; ++j) zaplat[j] = 0;
    somNaKonci = false;
    uzJeDacoVypisane = false;

    if (zaciatok > koniec) {
        kx = zaciatok;
        zx = koniec;
    } else {
        kx = koniec;
        zx = zaciatok;
    }
    if (zaciatok == koniec || zx < 0 || kx < 0 || zx> useky[pocet-1].koniec || kx> useky[pocet-1].koniec)
        return NESPRAVNY_VSTUP;

    do {
        if (vzdialenost == 0) {
            if (zx < useky[i].koniec) {
                if (kx < useky[i].koniec) {
                    vzdialenost = kx - zx;
                    somNaKonci = true;
                } else {
                    vzdialenost = useky[i].koniec - zx;
                }
            }
        } else {
            if (kx < useky[i].koniec) {
                vzdialenost = kx - useky[i].zaciatok;
                somNaKonci = true;
            } else {
                vzdialenost = useky[i].koniec - useky[i].zaciatok;
            }
        }
        if (vzdialenost != 0)
            for (j = 0; j < 26; ++j)
                if (useky[i].myto[j] > 0)
                    zaplat[j] = zaplat[j] + vzdialenost * useky[i].myto[j];

    } while (++i < pocet && !somNaKonci);

    printf("%li - %li: ", zaciatok, koniec);
    for (j = 0; j < 26; ++j)
        if ((zaplat[j]) != 0) {
            if (uzJeDacoVypisane)
                printf(", ");
            else
                uzJeDacoVypisane = true;
            printf("%c=%lf", (char) ('A' + j), zaplat[j]);
        }
    printf("\n");

    return 1;
}

int main() {
    long int zaciatok, koniec;
    int tmp, tmpOddelovac;
    useky = (struct usek *) calloc((size_t) maxPocet, sizeof(struct usek));

    pocet = nacitajVstupy();
    if (pocet == NESPRAVNY_VSTUP || pocet<1) {
        printf("Nespravny vstup.\n");
        return NESPRAVNY_VSTUP;
    }

    printf("Hledani:\n");
    do {
        tmp = scanf("%li %li", &zaciatok, &koniec);
        tmpOddelovac = getchar();
        if (tmp <= 0 && tmpOddelovac == EOF)
            return 0;
        if (tmp != 2 || (tmpOddelovac != EOF && tmpOddelovac != '\n' && tmpOddelovac != ' ')) {
            printf("Nespravny vstup.\n");
            return NESPRAVNY_VSTUP;
        }
        /*vstupy su zrejme v poriadku, skusim vypocitat myto*/
        if (urciMyto(zaciatok, koniec) == NESPRAVNY_VSTUP) {
            printf("Nespravny vstup.\n");
            return NESPRAVNY_VSTUP;
        }
    } while (tmpOddelovac != EOF);
}



