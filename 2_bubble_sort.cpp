#include <iostream>
#include <ctime>
#include <time.h>
#include <fstream>

using namespace std;

void wypiszf(int* t, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "A[" << (i + 1) * 10 << "] = " << t[i] << endl;
	}
}

void losuj(int* t, int n, int zakres)
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

void BubbleSort1(int arr[], int n, int &k)
{
	int ch;
	k = 0;

	do
	{
		ch = 0;
		for (int i = 0; i < n - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				ch = 1;
				Swap(&arr[i], &arr[i+1]);
			}
			k++;
		}
	} 	while (ch != 0);
}

void BubbleSort2(int* tab, int length, int &k)
{
	int ch, p = 0;
	k = 0;
	do
	{
		ch = 0;
		for (int i = 0; i < length - p - 1; i++)
		{
			k++;
			if (tab[i] >= tab[i + 1])
			{

				ch = 1;
				Swap(&tab[i], &tab[i + 1]);
			}
		}
		p++;
	} while (ch != 0);
}

int BubbleSortStatistics1(int krok, int ilosc, int& k, int max)
{
	int res,
		*temp = new int[max];
	for (int i = 0; i < max; i++) //tab avr loop
	{
		int* tab = new int[krok];

		losuj(tab, krok, 0);

		BubbleSort1(tab, krok, k);

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

int BubbleSortStatistics2(int krok, int ilosc, int& k, int max)
{
	int res,
		* temp = new int[max];
	for (int i = 0; i < max; i++) //tab avr loop
	{
		int* tab = new int[krok];

		losuj(tab, krok, 0);

		BubbleSort2(tab, krok, k);

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

int* TestBubbleSort1(int len, int ilosc, int skok, int& k, int max)
{
	int* res = new int[ilosc];
	for (int i = 0; i < ilosc; i++) //tab length loop
	{
		int krok = len + i * skok;
		int _res = BubbleSortStatistics1(krok, ilosc, k, max);
		res[i] = _res;

		system("CLS");
		cout << "> BubbleTest1" << endl;
		cout << "Badany rozmiar tablicy: " << i * 10 << endl;
		cout << i + 1 << " z " << ilosc * 2 << " ..";
		if(i == 99) system("CLS");
	}
	return res;
}

int* TestBubbleSort2(int len, int ilosc, int skok, int& k, int max)
{
	int* res = new int[ilosc];
	for (int i = 0; i < ilosc; i++) //tab length loop
	{
		int krok = len + i * skok;
		int _res = BubbleSortStatistics2(krok, ilosc, k, max);
		res[i] = _res;

		system("CLS");
		cout << "> BubbleTest2" << endl;
		cout << "Badany rozmiar tablicy: " << i * 10 << endl;
		cout << i + 101 << " z " << ilosc * 2 << " ..";
		if (i == 99) system("CLS");
	}
	return res;
}

void output(int* t, int n, int len, int skok, const char* output)
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

void usun(int* tab)
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

	int* res1, *res2;
	char znak = 0;

	time_t _time;
	srand((unsigned)time(&_time));

	do
	{

		res1 = TestBubbleSort1(len, ilosc, skok, k, max);

		output(res1, ilosc, len, skok, "output1.txt");

		res2 = TestBubbleSort2(len, ilosc, skok, k, max);

		output(res2, ilosc, len, skok, "output2.txt");

		wypiszf(res1, ilosc);
		wypiszf(res2, ilosc);
		
		usun(res1);
		usun(res2);

		cout << "\nZakonczyc? t-tak inny-nie" << endl;
		cin >> znak;

	} while (znak != 't');

	return EXIT_SUCCESS;
}