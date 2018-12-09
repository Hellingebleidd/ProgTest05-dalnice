**Termín odevzdání: 09.12.2018 23:59:59**
**Pozdní odevzdání s penalizací: 06.01.2019 23:59:59** (Penále za pozdní odevzdání: 100.0000 %)
**Max. hodnocení: 3.0000** (bez bonusů)

Úkolem je realizovat program, který bude počítat mýto na dálnici.

Předpokládáme agendu výběru mýtného na dálnici. Mýtné poplatky se vždy vybírají podle ujeté vzdálenosti. Poplatky jsou různé (použití dálnice, ekologický poplatek, silniční daň, ...). Pro jednoduchost budeme předpokládat, že poplatky jsou označené písmeny velké abecedy A až Z (tedy existuje nejvýše těchto 26 různých poplatků).

Pro různé úseky dálnice je stanovena různá výše těchto poplatků. Při zadávání bude vyplněna informace o délce úseku a seznam poplatků s uvedením jejich nové výše. Ostatní nezměněné poplatky budou ve stejné výši jako v předešlém úseku. Tedy například vstup:

{
  [ 50: A=10.5, E=80 ],
  [ 30: Z=20, A=7.5, X=130 ],
  [ 200: A=0, E=300 ]
}

budeme interpretovat takto:

-   První úsek dálnice v délce 50 km (tedy od 0 km do 50 km) bude poplatek A 10.5 za km a poplatek E 80 za km. Ostatní poplatky budou nulové (u prvního úseku dálnice není co přebrat z minulého úseku, proto budou mít nenastavené poplatky hodnotu 0),
-   druhý úsek dálnice o délce 30 km (tedy od 50 km do 80 km) bude poplatek A 7.5 za km (změněno), poplatek E 80 za km (převzato z předešlého úseku), X 130 za km a Z 20 za km (ostatní budou nulové),
-   třetí úsek dálnice o délce 200 km (tedy od 80 km do 280 km) bude poplatek A nulový, E 300 za km, X 130 za km a Z 20 za km (X i Z jsou převzaté z minulého úseku, ostatní budou nulové).

Pro takto definované mýto bude program počítat poplatky, které je potřeba zaplatit za průjezd zadaným úsekem dálnice. Program dostane na vstupu seznam dvojic celých čísel, čísla ve dvojici udávají kilometráž míst, kde najedeme na dálnici a kde z dálnice sjedeme. Pro tento interval program vypočte všechny poplatky A až Z a zobrazí ty nenulové.

Vstupem programu je nejprve seznam úseků dálnice a výše mýtných poplatků v jednotlivých úsecích. Celý seznam úseků je uzavřen ve složených závorkách, každý úsek je pak uzavřen do závorek hranatých. Dálka úseku je celé kladné číslo, mýtné poplatky jsou označené písmeny velké abecedy A až Z. Výše mýtného poplatku je desetinné číslo (může být i nulová). Po zadání mýtných poplatků následuje seznam dotazů. Každý dotaz je tvořen dvojicí celých čísel. Čísla udávají počáteční a koncový kilometr použité části dálnice. Čísla mohou být zadaná v pořadí menší větší i v pořadí větší menší (cestujeme v opačném směru). Zadávání dotazů končí po dosažení konce vstupu (end-of-file).

Je-li počáteční/koncový kilometr přesně rovný rozhraní mezi dvojicí úseků dálnice s různými poplatky, uplatní se pouze poplatky ve směru jízdy. Tedy pokud pro ukázkový seznam úseků dálnice zadáme dotazy:
40 50
50 10
uplatní se pouze poplatky stanovené pro první úsek dálnice. Naopak, pro dotazy:
50 60
70 50
se uplatní pouze poplatky pro druhý úsek dálnice. Pokud použitá část dálnice spadá do více úseků s různými poplatky, uplatní se podle počtu kilometrů poplatky všech využitých úseků, např.:

30 75 - 20km v prvním úseku a 25km ve druhém úseku
100 20 30km v prvním úseku, 30km ve druhém úseku (celý) a 20km ve třetím úseku

Výstupem programu je seznam poplatků k zaplacení pro každý vstupní dotaz. Zobrazované výše poplatků budou mít formát podle ukázky, výše poplatků bude zobrazena v pořadí A až Z a v seznam budou pouze nenulové poplatky.

Program musí být schopen detekovat nesprávný vstup. Pokud je vstup nesprávný, program zobrazí chybové hlášení a ukončí se. Za nesprávný vstup je považováno:

