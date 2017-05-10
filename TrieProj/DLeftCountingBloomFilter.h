#ifndef __DLEFTCOUNTINGBLOOMFILTER_H__
#define __DLEFTCOUNTINGBLOOMFILTER_H__

#include <stdint.h>
#include <string>
#include <stdlib.h>
#include <iostream>
using std::string;

#define FNV_OFFSET_BASIS (uint64_t)2166136261
#define FNV_PRIME (uint64_t)16777619

#define HASHVALUE_MAX_LOG2 32
#define BUCKET_SIZE 16
#define HASHTALBE_SIZE_LOG2 16
#define FINGERPRINT_MAX_LOG2 16
#define HASHTALBE_SIZE (uint32_t)(1 << HASHTALBE_SIZE_LOG2)
#define FINGERPRINT_MAX (uint32_t)(1 << FINGERPRINT_MAX_LOG2)
#define DLEFT_SUBTALBE_SIZE 4
#define PERMUTATION_ODDNUMBER (uint64_t)13099

struct Cell
{
	uint16_t fingerprint = 0;
	uint8_t counter = 0;
};
struct Bucket
{
	Cell cells[BUCKET_SIZE];
};
struct HashTable
{
	Bucket buckets[HASHTALBE_SIZE];
};

class DLeftCountingBloomFilter
{
public:
	DLeftCountingBloomFilter();
	void add(const string &str);
	void remove(const string &str);
	bool isContain(const string &str) const;
private:
	HashTable* hashtables[DLEFT_SUBTALBE_SIZE];
	uint32_t FNV32_1a_hash(const string &str) const;
	void permutation(uint32_t &hashvalue) const;
};

#endif // __DLEFTCOUNTINGBLOOMFILTER_H__
