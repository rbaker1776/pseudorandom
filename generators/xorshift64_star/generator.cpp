#include <iostream>
#include <fstream>


constexpr int BITSTRING_SIZE = 16'000'000;


uint64_t xorshift64star_rand()
{
	static uint64_t x = 123456789ull;
	x ^= x >> 12;
	x ^= x << 25;
	x ^= x >> 27;
	return x * 0x2545f4914f6cdd1dull;
}


int main()
{
	std::ofstream outfile("./randomness.txt");
	for (int i = 0; i < BITSTRING_SIZE / 8; ++i)
	{
		uint64_t r = xorshift64star_rand();
		outfile.write(reinterpret_cast<char*>(&r), sizeof(r));
	}

	outfile.close();
	return 0;
}
