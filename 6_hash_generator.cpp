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
		cout << "A[" << (i + 1) * 50 << "] = " << t[i] << endl;
	}
}

int GenerateKey1()
{
	int z;
	do
	{
		z = rand();
	} while (z > 9999 || z <= 0);
	return z;
}

int GenerateKey2()
{
	int z;
	do
	{
		z = rand();
	} while (z > 19999 || z <= 10000);
	return z;
}

int Hash1(int k)
{
	int m = 701;
	return k % m;
}

int Hash2(int k)
{
	int q = 700;
	return 1 + k % q;
}

int Hash(int k, int i)
{
	int m = 701;
	return (Hash1(k) + i * Hash2(k)) % m;
}

void AddKey(int k, int* tab, int& c)
{
	for (int i = 0; i < 701; i++)
	{
		int index = Hash(k, i);
		if (tab[index] == 0)
		{
			c++;
			tab[index] = k;
		}
		else return;
	}
}

void FillTab(int* tab, int fill)
{
	for (int i = 0; i < fill; i++)
		tab[i] = GenerateKey1();
}

float HashStatistics(int fill, int ilosc, int& c, int max)
{
	float res;
	int sum = 0;

	for (int i = 0; i < max; i++) //tab avr loop
	{
		int* tab = new int[ilosc];

		FillTab(tab, fill);

		int k = GenerateKey2();
		c = 0; //reset c
		AddKey(k, tab, c);


		int temp;
		temp = c;
		sum += temp;

		delete[] tab; //free mem
		tab = NULL;
	}

	res = (float)sum / (float)max;

	return res;
}

float* TestHash(int len, int ilosc, int skok, int& c, int max)
{
	float* res = new float[10];

	cout << "> TestHash <" << endl;

	for (int i = 0; i < 10; i++) //tab length loop
	{
		int fill = (i + 1) * skok;
		float _res = HashStatistics(fill, ilosc, c, max);
		res[i] = _res;

		//system("CLS");
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
	int len = 50, // wyraz a1
		ilosc = 701,
		skok = 50,
		max = 1000, //1000
		c;

	float* res;
	char znak = 0;

	time_t _time;
	srand((int)time(&_time));

	do
	{
		res = TestHash(len, ilosc, skok, c, max);

		Output(res, ilosc, len, skok, "output.txt");

		Print(res, 10);

		Del(res);

		cout << "\nZakonczyc? t-tak inny-nie" << endl;
		cin >> znak;

	} while (znak != 't');

	return EXIT_SUCCESS;
}