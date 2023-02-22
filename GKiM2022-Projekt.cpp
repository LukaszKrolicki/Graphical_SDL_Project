#include <exception>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <vector>

using namespace std;

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

#define szerokosc 512
#define wysokosc 340

#define tytul "GKiM2022 - Projekt - Zespół14 "


void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel (int x, int y);

void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

void Funkcja1();
void Funkcja2();
void Funkcja3();
void Funkcja4();
void Funkcja5();
void Funkcja6();
void Funkcja7();
void Funkcja8();
void Funkcja9();

Uint8 z24na3RGB(SDL_Color kolor){ //przesyłamy SDL_Color, dostajemy kolor3bit

    int R,G,B;
    int kolor3bit;
    int nowyR,nowyG,nowyB;

    R=kolor.r;
    G=kolor.g;
    B=kolor.b;

    nowyR=R>>7;
    nowyG=G>>7;
    nowyB=B>>7;

    kolor3bit=(nowyR<<2)+(nowyG<<1)+nowyB;

    return kolor3bit;
}
Uint8 z24na8RGB(SDL_Color kolor){ //przesyłamy SDL_Color, dostajemy kolor3bit

    int R,G,B;
    int kolor3bit;
    int nowyR,nowyG,nowyB;

    R=kolor.r;
    G=kolor.g;
    B=kolor.b;
    //nowyR=R>>5;
    //nowyG=G>>5;
    //nowyB=B>>6;
    nowyR=R/39.0;
    nowyG=G/39.0;
    nowyB=B/79.0;

    kolor3bit=(nowyR<<5)+(nowyG<<2)+nowyB;

    return kolor3bit;
}
Uint8 z24na8rgb(SDL_Color kolor){
    int R,G,B;
    int kolor3bit;
    int nowyR,nowyG,nowyB;

    R=kolor.r;
    G=kolor.g;
    B=kolor.b;
    //nowyR=R>>5;
    //nowyG=G>>5;
    //nowyB=B>>6;
    nowyR=R/32.0;
    nowyG=G/32.0;
    nowyB=B/75.0;

    kolor3bit=(nowyR<<5)+(nowyG<<2)+nowyB;

    return kolor3bit;
}
SDL_Color z8Rgbna24RGB(Uint8 kolor3bit){

    SDL_Color kolor;
    int nowyR,nowyG,nowyB;

    nowyR = ((kolor3bit & 0b11100000)>>5);
    nowyG = ((kolor3bit & 0b00011100)>>2);
    nowyB = ((kolor3bit & 0b00000011));

    kolor.r=nowyR*32.0;
    kolor.g=nowyG*32.0;
    kolor.b=nowyB*75.0;

    return kolor;
}
SDL_Color z8rgbna24RGB(Uint8 kolor3bit){

    SDL_Color kolor;
    int nowyR,nowyG,nowyB;

    nowyR = ((kolor3bit & 0b11100000)>>5);
    nowyG = ((kolor3bit & 0b00011100)>>2);
    nowyB = ((kolor3bit & 0b00000011));

    kolor.r=nowyR*33.0;
    kolor.g=nowyG*33.0;
    kolor.b=nowyB*79.0;

    return kolor;
}
Uint8 z24na8BW(SDL_Color kolor){ //przesyłamy SDL_Color, dostajemy kolor3bit

    int R,G,B;
    int kolor3bit;
    int nowyR,nowyG,nowyB;

    R=kolor.r;
    G=kolor.g;
    B=kolor.b;

    nowyR=round(R*0.299);
    nowyG=round(G*0.587);
    nowyB=round(B*0.114);

    kolor3bit=(nowyR<<5)+(nowyG<<2)+nowyB;

    return kolor3bit;
}
SDL_Color z8BWna24RGB(Uint8 kolor3bit){

    SDL_Color kolor;
    int nowyR,nowyG,nowyB;
    int R, G, B;

    nowyR = ((kolor3bit & 0b11100000)>>5);
    nowyG = ((kolor3bit & 0b00011100)>>2);
    nowyB = ((kolor3bit & 0b00000011));

    //R=round(nowyR/0.299);
    //G=round(nowyG/0.587);
    //B=round(nowyB/0.114);
    int BW=(nowyR+nowyB+nowyG)*255.0/14.0;
    //int BW=kolor3BW*255.0/7.0;

    kolor.r=BW;
    kolor.g=BW;
    kolor.b=BW;

    return kolor;
}
SDL_Color z3rgbna24RGB(Uint8 kolor3bit){

    SDL_Color kolor;
    int nowyR,nowyG,nowyB;

    nowyR = ((kolor3bit & 0b00000100)>>2);
    nowyG = ((kolor3bit & 0b00000010)>>1);
    nowyB = ((kolor3bit & 0b00000001));

    kolor.r=nowyR*255.0/1.0;
    kolor.g=nowyG*255.0/1.0;
    kolor.b=nowyB*255.0/1.0;

    return kolor;
} //przesyłamy kolor3bit, dostajemy SDL_Color;

Uint8 z24Rgbna3BW(SDL_Color kolor){

    int R,G,B;
    int kolor3bitBW;
    int nowyR,nowyG,nowyB;

    R=kolor.r;
    G=kolor.g;
    B=kolor.b;

    nowyR=round(R*0.299);
    nowyG=round(G*0.587);
    nowyB=round(B*0.114);

    nowyR = R>>7;
    nowyG = G>>7;
    nowyB = B>>7;

    kolor3bitBW=(nowyR<<2)+(nowyG<<1)+nowyB;
    return kolor3bitBW;

};//przesyłamy SDL, dostajemy BW3bit
SDL_Color z3BWna24RGB(Uint8 kolor3BW){

    SDL_Color kolor;
    int nowyR,nowyG,nowyB;
    int R,G,B;
    nowyR = ((kolor3BW & 0b00000100)>>2);
    nowyG = ((kolor3BW & 0b00000010)>>1);
    nowyB = ((kolor3BW & 0b00000001));
    R=round(nowyR/0.299);
    G=round(nowyG/0.587);
    B=round(nowyB/0.114);
    int BW=(R+B+G)*255.0/7.0;
    //int BW=kolor3BW*255.0/7.0;

    kolor.r=BW;
    kolor.g=BW;
    kolor.b=BW;

    return kolor;

};//przesyłamy kolor3bit, dostajemy SDL_Color;
SDL_Color z3BWna24RGB2(Uint8 kolor3BW){

    SDL_Color kolor;
    int nowyR,nowyG,nowyB;
    int R,G,B;
    nowyR = ((kolor3BW & 0b00000100)>>2);
    nowyG = ((kolor3BW & 0b00000010)>>1);
    nowyB = ((kolor3BW & 0b00000001));
    //R=round(nowyR/0.299);
    //G=round(nowyG/0.587);
    //B=round(nowyB/0.114);
    //int BW=(R+B+G)*255.0/7.0;
    int BW=kolor3BW*255.0/7.0;

    kolor.r=BW;
    kolor.g=BW;
    kolor.b=BW;

    return kolor;

};//przesyłamy kolor3bit, dostajemy SDL_Color;
struct kolor3bit {
    unsigned int r : 1;
    unsigned int b : 1;
    unsigned int g : 1;
};

int kolor3bitToInt(kolor3bit a) {
    return (a.r << 7 | a.g << 7 | a.b << 7);
}

