#pragma once
#include"common.h"
#include"charactor.h"
#include"huff_tree.h"
using namespace std;

class DeCode
{
	friend class UnZip;
private:
	HuffTree tree_;
	string src_file_;
	CharDict dict_;
    streampos last_pos_;

	void AnalyzeFile();
public:
	DeCode(const string& file_name);
	inline int get_all_alpha()//获取总共的字符数
	{
		int ret = 0;
		for (const auto &entry : dict_)
		{
			ret += entry.second.times_;
		}
		return ret;
	}
};
