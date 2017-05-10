#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <time.h>
#include <unordered_map>

#include "TrieTree.h"
#include "Routerlist.h"
#include "DLeftCountingBloomFilter.h"

using std::unordered_map;
using std::cout;
using std::endl;
using std::ifstream;
using std::list;
using std::unordered_map;
using std::iterator;

string path_name_data("D:\\C++_Project\\TrieProj\\TrieProj\\data.txt");
string path_name_diffdata("D:\\C++_Project\\TrieProj\\TrieProj\\diffdata.txt");
string path_ip_data("D:\\C++_Project\\TrieProj\\TrieProj\\ipdata.txt");
string path_ip_diffdata("D:\\C++_Project\\TrieProj\\TrieProj\\ipdiffdata.txt");
string path_resultdata("D:\\C++_Project\\TrieProj\\TrieProj\\resultdata.txt");

unordered_map<string, string> routerlist;
TrieTree trietree;
vector<string> urls;
vector<string> prefixs;
vector<string> postfixs;
ofstream res;

int test_hash();
int test_trie();
int test_dleft();
int test_cbf();
string shorten(string&);
void create_hash_list(string&);
void create_trietree();
void test(int, double);
void generate_data(int, double);

//int total = 0;
//int trie_target = 0;
//int cbf_target = 0;
//int dleft_target = 0;

int main()
{
	//res.open(path_resultdata);
	//res << "类型 总量 命中率 时间" << endl;

	//建立路由表和树
	create_hash_list(path_name_data);
	create_trietree();

	cout << "路由表建立完成！" << endl;
	test(1000, 0.5);
	//test(73000, 0.0);
	//test(91000, 0.0);
	//test(75000, 1.0);

	//生成不同命中率和总量的数据
	//cout << "------------------命中率：0%------------------"<< endl;
	//for (int num = 1000; num <= 100000; num += 2000)
	//{
		//total = num;
	//	test(num, 0.0);
	//}
	//cout << "------------------命中率：100%------------------" << endl;
	//for (int num = 1000; num <= 100000; num += 2000)
	//{
		//total = num;
	//	test(num, 1.0);
	//}
	//cout << "------------------命中率：50%------------------" << endl;
	//for (int num = 10000; num <= 100000; num += 10000)
	//{
	//	total = num;
	//	test(num, 0.5);
	//}

	//res.close();

	getchar();

	return 0;
}

void test(int num, double rate)
{
	generate_data(num, rate);
	test_trie();
	test_cbf();
	test_dleft();

	//cout << "========================" << endl;
	//cout << "总量: " << num << endl;
	//cout << "命中率: " << rate << endl;
	//cout << "========================" << endl;

	//res << "hash " << num << " " << rate << " " << (test_hash()+ test_hash()+ test_hash())/3 << endl;
	//res << "hash_trie " << num << " " << rate << " " << (test_hash_trie()+ test_hash_trie()+ test_hash_trie())/3 << endl;
	//res << "hash_trie_cbf " << num << " " << rate << " " << (test_hash_trie_cbf()+ test_hash_trie_cbf()+test_hash_trie_cbf())/3<< endl;

	//res << "hash " << num << " " << rate << " " << test_hash() << endl;
	//int r = 0;
	//r += test_trie();
	//r += test_trie();
	//r += test_trie();
	//res << "trie " << num << " " << rate << " " << r/3 <<endl;
	//r += test_cbf();
	//r += test_cbf();
	//r += test_cbf();
	//res << "cbf " << num << " " << rate << " " << r/3 << endl;
	
	//r = 0;
	//r += test_dleft();
	//r += test_dleft();
	//r += test_dleft();
	//res << "dleft " << num << " " << rate << " " << r/3 << endl;

	//cout << "========================" << endl;
}

void create_hash_list(string& path)
{
	//根据原有数据构建Trie树和hash表

	ifstream infile;
	infile.open(path);
	routerlist.clear();
	routerlist = createRouterlist(infile);
	infile.close();
}

void create_trietree()
{
	trietree = createTrieTree(routerlist);
}

int test_dleft()
{
	clock_t start, end;

	cout << "Dleft : " << endl;

	start = clock();
	//int n = 0, m = 0;
	//dleft_target = trie_target;
	for (int i = 0; i < (int)urls.size(); i++)
	{
		//m++;
		string prefix = prefixs[i];
		string postfix = postfixs[i];
		Node* node = trietree.searchNode(postfix);
		if (node != NULL)
		{
			unordered_map<int, DLeftCountingBloomFilter>* dleftList = node->getDLeftList();
			//unordered_map<string, string> ipList = *(node->getIpList());
			int length = getLength(prefix);

			while (length > 0) {
				int index = 0;
				if (length >= 5)
				{
					index = 5;
				}
				else
				{
					index = length;
				}
				DLeftCountingBloomFilter dleft = (*dleftList)[index];
				//域名退化
				if (!dleft.isContain(prefix))
				{
					prefix = shorten(prefix);
				}
				else
				{
					(*(node->getIpList()))[prefix];
					break;
				}
				length--;
			}
		}
	}
	end = clock();
	//dleft_target = abs(dleft_target);

	cout << end - start << endl;
	//cout << dleft_target << endl;
	//cout << n << endl;
	//cout << m << endl << endl;
	return end - start;
}

