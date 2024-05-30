#include <iostream>
#include <fstream>


constexpr int BITSTRING_SIZE = 16'000'000;


uint64_t xorshift64_rand()
{
	static uint64_t x = 123456789ull;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return x;
}


int main()
{
	std::ofstream outfile("./randomness.txt");
	for (int i = 0; i < BITSTRING_SIZE / 8; ++i)
	{
		uint64_t r = xorshift64_rand();
		outfile.write(reinterpret_cast<char*>(&r), sizeof(r));
	}

	outfile.close();
	return 0;
}
