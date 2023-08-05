#pragma once
#include"common.h"
using namespace std;

struct Charactor
{
	char char_ = 0;//字符
	unsigned int times_ = 0;//出现次数
	unsigned int code_ = 0;//编码
    ind_t code_len_ = 0;
	Charactor() = default;
	Charactor(char ch, int times);
	bool operator==(const Charactor& msg);
};

//字典
using CharDict = unordered_map<char,Charactor>;

void DictWriteToFile(const CharDict &dict,ofstream &ofs);//字典写入文件
void FileReadToDict(CharDict &dict,ifstream &ifs);//从文件中读字典