kolor3bit z24na3RGB2(SDL_Color kolor) {
    kolor3bit k;
    k.r = round(1.0*kolor.r/255.0);
    k.g = round(1.0*kolor.g/255.0);
    k.b = round(1.0*kolor.b/255.0);

    return k;
}

Uint8 z24Rgbna3BW2(SDL_Color kolor){
    return (int)round(0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b);
}




void Funkcja1() { //z24na3

    SDL_Color kolor;
    Uint8 kolor3bit;

        for(int y=0; y<wysokosc/2;y++){
            for(int x=0; x<szerokosc/2;x++)
                {
                    kolor = getPixel(x,y);

                    kolor3bit = z24na3RGB(kolor);

                    kolor = z3rgbna24RGB(kolor3bit);

                    setPixel(x+szerokosc/2,y,kolor.r,kolor.g,kolor.b);

        }
    }
    SDL_UpdateWindowSurface(window);

}

void Funkcja2() { // skala szarosci

    SDL_Color kolor;
    int BW;
    Uint8 kolor3bit;
    for (int y = 0; y < wysokosc/2; y++) {
        for (int x = 0; x < szerokosc/2; x++) {
            kolor = getPixel(x, y);
            kolor3bit=z24na3RGB(kolor);
            kolor = z3rgbna24RGB(kolor3bit);
            BW = z24Rgbna3BW(kolor);
            kolor = z3BWna24RGB(BW);
            setPixel(x + szerokosc/2, y, kolor.r, kolor.g, kolor.b);
        }
    }
    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {//nic

    SDL_Color kolor;
    int BW;
    Uint8 kolor3bit;
    for (int y = 0; y < wysokosc/2; y++) {
        for (int x = 0; x < szerokosc/2; x++) {
            kolor = getPixel(x, y);
            kolor3bit=z24na3RGB(kolor);
            kolor = z3rgbna24RGB(kolor3bit);
            BW = z24Rgbna3BW(kolor);
            kolor = z3BWna24RGB(BW);
            setPixel(x + szerokosc/2, y, kolor.r, kolor.g, kolor.b);
        }
    }
    SDL_UpdateWindowSurface(window);
}


SDL_Color paleta[(szerokosc/2)*(wysokosc/2)];

int ileKolorow = 0;

int dodajKolor(SDL_Color kolor){
    int aktualnyKolor = ileKolorow;
    paleta[aktualnyKolor] = kolor;
    ileKolorow++;
    return aktualnyKolor;
}

bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2){
    if(kolor1.r != kolor2.r)
        return false;
    if(kolor1.g != kolor2.g)
        return false;
    if(kolor1.b != kolor2.b)
        return false;

    return true;
}

int sprawdzKolor(SDL_Color kolor){
    if(ileKolorow>0){
        for(int k=0; k<ileKolorow; k++){
            if(porownajKolory(kolor,paleta[k]))
            {
                return k;
            }
        }

        return dodajKolor(kolor);
    }

    return dodajKolor(kolor);
}

SDL_Color paleta3d[8];

SDL_Color paleta3bw[8];

SDL_Color paleta3n[8];

void Funkcja4() {

    SDL_Color kolor;
    int nrKoloru;

    for(int y=0; y<wysokosc/2; y++)
    {
        for(int x=0; x<szerokosc/2; x++){
            kolor=getPixel(x, y);
            nrKoloru=sprawdzKolor(kolor);
        }
    }

    if(ileKolorow<=8){
        for(int k=0; k<ileKolorow; k++){
            paleta3d[k] = paleta[k];
        }
    }

    for(int k=0; k<8; k++){
        paleta3n[k]= z3rgbna24RGB(k);
        paleta3bw[k]= z3BWna24RGB2(k);
    }

    for(int k=0; k<8; k++){
        for(int y = 0; y<20; y++){
            setPixel(k, y+(wysokosc/2), paleta3d[k].r, paleta3d[k].g, paleta3d[k].b);
            setPixel(k, y+(wysokosc/2)+20, paleta3bw[k].r, paleta3bw[k].g, paleta3bw[k].b);
            setPixel(k, y+(wysokosc/2)+40, paleta3n[k].r, paleta3n[k].g, paleta3n[k].b);

        }
    }

    cout<<"Wszystkich kolorow: "<<ileKolorow<<endl;
    cout<<"wszystkich pikseli: "<<(szerokosc/2)*(wysokosc/2)<<endl;

    SDL_UpdateWindowSurface(window);
}


void narysujPalete(int px, int py, SDL_Color paleta3[]) {

    int x=px;

    for(int i=0; i<4; i++){

    setPixel(px, py, paleta3[i].r, paleta3[i].g, paleta3[i].b);
    px+=64;
    }

    px=x;
    py+=85;
    for(int i=4; i<8; i++){

    setPixel(px, py, paleta3[i].r, paleta3[i].g, paleta3[i].b);
    px+=64;
    }

}
void medianCut(int start, int koniec, int iteracja);
int median_index;
SDL_Color paleta3bwd[8];
SDL_Color obrazek[szerokosc*wysokosc/4];
void Funkcja5() {
    Funkcja4();
    for(int y=0; y<wysokosc/4;y++){
        for(int x=0;x<szerokosc/8;x++)
        {

            narysujPalete(x, y+wysokosc/2,paleta3bw);

            narysujPalete(x+szerokosc/2, y+wysokosc/2,paleta3n);

        }
    }
        median_index = 0;
    for(int y=0;y<wysokosc/2;y++)
        for(int x=0;x<szerokosc/2;x++)
            obrazek[x+(y*szerokosc/2)] = getPixel(x,y);
    medianCut(0,szerokosc*wysokosc/4,0);
       for(int y=0; y<wysokosc/4;y++){
        for(int x=0;x<szerokosc/8;x++){
            narysujPalete(x+szerokosc/2, y, paleta3d);
        }
       }
    SDL_UpdateWindowSurface(window);

}


Uint8 najwiekszaRoznica(int start, int koniec) {
    int skrajne[3][2] = {{obrazek[0].r,obrazek[0].r},
                         {obrazek[0].g,obrazek[0].g},
                         {obrazek[0].b,obrazek[0].b}};
    int temp[3];
    int max_roznica = 0;
    int skladowa = 0;
    for(int i=start;i<koniec;i++) {
        temp[0]=obrazek[i].r;
        temp[1]=obrazek[i].g;
        temp[2]=obrazek[i].b;
        for(int j=0;j<3;j++) {
            if(temp[j]<skrajne[j][0]) {
                skrajne[j][0]=temp[j];
                if(skrajne[j][1]-skrajne[j][0]>max_roznica) {
                    max_roznica = skrajne[j][1]-skrajne[1][0];
                    skladowa = j;
                }
            }
            else if(temp[j]>skrajne[j][1]) {
                skrajne[j][1]=temp[j];
                if(skrajne[j][1]-skrajne[j][0]>max_roznica) {
                    max_roznica = skrajne[j][1]-skrajne[1][0];
                    skladowa = j;
                }
            }
        }
    }
    return skladowa;
}

