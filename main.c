#include <stdio.h>
#include <stdlib.h>

const int NESPRAVNY_VSTUP = -1;

struct usek {
    long zaciatok;  //zaciatok useku
    long koniec;
    float myto[26]; //pole pre myto A..Z
};
struct usek *useky;
long maxPocet = 100, pocetKrok = 100;    //maxPocet alokovanych usekov, a kolko bude realloc
long pocet;     //skutocny pocet usekov


int nacitajVstupy();    //nacita hodnoty zo stdin. Ak je chyba -> NESPRAVNY_VSTUP

int urciMyto(long zaciatok, long koniec); //nacita hodnoty zo stdin a urci myto. Ak je chyba -> NESPRAVNY_VSTUP

int main() {

//struct usek *useky;
    long i, zaciatok, koniec;
    int tmp, tmpOddelovac;
    useky = (struct usek *) calloc(maxPocet, sizeof(struct usek));

    pocet = nacitajVstupy();
    if (pocet == NESPRAVNY_VSTUP) {
        printf("Nespravny vstup.\n");
        return NESPRAVNY_VSTUP;
    }

    //skusim precitat zaciatok a koniec
    printf("Hledani:\n");
    tmp = scanf("%ld %ld", &zaciatok, &koniec);
    tmpOddelovac = getchar();
    if (tmp <= 0 && tmpOddelovac == EOF)
        return 0;
    if (tmp != 1 || (koniec != EOF && koniec != '\n' && koniec != ' ')) {
        printf("Nespravny vstup.\n");
        return NESPRAVNY_VSTUP;
    }
    //vstupy su zrejme v poriadku, skusim vypocitat myto
    if (urciMyto(zaciatok, koniec) == NESPRAVNY_VSTUP) {
        printf("Nespravny vstup.\n");
        return NESPRAVNY_VSTUP;
    }
}

int nacitajVstupy() {
    char myto, tmpOddelovac;
    int tmp, j;
    long i = 0, km;
    float cena;
    printf("Myto:\n");
    //ocakavam { [ 50: A=10.5, E=80 ], [ 30: Z=20, A=7.5, X=130 ], [ 200: A=0, E=300 ] }

    //debug nastavenie hodnot
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
    return 3;



    do{tmp = getchar();} while( tmp==' ');  //preskocim vsetky medzery
    if (tmp != '{')
        return NESPRAVNY_VSTUP;
    do {
        tmp = scanf(" [ %ld : ", &km);
        if (tmp != 1 || km < 0)
            return NESPRAVNY_VSTUP;
        useky[i].koniec = useky[i].zaciatok + km;

        do {
            tmp = scanf(" %c = %f %c", &myto, &cena, &tmpOddelovac);
            if (tmp != 3 || myto < 'A' || myto > 'Z' || cena < 0 || (tmpOddelovac != ',' && tmpOddelovac != ']'))
                return NESPRAVNY_VSTUP;
            useky[i].myto[myto - 'A'] = cena;

        } while (tmpOddelovac != ']');
        do{tmp = getchar();} while( tmp==' ');  //preskocim vsetky medzery
        if (tmp == '}' )
            return i+1;   //koniec vypoctu

        if (tmp != ',' )
            return NESPRAVNY_VSTUP;

        //novy usek
        if (++i >= maxPocet) {   //treba alokovat dalsi usek
            maxPocet = maxPocet + pocetKrok;
            useky = (struct usek *) realloc(useky, maxPocet*(sizeof(struct usek)));
        }
        useky[i].zaciatok = useky[i - 1].koniec;    //stary koniec => novy zaciatok
        for (j = 0; j < 26; ++j)                    //prekopirujem stare poplatky
            useky[i].myto[j] = useky[i - 1].myto[j];


    } while (1);    //rob furt


}


int urciMyto(long zaciatok, long koniec) {
    long i;
    int cena;
    if (zaciatok == koniec || zaciatok < 0 || koniec < 0)
        return NESPRAVNY_VSTUP;

    //mam { [ 50: A=10.5, E=80 ], [ 30: Z=20, A=7.5, X=130 ], [ 200: A=0, E=300 ] }
    for (i = 0; i < pocet; ++i) {
        //najdi zaciatok
        useky[0].zaciatok=zaciatok;


        // spocitaj cisla

        //najdi koniec

    }
}
