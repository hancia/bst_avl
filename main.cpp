#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int n=10;
int zakres=40;
 string cr, cl, cp;



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

 void printBT(string sp, string sn, lisc * v)
 {
 	string s;

 	if (v)
 	{
 		s = sp;
 		if (sn == cr) s[s.length() - 2] = ' ';
 		printBT(s + cp, cr, v->prawy);

 		s = s.substr(0, sp.length() - 2);
 		cout << s << sn << v->wartosc << endl;

 		s = sp;
 		if (sn == cl) s[s.length() - 2] = ' ';
 		printBT(s + cp, cl, v->lewy);
 	}
}

void stworz_tablice(int A[])
{
   int T[zakres];
    for(int i=0; i<zakres; i++)
    {
        T[i]=1;
    }
    for(int i=0; i<n; i++)
    {
        A[i]=rand()%zakres;
        while(T[A[i]]!=1)
        {
            A[i]=rand()%zakres;
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
            if(obecna=szukana)
            {
                obecna=NULL;
            }
            else
                obecna=obecna->wsk;
        }
        szukana=szukana->wsk;
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

int main()
{

  cr = cl = cp = "  ";
  cr[0] = 218; cr[1] = 196;
  cl[0] = 192; cl[1] = 196;
  cp[0] = 179;
    srand(time(NULL));
    int A[n], B[n];;
    double koniec;
    item first;
    lisc korzen;
    stworz_tablice(A);
    clock_t start = clock();
    sortowanietab(A,B);
    koniec=clock()-start;
    for(int i=0; i<n; i++) cout<<A[i]<<" ";
    cout<<endl<<"czas tworzenia talicy B wynosi "<<koniec;
    start=clock();
    wyszukajwtab(B);
    koniec=clock()-start;
    cout<<endl<<"czas znajdowania elementow w talicy B wynosi "<<koniec;
    start=clock();
    stworzliste(A,&first);
    koniec=clock()-start;
    cout<<endl<<"czas tworzenia listy wynosi "<<koniec;
    start=clock();
    wyszukajwliscie(&first);
    koniec=clock()-start;
    cout<<endl<<"czas szukania w liœcie wynosi "<<koniec;
    drzewo_tr(A,&korzen);
    lisc *wsk;
    wsk=&korzen;
    cout<<endl;
    printBT("", "", wsk);
    znajdz_wszystkie_tr(&korzen, &korzen, &korzen);
    cout<<"wysokosc to: ";
    int h=0;
    wysokosc_tr(&korzen,&korzen,&korzen,h);
    cout<<h;
    return 0;
}
