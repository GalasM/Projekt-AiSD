#include<iostream>
#include<cstdlib>
#include<chrono>
#include<fstream>
#include "main.h"

//ZMIENNE GLOBALNE
unsigned long long loop_counter,changes_counter,I;

using namespace std;



int main()
{
    unsigned long long I;
    int wybor;
    cout<<"Ile elementow ma posiadac tablica do posortowania"<<endl;
    cin >> I;
    if (cin.fail())
    {
        system("cls");
        cout << "Podano bledna wartosc" << endl;
        return 0;
    }
    if(I<1)
    {
        system("cls");
        cout<<"Podano za mala wartosc"<<endl;
        return 0;
    }
    double *t=new double[I];
    double *t2=new double[I];
    system("cls");
    cout<<"Jaka tablice posortowac? Wcisnij..."<<endl<<endl<<"1.Wypelniona losowymi liczbami"<<endl;
    cout<<"2.Wypelniona posortowanymi liczbami(rosnaco)"<<endl;
    cout<<"3.Wypelniona posortowanymi liczbami(malejaco)"<<endl<<endl;
    cin>>wybor;

    switch(wybor)
    {
    case 1:
        system("cls");
        FillFile(t,I);
        loadFromFile(t);
        coppyArray(t,t2,I);
        break;
    case 2:
        system("cls");
        FillFile(t,I);
        loadFromFile(t);
        bubbleSortPerf(t,I);
        coppyArray(t,t2,I);
        break;
    case 3:
        system("cls");
        FillFile(t,I);
        loadFromFile(t);
        bubbleSortReverse(t,I);
        coppyArray(t,t2,I);
        break;
    default:
        system("cls");
        puts("Podano bledna wartosc");
        return 0;
        break;
    }
    /* cout<<"Tablica przed sortowaniem:"<<endl;
     printArray(t,I);
     puts("");*/
    cout<<"Liczba elementow tablicy: "<<I<<endl<<endl;
    cout<<"Sortowanie algorytmem z udoskonaleniami"<<endl;
    auto start = chrono::system_clock::now();
    bubbleSortPerf(t,I);
    chrono::duration<double> d = chrono::system_clock::now() - start;
    cout<<"Liczba przejsc petli: "<<loop_counter<<endl;
    cout<<"Liczba zamian: "<<changes_counter<<endl;
    cout <<"Czas sortowania algorytmem z udoskonaleniami: "<< d.count()<<endl<<endl;
    cout<<"Sortowanie algorytmem bez udoskonalen"<<endl;
    auto start1 = chrono::system_clock::now();
    bubbleSort(t2,I);
    chrono::duration<double> e = chrono::system_clock::now() - start1;
    cout<<"Liczba przejsc petli: "<<loop_counter<<endl;
    cout<<"Liczba zamian: "<<changes_counter<<endl;
    cout <<"Czas sortowania algorytmem bez udoskonalen: "<< e.count()<<endl<<endl;
   /* cout<<"Tablica posortowana algorytmem z udoskonaleniami:"<<endl;
    printArray(t,I);
    puts("");
    cout<<"Tablica posortowana algorytmem bez udoskonalen:"<<endl;
    printArray(t2,I);*/
    return 0;
}

//**********************************FUNKCJE***********************************

//******SORTOWANIE Z UDOSKONALENIAMI**********
void bubbleSortPerf(double *t,unsigned long long N)
{
    int change=0;
    changes_counter=0,loop_counter=0;
    unsigned long long k=0,i,j;
    double temp;
    do
    {
        for (i=k; i<N-1-k; i++)
        {
            if (t[i]>t[i+1])
            {
                change++;
                temp=t[i];
                t[i]=t[i+1];
                t[i+1]=temp;
                changes_counter++;
            }
            loop_counter++;
        }
        change=0;
        for(j=N-1-k; j>k; j--)
        {
            if (t[j]<t[j-1])
            {
                change++;
                temp=t[j];
                t[j]=t[j-1];
                t[j-1]=temp;
                changes_counter++;
            }
            loop_counter++;
        }
        k++;
    }
    while(change!=0);
}

//********SORTOWANIE BEZ UDOSKONALEN***********
void bubbleSort(double *t,unsigned long long N)
{
    double temp;
    changes_counter=0,loop_counter=0;
    unsigned long long i,j;
    for(j = 0; j < N-1; j++)
        for(i = 0; i < N -1; i++)
        {
            if(t[i] > t[i + 1])
            {
                temp=t[i];
                t[i]=t[i+1];
                t[i+1]=temp;
                changes_counter++;
            }
            loop_counter++;
        }
}
//********OPERACJE NA PLIKACH************
void FillFile(double *tab,unsigned long long N)
{
    fstream file;
    filltab(tab,N);
    file.open("data.txt",ios::out);
    if(file.good()==true)
    {
        for(unsigned long long i =0; i<N; i++)
            file<<tab[i]<<endl;
    }
    else
    {
        cout<<"Blad pliku"<<endl;
        exit(0);
    }
    file.close();
}

void loadFromFile(double *t)
{
    string line;
    unsigned long long i=0;
    fstream file;
    file.open("data.txt", ios::in);

    if(file.is_open()==true)
    {
        while (getline(file, line))
        {
            t[i]=atof(line.c_str());
            i++;
        }
    }
    else
    {
        cout<<"Blad pliku"<<endl;
        exit(0);
    }
    file.close();
}
//**************POZOSTALE FUNKCJE***************
void bubbleSortReverse(double *t,unsigned long long N)
{
    int change=1;
    unsigned long long loop_counter=0,changes_counter=0,k=0,i,j;
    double temp;

    do
    {
        change=0;
        for (i=k; i<N-1-k; i++)
        {
            if (t[i]<t[i+1])
            {
                change++;
                temp=t[i];
                t[i]=t[i+1];
                t[i+1]=temp;
                changes_counter++;
            }
            loop_counter++;
        }
        change=0;
        for(j=N-2-k; j>k; j--)
        {
            if (t[j]>t[j-1])
            {
                change++;
                temp=t[j];
                t[j]=t[j-1];
                t[j-1]=temp;
                changes_counter++;
            }
            loop_counter++;
        }
        k++;
    }
    while(change!=0);
}


void filltab(double *tab,unsigned long long N)
{
    unsigned long long i,min,range;
    min = 0;
    range = 10;
    srand(time(NULL));
    for(i = 0; i < N; i++)
    {
        tab[i] = min + (double)rand()/RAND_MAX * range;

    }
}

void printArray(double *t,unsigned long long N)
{
    for (unsigned long long j=0; j<N; j++)
    {
        cout<<t[j]<<endl;
    }
}

void coppyArray(double *t,double *t2,unsigned long long N)
{

    for(unsigned long long i=0; i<N; i++)
    {
        t2[i]=t[i];
    }
}

