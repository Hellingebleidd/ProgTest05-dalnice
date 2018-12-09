#include <stdio.h>
#include <stdlib.h>

struct usek {
    long zaciatok;  //zaciatok useku
    long koniec;
    float myto[26]; //pole pre myto A..Z
};
struct usek *useky;
long pocet = 1000;    //pocet alokovanych usekov

int nacitajVstupy();

int urciMyto(long zaciatok, long koniec);

int main() {

//struct usek *useky;
    long i, zaciatok, koniec;
    int tmp, tmpOddelovac;
    useky = (struct usek *) calloc(pocet, sizeof(struct usek));

    if (nacitajVstupy() == -1) {
        printf("Nespravny vstup.\n");
        return -1;
   }

    printf("Hledani:\n");
    tmp = scanf("%ld %ld", &zaciatok, &koniec);
    tmpOddelovac = getchar();
    if (tmp <= 0 && tmpOddelovac == EOF)
        return 0;
    if (tmp != 1 || (koniec != EOF && koniec != '\n' && koniec != ' ')) {
        printf("Nespravny vstup.\n");
        return -1;
    }

    if (urciMyto(zaciatok, koniec) == -1) {
        printf("Nespravny vstup.\n");
        return -1;
    }


}

int nacitajVstupy(){

    printf("Myto:\n");
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
    useky[1].myto[0] = 0;
    useky[1].myto[4] = 300;
    useky[1].myto[25] = 20;
    useky[1].myto[23] = 130;
//koniec debugu
    return 1;
}


int urciMyto(long zaciatok, long koniec) {
    long i;

    for (i = 0; i < pocet; ++i) {
        //najdi zaciatok

        // spocitaj cisla

        //najdi koniec

    }
}
