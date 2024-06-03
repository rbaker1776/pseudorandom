#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <chrono>


constexpr uint64_t BITSTRING_SIZE = 16'000'000; // bytes
static uint8_t bytes[BITSTRING_SIZE];

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;


// Writes the outstream operator for a vector
// Useful for debugging and printing vectors
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	os << "<";
	for (int i = 0; i < v.size(); ++i)
	{
		os << v[i];
		if (i != v.size() - 1) { os << ", "; }
	}
	os << ">";
	return os;
}


// Reads a file into the global "bytes" array in a bitwise manner
// Each character in the file is written to the array
void read_file_into_array(const std::string& f)
{
	std::cout << "Reading " << f << "..." << std::endl;
	auto start = steady_clock::now();
	std::ifstream file(f, std::ios::binary);
	
	if (!file.is_open())
	{
		std::cerr << "Error opening: " << f << std::endl;
		return;
	}
	
	for (int i = 0; file >> std::noskipws >> bytes[i]; ++i) {}
	file.close();
	
	auto end = steady_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
	std::cout << "Successfully read " << f << " in " << double(duration.count()) / 1000.0 
			  << " seconds" << std::endl;
}


// Returns a sub-bitstring of length k, beginning "offset" bits past the pointer "byte" 
uint32_t extract_substring(const uint8_t* byte, int offset, int k)
{
	int num_bytes_to_read_ahead = (k + offset - 1) / 8;
	int bits_to_read_from_last_byte = (k + offset) % 8;
	if (bits_to_read_from_last_byte == 0) { bits_to_read_from_last_byte = 8; }
	uint32_t substring = 0;

	for (int i = num_bytes_to_read_ahead, j = 0; i >= 0; --i, ++j)
	{
		substring |= byte[i] << (8 * j);
	}

	substring >>= 8 - bits_to_read_from_last_byte;
	return substring & ((1 << k) - 1);
}


// Returns the distribution of sub-bitstrings of length k within global bytes array
std::vector<int> substring_distribution(int k)
{
	std::vector<int> dist(1 << k, 0);
	auto start = steady_clock::now();

	for (int i = 0; i < (BITSTRING_SIZE * 8) - k + 1; ++i)
	{
		int byte_offset = i / 8;
		int bit_offset  = i % 8;
		uint32_t substring = extract_substring(&bytes[byte_offset], bit_offset, k);
		++dist[substring];
	}

	auto end = steady_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
	std::cout << "Successfully calculated substring distribution for k=" << k << " in " 
			  << double(duration.count()) / 1000.0 << " seconds" << std::endl;
	return dist;
}


// Returns the expected substring distribution of length k within bytes
std::vector<double> expected_distribution(int k)
{
	return std::vector<double>(1 << k, (BITSTRING_SIZE * 8 - k + 1) / (1 << k));
}


// Returns the chi-square statistic between two distributions
double chi_square(const std::vector<double>& expected, const std::vector<int>& observed)
{
	double xi = 0;
	for (int i = 0; i < expected.size(); ++i)
	{
		xi += double(pow(observed[i] - expected[i], 2)) / double(expected[i]);
	}
	return xi;
}


int main()
{
	const std::vector<std::string> infiles = 
	{
		//"./generators/c++_mt19937/randomness.txt",
		//"./generators/c_stdlib_rand/randomness.txt",
		//"./generators/python_random/randomness.txt",
		//"./generators/python_numpy_random/randomness.txt",
		//"./generators/java_math_random/randomness.txt",
		//"./generators/java_util_random/randomness.txt",
		//"./generators/matlab_randi/randomness.txt",
		//"./generators/xorshift64/randomness.txt",
		//"./generators/xorshift64_star/randomness.txt",
		"./generators/atmospheric_noise/randomness.txt",
	};
	const std::vector<std::string> outfiles = 
	{
		//"./generators/c++_mt19937/chi_square_results.txt",
		//"./generators/c_stdlib_rand/chi_square_results.txt",
		//"./generators/python_random/chi_square_results.txt",
		//"./generators/python_numpy_random/chi_square_results.txt",
		//"./generators/java_math_random/chi_square_results.txt",
		//"./generators/java_util_random/chi_square_results.txt",
		//"./generators/matlab_randi/chi_square_results.txt",
		//"./generators/xorshift64/chi_square_results.txt",
		//"./generators/xorshift64_star/chi_square_results.txt",
		"./generators/atmospheric_noise/chi_square_results.txt",
	};

	for (int i = 0; i < infiles.size(); ++i)
	{
		auto start = steady_clock::now();
		read_file_into_array(infiles[i]);
		std::ofstream outfile(outfiles[i]);
		outfile << "### k, chi-square, degrees-of-freedom, p-value" << std::endl;

		for (int k = 1; k <= 24; ++k)
		{
			std::vector<double> exp = expected_distribution(k);
			std::vector<int> obs = substring_distribution(k);
			outfile << k << ", ";
			outfile << std::fixed << std::setprecision(8) << chi_square(exp, obs) << ", ";
			outfile << (1 << k) - 1 << ", ";
			outfile << std::endl;
		}

		outfile.close();
		auto end = steady_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);
		std::cout << "Completed chi-square analysis of " << infiles[i] << " in " 
				  << double(duration.count()) / 1000.0 << " seconds" << std::endl << std::endl;
	}

	read_file_into_array("./generators/atmospheric_noise/randomness.txt");
	std::cout << substring_distribution(1) << std::endl;

	return 0;
}
