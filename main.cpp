#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;
int n=32000;



struct item
{
    int wartosc;
    item* wsk;
};

struct lisc
{
    int wartosc;
    lisc* lewy;
    lisc* prawy;
};


void stworz_tablice(int A[])
{
   int T[n];
    for(int i=0; i<n; i++)
    {
        T[i]=1;
    }
    for(int i=0; i<n; i++)
    {
        A[i]=rand()%n;
        while(T[A[i]]!=1)
        {
            A[i]=rand()%n;
        }
        T[A[i]]=0;
    }
}

void quicksort(int A[], int p, int k)
{
    int s, i, j;
    i=p; j=k;
    s=A[(p+k)/2];
    while(i<j)
    {
        while(A[i]<s) i++;
        while(A[j]>s) j--;
        if(i<=j) swap(A[i++],A[j--]);
    }
    if(p<j) quicksort(A,p,j);
    if(i<k) quicksort(A,i,k);
}

int szukanie_pol(int szukana, int A[], int p, int k)
{
    int s;
    s=(p+k)/2;
    if(A[s]==szukana) return s;
    else
    {
        if(s<p||s>k)
        return -1;
        else
        {
            if(A[s]<szukana) return szukanie_pol(szukana,A,s+1,k);
            else return szukanie_pol(szukana,A,p,s-1);
        }
    }
}
void sortowanietab(int A[], int B[])
{
    for(int i=0; i<n; i++) B[i]=A[i];
    quicksort(B,0,n-1);
}

void wyszukajwtab(int B[])
{
    int a;
    for(int i=0; i<n; i++)
    {
        a=szukanie_pol(B[i],B,0,n-1);
    }
}

void stworzliste(int A[], item *first)
{
    first->wartosc=A[0];
    first->wsk=NULL;
    for(int i=1; i<n; i++)
    {
        item *next= new item;
        next->wartosc=A[i];
        next->wsk=NULL;
        first->wsk=next;
        first=next;
    }
}
void wyszukajwliscie(item *first)
{
    item *szukana, *obecna;
    int a;
    szukana=first;
    while(szukana!=NULL)
    {
        obecna=first;
        while(obecna!=NULL)
        {
            if(obecna==szukana)
            {
                obecna=NULL;
            }
            else
                obecna=obecna->wsk;
        }
        szukana=szukana->wsk;
    }
}

void usun_liste(item *first)
{
    item *next;
    while(first!=NULL)
    {
        next=first;
        first=first->wsk;
        delete next;
    }
}

void dodaj_tr(lisc *obecny, int szukana, lisc *rodzic)
{
    if(obecny == NULL)
    {
        lisc *next= new lisc;
        next->wartosc=szukana;
        next->lewy=NULL;
        next->prawy=NULL;
        if(rodzic->wartosc>next->wartosc)
            rodzic->lewy=next;
        else
            rodzic->prawy=next;
    }
    else
        {
            if(szukana<obecny->wartosc)
                dodaj_tr(obecny->lewy,szukana,obecny);
            else
                dodaj_tr(obecny->prawy,szukana,obecny);
        }
}

void drzewo_tr(int A[], lisc *korzen)
{
    korzen->wartosc=A[0];
    korzen->lewy=NULL;
    korzen->prawy=NULL;
    lisc* obecny;
    for(int i=1; i<n; i++)
    {
        obecny=korzen;
        dodaj_tr(obecny,A[i],obecny);
    }
}

int znajdz_tr(lisc *korzen, int szukana)
{
    lisc *obecny;
    obecny=korzen;
    while(obecny!=NULL)
    {
        if(obecny->wartosc==szukana) return 1;
        else
        {
            if(obecny->wartosc>szukana) obecny=obecny->lewy;
            else obecny=obecny->prawy;
        }
    }
    return 0;
}

void znajdz_wszystkie_tr(lisc *dziecko,lisc *rodzic, lisc *korzen)
{
    int a;
    if(dziecko == NULL) return;
    else
    {
        znajdz_wszystkie_tr(dziecko->lewy,dziecko,korzen);
        a=znajdz_tr(korzen,dziecko->wartosc);
        znajdz_wszystkie_tr(dziecko->prawy,dziecko,korzen);
    }
}

