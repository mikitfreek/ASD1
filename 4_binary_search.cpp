#include <iostream>
#include <ctime>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

void Print(float* t, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "A[" << (i + 1) * 10 << "] = " << t[i] << endl;
	}
}

void Random(long long* t, int n, int zakres)
{
	for (int i = 0; i < n; i++)
	{
		if (zakres == 0) t[i] = rand();
		else t[i] = rand() % (zakres);
	}
}

int randomIndex(int n)
{
	int z;
	do
	{
		z = rand();
	} while (z > n || z == 0);
	return z;
}

void Swap(long long* t, long long* p)
{
	long long temp = *t;
	*t = *p;
	*p = temp;
}

//---------------------------------------------------------
//						<QuickSort>
//---------------------------------------------------------

void QuickSort(long long tab[], int left, int right)
{
	int pos, i;

	if (left < right)
	{
		pos = left;
		i = left + 1;

		for (; ; )
		{
			if (i > right)
			{
				Swap(&tab[pos], &tab[left]);
				QuickSort(tab, left, pos - 1);
				QuickSort(tab, pos + 1, right);

				return;
			}
			else
			{
				if (tab[i] < tab[left])
				{
					pos++;
					Swap(&tab[pos], &tab[i]);
				}
				i++;
			}
		}
	}
}

//---------------------------------------------------------
//						<BinarySearch>
//---------------------------------------------------------

int BinarySearch(long long tab[], int length, int s, int& k)
{
	int left = 0,
		right = length - 1,
		mid;

	while (left <= right)
	{
		mid = (left + right) / 2;

		k++;
		if (tab[mid] == s)
			return mid;

		k++;
		if (tab[mid] < s)
			left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}

float BinarySearchStatistics(int krok, int ilosc, int& k, int max)
{
	float res;
	int * temp = new int[max];
	for (int i = 0; i < max; i++) //tab avr loop
	{
		long long* tab = new long long[krok];

		Random(tab, krok, 0);

		int left = 0, right = krok - 1;
		QuickSort(tab, left, right);

		int r = randomIndex(krok);
		int s = tab[r - 1]; //przekazanie indexu i zamina na wart liczbowa

		k = 0; //reset k
		int mid = BinarySearch(tab, krok, s, k);

		temp[i] = k;
	}

	float sum = 0;
	for (int i = 0; i < max; i++) //tab avr loop
	{
		sum += temp[i];
	}
	sum = sum / max;
	res = sum;

	return res;
}

float* TestBinarySearch(int len, int ilosc, int skok, int& k, int max)
{
	float* res = new float[ilosc];
	for (int i = 0; i < ilosc; i++) //tab length loop
	{
		int krok = len + i * skok;

		float _res = BinarySearchStatistics(krok, ilosc, k, max);
		res[i] = _res;

		//system("CLS");
		cout << "> TestBinarySearch przy uzyciu QuickSort" << endl;
		cout << "Badany rozmiar tablicy: " << krok << endl;
		cout << i + 1 << " z " << ilosc << " ..";
		cout << endl;
		if (i == ilosc - 1) system("CLS");
	}
	return res;
}

//---------------------------------------------------------
//						</BinarySearch>
//---------------------------------------------------------

void Output(float* t, int n, int len, int skok, const char* output)
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

			string s(to_string(*(t + i))); // float -> string
			replace(s.begin(), s.end(), '.', ','); // '.' -> ','
			
			s = s.substr(0, s.find_last_not_of('0') + 1); // skracanie '0'
			if (s.find(',') == s.size() - 1) // skracanie ','
			{
				s = s.substr(0, s.size() - 1);
			}

			file << krok << "	";
			file << s << endl;
		}
		file.close();
	}
}

void Del(float* tab)
{
	delete[] tab;
	tab = NULL;
}

int main()
{
	int len = 10, // wyraz a1
		ilosc = 1000, //skok*1000=10000
		skok = 10,
		max = 1000, //1000
		k;

	float* res;
	char znak = 0;

	time_t _time;
	srand((unsigned)time(&_time));

	do
	{
		res = TestBinarySearch(len, ilosc, skok, k, max);

		Output(res, ilosc, len, skok, "output.txt");

		Print(res, ilosc);

		Del(res);

		cout << "\nZakonczyc? t-tak inny-nie" << endl;
		cin >> znak;

	} while (znak != 't');

	return EXIT_SUCCESS;
}