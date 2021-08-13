#include "hederi.h"



void formiranjePrazneDatoteke(){
    Datoteka data;
    Baket bak;

    printf("\nUneti naziv datoteke: \n");
    fflush(stdin);
    gets(data.imeDat);

    data.file=fopen(data.imeDat, "wb");
    if(data.file == NULL) {
        printf("\tNije uspesno otvorena datoteka '%s'",data.imeDat);
    }else {
        int i=0;

        while(i<b){
            bak.slog[i].evBroj = -1;
            bak.slog[i].status = slobodan_slog;
            i++;
        }

        i = 0;
        while(i<B){
            upisiUBaket(&data, i, &bak);
            i++;
        }

        printf("\n Uspesno formirana datoteka '%s'\n",data.imeDat);
    }

    fclose(data.file);
}



void izborAktivneDatoteke(Datoteka* aktivna) {
    Datoteka data;

    printf("\nUnesi naziv datoteke: ");
    fflush(stdin);
	gets(data.imeDat);

    data.file = fopen(data.imeDat,"r+b");

    if(data.file == NULL) {
        printf("\nGreska");
        return ;
    }
    else {
        if(aktivna->file != NULL)
			fclose(aktivna->file);

		aktivna->file = data.file;
        memcpy(aktivna->imeDat, data.imeDat, ime_datoteke);

		printf("\nDatoteka '%s' je aktivirana\n", data.imeDat);
    }

    aktivna->file = data.file;
    strcpy(aktivna->imeDat,data.imeDat);
}

void prikazNazivaAktivneDatoteke(Datoteka* aktivna){
    int op = aktivna->file == NULL ? 1 : 0;

    switch(op){
        case 0:
            printf("\nNaziv aktivne datoteke: %s\n", aktivna->imeDat);
            return;
            break;
        case 1:
            printf("\nNe postoji aktivna datoteka.");
            break;
    }
}

void upisNovogSlogaUDatoteku(Datoteka* aktivna){
    Elektrana elektrana;
    int trenutniBak;
    int maticniBak;
    int upisanSlog=0;
    int brBak, brLok;
    Baket bak;

    if(aktivna->file == NULL){
        printf("\n Ne postoji aktivna datoteka. \n");
        return;
    }

    printf("\n\t\t\tElektrana:\n");

    elektrana.status = aktivan_slog;

    while(1){
    printf("\nUnesite evBroj(tacno pet cifara):\n");
    fflush(stdin);
    scanf("%d", &elektrana.evBroj);
    if(elektrana.evBroj>99999 || elektrana.evBroj<10000)
        printf("\nEvBroj mora imati 5 cifara.\n");
    else
        break;
    }


    if (pretragaZaDatumIVreme(aktivna, elektrana.evBroj, &brBak, &brLok)==1){
        printf("\nEvBroj '%d' vec postoji.", elektrana.evBroj);
        return;
    }


    while(1){
        printf("\nUneti lokaciju (najvise 50 karaktera):\n");
        fflush(stdin);
        gets(elektrana.lokacija);
        if(strlen(elektrana.lokacija)>lokacija_duzina){
            printf("\nLokcija moze imati najvise 50 karaktera\n");
        }
        else{
            break;
        }
    }


    printf("\nUnos datuma i vremena pustanja u rad:\n");

    while(1){
        printf("\nDan:\n");
        fflush(stdin);
        scanf("%d", &elektrana.v.dd);
        if (elektrana.v.dd>31 || elektrana.v.dd<1){
            printf("\nDan mora imati vrednosti izmedju 1 i 31.\n");
        }
        else
            break;
    }

    while(1){
        printf("\nMesec:\n");
        fflush(stdin);
        scanf("%d", &elektrana.v.mm);
        if (elektrana.v.mm>12 || elektrana.v.mm<1){
            printf("\nMesec mora imati vrednosti izmedju 1 i 12.\n");
        }
        else
            break;
    }

    while(1){
        printf("\nGodina:\n");
        fflush(stdin);
        scanf("%d", &elektrana.v.gggg);
        if (elektrana.v.gggg>2018 || elektrana.v.gggg<1900){
            printf("\nGodina mora imati vrednosti izmedju 1900 i 2018.\n");
        }
        else
            break;
    }

    while(1){
        printf("\nSati:\n");
        fflush(stdin);
        scanf("%d", &elektrana.v.ss);
        if (elektrana.v.ss>24 || elektrana.v.ss<0){
            printf("\nSati moraju imati vrednosti izmedju 0 i 24.\n");
        }
        else
            break;
    }

    while(1){
        printf("\nMinuti:\n");
        fflush(stdin);
        scanf("%d", &elektrana.v.minuti);
        if (elektrana.v.minuti>60 || elektrana.v.minuti<0){
            printf("\nMinuti moraju imati vrednosti izmedju 0 i 60.");
        }
        else
            break;
    }

    while(1){
        printf("\nUneti tip (tacno 5 karaktera):");
        fflush(stdin);
        gets(elektrana.tip);
        if (strlen(elektrana.tip) > 5 || strlen(elektrana.tip) < 5)
            printf("\nTip mora imati tacno 5 karaktera.\n");
        else
            break;
    }

    while(1){
        printf("\nUneti snagu (najvise 100 000 000 000):");
        fflush(stdin);
        scanf("%d", &elektrana.snaga);
        if (elektrana.snaga > 100000000000 || elektrana.snaga < 0){
            printf("Niste dobro uneli snagu.");
        }
        else
            break;
    }

    trenutniBak = elektrana.evBroj % B + 1;
    maticniBak = trenutniBak;

    do{
        pronadjiBaket(aktivna, trenutniBak, &bak);

        for(int i=0; i<b; i++){
            if(bak.slog[i].status == slobodan_slog){
                bak.slog[i] = elektrana;
                if (upisiUBaket(aktivna, trenutniBak, &bak) == 1){
                    printf("\nSlog je upisan.\n");
                    printf("\nAdresa baketa je: %d\n", trenutniBak);
                    printf("\nRedni broj sloga u baketu je: %d\n", i+1);
                    if (trenutniBak!=maticniBak)
                        printf("\nPojava prekoracioca!\nMaticni baket: %d\nTrenutni baket: %d\n", maticniBak, trenutniBak);
                 }
                upisanSlog = 1;
                break;
            }
        }

        if(upisanSlog == 0){
            trenutniBak += k;
            if (trenutniBak>B)
                trenutniBak = trenutniBak%B;
        }

    }while(upisanSlog==0 && trenutniBak!= maticniBak);

}

