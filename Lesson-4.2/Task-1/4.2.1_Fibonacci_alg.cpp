#include <iostream>

int fibo(int n)

{
	return n < 2 ? n : fibo(n - 2) + fibo(n - 1);
}

int main()
{
	int N{};

	std::cout << "Enter an int number (how many Fibo nums to show): ";
	std::cin >> N;
	std::cout << N << std::endl;
	std::cout << "\nFibonacci numbers: ";

	for (int i = 0; i < N; i++)
	{
		if (i == N - 1) {
			std::cout << fibo(i) << std::endl;
		}
		else {
			std::cout << fibo(i) << ", ";
		}
	}
	return 0;
}
