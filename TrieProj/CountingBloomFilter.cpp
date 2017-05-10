#include "CountingBloomFilter.h"

CountingBloomFilter::CountingBloomFilter()
{
	//ctor
}

CountingBloomFilter::~CountingBloomFilter()
{
	//dtor
}

void CountingBloomFilter::add(const std::string &str)
{
	if (isContain(str))
		return;
	int position = 0;
	for (int seed : seeds)
	{
		position = BKDR_hash(seed, str);
		cbf_counter_array[position] += 1;
	}
}

void CountingBloomFilter::remove(const std::string &str)
{
	unsigned int position = 0;
	//std::vector<unsigned int> positions;
	int positions[3];
	int i = 0;
	for (unsigned int seed : seeds)
	{
		position = BKDR_hash(seed, str);
		if (cbf_counter_array[position] == 0)
			return;
		//positions.push_back(position);
		positions[i++] = position;
	}

	for (auto pos : positions)
	{
		cbf_counter_array[pos] -= 1;
	}
}

bool CountingBloomFilter::isContain(const std::string &str)
{
	unsigned int position = 0;
	for (unsigned int seed : seeds)
	{
		position = BKDR_hash(seed, str);
		if (cbf_counter_array[position] == 0)
			return false;
	}
	return true;
}

//std::vector<unsigned int> CountingBloomFilter::seeds = { 31, 131, 1313 };
int CountingBloomFilter::seeds[3] = { 31, 131, 1313 };
// BKDRhash
unsigned int CountingBloomFilter::BKDR_hash(unsigned int seed, const std::string &str)
{
	unsigned int result = 0;
	for (auto ch : str)
		result = seed * result + (unsigned int)ch;
	return ((CBF_LENGTH)-1) & result;
}
