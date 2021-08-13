#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hederi.h"




int main()
{
    Datoteka aktivna;
    aktivna.file = NULL;
    int izaberi;

   do{

        printf("\n\t\tElektrana Grad\t\t  \n");
        printf("\t\t\t\t\t\t\t  \n");
        printf("\t\t\t\t\t\t\t  \n");
        printf(" 1. Formiranje prazne datoteke\t\t\t\t  \n");
        printf(" 2. Izbor aktivne datoteke\t\t\t\t  \n");
        printf(" 3. Prikaz naziva aktivne datoteke\t\t\t  \n");
        printf(" 4. Upis novog sloga u datoteku\t\t\t  \n");
        printf(" 5. Prikaz svih slogova aktivne datoteke\t\t  \n");
        printf(" 6. Promena vrednosti datum i vreme\t\t  \n");
        printf(" 7. Fizicko brisanje aktuelnog sloga iz aktivne datoteke \n");
        printf(" 0. Izadji\t\t\t\t\t\t  ");
        printf("\n>>");
        fflush(stdin);
        scanf("%d", &izaberi);




        switch(izaberi){
            case 1: {
                formiranjePrazneDatoteke();
                break;
            }
            case 2: {
                izborAktivneDatoteke(&aktivna);
                break;
            }
            case 3: {
                prikazNazivaAktivneDatoteke(&aktivna);
                break;
            }
            case 4: {
                upisNovogSlogaUDatoteku(&aktivna);
                break;
            }
            case 5: {
                prikazSlogovaAktivneDatoteke(&aktivna);
                break;
            }
            case 6: {
                promenaDatumaIVremena(&aktivna);
                break;
            }
            case 7: {
                brisanjeSlogaFizicki(&aktivna);
                break;
            }
            case 0: {
                return 0;
            }

        }
    }while(izaberi!=0);
}