void prikazSlogovaAktivneDatoteke(Datoteka* aktivna){
    Baket bak;
    int i,j;

    if (aktivna->file == NULL){
        printf("\nNe postoji aktivna datoteka.");
        return;
    }

    printf("\n");
    for(i=1; i<B; i++){
        pronadjiBaket(aktivna, i, &bak);
        for (j=0; j<b; j++){
            if(bak.slog[j].status == aktivan_slog){
                printf("\n\n---------------------------------------------------------");
                printf("\nAdresa baketa: %d", i);
                printf("\nRedni broj sloga u baketu: %d", j+1);
                prikaziJedanSlog(&bak.slog[j]);
            }
        }
    }
}

void promenaDatumaIVremena(Datoteka* aktivna){

    int evBroj1,dd1,mm1,gggg1,ss1,minuti1;
    int brBak,brLokacije;
    Baket bak;

    if(aktivna->file != NULL ){
     }else
        return;

    printf("Uneti ev_broj: \n");
    fflush(stdin);
    scanf("%d",&evBroj1);

    if(pretragaZaDatumIVreme(aktivna,evBroj1,&brBak,&brLokacije)==0) {
         printf("\nPromena ne postoji pod datim ev_brojem: '%d'", evBroj1);
         return ;
    }

    printf("Unesi novo vreme\nDan: ");
    fflush(stdin);
    scanf("%d",&dd1);

    printf("Mesec: ");
    fflush(stdin);
    scanf("%d",&mm1);

    printf("Godina: ");
    fflush(stdin);
    scanf("%d",&gggg1);

    printf("Sati: ");
    fflush(stdin);
    scanf("%d",&ss1);

    printf("Minuti: ");
    fflush(stdin);
    scanf("%d",&minuti1);

    pronadjiBaket(aktivna, brBak, &bak);
    bak.slog[brLokacije].v.dd = dd1;
    bak.slog[brLokacije].v.mm = mm1;
    bak.slog[brLokacije].v.gggg = gggg1;
    bak.slog[brLokacije].v.ss = ss1;
    bak.slog[brLokacije].v.minuti = minuti1;

    if(upisiUBaket(aktivna,brBak,&bak) == 1) {
        printf("\nIzmenjen slog:");
        prikaziJedanSlog(&bak.slog[brLokacije]);
        printf("\nSlog je uspesno promenjen na adresu (%d,%d)\n", brBak, brLokacije+1);
    }
    else
        printf("\nSlog nije uspesno promenjen.\n");
}