void wysokosc_tr(lisc *dziecko, lisc *rodzic, lisc *korzen, int &h)
{
    int h1=0, h2=0;
    if(dziecko == NULL) return;
    else
    {
        wysokosc_tr(dziecko->lewy,dziecko,korzen,h1);
        h1++;
        wysokosc_tr(dziecko->prawy,dziecko,korzen,h2);
        h2++;
        if(h1>h2) h=h1;
        else h=h2;
    }
}

void usun_tr(lisc *dziecko, lisc *rodzic)
{
    if(dziecko==NULL) return;
    else
    {
        usun_tr(dziecko->lewy,dziecko);
        usun_tr(dziecko->prawy,dziecko);
        if(dziecko==rodzic->lewy)
        {
            delete dziecko;
            rodzic->lewy=NULL;
        }
        else
        if(dziecko==rodzic->prawy)
        {
            delete dziecko;
            rodzic->prawy=NULL;
        }
    }
}

void stworz_C(int A[], int C[],int &i, int p, int k)
{
    int s =(p+k)/2;
    if(s<p||s>k) return;
    else
    {
        s =(p+k)/2;
        C[i]=A[s];
        i++;
        stworz_C(A,C,i,s+1,k);
        stworz_C(A,C,i,p,s-1);
    }

}

void drzewo_tb(int C[],lisc *korzen2)
{
    drzewo_tr(C,korzen2);
}
void wyswietl_preorder(lisc *obecny)
{
    if(obecny==NULL) return;
    else
    {
        cout<<obecny->wartosc<<" ";
        wyswietl_preorder(obecny->lewy);
        wyswietl_preorder(obecny->prawy);
    }
}
int main()
{
    srand(time(NULL));
    int A[n], B[n], C[n];
    double koniec;
    item first;
    lisc korzen,korzen2;

    cout<<"ilosc_danych: "<<n;


    //pomiar dla tablicy
    stworz_tablice(A);
    clock_t start = clock();
    sortowanietab(A,B);
    koniec=(clock()-start)/(double)CLOCKS_PER_SEC;
    cout<<endl<<"tworzenie_tablicy_B "<<koniec;

    start=clock();
    wyszukajwtab(B);
    koniec=(clock()-start)/(double)CLOCKS_PER_SEC;
    cout<<endl<<"znajdowanie_w_tablicy_B "<<koniec;


    //pomiar dla listy
    start=clock();
    stworzliste(A,&first);
    koniec=(clock()-start)/(double)CLOCKS_PER_SEC;
    cout<<endl<<"tworzenie_listy "<<koniec;

    start=clock();
    wyszukajwliscie(&first);
    koniec=(clock()-start)/(double)CLOCKS_PER_SEC;
    cout<<endl<<"szukanie_w_liscie "<<koniec;


    //pomiar dla drzewa tr
    start=clock();
    drzewo_tr(A,&korzen);
    koniec=(clock()-start)/(double)CLOCKS_PER_SEC;
    cout<<endl<<"tworzenie_tr "<<koniec;

    start=clock();
    znajdz_wszystkie_tr(&korzen, &korzen, &korzen);
    koniec=(clock()-start)/(double)CLOCKS_PER_SEC;
    cout<<endl<<"znajdowanie_w_tr "<<koniec;
    int h=0, h2=0;
    wysokosc_tr(&korzen,&korzen,&korzen,h);
    cout<<endl<<"wysokosc_tr: "<<h<<endl;

    //pomiar dla drzewa tb
    int wielkosc=0;
    stworz_C(B,C,wielkosc,0,n-1);
    start=clock();
    drzewo_tb(C,&korzen2);
    koniec=(clock()-start)/(double)CLOCKS_PER_SEC;
    cout<<"tworzenie_tb "<<koniec;
    wysokosc_tr(&korzen2,&korzen2,&korzen2,h2);
    cout<<endl<<"wysokosc_tb: "<<h2<<endl;
    //wyswietl_preorder(&korzen2);
    start=clock();
    znajdz_wszystkie_tr(&korzen2, &korzen2, &korzen2);
    koniec=(clock()-start)/(double)CLOCKS_PER_SEC;
    cout<<"znajdowanie_w_tb "<<koniec;


    usun_tr(&korzen,&korzen);
    usun_liste(&first);
    usun_tr(&korzen2,&korzen2);
    return 0;
}