void sortujKubelek(int start, int koniec, Uint8 ktoraSkladowa) {
    switch (ktoraSkladowa) {
    case 0:
        for(int i=start;i<koniec;i++)
            for(int j=i+1;j<koniec;j++) {
                if(obrazek[i].r>obrazek[j].r)
                    swap(obrazek[i],obrazek[j]);
            }
        break;
    case 1:
        for(int i=start;i<koniec;i++)
            for(int j=i+1;j<koniec;j++) {
                if(obrazek[i].g>obrazek[j].g)
                    swap(obrazek[i],obrazek[j]);
            }
        break;
    case 2:
        for(int i=start;i<koniec;i++)
            for(int j=i+1;j<koniec;j++) {
                if(obrazek[i].b>obrazek[j].b)
                    swap(obrazek[i],obrazek[j]);
            }
        break;
    }
}

void medianCut(int start, int koniec, int iteracja) {

    if(iteracja==3) {
        int srednia[3] {};
        for(int i=start;i<koniec;i++) {
            srednia[0]+=obrazek[i].r;
            srednia[1]+=obrazek[i].g;
            srednia[2]+=obrazek[i].b;
        }
        int w = koniec-start;
        srednia[0]/=w;
        srednia[1]/=w;
        srednia[2]/=w;
        SDL_Color s = {srednia[0],srednia[1],srednia[2]};
        paleta3d[median_index++]=s;
        return;
    }
    sortujKubelek(start,koniec,najwiekszaRoznica(start,koniec));

    medianCut(start,(koniec+start)/2,iteracja+1);
    medianCut((koniec+start)/2,koniec,iteracja+1);
}


int znajdzSasiada(SDL_Color kolor) {
    int r = kolor.r-paleta3d[0].r;
    int b = kolor.b-paleta3d[0].b;
    int g = kolor.g-paleta3d[0].g;
    int min_roznica=sqrt(r*r+b*b+g*g);
    int indeks=0;
    int roznica;
    for(int i=1;i<8;i++) {
        r = kolor.r-paleta3d[i].r;
        b = kolor.b-paleta3d[i].b;
        g = kolor.g-paleta3d[i].g;
        roznica=sqrt(r*r+b*b+g*g);
        if(roznica<min_roznica) {
            min_roznica=roznica;
            indeks=i;
        }
    }
    return indeks;
}
int znajdzSasiadaBW(SDL_Color kolor) {
    int min_roznica=abs(kolor.r-paleta3bwd[0].r);
    int indeks=0;
    int roznica;
    for(int i=1;i<8;i++) {
        roznica=abs(kolor.r-paleta3bwd[i].r);
        if(roznica<min_roznica) {
            min_roznica=roznica;
            indeks=i;
        }
    }
    return indeks;
}

void narysujObrazek(int px, int py) {
    int i;
    for(int y=0;y<wysokosc/2;y++)
        for(int x=0;x<szerokosc/2;x++) {
            SDL_Color p = paleta3d[znajdzSasiada(getPixel(x,y))];
            setPixel(px+x,py+y,p.r,p.g,p.b);
    }
}

void narysujObrazekBW(int px, int py) {
    int i;
    int p;
    for(int y=0;y<wysokosc/2;y++)
        for(int x=0;x<szerokosc/2;x++) {
            p = paleta3bwd[znajdzSasiadaBW(getPixel(x,y))].r;
            setPixel(px+x,py+y,p,p,p);
    }
}

void medianCutBW(int start, int koniec, int iteracja) {

    if(iteracja==3) {
        int srednia = 0;
        for(int i=start;i<koniec;i++) {
            srednia+=obrazek[i].r;
        }
        srednia/=(koniec-start);
        SDL_Color s = {srednia,srednia,srednia};
        paleta3bwd[median_index++]=s;
    }
    else {
    medianCutBW(start,(koniec+start)/2,iteracja+1);
    medianCutBW((koniec+start)/2,koniec,iteracja+1);
    }
}


void Funkcja6(int a) {
    median_index = 0;
    for(int y=0;y<wysokosc/2;y++)
        for(int x=0;x<szerokosc/2;x++)
            obrazek[x+(y*szerokosc/2)] = getPixel(x,y);
    medianCut(0,szerokosc*wysokosc/4,0);
    /*
        for(int y=0; y<wysokosc/4;y++){
            for(int x=0;x<szerokosc/8;x++){
                narysujPalete(x+szerokosc/2, y, paleta3d);
            }
        }
        if(x==1){
        }
        */
    if(a==1){
        narysujObrazek(szerokosc/2, 0);
    }
    SDL_UpdateWindowSurface(window);
    median_index=0;

    for(int i=0;i<wysokosc*szerokosc/4;i++) {
        obrazek[i].r = z24Rgbna3BW2(obrazek[i]);
        obrazek[i].g = obrazek[i].r;
        obrazek[i].b = obrazek[i].r;
    }

    sortujKubelek(0,wysokosc*szerokosc/4,0);
    medianCutBW(0,szerokosc*wysokosc/4,0);
    if(a==2){
        narysujObrazekBW(szerokosc/2, 0);
    }

    SDL_UpdateWindowSurface(window);

}

uint8_t* pack(uint8_t* a) {
    uint8_t* arr = new uint8_t[3];
    arr[0] = (a[0]<<5)+(a[1]<<2)+(a[2]>>1);
    arr[1] = (a[2]<<7)+(a[3]<<4)+(a[4]<<1)+(a[5]>>2);
    arr[2] = (a[5]<<6)+(a[6]<<3)+(a[7]);
    return arr;
}
uint8_t* rozpakujBity(uint8_t* wejscie) {
    uint8_t* wyjscie = new uint8_t[8];

    wyjscie[0] = (wejscie[0] >> 5);
    wyjscie[1] = (wejscie[0] >> 2);
    wyjscie[2] = (wejscie[0] << 1) + (wejscie[1] >> 7);
    wyjscie[3] = wejscie[1]>>4;
    wyjscie[4] = wejscie[1]>>1;
    wyjscie[5] = (wejscie[1]<<2) + (wejscie[2] >> 6);
    wyjscie[6] = wejscie[2]>>3;
    wyjscie[7] = wejscie[2];

    return wyjscie;
}

