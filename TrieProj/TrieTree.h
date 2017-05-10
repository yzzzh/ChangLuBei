#pragma once
#ifndef GUARD_TrieTree_h
#define GUARD_TrieTree_h

#include <map>
#include <string>
#include <vector>
#include "DLeftCountingBloomFilter.h"
#include "CountingBloomFilter.h"
#include <unordered_map>

using std::unordered_map;
using std::string;
using std::vector;
using std::unordered_map;

class Node
{
public:

	Node();
	~Node();

	Node* search(const char&);	//���Ҵ洢c���ӽ��
	void addChild(const char&, Node*);
	void setIpList(const string&, const string&);
	unordered_map<string, string>* getIpList();
	unordered_map<int, DLeftCountingBloomFilter>* getDLeftList();
	unordered_map<int, CountingBloomFilter>* getCBFList();
	void addDLeft(int,const string&);
	void removeDLeft(int,const string&);
	void addCBF(int,const string&);
	void removeCBF(int,const string&);

private:

	unordered_map<char, Node*> childs;	//�ӽ���
	unordered_map<string, string> ipList;
	unordered_map<int, DLeftCountingBloomFilter> dleftList;
	unordered_map<int, CountingBloomFilter> cbfList;
};

class TrieTree
{
public:

	TrieTree();
	TrieTree(Node *);
	~TrieTree();
	Node* searchNode(const string&);

private:

	Node *root;

};
//��ú�׺
string getPostfix(const string&);
//���ǰ׺
string getPrefix(const string&);
//������
TrieTree createTrieTree(const unordered_map<string, string>&);
//��ȡ��������
int getLength(const string&);
#endif 
