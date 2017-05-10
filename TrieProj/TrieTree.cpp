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

Node::Node() {}

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


DLeftCountingBloomFilter* Node::getDLeft()
{
	return &dleft;
}
CountingBloomFilter* Node::getCBF()
{
	return &cbf;
}

void Node::addDLeft(const string& str)
{
	dleft.add(str);
}

void Node::removeDLeft(const string& str)
{
	dleft.remove(str);
}

void Node::addCBF(const string& str)
{
	cbf.add(str);
}

void Node::removeCBF(const string& str)
{
	cbf.remove(str);
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
		topName = getPostfix(mit->first);//获取顶级域名
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
		temp1->setIpList(prefix, mit->second);
		temp1->addDLeft(prefix);
		temp1->addCBF(prefix);
	}
	return TrieTree(root);
}