void zapisz0braz3N(){
    SDL_Color kolor;
    uint16_t szerokosc0brazka = szerokosc/2;
    uint16_t wysokosc0brazka = wysokosc/2;
    uint8_t wartosc;
    uint8_t* upakowane;
    uint8_t RGB[8];

    cout << "Zapisujemy plik 'obraz1.bin' uzywajac metody write()"<<endl;
    ofstream wyjscie("3N.snk", ios::binary);

    char identyfikator[] = "n";
    wyjscie.write((char*)&identyfikator, sizeof(char));
    wyjscie.write((char*)&szerokosc0brazka, sizeof(uint16_t));
    wyjscie.write((char*)&wysokosc0brazka, sizeof(uint16_t));

    int i=0;
    for(int y=0;y<wysokosc/2;y++) {
        for(int x=0;x<szerokosc/2;x++) {
            kolor = getPixel(x, y);
            RGB[i] = z24na3RGB(kolor);
            i++;
            if (i < 8) {
                continue;
            } else {
                upakowane = pack(RGB);
                for (int j = 0; j < 3; j++) {
                    wyjscie.write((char*)&upakowane[j], sizeof(uint8_t));
                }
                for (int j = 0; j < 8; j++) {
                    RGB[j] = 0;
                }
                i = 0;
            }
        }
    }
    delete upakowane;
    wyjscie.close();

};
void zapiszObraz3BW() {
    SDL_Color kolor;
    uint16_t szerokoscObrazka = szerokosc / 2;
    uint16_t wysokoscObrazka = wysokosc / 2;
    const char* identyfikator = "bw";
    uint8_t BW[8];
    uint8_t* upakowane;

    ofstream wyjscie("3BW.snk", ios::binary);
    wyjscie.write(identyfikator, sizeof(char) * 2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(uint16_t));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(uint16_t));

    int i = 0;
    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            kolor = getPixel(x, y);
            BW[i] = z24Rgbna3BW(kolor);
            i++;
            if (i < 8) {
                continue;
            } else {
                upakowane = pack(BW);
                for (int j = 0; j < 3; j++) {
                    wyjscie.write((char*)&upakowane[j], sizeof(uint8_t));
                }
                for (int j = 0; j < 8; j++) {
                    BW[j] = 0;
                }
                i = 0;
            }
        }
    }

    delete upakowane;
    wyjscie.close();
}
void odczytajObraz3N(string filename) {
    SDL_Color kolor;
    uint16_t szerokosc0brazka = 0;
    uint16_t wysokosc0brazka = 0;
    char* identyfikator = new char[1];
    uint8_t RGB[3];
    uint8_t* rozpakowane = new uint8_t[8];

    ifstream wejscie(filename, ios::binary);
    wejscie.read(identyfikator, sizeof(char));
    wejscie.read((char*)&szerokosc0brazka, sizeof(uint16_t));
    wejscie.read((char*)&wysokosc0brazka, sizeof(uint16_t));

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << szerokosc0brazka << endl;
    cout << "wysokosc: " << wysokosc0brazka << endl;

    int i = 0;
    int x = 0;
    int y = 0;
    while (wejscie.read((char*)&RGB[i], sizeof(uint8_t))) {
        i++;
        if (i < 3) {
            continue;
        } else {
            rozpakowane = rozpakujBity(RGB);
            for (int j = 0; j < 8; j++) {
                kolor = z3rgbna24RGB(rozpakowane[j]);
                setPixel(x + szerokosc0brazka, y, kolor.r, kolor.g, kolor.b);
                if (x == szerokosc0brazka - 1) {
                    y++;
                    x = 0;
                } else {
                    x++;
                }
            }
            i = 0;
        }
    }

    delete[] rozpakowane;
    wejscie.close();
}
void odczytajObraz3BW() {
    SDL_Color kolor;
    uint16_t szerokoscObrazka = 0;
    uint16_t wysokoscObrazka = 0;
    char* identyfikator = new char[2];
    uint8_t BW[3];
    uint8_t* rozpakowane = new uint8_t[8];

    ifstream wejscie("3BW.snk", ios::binary);
    wejscie.read(identyfikator, sizeof(char) * 2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(uint16_t));
    wejscie.read((char*)&wysokoscObrazka, sizeof(uint16_t));

    int i = 0;
    int x = 0;
    int y = 0;
    while (wejscie.read((char*)&BW[i], sizeof(uint8_t))) {
        i++;
        if (i < 3) {
            continue;
        } else {
            rozpakowane = rozpakujBity(BW);
            for (int j = 0; j < 8; j++) {
                kolor = z3BWna24RGB(rozpakowane[j]);
                setPixel(x + szerokoscObrazka, y, kolor.r, kolor.g, kolor.b);
                if (x == szerokoscObrazka - 1) {
                    y++;
                    x = 0;
                } else {
                    x++;
                }
            }
            i = 0;
        }
    }

    delete[] rozpakowane;
    wejscie.close();
}
void generujDedykowana() {
    median_index = 0;
    for(int y=0;y<wysokosc/2;y++)
        for(int x=0;x<szerokosc/2;x++)
            obrazek[x+(y*szerokosc/2)] = getPixel(x,y);
    medianCut(0,szerokosc*wysokosc/4,0);
}
void generujDedykowanaBW() {
    median_index = 0;
    for(int y=0;y<wysokosc/2;y++)
        for(int x=0;x<szerokosc/2;x++)
            obrazek[x+(y*szerokosc/2)] = getPixel(x,y);
    sortujKubelek(0,wysokosc*szerokosc/4,0);
    medianCutBW(0,szerokosc*wysokosc/4,0);
}
void zapiszObraz3D() {
    string f; int length;
    const char* identyfikator = "d";
    generujDedykowana();
    unsigned char arr[szerokosc*wysokosc/2+8*3];
    for(int i=0;i<8;i++) {
        arr[i*3+1]=paleta3d[i].r;
        arr[(i*3)+2]=paleta3d[i].g;
        arr[(i*3)+3]=paleta3d[i].b;
    }
    for(int y=0;y<wysokosc/2;y++) {
        for(int x=0;x<szerokosc/2;x++) {
            arr[y*(szerokosc/2)+x+8*3] = znajdzSasiada(getPixel(x,y));
        }
    }
    f = "3D.snk";
    cout << "Zapisuje obrazek " << f << endl;
    length = szerokosc*wysokosc/4+8*3;

    ofstream file(f, fstream::out | fstream::binary);
    file.write(identyfikator, sizeof(char) * 1);
    file.write((char*)arr, length);
    file.close();
}
void odczytajObraz3D(string filename) {
    char* identyfikator = new char[1];
    ifstream file(filename,ifstream::in | ifstream::binary);
    file.read(identyfikator, sizeof(char) * 1);
    cout << "Odczytuje obrazek " << filename;
    unsigned char arr[szerokosc*wysokosc/4];
    file.read((char*)arr,szerokosc*wysokosc/4);
    for(int i=0;i<8;i++) {
        paleta3d[i]={arr[(i*3)+1],arr[(i*3)+2],arr[(i*3)+3]};
    }
    int t;
    for(int y=0;y<wysokosc/2;y++) {
        for(int x=0;x<szerokosc/2;x++) {
            t = y*szerokosc/2+x+8*3;
            setPixel(x+szerokosc/2,y,paleta3d[arr[t]].r,paleta3d[arr[t]].g,paleta3d[arr[t]].b);
        }
    }
}


void zapiszObraz3BWD() {
    string f; int length;
    const char* identyfikator = "bd";
    generujDedykowanaBW();
    unsigned char arr[szerokosc*wysokosc/2+8*3];
    for(int i=0;i<8;i++) {
        arr[i*3+1]=z24Rgbna3BW2(paleta3bwd[i]);
        arr[(i*3)+2]=z24Rgbna3BW2(paleta3bwd[i]);
        arr[(i*3)+3]=z24Rgbna3BW2(paleta3bwd[i]);
    }
    for(int y=0;y<wysokosc/2;y++) {
        for(int x=0;x<szerokosc/2;x++) {
            arr[y*(szerokosc/2)+x+8*3] = znajdzSasiadaBW(getPixel(x,y));
        }
    }
    f = "3BWD.snk";
    cout << "Zapisuje obrazek " << f << endl;
    length = szerokosc*wysokosc/4+8*3;

    ofstream file(f, fstream::out | fstream::binary);
    file.write(identyfikator, sizeof(char) * 2);
    file.write((char*)arr, length);
    file.close();
}
void odczytajObraz3BWD(string filename) {
    char* identyfikator = new char[2];
    ifstream file(filename,ifstream::in | ifstream::binary);
    file.read(identyfikator, sizeof(char) * 2);
    cout << "Odczytuje obrazek " << filename;
    unsigned char arr[szerokosc*wysokosc/4];
    file.read((char*)arr,szerokosc*wysokosc/4);
    for(int i=0;i<8;i++) {
        paleta3bwd[i]={arr[(i*3)+1],arr[(i*3)+2],arr[(i*3)+3]};
    }
    int t;
    for(int y=0;y<wysokosc/2;y++) {
        for(int x=0;x<szerokosc/2;x++) {
            t = y*szerokosc/2+x+8*3;
            setPixel(x+szerokosc/2,y,paleta3bwd[arr[t]].r,paleta3bwd[arr[t]].r,paleta3bwd[arr[t]].r);
        }
    }


}

