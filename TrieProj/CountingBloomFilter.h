#pragma once
#ifndef __COUNTINGBLOOMFILTER_H__
#define __COUNTINGBLOOMFILTER_H__

#include <string>
#include <vector>

#define CBF_LENGTH 1 << 16

class CountingBloomFilter
{
public:

	CountingBloomFilter();
	~CountingBloomFilter();

	void add(const std::string &str);
	void remove(const std::string &str);
	bool isContain(const std::string &str);

protected:

private:
	//        uint32_t cbf_counter_vector_size = 0;
	//        uint16_t cbf_hash_amount = 0;
	//        BYTE cbf_bit_array[BITNSLOTS(CBF_LENGTH)] = {'\0'};
	uint8_t cbf_counter_array[CBF_LENGTH] = { 0 };
	static std::vector<unsigned int> seeds;
	static unsigned int BKDR_hash(unsigned int seed, const std::string &str);
};

#endif // __COUNTINGBLOOMFILTER_H__
