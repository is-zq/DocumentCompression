#pragma once
#include"common.h"
#include"charactor.h"
#include"huff_tree.h"
#include"decoding.h"
using namespace std;


class UnZip
{
private:
	DeCode decode_;
public:
	UnQZip(const string& src_file);
	void UnQZipFile(const string& dst_path);
};