void kompresjaByteRun(uint8_t* wejscie, const int& dlugosc, vector<int8_t>& wyjscie) {
    int i = 0;
    int licznik = 0;
    // int licznikZapis;
    // vector<int8_t> wyjscie;

    // dopóki wszystkie bajty nie są skompresowane
    while (i < dlugosc) {
        // sekwencja powtarzających się min. 2 bajtów
        if ((i < dlugosc - 1) && (wejscie[i] == wejscie[i + 1])) {
            // mierzymy długość sekwencji
            licznik = 0;
            while ((i + licznik < dlugosc - 1) && (wejscie[i + licznik] == wejscie[i + licznik + 1]) && (licznik < 127)) {
                licznik++;
            }
            // wypisujemy skompresowaną sekwencję
            // cout << -licznik << ", " << wejscie[i + licznik] << ", ";
            // licznikZapis = -licznik;
            wyjscie.push_back(-licznik);
            wyjscie.push_back(wejscie[i + licznik]);
            // wyjscie.write((char*)&licznikZapis, sizeof(int8_t));
            // wyjscie.write((char*)&wejscie[i + licznik], sizeof(int8_t));
            i += (licznik + 1);
        } else {
            // mierzymy długość sekwencji
            licznik = 0;
            while ((i + licznik < dlugosc - 1) && (wejscie[i + licznik] != wejscie[i + licznik + 1]) && (licznik < 127)) {
                licznik++;
            }
            // dodajemy jeszcze końcówkę
            if ((i + licznik == dlugosc - 1) && (licznik < 127)) {
                licznik++;
            }
            // wypisujemy "skompresowaną" sekwencję
            // cout << licznik - 1 << ", ";
            wyjscie.push_back(licznik - 1);
            for (int j = 0; j < licznik; j++) {
                // cout << wejscie[i + j] << ", ";
                // wyjscie.write((char*)&wejscie[i + j], sizeof(int8_t));
                wyjscie.push_back(wejscie[i + j]);
            }
            // przesuwamy wskaźnik o długośc sekwencji
            i += licznik;
        }
    }
}
void dekompresjaByteRun(const int* wejscie, const int& dlugosc, int* wyjscie) {
    int i = 0;
    int globalCount = 0;
    // dopóki wszystkie bajty nie są zdekompresowane
    while (i < dlugosc) {
        if (wejscie[i] == -128) {
            // kod pusty
            i++;
        } else if (wejscie[i] < 0) {
            // sekwencja powtarzających się bajtów
            int licznik = -(wejscie[i] - 1);
            for (int j = 0; j < licznik; j++) {
                // cout << wejscie[i + 1] << ", ";
                wyjscie[globalCount++] = wejscie[i + 1];
            }
            i += 2;
        } else {
            // sekwencja  różnych bajtów
            int licznik = wejscie[i] + 1;
            for (int j = 0; j < licznik; j++) {
                // cout << wejscie[i + 1 + j] << ", ";
                wyjscie[globalCount++] = wejscie[i + 1 + j];
            }
            i += wejscie[i] + 1 + 1;
        }
    }
}
void zapiszSkompresowanyObraz3BW() {
    SDL_Color kolor;
    uint16_t szerokoscObrazka = szerokosc / 2;
    uint16_t wysokoscObrazka = wysokosc / 2;
    uint16_t dlugosc = szerokoscObrazka * wysokoscObrazka;
    const char* identyfikator = "BW";
    uint8_t* wartosci = new uint8_t[dlugosc];

    ofstream wyjscie("3BW_byterun.snk", ios::binary);
    wyjscie.write(identyfikator, sizeof(char) * 4);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(uint16_t));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(uint16_t));

    int i = 0;
    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            kolor = getPixel(x, y);
            wartosci[i] = z24Rgbna3BW(kolor);
            i++;
        }
    }
    vector<int8_t> skompresowane;
    kompresjaByteRun(wartosci, dlugosc, skompresowane);

    for (int8_t i : skompresowane) {
        wyjscie.write((char*)&i, sizeof(uint8_t));
    }

    wyjscie.close();
    delete[] wartosci;
}

void odczytajSkompresowanyObraz3BW() {
    SDL_Color kolor;
    uint16_t szerokoscObrazka = 0;
    uint16_t wysokoscObrazka = 0;
    char* identyfikator = new char[4];

    ifstream wejscie("3BW_byterun.snk", ios::binary);
    wejscie.read(identyfikator, sizeof(char) * 4);
    wejscie.read((char*)&szerokoscObrazka, sizeof(uint16_t));
    wejscie.read((char*)&wysokoscObrazka, sizeof(uint16_t));

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << szerokoscObrazka << endl;
    cout << "wysokosc: " << wysokoscObrazka << endl;

    vector<int> daneOdczytane;
    int8_t dana;

    while (wejscie.read((char*)&dana, sizeof(int8_t))) {
        daneOdczytane.push_back(dana);
    }

    int* doDekompresji = &daneOdczytane[0];
    int* zdekompresowane = new int[szerokoscObrazka * wysokoscObrazka];

    dekompresjaByteRun(doDekompresji, daneOdczytane.size(), zdekompresowane);

    int i = 0;
    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            // wejscie.read((char*)&BW, sizeof(uint8_t));
            kolor = z3BWna24RGB(zdekompresowane[i]);
            setPixel(x + szerokoscObrazka, y, kolor.r, kolor.g, kolor.b);
            i++;
        }
    }

    delete[] zdekompresowane;
    delete[] identyfikator;
    wejscie.close();
}
void zapiszSkompresowanyObraz3N() {
    SDL_Color kolor;
    uint16_t szerokoscObrazka = szerokosc / 2;
    uint16_t wysokoscObrazka = wysokosc / 2;
    uint16_t dlugosc = szerokoscObrazka * wysokoscObrazka;
    const char* identyfikator = "N";
    uint8_t* wartosci = new uint8_t[dlugosc];

    ofstream wyjscie("3N_byterun.snk", ios::binary);
    wyjscie.write(identyfikator, sizeof(char) * 3);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(uint16_t));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(uint16_t));

    int i = 0;
    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            kolor = getPixel(x, y);
            wartosci[i] = z24na3RGB(kolor);
            i++;
        }
    }
    vector<int8_t> skompresowane;
    kompresjaByteRun(wartosci, dlugosc, skompresowane);

    for (int8_t i : skompresowane) {
        wyjscie.write((char*)&i, sizeof(uint8_t));
    }

    wyjscie.close();
    delete[] wartosci;
}