void brisanjeSlogaFizicki(Datoteka* aktivna){
    int eBrojBak;
    int status1;
    int brBak;
    int brLok;
    Baket bak;

    while(aktivna->file == NULL){
        printf("\nNema aktivnih datoteka \n.");
        return;
    }

    printf("Uneti evidencioni broj sloga za fizicko brisanje: \n");
    fflush(stdin);
    scanf("%d", &eBrojBak);

    status1 = pretragaZaDatumIVreme(aktivna, eBrojBak, &brBak, &brLok);
    if(status1==1){
        fseek(aktivna->file, sizeof(Baket)*(brBak-1), SEEK_SET);
        if(fread(&bak, sizeof(Baket), 1, aktivna->file)!=1){
            printf("\nGreska prilikom citanja datoteke.");
            return;
        }
        bak.slog[brLok].status = slobodan_slog;
        bak.slog[brLok].evBroj = -1;
        bak.slog[brLok].lokacija[0] = '\0';
        bak.slog[brLok].snaga = -1;
        bak.slog[brLok].v.dd = -1;
        bak.slog[brLok].v.mm = -1;
        bak.slog[brLok].v.gggg = -1;
        bak.slog[brLok].v.ss = -1;
        bak.slog[brLok].v.minuti = -1;
        bak.slog[brLok].tip[0] = '\0';

        fseek(aktivna->file, sizeof(Baket)*(brBak-1), SEEK_SET);
        fwrite(&bak, sizeof(Baket), 1, aktivna->file);
        printf("\nSlog sa evidencionim brojem '%d' je obrisan.", eBrojBak);
        printf("\nSlog u baketu %d sa lokacijom %d je slobodan.", brBak, brLok+1);
    }else{
        printf("\nNe postoji slog sa istim ev_brojem.");
        return;
    }

    int prekoraciocLok[b*B], prekoraciocLokBak[b*B], prekoraciocEvBroja[b*B];
    int i=0;
    int j;
    int posedujePrekoracioca = 0;
    Baket bak1;
    int cnt=0;

    while(i<b*B){
        prekoraciocLokBak[i]=-1; prekoraciocLok[i]=-1; prekoraciocEvBroja[i]=-1;
        i++;
    }

    int temp = brLok;

    for(i=brBak; i<B; i++){
        pronadjiBaket(aktivna, i, &bak1);
        for(j=temp; j<b; j++){
            if(bak1.slog[j].status == aktivan_slog && (bak1.slog[j].evBroj % B + 1)<i){     //prekoracioc
                prekoraciocEvBroja[cnt] = bak1.slog[j].evBroj;
                prekoraciocLok[cnt] = j;
                prekoraciocLokBak[cnt]=i;
                cnt=cnt+1;
                posedujePrekoracioca = 1;
            }
        }
        temp = 0;
    }

    if (posedujePrekoracioca == 1){
        printf("\nReogranizacija...\n");
    }

    int temp1 = 0;
    Baket stariBak;

    for(i=temp1; i<cnt; i++){
        if(prekoraciocLokBak[i]!=-1){
            if(prekoraciocLokBak[i]>brBak && prekoraciocEvBroja[i]%9+1==brBak){
                printf("\nPremestanje sloga sa %d,%d na %d,%d", prekoraciocLokBak[i], prekoraciocLok[i]+1, brBak, brLok+1);
                pronadjiBaket(aktivna, prekoraciocLokBak[i],&stariBak);
                premestiSlog(aktivna, bak, brBak, brLok, stariBak, prekoraciocLokBak[i], prekoraciocLok[i]);
                brBak = prekoraciocLokBak[i];
                brLok = prekoraciocLok[i];
                pronadjiBaket(aktivna, brBak, &bak);
                temp1 = 0;
                prekoraciocLokBak[i] = -1;
            }
        }
    }

    temp1 = 0;
     for(i=temp1; i<cnt; i++){
        if(prekoraciocLokBak[i]!=-1){
            if(prekoraciocLokBak[i]>brBak && prekoraciocEvBroja[i]%9+1<=brBak){
                printf("\nPremestanje sloga sa %d,%d na %d,%d", prekoraciocLokBak[i], prekoraciocLok[i]+1, brBak, brLok+1);
                pronadjiBaket(aktivna, prekoraciocLokBak[i],&stariBak);
                premestiSlog(aktivna, bak, brBak, brLok, stariBak, prekoraciocLokBak[i], prekoraciocLok[i]);
                brBak = prekoraciocLokBak[i];
                brLok = prekoraciocLok[i];
                pronadjiBaket(aktivna, brBak, &bak);
                temp1 = 0;
            }
        }
    }
}


