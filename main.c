#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const long int NESPRAVNY_VSTUP = -1;

struct usek {
    long long int zaciatok;  //zaciatok useku
    long long int koniec;
    double myto[26]; //pole pre myto A..Z
};
struct usek *useky;
long long int maxPocet = 100, pocetKrok = 100;    //maxPocet alokovanych usekov, a kolko bude realloc
long long int pocet;     //skutocny pocet usekov


long int nacitajVstupy();    //nacita hodnoty zo stdin. Ak je chyba -> NESPRAVNY_VSTUP

int urciMyto(long long int zaciatok,
             long long int koniec); //nacita hodnoty zo stdin a urci myto. Ak je chyba -> NESPRAVNY_VSTUP

int main() {

//struct usek *useky;
    long long int i, zaciatok, koniec;
    int tmp, tmpOddelovac;
    useky = (struct usek *) calloc(maxPocet, sizeof(struct usek));

    pocet = nacitajVstupy();
    if (pocet == NESPRAVNY_VSTUP || pocet<1) {
        printf("Nespravny vstup.\n");
        return NESPRAVNY_VSTUP;
    }

    //skusim precitat zaciatok a koniec
    printf("Hledani:\n");
    do {
        tmp = scanf("%lli %lli", &zaciatok, &koniec);
        tmpOddelovac = getchar();
        if (tmp <= 0 && tmpOddelovac == EOF)
            return 0;
        if (tmp != 2 || (tmpOddelovac != EOF && tmpOddelovac != '\n' && tmpOddelovac != ' ')) {
            printf("Nespravny vstup.\n");
            return NESPRAVNY_VSTUP;
        }
        //vstupy su zrejme v poriadku, skusim vypocitat myto
        if (urciMyto(zaciatok, koniec) == NESPRAVNY_VSTUP) {
            printf("Nespravny vstup.\n");
            return NESPRAVNY_VSTUP;
        }
    } while (tmpOddelovac != EOF);


}

long int nacitajVstupy() {
    char myto, tmpOddelovac;
    int tmp, j;
    long long int i = 0, km;
    double cena;
    printf("Myto:\n");

/*    //debug nastavenie hodnot
    //ocakavam { [ 50: A=10.5, E=80 ], [ 30: Z=20, A=7.5, X=130 ], [ 200: A=0, E=300 ] }
    useky[0].zaciatok = 0;
    useky[0].koniec = 50;
    useky[0].myto[0] = 10.5;
    useky[0].myto[4] = 80;
    useky[1].zaciatok = 50;
    useky[1].koniec = 80;
    useky[1].myto[0] = 7.5;
    useky[1].myto[4] = 80;
    useky[1].myto[25] = 20;
    useky[1].myto[23] = 130;
    useky[2].zaciatok = 80;
    useky[2].koniec = 280;
    useky[2].myto[0] = 0;
    useky[2].myto[4] = 300;
    useky[2].myto[25] = 20;
    useky[2].myto[23] = 130;
//koniec debugu
    //return NESPRAVNY_VSTUP;
    return 3;*/

    do { tmp = getchar(); } while (tmp == ' ');  //preskocim vsetky medzery
    if (tmp != '{')
        return NESPRAVNY_VSTUP;
    do {
        tmp = scanf(" [ %lli : ", &km);
        if (tmp != 1 || km < 0)
            return NESPRAVNY_VSTUP;
        useky[i].koniec = useky[i].zaciatok + km;

        do {
            tmp = scanf(" %c = %lf %c", &myto, &cena, &tmpOddelovac);
            if (tmp != 3 || myto < 'A' || myto > 'Z' || cena < 0 || (tmpOddelovac != ',' && tmpOddelovac != ']'))
                return NESPRAVNY_VSTUP;
            useky[i].myto[myto - 'A'] = cena;

        } while (tmpOddelovac != ']');
        do { tmp = getchar(); } while (tmp == ' ');  //preskocim vsetky medzery
        if (tmp == '}')
            return i + 1;   //koniec vypoctu

        if (tmp != ',')
            return NESPRAVNY_VSTUP;

        //novy usek
        if (++i >= maxPocet) {   //treba alokovat dalsi usek
            maxPocet = maxPocet + pocetKrok;
            useky = (struct usek *) realloc(useky, maxPocet * (sizeof(struct usek)));
        }
        useky[i].zaciatok = useky[i - 1].koniec;    //stary koniec => novy zaciatok
        for (j = 0; j < 26; ++j)                    //prekopirujem stare poplatky
            useky[i].myto[j] = useky[i - 1].myto[j];

    } while (1);    //rob furt
}

int urciMyto(long long int zaciatok, long long int koniec) {
    long long int i = 0, j, vzdialenost = 0, zx, kx;
    double zaplat[26] = {0}; //asi??
    int somNaKonci, uzJeDacoVypisane;

    //init
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

        printf("%lli - %lli: ", zaciatok, koniec);
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