void odczytajSkompresowanyObraz3N() {
    SDL_Color kolor;
    uint16_t szerokoscObrazka = 0;
    uint16_t wysokoscObrazka = 0;
    char* identyfikator = new char[3];

    ifstream wejscie("3N_byterun.snk", ios::binary);
    wejscie.read(identyfikator, sizeof(char) * 3);
    wejscie.read((char*)&szerokoscObrazka, sizeof(uint16_t));
    wejscie.read((char*)&wysokoscObrazka, sizeof(uint16_t));

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << szerokoscObrazka << endl;
    cout << "wysokosc: " << wysokoscObrazka << endl;

    vector<int> daneOdczytane;
    int8_t dana;

    while (wejscie.read((char*)&dana, sizeof(int8_t))) {
        daneOdczytane.push_back(dana);
    }

    int* doDekompresji = &daneOdczytane[0];
    int* zdekompresowane = new int[szerokoscObrazka * wysokoscObrazka];

    dekompresjaByteRun(doDekompresji, daneOdczytane.size(), zdekompresowane);

    int i = 0;
    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            // wejscie.read((char*)&BW, sizeof(uint8_t));
            kolor = z3rgbna24RGB(zdekompresowane[i]);
            setPixel(x + szerokoscObrazka, y, kolor.r, kolor.g, kolor.b);
            i++;
        }
    }

    delete[] zdekompresowane;
    delete[] identyfikator;
    wejscie.close();
}
void zapiszSkompresowanyObraz3D() {
    generujDedykowana();
    SDL_Color kolor;
    uint16_t szerokoscObrazka = szerokosc / 2;
    uint16_t wysokoscObrazka = wysokosc / 2;
    uint16_t dlugosc = szerokoscObrazka * wysokoscObrazka;
    const char* identyfikator = "D";
    uint8_t* wartosci = new uint8_t[dlugosc];

    ofstream wyjscie("3D_byterun.snk", ios::binary);
    wyjscie.write(identyfikator, sizeof(char) * 3);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(uint16_t));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(uint16_t));

    int i = 0;
    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            kolor = paleta3d[znajdzSasiada(getPixel(x,y))];
            wartosci[i] = z24na8RGB(kolor);
            i++;
        }
    }
    vector<int8_t> skompresowane;
    kompresjaByteRun(wartosci, dlugosc, skompresowane);

    for (int8_t i : skompresowane) {
        wyjscie.write((char*)&i, sizeof(uint8_t));
    }

    wyjscie.close();
    delete[] wartosci;
}

void odczytajSkompresowanyObraz3D() {
    SDL_Color kolor;
    uint16_t szerokoscObrazka = 0;
    uint16_t wysokoscObrazka = 0;
    char* identyfikator = new char[3];

    ifstream wejscie("3D_byterun.snk", ios::binary);
    wejscie.read(identyfikator, sizeof(char) * 3);
    wejscie.read((char*)&szerokoscObrazka, sizeof(uint16_t));
    wejscie.read((char*)&wysokoscObrazka, sizeof(uint16_t));

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << szerokoscObrazka << endl;
    cout << "wysokosc: " << wysokoscObrazka << endl;

    vector<int> daneOdczytane;
    int8_t dana;

    while (wejscie.read((char*)&dana, sizeof(int8_t))) {
        daneOdczytane.push_back(dana);
    }

    int* doDekompresji = &daneOdczytane[0];
    int* zdekompresowane = new int[szerokoscObrazka * wysokoscObrazka];

    dekompresjaByteRun(doDekompresji, daneOdczytane.size(), zdekompresowane);

    int i = 0;
    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            // wejscie.read((char*)&BW, sizeof(uint8_t));
            kolor = z8rgbna24RGB(zdekompresowane[i]);
            setPixel(x + szerokoscObrazka, y, kolor.r, kolor.g, kolor.b);
            i++;
        }
    }

    delete[] zdekompresowane;
    delete[] identyfikator;
    wejscie.close();
}
void zapiszSkompresowanyObraz3BWD() {
    generujDedykowanaBW();
    SDL_Color kolor;
    uint16_t szerokoscObrazka = szerokosc / 2;
    uint16_t wysokoscObrazka = wysokosc / 2;
    uint16_t dlugosc = szerokoscObrazka * wysokoscObrazka;
    const char* identyfikator = "BWD";
    uint8_t* wartosci = new uint8_t[dlugosc];

    ofstream wyjscie("3BWD_byterun.snk", ios::binary);
    wyjscie.write(identyfikator, sizeof(char) * 3);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(uint16_t));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(uint16_t));

    int i = 0;
    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            kolor = paleta3bwd[znajdzSasiadaBW(getPixel(x,y))];
            wartosci[i] = z24na8rgb(kolor);
            i++;
        }
    }
    vector<int8_t> skompresowane;
    kompresjaByteRun(wartosci, dlugosc, skompresowane);

    for (int8_t i : skompresowane) {
        wyjscie.write((char*)&i, sizeof(uint8_t));
    }

    wyjscie.close();
    delete[] wartosci;
}
void odczytajSkompresowanyObraz3BWD() {
    SDL_Color kolor;
    uint16_t szerokoscObrazka = 0;
    uint16_t wysokoscObrazka = 0;
    char* identyfikator = new char[3];

    ifstream wejscie("3BWD_byterun.snk", ios::binary);
    wejscie.read(identyfikator, sizeof(char) * 3);
    wejscie.read((char*)&szerokoscObrazka, sizeof(uint16_t));
    wejscie.read((char*)&wysokoscObrazka, sizeof(uint16_t));

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << szerokoscObrazka << endl;
    cout << "wysokosc: " << wysokoscObrazka << endl;

    vector<int> daneOdczytane;
    int8_t dana;

    while (wejscie.read((char*)&dana, sizeof(int8_t))) {
        daneOdczytane.push_back(dana);
    }

    int* doDekompresji = &daneOdczytane[0];
    int* zdekompresowane = new int[szerokoscObrazka * wysokoscObrazka];

    dekompresjaByteRun(doDekompresji, daneOdczytane.size(), zdekompresowane);

    int i = 0;
    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            // wejscie.read((char*)&BW, sizeof(uint8_t));
            kolor = z8Rgbna24RGB(zdekompresowane[i]);
            setPixel(x + szerokoscObrazka, y, kolor.r, kolor.g, kolor.b);
            i++;
        }
    }

    delete[] zdekompresowane;
    delete[] identyfikator;
    wejscie.close();
}
void zapisz0braz3N_surowe(){
    SDL_Color kolor;
    Uint16 szerokosc0brazka = szerokosc/2;
    Uint16 wysokosc0brazka = wysokosc/2;
    char identyfikator[] = "NS";
    Uint8 wartosc;

    cout << "Zapisujemy plik 'obraz1.bin' uzywajac metody write()"<<endl;
    ofstream wyjscie("3N_surowe.snk", ios::binary);

    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&szerokosc0brazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokosc0brazka, sizeof(Uint16));

    for(int y=0; y<wysokosc0brazka; y++) {
        for(int x=0; x<szerokosc0brazka;x++) {
            kolor=getPixel(x,y);
            wartosc = z24na3RGB(kolor);
            wyjscie.write((char*)&wartosc, sizeof(Uint8));
            //wyjscie.write((char*)&kolor, sizeof(Uint8)*3);
        }
    }

    wyjscie.close();
};

