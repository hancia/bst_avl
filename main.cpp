#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int n=10;
int zakres=40;

struct item
{
    int wartosc;
    item* wsk;
};
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
        cout<<B[i]<<" ";
    }
    for(int i=0; i<n; i++)
    {
        a=szukanie_pol(B[i],B,0,n-1);
        cout<<a<<endl;
    }
}
int main()
{
    srand(time(NULL));
    int A[n];
    double koniec;
    stworz_tablice(A);
    clock_t start = clock();
    int B[n];
    sortowanietab(A,B);
    koniec=clock()-start;
    for(int i=0; i<n; i++) cout<<A[i]<<" ";
    cout<<endl<<"czas tworzenia talicy B wynosi "<<koniec;
    start=clock();
    wyszukajwtab(B);
    koniec=clock()-start;
    cout<<endl<<"czas znajdowania elementow w talicy B wynosi "<<koniec;
    return 0;
}