-   délka úseku v zadání poplatku není celé kladné číslo (tedy nula je též neplatná),
-   poplatek není identifikován velkým písmenem A až Z,
-   výše poplatku není platné desetinné číslo nebo je záporná (tj. musí být kladná nebo nulová),
-   pro dálnici není definovaná žádná sekce (platná dálnice musí mít alespoň jednu sekci),
-   dotaz není tvořen dvojicí celých čísel,
-   počáteční a koncový kilometr dotazu jsou stejné,
-   počáteční nebo koncový kilometr dotazu zasahují mimo zadanou dálnici (menší než 0 nebo větší než součet délek úseků dálnice),
-   chybí nebo přebývají nějaké oddělovače (hranaté závorky, kulaté závorky, dvojtečky, čárky).

Program je testován v omezeném prostředí. Je omezena doba běhu a dostupná paměť. Parametry jsou nastavené tak, aby jimi prošla správná implementace postavená na naivním algoritmu. Úloha vyžaduje, abyste si rozmysleli vhodnou reprezentaci dat v paměti. Dostupná paměť je omezena podle velikosti vstupů. Určitě neprojde řešení, které staticky alokuje paměť (např. pro 100000 úseků dálnice). Počítejte s tím, že úseků dálnice může být mnoho a dále počítejte s tím, že celková délka dálnice bude velká (milióny až miliardy km). Bude určitě jen dobře, pokud SW bude připraven na slibované navýšení rychlosti stavby dálnic v ČR.

Ukázka práce programu:

**Myto:**
{ [ 50: A=10.5, E=80 ], [ 30: Z=20, A=7.5, X=130 ], [ 200: A=0, E=300 ] }
**Hledani:**
10 70
**10 - 70: A=570.000000, E=4800.000000, X=2600.000000, Z=400.000000**
100 200
**100 - 200: E=30000.000000, X=13000.000000, Z=2000.000000**
55 166
**55 - 166: A=187.500000, E=27800.000000, X=14430.000000, Z=2220.000000**
166 55
**166 - 55: A=187.500000, E=27800.000000, X=14430.000000, Z=2220.000000**
0 280
**0 - 280: A=750.000000, E=66400.000000, X=29900.000000, Z=4600.000000**
49 50
**49 - 50: A=10.500000, E=80.000000**
49 51
**49 - 51: A=18.000000, E=160.000000, X=130.000000, Z=20.000000**
50 51
**50 - 51: A=7.500000, E=80.000000, X=130.000000, Z=20.000000**
50 50
**Nespravny vstup.**

----------
**Myto:**
{ [ 1000000 : A = 3.25 , C = 1 ] , [ 10000000 : B = 1.75 , D = 2 ], [1000000000:X=7] }
**Hledani:**
500000 3000000
**500000 - 3000000: A=8125000.000000, B=3500000.000000, C=2500000.000000, D=4000000.000000**
20000000 2000000000
**Nespravny vstup.**

----------
**Myto:**
{[1:A=3.25,C=1],[1:B=1.75,D=2]}
**Hledani:**
1 2
**1 - 2: A=3.250000, B=1.750000, C=1.000000, D=2.000000**
0 2
**0 - 2: A=6.500000, B=1.750000, C=2.000000, D=2.000000**
0 1
**0 - 1: A=3.250000, C=1.000000**

----------
**Myto:**
{[5:A=10],[6:B=10],
[7:A=0],[8:B=0]}
**Hledani:**
3 5
**3 - 5: A=20.000000**
7 9
**7 - 9: A=20.000000, B=20.000000**
12 14
**12 - 14: B=20.000000**
20 23
**20 - 23:**

----------
**Myto:**
{ [ 30: a=10 ] }
**Nespravny vstup.**

----------

**Myto:**

{ [ 30: A=20 ]

**Nespravny vstup.**

----------
**Nápověda:**

-   Ukázkové běhy zachycují očekávané výpisy Vašeho programu (tučné písmo) a vstupy zadané uživatelem (základní písmo). Zvýraznění tučným písmem je použité pouze zde na stránce zadání, aby byl výpis lépe čitelný. Váš program má za úkol pouze zobrazit text bez zvýrazňování (bez HTML markupu).
-   Počet úseků dálnice není shora omezen, je požadovaná dynamická alokace. Statická alokace buď neprojde základním testem (bude-li staticky alokované pole příliš velké), nebo neprojde testem mezních hodnot (bude-li příliš malé).
-   Pro ukládání úseků dálnice se hodí datový typ struktura.
-   Je požadované řešení využívající možnosti jazyka C. Nepoužívejte C++ a kontejnery STL (vector ...). Jejich použití v tomto příkladu povede k chybě při kompilaci.
-   Na výstupu jsou desetinná čísla, tedy podle způsobu výpočtu se může Váš výsledek mírně odlišovat od reference. Testovací prostředí porovnává desetinná čísla s tolerancí 1 ‰.

Bonusový test zadává velké množství úseků dálnice a velké množství dotazů. Pro zvládnutí bonusu je potřeba efektivní algoritmus a předzpracování vstupních dat.