void zapiszobraz3bw_surowe(){

    SDL_Color kolor;
    Uint16 szerokosc0brazka = szerokosc/2;
    Uint16 wysokosc0brazka = wysokosc/2;
    char identyfikator[] = "BS";
    Uint8 BW;

    cout << "Zapisujemy plik 'obraz3BW.bin' uzywajac metody write()"<<endl;
    ofstream wyjscie("3BW_surowe.snk", ios::binary);

    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&szerokosc0brazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokosc0brazka, sizeof(Uint16));

    for(int y=0; y<wysokosc0brazka; y++) {
        for(int x=0; x<szerokosc0brazka;x++) {
            kolor=getPixel(x,y);
            BW = z24Rgbna3BW(kolor);
            wyjscie.write((char*)&BW, sizeof(Uint8));
        }
    }

    wyjscie.close();

}

void odczytajobraz3(string filename){

    Uint16 szerokosc0brazka = 0;
    Uint16 wysokosc0brazka = 0;
    char identyfikator[] = "  ";
    SDL_Color kolor;
    Uint8 wartosc;

    cout << "Odczytujemy plik "<<filename<< " uzywajac metody read()"<<endl;
    ifstream wejscie(filename, ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char)*2);
    wejscie.read((char*)&szerokosc0brazka, sizeof(Uint16));
    wejscie.read((char*)&wysokosc0brazka, sizeof(Uint16));

    cout<< "id: "<<identyfikator<<endl;
    cout<< "szerokosc: "<<szerokosc0brazka<<endl;
    cout<< "wysokosc: "<<wysokosc0brazka<<endl;
    cout<<identyfikator<<endl;
    string x = identyfikator;
    if(x=="NS") //narzucona normlanie
    {
        for(int y=0; y<wysokosc0brazka; y++) {
            for(int x=0; x<szerokosc0brazka;x++) {
                kolor=getPixel(x,y);
                wejscie.read((char*)&wartosc, sizeof(Uint8));
                kolor = z3rgbna24RGB(wartosc);
                setPixel(x+szerokosc0brazka, y,kolor.r , kolor.g, kolor.b);
                }
        }
    }
    if(x=="BS"){ //skala szarosci normalnie
        for(int y=0; y<wysokosc0brazka; y++) {
            for(int x=0; x<szerokosc0brazka;x++) {
                kolor=getPixel(x,y);
                wejscie.read((char*)&wartosc, sizeof(Uint8));
                kolor = z3BWna24RGB(wartosc);
                setPixel(x+szerokosc0brazka, y, kolor.r, kolor.g, kolor.b);
                }
        }
    }
    if(x=="d") //dedykowana normlanie
    {
        odczytajObraz3D(filename);
    }
    if(x=="bd"){ //bwd normalnie
        odczytajObraz3BWD(filename);
    }
    if(x=="n"){ //narzucona za pmoca pack()
        odczytajObraz3N(filename);
    }
    if(x=="bw"){//bw za pomoca pack
        odczytajObraz3BW();
    }
    if(x=="N"){ //narzucona za pomoca byterun
        odczytajSkompresowanyObraz3N();
    }
    if(x=="BW"){ //skala szarosci za pomoca byterun
        odczytajSkompresowanyObraz3BW();
    }
    if(x=="D"){ //dedykowana za pomoca byterun
        odczytajSkompresowanyObraz3D();
    }

    wejscie.close();

}
void Funkcja7(int x) {
    if(x==-1){
        zapisz0braz3N_surowe();
        odczytajobraz3("3N_surowe.snk");
    }
    if(x==0){
        zapiszobraz3bw_surowe();
        odczytajobraz3("3BW_surowe.snk");
    }

    if(x==1){
        zapisz0braz3N();
        odczytajobraz3("3N.snk");
    }

    if(x==2){
        zapiszObraz3BW();
        odczytajobraz3("3BW.snk");
    }

    if(x==3){
        zapiszObraz3D();
        odczytajobraz3("3D.snk");
    }

    if(x==4){
        zapiszObraz3BWD();
        odczytajobraz3("3BWD.snk");
    }

    if(x==5){
        zapiszSkompresowanyObraz3N();
        odczytajobraz3("3N_byterun.snk");
    }

    if(x==6){
        zapiszSkompresowanyObraz3BW();
        odczytajobraz3("3BW_byterun.snk");
    }

    if(x==7){
        zapiszSkompresowanyObraz3D();
        odczytajobraz3("3D_byterun.snk");
    }
    if(x==8){

        zapiszSkompresowanyObraz3BWD();
        odczytajSkompresowanyObraz3BWD();
    }
    SDL_UpdateWindowSurface(window);

}

void Funkcja8() {


}


void Funkcja9() {

}

