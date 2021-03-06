#include <algorithm>
#include <unordered_map>
#include "TrieTree.h"
#include "DLeftCountingBloomFilter.h"


using std::unordered_map;
using std::string;
using std::vector;
using std::unordered_map;
using std::find_if;
using std::cout;
using std::endl;

Node::Node() 
{
}

Node::~Node() {}

Node* Node::search(const char& c)
{
	unordered_map<char, Node*>::iterator i;
	i = childs.find(c);
	if (i == childs.end())
	{
		return NULL;
	}
	else
	{
		return i->second;
	}
}

void Node::addChild(const char& c, Node* child)
{
	childs[c] = child;
}
void Node::setIpList(const string &prefix, const string& ip)
{
	ipList[prefix] = ip;
}

unordered_map<string, string>* Node::getIpList()
{
	return &ipList;
}


unordered_map<int, DLeftCountingBloomFilter>* Node::getDLeftList()
{
	return &dleftList;
}
unordered_map<int, CountingBloomFilter>* Node::getCBFList()
{
	return &cbfList;
}

void Node::addDLeft(int i,const string& str)
{
	dleftList[i].add(str);
}

void Node::removeDLeft(int i ,const string& str)
{
	dleftList[i].remove(str);
}

void Node::addCBF(int i,const string& str)
{
	cbfList[i].add(str);
}

void Node::removeCBF(int i,const string& str)
{
	cbfList[i].remove(str);
}

TrieTree::TrieTree() {}

TrieTree::TrieTree(Node *node) : root(node) {}

TrieTree::~TrieTree() {}

Node* TrieTree::searchNode(const string& name)
{
	Node* temp1, *temp2;
	temp1 = root;
	for (char c : name)
	{
		temp2 = (*temp1).search(c);
		if (!temp2)
		{
			return NULL;
		}
		temp1 = temp2;
	}
	return temp1;
}
string getPostfix(const string& url)
{
	string::size_type begin;
	begin = url.find_last_of(".");
	return url.substr(begin + 1);
}

string getPrefix(const string& url)
{
	string::size_type begin;
	begin = url.find_last_of(".");
	return url.substr(0, begin);
}

TrieTree createTrieTree(const unordered_map<string, string>& routerlist)
{
	Node *root = new Node(), *temp1, *temp2;
	string topName;
	string prefix;
	unordered_map<string, string>::const_iterator mit;
	for (mit = routerlist.begin(); mit != routerlist.end(); mit++)
	{
		temp1 = root;
		topName = getPostfix(mit->first);//��ȡ��������
		prefix = getPrefix(mit->first);
		for (char c : topName)
		{
			temp2 = (*temp1).search(c);
			if (!temp2)
			{
				temp2 = new Node();
				(*temp1).addChild(c, temp2);
			}
			temp1 = temp2;
		}
		int length = getLength(prefix);
		temp1->setIpList(prefix, mit->second);
		if (length < 5) {
			temp1->addDLeft(length,prefix);
			temp1->addCBF(length,prefix);
		}
		else
		{
			temp1->addDLeft(5, prefix);
			temp1->addCBF(5, prefix);
		}
	}
	return TrieTree(root);
}

int getLength(const string& s)
{
	int sum = 0;
	char ch = '.';
	for (char c : s)
	{
		if (c == ch)
			sum++;
	}
	return ++sum;
}

