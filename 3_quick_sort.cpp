#include <iostream>
#include <ctime>
#include <time.h>
#include <fstream>

using namespace std;

void Print(int* t, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "A[" << (i + 1) * 10 << "] = " << t[i] << endl;
	}
}

void Random(int* t, int n, int zakres)
{
	for (int i = 0; i < n; i++)
	{
		if (zakres == 0) t[i] = rand();
		else t[i] = rand() % (zakres);
	}
}

void Swap(int* t, int* p)
{
	int temp = *t;
	*t = *p;
	*p = temp;
}

//---------------------------------------------------------
//						<QuickSort>
//---------------------------------------------------------

void QuickSort(int tab[], int left, int right, int& k)
{
	int pos, i;

	if (left < right)
	{
		k++;
		pos = left;
		i = left + 1;

		for (; ; )
		{
			if (i > right)
			{
				k++;
				Swap(&tab[pos], &tab[left]);
				QuickSort(tab, left, pos - 1, k);
				QuickSort(tab, pos + 1, right, k);
				
				return;
			}
			else
			{
				if (tab[i] < tab[left])
				{
					k++;
					pos++;
					Swap(&tab[pos], &tab[i]);
				}
				i++;
			}
		} 
	}
}

int QuickSortStatistics(int krok, int ilosc, int& k, int max)
{
	int res,
		* temp = new int[max];
	for (int i = 0; i < max; i++) //tab avr loop
	{
		int* tab = new int[krok];

		Random(tab, krok, 0);

		int left = 0, right = krok - 1;
		k = 0;
		QuickSort(tab, left, right, k);

		temp[i] = k;
	}

	int sum = 0;
	for (int i = 0; i < max; i++) //tab avr loop
	{
		sum += temp[i];
	}
	sum = sum / max;
	res = sum;

	return res;
}

int* TestQuickSort(int len, int ilosc, int skok, int& k, int max)
{
	int* res = new int[ilosc];
	for (int i = 0; i < ilosc; i++) //tab length loop
	{
		int krok = len + i * skok;
		int _res = QuickSortStatistics(krok, ilosc, k, max);
		res[i] = _res;

		system("CLS");
		cout << "> QuickTest" << endl;
		cout << "Badany rozmiar tablicy: " << i * 10 << endl;
		cout << i + 1 << " z " << ilosc << " ..";
		if (i == 99) system("CLS");
	}
	return res;
}

//---------------------------------------------------------
//						</QuickSort>
//---------------------------------------------------------

void Output(int* t, int n, int len, int skok, const char* output)
{
	fstream file;
	file.open(output, ios::out);

	if (!file) {
		cout << "Blad zapisu pliku!" << endl;
	}
	else {
		cout << "Zapisano do pliku o nazwie: " << output << endl;
		for (int i = 0; i < n; i++)
		{
			int krok = len + i * skok;

			file << krok << "	";
			file << *(t + i) << endl;
		}
		file.close();
	}
}

void Del(int* tab)
{
	delete[] tab;
	tab = NULL;
}

int main()
{
	int len = 10, // wyraz a1
		ilosc = 100,
		skok = 10,
		max = 1000,
		k;

	int* res;
	char znak = 0;

	time_t _time;
	srand((unsigned)time(&_time));

	do
	{

		res = TestQuickSort(len, ilosc, skok, k, max);

		Output(res, ilosc, len, skok, "output1.txt");

		Print(res, ilosc);
		
		Del(res);

		cout << "\nZakonczyc? t-tak inny-nie" << endl;
		cin >> znak;

	} while (znak != 't');

	return EXIT_SUCCESS;
}