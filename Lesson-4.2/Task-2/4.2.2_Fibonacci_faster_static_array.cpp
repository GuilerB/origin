#include <iostream>

unsigned long long fibo(unsigned long long* arr, const int& size, int n)

{
	if (arr[n] != -1) { return arr[n]; }
	if (n < 2) { return n; }
	arr[n] = fibo(arr, size, n - 2) + fibo(arr, size, n - 1);

	return arr[n];
}

int main()
{
	while (true) {

		int N{ 0 };

		std::cout << "Enter an int number (how many Fibo nums to show) less than 150: ";
		std::cin >> N;
		std::cout << "\nFibonacci numbers: ";

		const int Nmax = 150;
		unsigned long long mem[Nmax];

		for (int i = 0; i < Nmax; ++i) {
			mem[i] = -1;
		}

		for (int i = 0; i < N; i++)
		{
			if (i == N - 1) {
				std::cout << fibo(mem, Nmax, i) << std::endl;
			}
			else {
				std::cout << fibo(mem, Nmax, i) << ", ";
			}
		}	
	}
}
