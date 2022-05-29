#include <iostream>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

void wypisz(float *t, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "A[" << (i + 1) * 10 << "] = " << t[i] << endl;
    }
}

int wyszukaj(int *t, int liczba, int n, int &k)
{
    k = 0;
    for (int i = 0; i < n; i++)
    {
        k++;
        if (*(t + i) == liczba)
        {
            return i;
        }
    }
    return -1;
}

void losuj(int *t, int n, int zakres)
{
    for (int i = 0; i < n; i++)
    {
        if (zakres == 0) t[i] = rand();
        else t[i] = rand() % (zakres);
    }
}

int losujIndex(int n)
{
    int z;
    do
    {
        z = rand();
    } while (z > n);
    return z;
}

float *wyszukajStat(int len, int ilosc, int skok, int liczba, int &k)
{
    int stat = 100;

    int **buff;
    buff = new int *[ilosc];
    for (int i = 0; i < ilosc; i++)
        buff[i] = new int[ilosc];

    float *res = new float[ilosc];

    for (int i = 0; i < ilosc; i++) //tab loop
    {
        int krok = len + i * skok;
        int* t = new int[krok];

        int index=0;
        for (int j = 0; j < ilosc; j++) //main loop
        {
            index = losujIndex(krok);

            t[index] = 1;

            int lic = wyszukaj(t, 1, krok, k);

            buff[i][j] = k;

            t[index] = 0;
        }

        float sum=0;
        for (int j = 0; j < ilosc; j++) //sum loop
        {
            sum += buff[i][j];
        }
        sum = sum / stat;
        res[i] = sum;
    }
    return res;
}

void zapisz(float *t, int n)
{
    fstream file;

    

    file.open("output.txt", ios::out);

    if (!file) {
        cout << "Blad zapisu pliku!";
    }
    else {
        cout << "Zapisano do pliku o nazwie: output.txt";
        for (int i = 0; i < n; i++)
        {
            string s(to_string(*(t + i))); // float -> string
            replace(s.begin(), s.end(), '.', ','); // '.' -> ','

            file << s << endl;
        }

        file.close();
    }
}

void usun(float *tab)
{
    delete[] tab;
    tab = NULL;
}

int main()
{
    int len = 10, ilosc, zakres = 0, liczba = 1, skok = 10, k;
    float *resStat;
    char znak;

    time_t _time;
    srand((unsigned)time(&_time));

    do
    {
        cout << "podaj ilosc tablic: " << endl;
        cin >> ilosc;

        resStat=wyszukajStat(len, ilosc, skok, liczba, k);
        wypisz(resStat, ilosc);
        zapisz(resStat, ilosc);

        cout << "\nZakonczyc? t-tak inny-nie" << endl;
        cin >> znak;
        cout << endl;

        //for (int i = 0; i < ilosc; i++) 
        usun(resStat);

    } while (znak != 't');
    return 0;
}