#ifndef HEDERI_H_INCLUDED
#define HEDERI_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define slobodan_slog 0
#define aktivan_slog 1

#define evidencioni_broj 5
#define lokacija_duzina 50
#define tip_duzina 5
#define snaga_jacina 100000000000
#define k 1
#define b 5
#define B 9
#define ime_datoteke 30

typedef struct vreme{
    int dd;
    int mm;
    int gggg;
    int ss;
    int minuti;
}Vreme;

typedef struct slog{
    int evBroj;
    char lokacija[lokacija_duzina];
    char tip[5];
    int snaga;
    Vreme v;
    int status;
}Elektrana;

typedef struct datoteka{
    FILE* file;
    char imeDat[ime_datoteke];
}Datoteka;

typedef struct baket{
    Elektrana slog[b];
}Baket;


void formiranjePrazneDatoteke();
void izborAktivneDatoteke(Datoteka* aktivna);
void prikazNazivaAktivneDatoteke(Datoteka* aktivna);
void upisNovogSlogaUDatoteku(Datoteka* aktivna);
void prikazSlogovaAktivneDatoteke(Datoteka* aktivna);
void promenaDatumaIVremena(Datoteka* aktivna);
void brisanjeSlogaFizicki(Datoteka* aktivna);

int upisiUBaket(Datoteka* data, int addr, Baket* bak);
void prikaziJedanSlog(Elektrana* slog);
void pronadjiBaket(Datoteka* aktivna, int addr, Baket* bak);
int pretragaZaDatumIVreme(Datoteka* aktivna, int kljuc, int* brBak, int* brLokacije);
void premestiSlog(Datoteka* aktivna, Baket bak1, int brBak1, int lokacija1, Baket bak2, int brBak2, int lokacija2);

#endif // HEDERI_H_INCLUDED
