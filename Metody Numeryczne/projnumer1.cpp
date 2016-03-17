#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

#define ELEMENTY_SZEREGU 15

double factorial(double n)
{
	if (n == 0)
		return 1;
	return n * factorial(n - 1);
}

double sinFront(double x, int numbElements)
{
	double result = 0.0;
	double top;
	double bottom;
	for (int n = 0; n <= numbElements; ++n)
	{
		double inside = 2 * n + 1;
		top = pow(-1, n) * pow(x, inside);
		bottom = factorial(inside);
		result += top / bottom;
	}
	return result;
}

double sinBack(double x, int numbElements)
{
	double result = 0.0;
	double top;
	double bottom;
	for (int n = numbElements; n >= 0; --n)
	{
		double inside = 2 * n + 1;
		top = pow(-1, n) * pow(x, inside);
		bottom = factorial(inside);
		result += top / bottom;
	}
	return result;
}


double sinPrev(double x, double E)
{
	double k = 0, y = 0, S = x;
	double sign = 1;
	while (abs(S) > E)
	{
		y += S;
		k++;
		S *= -(x * x) / ((2 * k  +1 ) * 2 * k);
	}
	return y;
}

int main()
{
	//sinPrev2(1, 0.0001);
	double x = 0;
	FILE * file;
	errno_t err;
	if (err = fopen_s(&file, "Obliczenia.txt", "w+") != 0)
	{
		printf("blad");
	}
	else
	{
		fprintf(file, "X\tsin(x) CMATH\tsin(x) od przodu\tsin(x) od tylu\tsin(x) z kroku wstecz\n");
		for (int i = 0; i < 1570; i++)
		{
			x += 0.004;
			fprintf(file, "%.10f\t%.14f\t%.14f\t%.14f\t%.14f\n", x, sin(x), sinFront(x, ELEMENTY_SZEREGU), sinBack(x, ELEMENTY_SZEREGU), sinPrev(x, 0.00000001));
		}
	}
	fclose(file);
	return 0;
}