void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p1 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2) * bpp;
    Uint8 *p2 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2) * bpp;
    Uint8 *p3 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2+1) * bpp;
    Uint8 *p4 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2+1) * bpp;

    /* Ustawiamy wartość piksela, w zależnoœci od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p1 = pixel;
            *p2 = pixel;
            *p3 = pixel;
            *p4 = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p1 = pixel;
            *(Uint16 *)p2 = pixel;
            *(Uint16 *)p3 = pixel;
            *(Uint16 *)p4 = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p1[0] = (pixel >> 16) & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = pixel & 0xff;
                p2[0] = (pixel >> 16) & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = pixel & 0xff;
                p3[0] = (pixel >> 16) & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = pixel & 0xff;
                p4[0] = (pixel >> 16) & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = pixel & 0xff;
            } else {
                p1[0] = pixel & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = (pixel >> 16) & 0xff;
                p2[0] = pixel & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = (pixel >> 16) & 0xff;
                p3[0] = pixel & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = (pixel >> 16) & 0xff;
                p4[0] = pixel & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p1 = pixel;
            *(Uint32 *)p2 = pixel;
            *(Uint32 *)p3 = pixel;
            *(Uint32 *)p4 = pixel;
            break;

        }
    }
}

void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc*2) && (y>=0) && (y<wysokosc*2))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    /* Ustawiamy wartość piksela, w zależności od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p = pixel;
            break;
        }
    }
}

SDL_Color getPixel(int x, int y) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)screen->pixels ;

        //przesunięcie względem y
        pPosition+=(screen->pitch*y*2) ;

        //przesunięcie względem x
        pPosition+=(screen->format->BytesPerPixel*x*2);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, screen->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}

SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)surface->pixels ;

        //przesunięcie względem y
        pPosition+=(surface->pitch*y) ;

        //przesunięcie względem x
        pPosition+=(surface->format->BytesPerPixel*x);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, surface->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}


void ladujBMP(char const* nazwa, int x, int y)
{
    SDL_Surface* bmp = SDL_LoadBMP(nazwa);
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Color kolor;
        for (int yy=0; yy<bmp->h; yy++) {
			for (int xx=0; xx<bmp->w; xx++) {
				kolor = getPixelSurface(xx, yy, bmp);
				setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
			}
        }
		SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }

}


void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_UpdateWindowSurface(window);
}

int wybor;
int menu=0;
void wyswietl_Menu(){
    cout<<"1. Wyswietl obrazek przetworzony z 24 RGB na 3 RGB"<<endl;
    cout<<"2. Wyświetl obrazek przetworzony z 24 RGB na 3 BW"<<endl;
    cout<<"3. Wyświetl palete kolorów narzuconą, skali szarosci oraz dedykowaną"<<endl;
    cout<<"4. Wyswietl obrazek utworzony za pomocą palety dedykowanej"<<endl;
    cout<<"5. Wyswietl obrazek utworzony za pomoca dedykowanej skali szarosci"<<endl;

    cout<<"6. Zapisz i  odczytaj obraz na surowo 3N"<<endl;
    cout<<"7. Zapisz i odczytaj obraz na surowo 3BW"<<endl;
    cout<<"8. Zapisz i odczytaj obraz 3N za pomoca pack()"<<endl;
    cout<<"9. Zapisz i odczytaj obraz 3BW za pomoca pack()"<<endl;

    cout<<"10. Zapisz obraz i odczytaj na surowo 3D dedykowana"<<endl;
    cout<<"11. Zapisz obraz i odczytaj na surowo 3BWD dedykowana w skali szarosci"<<endl;
    cout<<"12. Zapisz i odczytaj obraz 3N za pomoca byterun"<<endl;
    cout<<"13. Zapisz i odczytaj obraz 3BW za pomoca byterun"<<endl;
    cout<<"14. Zapisz i odczytaj obraz 3D za pomoca byterun"<<endl;
    cout<<"15. Zapisz i odczytaj obraz 3BWD za pomoca byterun"<<endl;
    cout<<endl;
    cout<<"Wybierz numer operacji jaka chcesz wykonac: "<<endl;
    cin>>wybor;
    menu=0;
}


int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(tytul, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc*2, wysokosc*2, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
    return false;
    }
    SDL_UpdateWindowSurface(window);


    bool done = false;
    SDL_Event event;
    cout<<"##############################"<<endl;
    cout<<"# Witamy w naszym programie! #"<<endl;
    cout<<"##############################"<<endl;
    cout<<"Wybierz obrazek od A...G"<<endl;
    cout<<endl;

    bool wybrany_obrazek=false;
    // główna pętla programu
    while (SDL_WaitEvent(&event)) {
        // sprawdzamy czy pojawiło się zdarzenie
        switch (menu) {
            case 10:
                done = true;
                break;

            case 0: {
                if (wybor == 1)
                {
                    wybor=0;
                    Funkcja1();
                    system("CLS");
                    cout<<"Obrazek przetworzony z 24 RGB na 3 RGB"<<endl;
                    cout<<endl;
                    menu=20;
                    wyswietl_Menu();

                }
                if (wybor==2)
                {
                    wybor=0;
                    Funkcja2();


                    cout<<endl;
                    system("CLS");
                    cout<<"Obrazek przetworzony z 24 RGB na 3 BW"<<endl;
                    cout<<endl;
                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }
                if (wybor==3)
                {
                    wybor=0;
                    Funkcja5();
                    system("CLS");
                    cout<<"paleta kolorów narzucona, w skali szarosci oraz dedykowana"<<endl;
                    cout<<endl;

                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }

                if (wybor==4)
                {
                    wybor=0;
                    Funkcja6(1);
                    system("CLS");
                    cout<<"Obrazek utworzony za pomocą palety dedykowanej"<<endl;
                    cout<<endl;
                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }

                if (wybor==5)
                {
                    wybor=0;
                    Funkcja6(2);

                    system("CLS");
                    cout<<"Obrazek utworzony za pomoca dedykowanej skali szarosci"<<endl;
                    cout<<endl;
                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }

                if (wybor==6)
                {
                    wybor=0;
                    Funkcja7(-1);

                    system("CLS");
                    cout<<"Zapisano i odczytano surowy obrazek 3N_surowe.snk"<<endl;
                    cout<<endl;
                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }

                if (wybor==7)
                {
                    wybor=0;
                    Funkcja7(0);

                    system("CLS");
                    cout<<"Zapisano i odczytano surowy obrazek 3BW_surowe.snk"<<endl;
                    cout<<endl;
                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }

                if (wybor==8)
                {
                    wybor=0;
                    Funkcja7(1);

                    system("CLS");
                    cout<<"Zapisano i odczytano obrazek za pomocą pack() 3N.snk"<<endl;
                    cout<<endl;
                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }
                if (wybor==9)
                {
                    wybor=0;
                    Funkcja7(2);

                    system("CLS");
                    cout<<"Zapisano i odczytano obrazek za pomocą pack() 3BW.snk"<<endl;
                    cout<<endl;
                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }
                if (wybor==10)
                {
                    wybor=0;
                    Funkcja7(3);

                    system("CLS");
                    cout<<"Zapisano i odczytano surowy obrazek 3D.snk"<<endl;
                    cout<<endl;
                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }
                if (wybor==11)
                {
                    wybor=0;
                    Funkcja7(4);

                    system("CLS");
                    cout<<"Zapisano i odczytano surowy obrazek 3BWD.snk"<<endl;
                    cout<<endl;
                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }

                if (wybor==12)
                {
                    wybor=0;
                    Funkcja7(5);

                    system("CLS");
                    cout<<"Zapisano i odczytano obrazek za pomocą byterun 3N_byterun.snk"<<endl;
                    cout<<endl;
                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }
                if (wybor==13)
                {
                    wybor=0;
                    Funkcja7(6);

                    system("CLS");
                    cout<<"Zapisano i odczytano obrazek za pomocą byterun 3BW_byterun.snk"<<endl;
                    cout<<endl;
                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }

                if (wybor==14)
                {
                    wybor=0;
                    Funkcja7(7);

                    system("CLS");
                    cout<<"Zapisano i odczytano obrazek za pomocą byterun 3D_byterun.snk"<<endl;
                    cout<<endl;
                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }

                if (wybor==15)
                {
                    wybor=0;
                    Funkcja7(8);

                    system("CLS");
                    cout<<"Zapisano i odczytano obrazek za pomocą byterun 3BWD_byterun.snk"<<endl;
                    cout<<endl;
                    wybor=0;
                    menu=20;
                    wyswietl_Menu();

                }

                if(wybrany_obrazek==false){
                    if (event.key.keysym.sym == SDLK_a){
                        ladujBMP("14-1.bmp", 0, 0);
                        wybrany_obrazek=true;
                        wyswietl_Menu();
                    }
                    if (event.key.keysym.sym == SDLK_s)
                    {
                        wybrany_obrazek=true;
                        ladujBMP("14-2.bmp", 0, 0);
                        wyswietl_Menu();
                    }

                    if (event.key.keysym.sym == SDLK_d){
                        wybrany_obrazek=true;
                        ladujBMP("obrazek3.bmp", 0, 0);
                        wyswietl_Menu();
                    }

                    if (event.key.keysym.sym == SDLK_f){
                        wybrany_obrazek=true;
                        ladujBMP("obrazek4.bmp", 0, 0);
                        wyswietl_Menu();
                    }

                    if (event.key.keysym.sym == SDLK_g)
                    {
                        wybrany_obrazek=true;
                        ladujBMP("obrazek5.bmp", 0, 0);
                        wyswietl_Menu();
                    }

                    if (event.key.keysym.sym == SDLK_h){
                        wybrany_obrazek=true;
                        ladujBMP("obrazek6.bmp", 0, 0);
                        wyswietl_Menu();
                    }

                    if (event.key.keysym.sym == SDLK_j){
                        wybrany_obrazek=true;
                        ladujBMP("obrazek7.bmp", 0, 0);
                        wyswietl_Menu();
                    }
                }


               }
        }

    }




    SDL_Quit();
    return 0;
}
