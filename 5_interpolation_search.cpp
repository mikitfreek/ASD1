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

void Random(int* t, int n, int zakres)
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
	} while (z > n || z <= 0);
	return z;
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

void QuickSort(int tab[], int left, int right)
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
//						< InterSearch(tab, length,s)>
//---------------------------------------------------------

int Interpolation(int tab[], int left, int right, int s)
{
	__int64 temp = (left + (((static_cast<__int64>(s) - tab[left]) * (static_cast<__int64>(right) - left) / (static_cast<__int64>(tab[right]) - tab[left]))));
	return (int)(temp);
}


int InterSearch(int* tab, int length, int s, int& k)
{
	int left = 0,
		right = (int)(length)-1,
		mid;

	while (left <= right)
	{
		mid = Interpolation(tab, left, right, s);

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

float InterSearchStatistics(int length, int ilosc, int& k, int max)
{
	float res;
	int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;

	for (int i = 0; i < max; i++) //tab avr loop
	{
		int* tab = new int[length + 1];

		Random(tab, length, 0);

		int left = 0, right = length - 1;
		QuickSort(tab, left, right);

		int r = randomIndex(length);
		int tmp = (int)(tab[r - 1]); //przekazanie indexu i zamina na wart liczbowa
		int s = tmp;

		k = 0; //reset k
		int mid = InterSearch(tab, length, s, k);

		int temp;
		if (i < 400) {
			temp = k;
			sum1 += temp;
		}

		if (i >= 400 && i < 700) {
			temp = k;
			sum2 += temp;
		}

		if (i >= 700 && i < 900) {
			temp = k;
			sum3 += temp;
		}

		if (i >= 900) {
			temp = k;
			sum4 += temp;
		}
		delete[] tab; //free mem
		tab = NULL;
	}

	res = (float)(sum1 + sum2 + sum3 + sum4) / (float)max;

	return res;
}

float* TestInterSearch(int len, int ilosc, int skok, int& k, int max)
{
	float* res = new float[ilosc];

	cout << "> TestBinarySearch przy uzyciu QuickSort" << endl;

	for (int i = 0; i < ilosc; i++) //tab length loop
	{
		int length = (int)(len)+(int)(i)*skok;

		float _res = InterSearchStatistics(length, ilosc, k, max);
		res[i] = _res;

		cout << i + 1 << " z " << _res << " .." << endl; //ilosc
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
	srand((int)time(&_time));

	do
	{
		res = TestInterSearch(len, ilosc, skok, k, max);

		Output(res, ilosc, len, skok, "output.txt");

		Print(res, ilosc);

		Del(res);

		cout << "\nZakonczyc? t-tak inny-nie" << endl;
		cin >> znak;

	} while (znak != 't');

	return EXIT_SUCCESS;
}