#pragma once
#include"common.h"
#include"charactor.h"
#include"huff_tree.h"
using namespace std;

class EnCode
{
	friend class Zip;
private:
	HuffTree tree_;
	string src_file_;
	CharDict dict_;

	void AnalyzeFile();
public:
	EnCode(const string &file_name);

	void CreateHuffCode(HTNode* root,unsigned int tmp_code,ind_t code_len);
};