int test_cbf()
{
	clock_t start, end;

	cout << "cbf : " << endl;

	start = clock();
	//int n = 0, m = 0;
	//cbf_target = trie_target;
	for (int i = 0; i < (int) urls.size(); i++)
	{
		//m++;
		string prefix = prefixs[i];
		string postfix = postfixs[i];
		Node* node = trietree.searchNode(postfix);
		if (node != NULL)
		{
			unordered_map<int , CountingBloomFilter>* cbfList = node->getCBFList();
			//unordered_map<string, string> list = *(node->getIpList());
			int length = getLength(prefix);
			
			while (length > 0) {
				int index = 0;
				if (length >= 5)
				{
					index = 5;
				}
				else
				{
					index = length;
				}
				CountingBloomFilter cbf = (*cbfList)[index];
				//域名退化
				if (!cbf.isContain(prefix))
				{
					prefix = shorten(prefix);
				}
				else
				{
					(*(node->getIpList()))[prefix];
					break;
				}
				length--;
			}
		}
	}
	end = clock();

	/*clock_t start1, end1;
	Node* node = trietree.searchNode("com");
	unordered_map<int, CountingBloomFilter>* cbfList = node->getCBFList();
	CountingBloomFilter cbf = (*cbfList)[1];

	start1 = clock();
	for (int i = 0; i < 1000; i++)
		cbf.isContain("123");
	end1 = clock();
	cout << "cbf: " << end1 - start1 << endl;

	unordered_map<string, string> list = *(node->getIpList());
	start1 = clock();
	for (int i = 0; i < 1000; i++)
		list["123"];
	end1 = clock();
	cout << "hash: " << end1 - start1 << endl;*/

	//cbf_target = abs(cbf_target);

	cout << end - start << endl;
	//cout << cbf_target << endl;
	//cout << n << endl;
	//cout << m << endl << endl;

	return end - start;
}

int test_trie()
{
	clock_t start, end;

	cout << "hash_trie : " << endl;

	start = clock();
	//int n = 0, m = 0;
	//trie_target = 0;
	for (int i = 0; i< (int)urls.size(); i++)
	{
		//m++;
		string prefix = prefixs[i];
		string postfix = postfixs[i];
		Node* node = trietree.searchNode(postfix);
		if (node != NULL)
		{
			while ((*(node->getIpList()))[prefix] != "")
			{
			//	n++;
				//trie_target++;
				prefix = shorten(prefix);
				//(*(node->getIpList()))[prefix];
			}
		}
	}

	end = clock();
	//trie_target = n;
	cout << end - start << endl;
	//cout << n << endl;
	//cout << m << endl << endl;


	return end - start;
}

int test_hash()
{
	clock_t start, end;
	int m = 0, n = 0;
	cout << "hash : " << endl;

	start = clock();
	for (string url : urls)
	{
		m++;
		if (routerlist[url] != "") {
			n++;
		}
	}

	end = clock();
	cout << end - start << endl << endl;
	cout << n << endl;
	cout << m << endl << endl;
	return end - start;
}

void generate_data(int count_total_data, double rate) {
	string url;
	string ip;

	ifstream data;
	urls.clear();
	prefixs.clear();
	postfixs.clear();

	data.open(path_name_data);
	int count_data = (int)(count_total_data * rate);
	int counter_data = 1;
	while (getline(data, url)) {
		if (counter_data > count_data)
			break;
		urls.push_back(url);
		prefixs.push_back(getPrefix(url));
		postfixs.push_back(getPostfix(url));
		getline(data, ip);
		counter_data++;
	}
	data.close();

	ifstream diff_data;
	diff_data.open(path_name_diffdata);
	int count_diffdata = count_total_data - count_data;
	int counter_diffdata = 1;
	while (getline(diff_data, url)) {
		if (counter_diffdata > count_diffdata)
			break;
		urls.push_back(url);
		prefixs.push_back(getPrefix(url));
		postfixs.push_back(getPostfix(url));
		getline(diff_data, ip);
		counter_diffdata++;
	}
	diff_data.close();
}

string shorten(string &str)
{
	string::size_type begin;
	begin = str.find_first_of(".");
	if (begin == string::npos)
		return "";
	return str.substr(begin);
}