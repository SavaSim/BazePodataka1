#include "hederi.h"


int upisiUBaket(Datoteka* data, int addr, Baket* bak) {
	int povVr;

	if(addr < 0 || addr > B) {
		printf("Nepostojeca adresa baketa \n");
		return 0;
	}

	povVr = fseek(data->file, (addr)*sizeof(Baket), SEEK_SET);
	if(povVr != 0) {
		printf("Greska pri trazenju '%s'\n", data->imeDat);
		return 0;
	}

	povVr = fwrite(bak, sizeof(Baket), 1, data->file);
	if(povVr != 1) {
		printf("Greska pri upisu baketa u datoteku '%s'\n", data->imeDat);
		return 0;
	}

	return 1;
}

void pronadjiBaket(Datoteka* aktivna, int addr, Baket* bak){
    int povVr;

    if(addr< 0 || addr>B){
        printf("\nNepostojeca adresa baketa.");
        return;
    }

    povVr = fseek(aktivna->file, (addr)*sizeof(Baket), SEEK_SET);

    if (povVr != 0){
        printf("\nGreska prilikom pretrazivanja baketa iz datoteke '%s'.", aktivna->imeDat);
        return;
    }

    povVr = fread(bak, sizeof(Baket), 1, aktivna->file);

    if (povVr!=1){
        printf("\nGreska prilikom citanja baketa iz datoteke '%s'.", aktivna->imeDat);
        return;
    }

}


void prikaziJedanSlog(Elektrana* slog){
    printf("\nEvidencioni broj: %d", slog->evBroj);
    printf("\nLokacija: %s", slog->lokacija);
    printf("\nDatum: %d.%d.%d.", slog->v.dd, slog->v.mm, slog->v.gggg);
    printf("\nVreme: %d:%d", slog->v.ss, slog->v.minuti);
    printf("\nTip: %s", slog->tip);
    printf("\nSnaga: %d", slog->snaga);
    printf("\nStatus: %s", slog->status == 1 ? "AKTIVAN" : "NEAKTIVAN");
}




int pretragaZaDatumIVreme(Datoteka* aktivna, int kljuc, int* brBak, int* brLokacije){
    int i;
    Baket bak;
    int aktivniBak;
    int originalniBak;

    aktivniBak = kljuc % B + 1;
    originalniBak = aktivniBak;

    do{
        pronadjiBaket(aktivna, aktivniBak, &bak);

        for(i=0; i<b; i++){
            if(bak.slog[i].status == aktivan_slog && bak.slog[i].evBroj == kljuc){
                *brBak = aktivniBak;
                *brLokacije = i;
                return 1;
            }
        }

        aktivniBak += k;

        if(aktivniBak>B)
            aktivniBak = aktivniBak % B;
    }while(aktivniBak!=originalniBak);

    return 0;
}

void premestiSlog(Datoteka* aktivna, Baket bak1, int brBak1, int lokacija1, Baket bak2, int brBak2, int lokacija2){

    bak1.slog[lokacija1] = bak2.slog[lokacija2];

    upisiUBaket(aktivna, brBak1, &bak1);

    bak2.slog[lokacija2].status = slobodan_slog;
    bak2.slog[lokacija2].evBroj = -1;
    bak2.slog[lokacija2].lokacija[0] = '\0';
    bak2.slog[lokacija2].snaga = -1;
    bak2.slog[lokacija2].v.dd = -1;
    bak2.slog[lokacija2].v.mm = -1;
    bak2.slog[lokacija2].v.gggg = -1;
    bak2.slog[lokacija2].v.ss = -1;
    bak2.slog[lokacija2].v.minuti = -1;
    bak2.slog[lokacija2].tip[0] = '\0';

    upisiUBaket(aktivna, brBak2, &bak2);
    printf("\nOslobodjena lokacija %d, %d", brBak2, lokacija2+1);
}
