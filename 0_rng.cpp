#include <iostream>
#include <time.h>

using namespace std;

void losuj(int* t, int n, int zakres)
{
    for (int i = 0; i < n; i++)
    {
        if (zakres == 0) t[i] = rand();
        else t[i] = rand() % (zakres);
    }
}

int* utworz(int n)
{
    int* tab;
    tab = new int[n];

    return tab;
}

void wypisz(int* t, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "A[" << i + 1 << "] = " << t[i] << endl;
    }
}

int wyszukaj(int* t, int liczba, int n, int& k)
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

void usun(int* tab)
{
    delete[] tab;
    tab = NULL;
}

int main()
{
    int ilosc, zakres, liczba, lic, k;
    char znak;
    do
    {
        cout << "podaj ilosc liczb: " << endl;
        cin >> ilosc;

        cout << "\npodaj zakres liczb (0 = inf): " << endl;
        cin >> zakres;

        time_t _time;
        srand((unsigned)time(&_time));
        int* t = utworz(ilosc);

        cout << "\nlosowanie.." << endl;
        losuj(t, ilosc, zakres);

        cout << "\nwylosowane liczby:" << endl;
        wypisz(t, ilosc);

        cout << "\npodaj liczbe do znalezienia: " << endl;
        cin >> liczba;

        lic = wyszukaj(t, liczba, ilosc, k);

        if (lic != -1) cout << "\nZnaleziono!" << endl;
        else cout << "\nNieznaleziono.." << endl;
        cout << "Ilosc operacji: " << k << endl;

        cout << "\nZakonczyc? t-tak inny-nie" << endl;
        cin >> znak;
        cout << endl;

        usun(t);

    } while (znak != 't');
    return 0;
}