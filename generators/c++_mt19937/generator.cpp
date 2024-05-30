#include <iostream>
#include <fstream>
#include <random>


constexpr int BITSTRING_SIZE = 16'000'000;


int main()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<uint32_t> dist(0, UINT32_MAX);

	std::ofstream outfile("./randomness.txt");
	for (int i = 0; i < BITSTRING_SIZE / 4; ++i)
	{
		uint32_t r = dist(mt);
        outfile.write(reinterpret_cast<char*>(&r), sizeof(r));
	}

	outfile.close();
	return 0;
}
